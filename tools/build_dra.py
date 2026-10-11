#!/usr/bin/env python3
"""Build and verify the Digimon Rumble Arena units (SLUS-01404 + overlays).

Relink the committed splat split byte-identically to retail.  Two kinds of
translation unit:

  * asm data/rodata/header (asm/us/<unit>/**/*.s outside nonmatchings/) ->
    assembled straight with mips-linux-gnu-as.
  * C source (src/<unit>/**/*.c) -> preprocess (mingw gcc -E) -> PSY-Q cc1 ->
    maspsx -> mips-linux-gnu-as.  A c file's INCLUDE_ASM stubs pull the
    per-function nonmatchings .s in through the assembler, so nonmatchings/ is
    never assembled on its own.

Then link with the splat linker script plus the auto symbol lists, objcopy to a
raw image, and SHA-1 the result against the retail file.

14 units: main (dumps/disc/SLUS_014.04, load 0x80010000) and 13 overlays
(game/title/movie at 0x800643C0, st00..st09 at 0x800D3B00) extracted to
assets/us/bin/<unit>.bin.

Usage:
    python tools/build_dra.py                 # build + verify every unit
    python tools/build_dra.py --unit main     # just one unit
    python tools/build_dra.py --objects-only  # no link/objcopy/verify
"""
from project_layout import source_dir
import argparse
import hashlib
import json
import os
import platform
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

BUILD = "build/us"

# Per-unit config.  `target` is the retail file, `sha1` its SHA-1 (also in
# config/us/<unit>.yaml), `ld` the splat linker script, `vram` the load
# address, `file_base` the file offset the load address maps to (main's image
# has a 0x800 PS-X EXE header before the loaded image; overlays are raw).
CONFIG = {
    "main": dict(
        target="disks/us/SLUS_014.04",
        sha1="179a3f7ae84762f9f60dc1ba97994eb7e673582e",
        ld="config/us/linkers/main.ld",
        vram=0x80010000, file_base=0x800,
        elf=BUILD + "/main.elf", out=BUILD + "/out/SLUS_014.04",
        # Retail main expands `div`/`divu` with the aspsx divide guard
        # (`bnez a0 / break 7 / ... / break 6 / mflo a0`); only main uses it
        # (8 split files contain `break 7`, no other unit does) and no matched
        # C file contains a division, so the flag cannot regress a match.
        maspsx_extra=["--expand-div"],
    ),
    "game": dict(
        target="assets/us/bin/game.bin",
        sha1="655cdf891af2caf44ae883eb952f8a60349947ec",
        ld="config/us/linkers/game.ld",
        vram=0x800643C0, file_base=0x0,
        elf=BUILD + "/game.elf", out=BUILD + "/out/game.bin",
    ),
    "title": dict(
        target="assets/us/bin/title.bin",
        sha1="bab9b6b1d1ef72c07f2f31c6228715b9d69d5e55",
        ld="config/us/linkers/title.ld",
        vram=0x800643C0, file_base=0x0,
        elf=BUILD + "/title.elf", out=BUILD + "/out/title.bin",
    ),
    "movie": dict(
        target="assets/us/bin/movie.bin",
        sha1="93fba61cdd820b4b889e747360b8888dd47b12f5",
        ld="config/us/linkers/movie.ld",
        vram=0x800643C0, file_base=0x0,
        elf=BUILD + "/movie.elf", out=BUILD + "/out/movie.bin",
    ),
}
for _i in range(10):
    _u = "st%02d" % _i
    CONFIG[_u] = dict(
        target="assets/us/bin/%s.bin" % _u,
        sha1=open(os.path.join(ROOT, "config/us/%s.yaml" % _u)).read().split("sha1:")[1].split()[0]
        if os.path.exists(os.path.join(ROOT, "config/us/%s.yaml" % _u)) else None,
        ld="config/us/linkers/%s.ld" % _u,
        vram=0x800D3B00, file_base=0x0,
        elf=BUILD + "/%s.elf" % _u, out=BUILD + "/out/%s.bin" % _u,
    )
UNITS = ["main", "game", "title", "movie"] + ["st%02d" % i for i in range(10)]

# Flags for hand-written asm TUs (data/rodata/header).  Already final machine
# asm; -O0 keeps as from reordering.
# -march=mips2 (not r3000): the retail code contains COP2 LDC2/SDC2 (opcode
# 0x36), which aspsx accepted but GNU as gates behind ISA >= MIPS II.  The
# encoding is identical, so this does not change the emitted bytes.
AS_FLAGS = ["-EL", "-march=mips2", "-mtune=mips2", "-no-pad-sections", "-O0", "-G0"]

# Flags for the C pipeline: cpp -> cc1 -> maspsx -> as.  INCLUDE_ASM stubs stay
# (no -DSKIP_ASM) so the nonmatchings asm is pulled into the object.
CPP_FLAGS = ["-E", "-P", "-undef", "-nostdinc", "-D_LANGUAGE_C", "-DVER_USA",
             "-I", "include", "-I", BUILD]
CC1_FLAGS = ["-O2", "-mips1", "-mcpu=3000", "-w",
             "-funsigned-char", "-fpeephole", "-ffunction-cse",
             "-fpcc-struct-return", "-fcommon",
             "-msoft-float", "-mgas", "-fgnu-linker",
             "-gcoff", "-G0", "-quiet"]
# The imported build uses these default compiler/assembler candidates, with
# verified slot overrides below. A matching mixed C/assembly unit does not
# establish one original compiler version or complete recovered source.
MASPSX_FLAGS = ["--aspsx-version=2.77", "--run-assembler"]
MASPSX_AS_FLAGS = ["-EL", "-march=mips2", "-mtune=mips2",
                   "-no-pad-sections", "-G0", "-I", "include"]

# Per-file flag overrides, DW2-style: keyed `unit/name.c` (wins over the
# per-unit CONFIG entry).  A unit is one C file per content slot, and retail's
# scheduling/delay-slot choices vary per slot, so this is the right granularity
# for slot-local differences.
UNIT_G = {           # `unit/name.c` -> -G value
    # Whole-slot paired zlib storage reproduction; original object provenance open.
    "main/2B800.c": 8,
    "main/2E000.c": 8,
    # Font getter and17 old siblings: whole-slot reproduction, provenance open.
    "main/22000.c": 8,
    # Compression-tag address is GP-relative; later global-pointer helpers
    # remain in their separately verified -G0 range.
    "main/18058.c": 8,
    "main/18804.c": 8,
    # Resident counter helpers use startup's gp base, not absolute addressing.
    # External small-data classification is supplied by UNIT_SDATA below.
    "main/F800.c": 8,
    "main/10004.c": 8,
    # Typed VFS mount: 4.6 plus bare-symbol addressing also matches the
    # indirect error callback; the archive globals remain absolute references.
    "main/23800.c": 8,
    "main/27810.c": 8,
    "main/1B000.c": 8,
    # func_8005D7CC stores a small global with `lui $at; sw $zero,%lo(D_800628BC)($at)`
    # (small-data addressing) — shipped -G0 emits `lui $v0` + an extra move (0x60 vs 0x5C).
    # Proven with tools/toolchain_probe.py main --file 4D850.c --g 8.
    "main/43800.c": 8,
    # 37200's SetIntrMask (func_80046AD8) and 56220's _chk_card_event pair
    # (func_80065CB4/65CF0) are the PSY-Q small-data bare-symbol form too:
    # -G0 picks a separate address register (`lui $v0`/`$v1`) and hoists every
    # `lui` above its `lw`, while -G8 makes the assembler expand `lw/lhu $r,sym`
    # with $r as base (retail `lui $v1; lw $v1,%lo`) and keeps each `lui` next to
    # its load (56220's interleaved schedule).  Verified on the unmasked image.
    "main/30000.c": 8,
    # (removed: dead UNIT_G key main/4B000.c)
    # 3A138 (libcd): CD_vol/CD_initvol need the same small-data bare-symbol form
    # (`lui $v1`/`$at` instead of a separate address register).
    "main/32948.c": 8,
    # -G8 small-data family (MigrateFinish reconnaissance): 99 stubs open with
    # `lui $r,%hi(D_x); <load> $r,%lo(D_x)($r)`; these are the densest shipped-cc1
    # slots. Gate-verified as a batch; bodies land per slot.
    "main/10800.c": 8,
    "main/17000.c": 8,
    "main/17804.c": 8,
    # Typed allocator wrappers use absolute address loads; -G0 retains the
    # retail base register while all eight earlier helpers remain exact.
    "main/1B800.c": 0,
    "main/20000.c": 8,
    "main/24800.c": 8,
    "main/25000.c": 8,
    "main/25800.c": 8,
    "main/29800.c": 0,
    "main/4C800.c": 8,
    "main/4AFDC.c": 8,
    # maspsx $at-store family (St04Subdiv): default-cc1 slots whose setters need
    # -G8 so cc1 emits the bare symbolic store the new maspsx delay-slot fill places.
    "main/30800.c": 8,
    "main/312CC.c": 8,
    "main/4E800.c": 8,
    # main/33000 keeps its 2.7.2 cc1 (shipped+-G8 would regress func_80042D2C);
    # -G8 lands func_80042B34 and leaves func_80042D4C for a future subdivision.
    "main/33000.c": 8,
    # 33000 three-way split (RecarveB): `func_80042D4C` needs shipped+-G8, the
    # remaining tail returns to 2.7.2; both halves keep -G8.
    "main/3354C.c": 8,
    "main/3356C.c": 8,
 # CD_init sub-unit (MainLayout, §9 carve): 2.7.2 + -G8 for both succ/pred variants.
 "main/32FEC.c": 8,
 # startIntrDMA sub-unit (succ variant).
 "main/307BC.c": 8,
 # SpuMalloc sub-unit.
 "main/4378C.c": 8,
 # _padChkRC2wait sub-unit.
 "main/4E478.c": 8,
 # 4A67C -G8 key removed: it changed neighbor func_8005A444's bytes (gate red).

 # $at setter slot (P4A_34800, actual slot 347CC): baseline==with-G==final, 0 regressions.
 "main/347CC.c": 8,
 # $at setter slot (P4A_3F800): with-G whole-slot 0 bad, 0 regressions.
 "main/3F7CC.c": 8,
 # $at setter slot (P4A_35800): with-G 12/0; 4570C blocked by $Le label (tool item).
 "main/35800.c": 8,
 # $at setter slot (P4B_5383C): delay-slot fill proven in the dump; 0 regressions.
 "main/43FDC.c": 8,
}
UNIT_SDATA = {
    # Native cc1 describes this external as .extern symbol,4. maspsx cannot
    # infer its small-data placement from that declaration alone. This is
    # non-emitting symbol metadata; the only definition remains in main data.
    "main/F800.c": {"D_800641A8": 4},
    "main/10004.c": {"D_800641A4": 4},
    "main/1B000.c": {"D_80064314": 4},
    "main/18058.c": {"D_800641D4": 4},
    "main/18804.c": {"D_800641D4": 4},
    "main/17000.c": {
        "D_800641B0": 4, "D_800641B4": 4, "D_800641B8": 4,
        "D_800641BC": 4, "D_800641C0": 4, "D_800641C4": 8,
        "D_800641CC": 8,
    },
}
UNIT_CC1 = {         # `unit/name.c` -> extra cc1 flags
    # Original zlib cleanup includes an optimized inline block reset.
    "main/2C800.c": ["-O3"],
    # Retail never strength-reduced these loops (it keeps `sll a0,s2,4; addu`
    # with immediate offsets per iteration); egcs (wired for st04/2A4) does.
    # Regression-free (65/65) but only size-aligns the two functions found so
    # far; exactness splits psyq4.0+nosr / shipped+nosr, so the slot looks
    # mixed-revision -> subdivide after the main migration.
    "st04/2A4.c": ["-fno-strength-reduce"],
    # st04 2A4 subdivision (St04Subdiv): per-sub-range nosr + compiler.
    "st04/5864.c": ["-fno-strength-reduce"],
    "st04/59B0.c": ["-fno-strength-reduce"],
    "st04/67EC.c": ["-fno-strength-reduce"],
    "st04/6948.c": ["-fno-strength-reduce"],
}
UNIT_MASPSX = {      # `unit/name.c` -> extra maspsx flags
    # Retail's `rem`/`div` on these slots carries the **zero-division guard only**
    # (`div; mfhi; bnez; nop; break 0x0,0x7`).  maspsx's default emits no guard and
    # `--expand-div` emits zero+overflow, so each file opts into the zero-only mode
    # (which wins when both are passed — `external/maspsx-expand-div-zero-only.patch`).
    # List = DivGuard's scan of the 46 retail functions containing `break 0x0,0x7`.
    # main (its unit-level --expand-div must not leak in):
    "main/11800.c": ["--expand-div-zero-only"],
    "main/12000.c": ["--expand-div-zero-only"],
    "main/16000.c": ["--expand-div-zero-only"],
    "main/17000.c": ["--expand-div-zero-only"],
    "main/17804.c": ["--expand-div-zero-only"],
    "main/18058.c": ["--expand-div-zero-only"],
    "main/1D800.c": ["--expand-div-zero-only"],
    "main/21000.c": ["--expand-div-zero-only"],
    "main/26000.c": ["--expand-div-zero-only"],
    "main/D800.c": ["--expand-div-zero-only"],
    # game:
    "game/12398.c": ["--expand-div-zero-only"],
    "game/1C120.c": ["--expand-div-zero-only"],
    "game/40E5C.c": ["--expand-div-zero-only"],
    "game/55164.c": ["--expand-div-zero-only"],
    "game/5922C.c": ["--expand-div-zero-only"],
    "game/5D3CC.c": ["--expand-div-zero-only"],
    "game/6155C.c": ["--expand-div-zero-only"],
    "game/6568C.c": ["--expand-div-zero-only"],
    "game/697BC.c": ["--expand-div-zero-only"],
    "game/9DF4.c": ["--expand-div-zero-only"],
    # Other units with zero-only guards (docs/PER_SLOT_TOOLCHAIN.md table):
    "movie/B4.c": ["--expand-div-zero-only"],
    "title/12AF0.c": ["--expand-div-zero-only"],
    "title/2570.c": ["--expand-div-zero-only"],
    "title/E6AC.c": ["--expand-div-zero-only"],
    "st01/59C.c": ["--expand-div-zero-only"],
    "st01/185C.c": ["--expand-div-zero-only"],
    "st01/1928.c": ["--expand-div-zero-only"],
    "st02/944.c": ["--expand-div-zero-only"],
    "st03/5F8.c": ["--expand-div-zero-only"],
    "st05/4CC.c": ["--expand-div-zero-only"],
    "st05/2A5C.c": ["--expand-div-zero-only"],
    "st05/2D64.c": ["--expand-div-zero-only"],
    "st08/EC.c": ["--expand-div-zero-only"],
}
UNIT_MASPSX_VER = {
    # Whole-slot paired zlib storage reproduction; original object provenance open.
    "main/2B800.c": "2.80",
    "main/2E000.c": "2.80",
    # Natural primitive swap and42 old siblings: coherent reproduction, provenance open.
    "main/17000.c": "2.80",
    # Whole-slot JP RNG/static-data reproduction; original TU unknown.
    "main/27810.c": "2.80",
    # These ranges require GP-relative `la` for the held ZP00 tag.
    "main/18058.c": "2.86",
    "main/18804.c": "2.86",
}
UNIT_MASPSX_AS = {}  # `unit/name.c` -> extra maspsx as flags
UNIT_CC1_EXE = {
    # Whole-slot zlib initializer reproduction; original object provenance open.
    "main/2B034.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Whole-slot zlib dynamic-tree reproduction; original object provenance open.
    "main/2D800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # CD finish dispatcher and four siblings: uniform reproduction; provenance open.
    "main/24800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Sprite cleanup and eight siblings: uniform reproduction; provenance open.
    "main/1E000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # VFS directory search and comparator: whole-slot reproduction, provenance open.
    "main/24000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # CD completion pair and five old siblings reproduce whole slot; provenance open.
    "main/25000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Coherent heap wrappers and thirteen old siblings reproduce whole slot; provenance open.
    "main/1B800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Coherent plane leaves plus old siblings reproduce whole slot; provenance open.
    "main/11800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Character loop getters and seven siblings reproduce whole slot; provenance open.
    "main/21800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Eleven complete TMD bounds frames reproduce whole slot; provenance open.
    "main/13000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Console clear/color and six siblings reproduce whole slot; provenance open.
    "main/1B000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Whole-slot quaternion helpers reproduce retail; original provenance open.
    "main/15800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Whole-slot box helpers and siblings reproduce retail; provenance open.
    "main/23000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # JP button setter and ten old siblings preserve the whole F000 slot;
    # this reproduction setting does not certify original-object provenance.
    "main/F000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # JP camera getter family and all five siblings preserve full slot bytes;
    # original object boundaries/compiler provenance remain unreviewed.
    "main/12000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Six JP math bodies preserve both complete slots and runtime relocations;
    # sector slots remain unproven original translation units.
    "main/14000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/15000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Eight JP vector helpers and all 22 old siblings preserve complete slot
    # bytes and runtime relocs; original translation-unit grouping unresolved.
    "main/16800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # JP path-source recovery preserves both old wrappers and all slot bytes;
    # this sector grouping is not certified original-object provenance.
    "main/26800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # JP source hypothesis: natural SEP constructor/destructor and all nine
    # existing siblings reproduce the whole slot; original objects unproven.
    "main/B800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Complete natural dialog loop plus old sibling2/2; no original-object claim.
    "main/D000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Stage01 list initialization isolated between shipped-profile ranges.
    "st01/185C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Controller helpers and the complete initialization state machine.
    "main/17804.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Stage05 constructors between shipped-profile ranges.
    "st05/2A5C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st00 wave4: isolated shipped leaves preserve all earlier matches.
    "st00/354.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st00/47BC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st00/5528.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st00/618C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st07 wave3: ESA45 ranges preserve every old match except the isolated shipped leaf.
    "st07/194.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    "st07/390.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",     # `unit/name.c` -> cc1 executable
    # Heap recovery and adjacent menu helpers: all retained C bodies match
    # in private whole-slot probes; acceptance still requires the full gate.
    "main/2A814.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/29800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/2A074.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/C000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/19800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/D800.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    "main/E800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/1A000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/1A800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Stage09's recovered control wrappers and all seven older source bodies
    # preserve their private matches under this revision.
    "st09/244.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # Complete F79C display clear: 4.6 emits separate zero arguments as retail
    # does; all ten earlier recovered helpers retain exact private matches.
    "main/F800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/23800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Strided flag scans and identified zlib 1.1.3 helpers retain their
    # neighboring matches under this compiler in private whole-slot probes.
    "main/12800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/2B800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/2C800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/27000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/27810.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/17000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Retail's loader clears a3 separately for its second zero argument.
    "main/18058.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/18E84.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Choice constructor and all six existing debug helpers reproduce together;
    # this is whole-slot reproduction evidence, not original-object certification.
    "main/19000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # func_8004B4F4's epilogue is `addiu sp / jr / nop` (deallocate before return);
    # the 2.8.1 cc1psx cannot emit it for any source/flags, the bundled 2.7.2 one does.
    "main/34000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # func_8004D910 came from the per-slot lever sweep (tools/slot_levers.py): 2.7.2
    # cc1 makes its 8 instructions match (same epilogue signature as 3BB80's), with
    # no sibling regression in 3E040.c.  ACTIVE once that function is written in C:
    # the three trailing retail nops that make its region 0xC long are now carved by
    # the generator as a split-owned pad (padseg), so the C becomes region-exact.
    # (The 2026-10-06 re-sweep saw the shipped baseline green only because D910 is
    # still a stub.)
    # (removed: dead key main/36000.c - slot absorbed by sub-unit 35FFC)
    # title/E6AC is the PSY-Q 4.6 (GCC 2.95.2) revision: under the shipped 2.8.1 every
    # nontrivial E6AC function mismatches on scheduler/delay-slot tie-breaks (retail
    # fills the `lw ra` load-delay slot; 2.8.1 emits `nop` + a separate load — e.g.
    # func_80072BF0 built 0x38 vs retail 0x34). Under 4.6 all but 3 of the slot's
    # functions verify. Binary: `bin/cc1_revisions/Psy-Q_46.zip` member
    # `Psy-Q - 46/BIN/CC1PSX.EXE`, extracted to psyq46/CC1PSX.EXE (dumps/ is
    # git-ignored; see README "Toolchain" for the extraction step).
    "title/E6AC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/34AFC: switched from egcs to 4.6 — psyq46 is a strict superset for this
    # slot (the 8 committed egcs matches stay OK under 4.6, and BlkF found
    # func_8009C0C0/9C138 byte-exact ONLY under 4.6).
    "game/34AFC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/5D3CC is also the 4.6 revision (whole-slot win per GameW6_5D3CC): of the
    # 25 candidate C functions, 25 mismatch under shipped, 11 under 4.6, 14 under
    # egcs, 32 under 2.7.2; the 7 pre-existing matches do not regress.
    "game/5D3CC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/1C120 is the 4.6 revision too: flips 12 functions (80A84..81A0C) with zero
    # regressions on the 7 pre-existing matches; egcs regresses those instead.
    "game/1C120.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/6155C is 4.6 as well: 91/96 entries match under it (80 under shipped), no
    # regressions; the 11 vtable-dtor functions flip because retail schedules the
    # vtable `lui/addiu` before the s0 save and only 2.95.2 does that. egcs regresses
    # func_800C91C0/93B8 -> 4.6 is the clean lever.
    "game/6155C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/6568C is 4.6: 30+ functions are byte-exact only under it (isolated
    # single-file compares; shipped mismatches incl. 9A4C/9C6C/9E60/9F14/9FC8/9D44/
    # 9F5C/CA764/CA7B8/CAAB4 and the SlotB/C set CAD88…CC2C4), all 12 pre-matched stay
    # OK (incl. CB7F8); two more needed the non-void-callee lever. egcs breaks matches.
    "game/6568C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # title/A660 is 4.6 as well (whole-slot win): 9/14 candidates OK vs 5/14 shipped
    # (flips func_8006EA20/EC98/71008/71C08, keeps F140/FF00/FF48/71C58/72814);
    # whole-unit probe count rises 314 -> 329.
    "title/A660.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/50FE4 is 4.6 as well: 9 pre-matched stay OK; 7 functions flip to OK
    # (771C 0x54, 65D4 0x4C, 7410 0x44, 76A0 0x7C, 61CC 0x94, 6674 0x124, 939C 0x188)
    # plus the 5-function 0x54 destructor family sharing 771C's shape; 8194/7770
    # remain a v0-vs-v1 allocator tie.
    "game/50FE4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/E324 is 4.6 and reaches an ENTIRE-slot match: 0 mismatches across all 161
    # symbols (28 pre-existing C + 31 new C), no regressions vs shipped; 12 of the new
    # functions mismatch under the shipped cc1 (register-tie/scheduler only).
    "game/E324.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # title/12AF0 is the egcs-1.1.2 revision: func_800792EC/A3BC/A41C go byte-exact
    # under it with no regressions (all 12AF0 functions OK under egcs).
    "title/12AF0.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # title/65A4 is 4.6: 11 reverted functions flip to OK (ACA4, AE7C, B028, B834,
    # B860, B880, CE08, D97C, E7AC, E830, E86C) with no regression on the 12 earlier
    # matches; the whole slot has 0 mismatches under 4.6.
    "title/65A4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/4CF7C is the egcs-1.1.2 revision: 15 functions are byte-exact only under it
    # (4.6 gets 14/15 — loses func_800B1788; 2.7.2 and shipped lose all 15), 0
    # regressions, and all 54 slot entries verify under egcs.
    "game/4CF7C.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # st04 (2A4.c) is the egcs revision: the cc1 panel goes 0/23 OK under shipped ->
    # 9/23 under egcs (flips D4080, D4184, D439C, D63B4, D6948, D6E30, D7724, D7D30,
    # D8394); toolchain_probe shows the unit 65/65 OK under egcs with no regressions.
    "st04/2A4.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # title/2570 was subdivided 2026-10-06: this file now covers [0x2570,0x3FC4),
    # where the 0x80067A30..0x800682F0 range (67A30/67EA4/67EFC/682F0) flips to OK
    # only under 4.6.  func_80068384 is shipped-ONLY and lives in title/3FC4.c;
    # title/40C4.c carries the 4.6 tail (see docs/CC1_REVISIONS.md § Sub-range
    # boundaries).
    "title/2570.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # title/3FC4 (0x3FC4..0x40C4) is shipped: func_80068384 is byte-exact only
    # under the shipped 2.8.1 cc1, while its neighbours need 4.6.  40C4 (the rest
    # of the old 2570 slot) is 4.6 again — its functions only verify under 2.95.2.
    "title/40C4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/12398 is 4.6: 134/134 entries OK under it (74 C-matched) vs 118/134
    # (58 matched) under shipped; +16 flips incl. 7695C/769C0/76D18/7789C/7798C/79580
    # /79E4C/7A328/7A358; no regressions.
    "game/12398.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st08 (EC.c) is 4.6: default cc1 = 16/19 (func_800D3EB8 +0x4 instruction order,
    # 4294 +0x20, 4A84 +0x8), 4.6 = 19/19, st08.bin OK. (An earlier audit called this
    # entry redundant on a --file+--cc1 reading that was shadowed by the entry itself;
    # the default-vs-forced comparison above, with the entry removed, is the truth.)
    "st08/EC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st06/3F0 is a mixed-revision slot split into three sub-units: the middle
    # range `st06/1FA4.c` (0x1FA4..0x22F4) is the psyq 4.6 revision — func_800D5AA4
    # and func_800D5BB8 are byte-exact only under 2.95.2 (shipped 2.8.1 mismatches
    # both on scheduler/delay-slot ties); the outer `3F0.c`/`22F4.c` stay shipped
    # because 4.6 regresses the five shipped-clean functions (func_800D3EF0, 47A4,
    # 506C, 549C, 5DF4; the last two shipped-only via register pinning).
    # Evidence: isolated compares scratch/subdiv/cmp.py + tools/check_unit.py st06.
    "st06/1FA4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st06/C48.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st06/1820.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "st06/1D5C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st02 (944.c) is 4.6: func_800D4444 is exact only under it (+0x10 reg-save order
    # on the others); probe shows 76/76 OK with no regressions among the 21 matches.
    "st02/944.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st03 (5F8.c) is 4.6: probe shows 92/92 with no regression on the 24 matches;
    # 2.7.2 drops to 74/92 and egcs to 87/92 (regresses func_800D908C/90D4/911C).
    "st03/5F8.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/16458 is 4.6 (real lever, not a sweep artifact — the earlier "artifact"
    # verdict came from re-checking a tree where the C had already been reverted to
    # stubs). Isolated whole-file compare: psyq46 74/74, shipped 50/74, egcs 67/74.
    # Micro-proof: func_8007BCA0 emits `addu a3,a2,zero` under shipped/egcs, retail
    # has `addu a3,zero,zero`, which only 4.6 produces.
    "game/16458.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/242D0 is 4.6: func_80033C10/C34/C58 are exact only under it (shipped emits
    # `lw $5,8($5)` — reusing a1 — where retail has `lw $6,8($5)`); the earlier cc272
    # sweep row was an artifact, but this lever is real (isolated per-file compare:
    # all 12 slot entries OK under 4.6 vs 9/12 under shipped).
    "main/1F800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Uniform graphics-slot reproduction profile: four natural packet allocators
    # share the same shipped scheduling mismatch and match PsyQ 4.6 -G8.
    # Neighbor 1F800's six existing source bodies also match with 4.6 -G8.
    # This is whole-slot byte evidence; original-object provenance is unreviewed.
    "main/20000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # (main/E5B0 and game/16458 were pre-wired from BuildPipeline's sweep3; E5B0's row
    #  was a whole-slot artifact (33/33 under shipped) and stays unwired. main/242D0's
    #  *cc272* row was an artifact, but it has a real 4.6 lever (above); game/16458's
    #  row was a real 4.6 lever too (above). Agents may still request a revision with
    #  isolated evidence.)
    # The Psy-Q library block (file offset >= 0x3542C / vram >= 0x80044C2C) is
    # **cygnus 2.7.2-built**: LibSpuSnd's 20 matches verify only under it (retail's
    # `lw ra; addiu sp; jr; nop` epilogue and v0-return regalloc), and LibCdPad's 14
    # verify under 2.8.1 *and* 2.7.2. psyq46 does NOT reproduce this block.
    # Exception: `50F70` (libgpu GetODE/SetDrawArea/SetDrawOffset) is shipped-only.
    "main/30000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/39800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/3C000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/3C800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/3F800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/40000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/40800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # (removed: dead key main/44000.c - slot absorbed by sub-unit 43FDC)
    "main/33000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # 3F2A0 (libds tail): DS_sync / DsDataCallback match under 2.7.2 g272 *and*
    # psyq4.0 (2.7.2.SN32.3.7.0002); the callback setters func_8004F03C/4F05C
    # reproduce only under psyq4.0, so the whole slot is wired to psyq4.0.  The
    # already-matched func_8004EBAC/4ECCC stay OK under it.
    "main/37000.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    # 54FC0 (libmcrd): MemCardCallback's address materialisation (single `lui`
    # base register for lw+sw) reproduces only under psyq4.0; no sibling is
    # converted yet.
    "main/4A000.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    # 57480 (libpad): func_80067418 byte-matches only under 2.7.2 (shipped emits
    # the byte stores in the wrong order); no sibling is converted yet.
    "main/4C000.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # 46A10 (libsnd): SsSepStop's sign-extend pair reproduces only under 2.7.2
    # (shipped/2.7.2-win/2.95.2 differ in the sll/sra placement); no sibling is
    # converted yet.
    "main/3D800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # (removed: dead key main/4A800.c - slot absorbed by sub-unit 4A67C)
    # (removed: dead key main/4B000.c - slot absorbed by sub-unit 4AFDC)
    "main/4D800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/4E800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # The libc/libds part of the range (`34D40`, `35670`, `3C4B0`, `3D710`, `3E970`) is
    # 2.7.2-built too (psyq46 matches none of its shapes).  Three individual libds
    # functions additionally need psyq4.0 — i.e. the slots are mixed at sub-range
    # level; see docs/LIBRARY_INVENTORY.md sections 6/7 and the open follow-up there.
    # Uniform source reproduction for zlib flush and two siblings; original
    # mixed libc/object provenance remains open; SDK functions remain ASM.
    "main/2E000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # (removed: dead key main/2E800.c - slot absorbed by sub-unit 2E79C)
    "main/34800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/35800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/36800.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # Mixed-revision sub-ranges of the three libds slots, split at the psyq 4.0
    # function (config/us/SLUS_014.04.yaml 0x3C8A8/0x3DEEC/0x3ECB4):
    # func_8004C0A8 / func_8004D6EC / func_8004E4B4 are byte-exact only under
    # 2.7.2.SN32.3.7.0002 — the bundled 2.7.2-win cc1 that builds the rest of
    # each slot emits them 4-8 bytes off — and no sibling in the sub-range
    # regresses.  Evidence: isolated compares (scratch/cand_ds.c) + check_unit main.
    "main/34BF8.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    "main/35FDC.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    "main/36B44.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    # The carved libgpu slots (`4FE1C`, `50470`, `53490`) are the 2.7.2-era build:
    # the SDK's own `LIBGPU.LIB` bytes (incl. `_GPU_ResetCallback`) reproduce under
    # `psyq4.0` (2.7.2.SN32.3.7.0002) — 7/7 on `53490` vs 6/7 for shipped/2.7.2-win —
    # so the shipped default was leaving their bodies 4 bytes short.
    # Equivalent 2.7.2-era builds: foxdie43 / rl40win (sha 06329afef726).
    "main/4590C.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    "main/45F60.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    "main/48860.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
    # game/9DF4 is 2.95.2-built (the div-guard function func_80070F2C is exact only
    # under it with natural source; all 82 of the slot's C functions re-verify under
    # gcc295 vs 1 failure under shipped).  Found by the BreakGame wave (stub-blind).
    "game/9DF4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/25E60 and main/2BA40 are 2.95.2-built too (found by BreakMain, stub-blind):
    # func_80035870 is 184/184 under psyq46 vs 95/172 bytes differing under shipped;
    # func_8003B4BC also needs psyq46's `lui` form.
    # Whole current20800 slot: four natural header accessors and all old siblings
    # match PsyQ46 or ESA45; reproduction choice only, not original-object proof.
    # Evidence: analysis/us/main/wave61_task_accessors_parent_contract_audit.json
    "main/20800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/21000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # Uniform current22000 slot:16/16 C bodies; reproduction evidence only.
    # See analysis/us/main/wave65_task_pair_parent_contract_audit.json
    "main/22000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/26000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/2E830 (game-side MD5 block, vram 0x8003E030..0x8003E960) is 2.95.2-built:
    # func_8003E5E8's `move a3,zero` guard-hoist is emitted only by 2.95/egcs (shipped
    # 2.8.1 emits the `beqz` first), while its siblings (func_8003E3E4/E40C/E618/E640)
    # also verify under psyq46.  Evidence: scratch/isolated_cc1.py + check_unit main.
    "main/28800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/2F160 (game-side list/table helpers): func_8003ECB8/ECD8's `lui v0; lw v1`
    # global-pointer load is the 2.95 shape (shipped 2.8.1 emits `lui v1`); the slot's
    # other converted functions (func_8003E960/EA9C) verify under psyq46 as well.
    "main/29000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/2FA90 (game-side memory-card/file helpers): func_8003F5E4's sign-extend
    # (`sll a0,16` before the guard, `sra` in the branch delay slot) is the 2.95
    # shape; shipped 2.8.1 emits it in the other order.
    "main/26000.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # main/21E10 is 2.95.2-built too (found by BreakMain, stub-blind): func_80031BC0
    # (break 0,7 guard) is 156/156 under psyq46 vs 61/156 bytes differing under
    # shipped; func_80031A10 lives in the same slot and runs under it too.
    "main/1D800.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/40E5C, game/55164, game/5922C are 2.95.2-built (GameRecover: each slot's
    # staged function is +1 function with zero unit regressions under psyq46; a
    # blanket psyq46 or egcs override elsewhere in game would regress 3/14 functions).
    "game/40E5C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "game/55164.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "game/5922C.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/697BC is egcs-4.5-built (func_800D0548 exact only under it; whole-unit
    # 1804/1804 verified with it in place).
    "game/697BC.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # game/2C7C4, 309F0, 38D84, 3CDF0 are 2.95.2-built too (GameWF2: once the real
    # source shapes are in place, every function in them is 0-bad under psyq46 while
    # shipped 2.8.1 mismatches on symbol-address materialisation order; whole-unit
    # verified zero regressions. The earlier "shipped-only" slot sweep predates
    # those conversions and only ever measured the then-existing C).
    "game/2C7C4.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "game/309F0.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "game/38D84.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "game/3CDF0.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/44E78 is 2.95.2-built (GameWF3 revisited: isolated slot compile shows
    # psyq46 58/58, egcs 1 bad (func_800AAD3C 3-word register tie), shipped 11 bad.
    # An earlier egcs recommendation was retracted — its "egcs-only" function was a
    # probe artifact of a redundant local in the candidate source.) func_800AA304 is
    # a genuine per-function exception (shipped-only, 4 pins) and stays a stub.
    "game/44E78.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # game/6DB60 is 2.95.2-built for its ctor/dtor cluster (GameWF4 whole-slot net:
    # psyyq46 = 0 regressions to the 9 converted functions, +6 cluster exact once
    # `extern s32 func_8002BC9C(s32, s32);` corrects the callee's return type - the
    # same declaration 6155C's stack-arg quartet needed, so it is source-shape).
    "game/6DB60.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    # st04 2A4 subdivision (St04Subdiv): 59B0/6948 are egcs-4.5; 67EC stays on
    # shipped+nosr (no entry); 5864 also builds under shipped+nosr (confirmed
    # size-exact 0x14C), so no psyq4.0 entry is needed.
    "st04/59B0.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    "st04/6948.c": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
    # main subdivision rows (MigrateFinish PENDING KEYS): each new sub-unit takes
    # the successor half's cc1 (2.7.2 in all eight cases).
    "main/2E79C.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/347CC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/35FFC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/3F7CC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/43FDC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    # 33000 split tail half (3354C runs shipped with -G8; see UNIT_G).
    "main/3356C.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
 # CD_init sub-unit (MainLayout, §9 carve).
 "main/32FEC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
 # §9 carve retries (MainLayout): DsCommand sub-unit and _padSioRW2 sub-unit.
 "main/33F00.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
 "main/4D7CC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
 # MemCardWriteFile sub-unit (psyq4.0 per the carve's pending-key report).
 "main/49FD4.c": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
 # DsSearchFile sub-unit (created by its carve) and _padChkRC2wait sub-unit.
 # StartCARD slot (P4_LibD): shipped cc1 exact for both rows (2.7.2/psyq4.0 2-word off), -G8 retained.
 "main/4E478.c": "bin/windows/gcc-psx/CC1PSX.EXE",
 # DsEndReadySystem slot (P4_LibB): shipped cc1 exact (2.7.2/psyq4.0/psyq46 all worse).
 "main/360FC.c": "bin/windows/gcc-psx/CC1PSX.EXE",
 # §9 carve retry (MainLayout): startIntrDMA sub-unit (pred variant needs both keys).
 "main/307BC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
 # 43FDC: psyq46 exchanges the 2-word wrapper order AND keeps func_8005389C at 0xA4 (2.7.2 emits 0xA8 -> +4 shift).
 "main/43FDC.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
 # 18800: psyq46 G0 whole-slot 25/0 vs shipped 25/4 + TEXT short (P4_GS_E evidence).
 "main/18804.c": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
    "main/4A67C.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/4AFDC.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    "main/4BF5C.c": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
}
# Game-side slots can opt into the PSY-Q 4.6 C++ frontend.  The source stays
# `.c` so it occupies the existing splat/linker slot; exported C helpers in a
# mixed C/C++ slot retain C linkage in the source.
UNIT_CXX = {
    "main/1C000.c": True,
    "main/10004.c": True,  # CxxWave_M3: g++ virtual-call rows; 8 converted (16/0 whole slot).
    "main/1D000.c": True,  # CxxWave_M1: vptr+0x14 virtual calls; 2CD24 C++ exact.
    "game/202B4.c": True,  # CxxWave_G1: virtual shapes; GO under verify-after-wire (23 existing C rows).
    "main/1C800.c": True,  # CxxWave_M2: virtual-dtor dispatch; GO under verify-after-wire (3 existing C rows).
    "st04/67EC.c": True,   # CxxWave_S1: derived-ctor (vptr+0x14) row; slot fully unconverted (1/1 stub).
    "main/1D800.c": True,  # CxxWave_G2: virtual-dtor dispatch (D108); verify-after-wire (7 existing C bodies).
    "main/11000.c": True,  # Cxx2_M1: verify-after-wire (2 existing C bodies).
    "game/243F0.c": True,  # Cxx2_G1: ctor/virtual hunt; verify-after-wire (12 existing C bodies).
    "game/697BC.c": True,  # Cxx2_G2: pinned-ctor migration experiment; verify-after-wire (18 bodies, ≤4 regressions).
    "game/6DB60.c": True,  # Cxx3_G2: verify-after-wire (17 existing bodies).
    "title/E6AC.c": True,  # Cxx3_T1: 4 C++-shaped rows (3 ctor/dtor/delete + 1 vcall); verify-after-wire (1 existing body).
    "game/40E5C.c": True,  # Cxx3_G1: verify-after-wire (21 existing bodies).
    "st02/944.c": True,    # Cxx4_S1: verify-after-wire staged (49 bodies, 11 pins).
    "game/28514.c": True,  # Cxx4_G1: verify-after-wire staged (22 bodies, 30 pins).
    "game/3CDF0.c": True,  # Cxx4_G2: verify-after-wire staged (23 bodies, 4 pins).
    "title/40C4.c": True,  # Cxx4_T1: verify-after-wire staged (26 bodies, 1 pin).
    "main/1E800.c": True,  # Cxx4_M1: verify-after-wire staged (1 body, 0 pins).
}
# C++ ABI aliases live in opted-in sources, so build_dra and slotcheck resolve
# their exported member names identically.




# cc1 emits every switch jump table into the object's single .rodata.  Retail
# sometimes places such a table at a *different* address inside the committed
# rodata slot, and game/6568C's two tables are 0x2C4 bytes apart, so one
# contiguous .rodata cannot reproduce them.  Name each `.rdata` block (in
# order) so the linker script can place it at its retail address.
# `unit/name.c` -> [section name per .rdata block].
UNIT_RODATA_SECTIONS = {
    "main/F800.c": [".rodata.flags_enable", ".rodata.flags_disable"],
    "game/12398.c": [".rodata.79680"],
    "game/6568C.c": [".rodata.a", ".rodata.b"],
    "title/65A4.c": [".rodata.ba9c"],
    "title/A660.c": [".rodata.f7f4"],
}


def append_external_sdata_metadata(text, symbols, limit):
    """Classify proven external small data without defining or emitting it."""
    if not symbols:
        return text
    declarations = dict(re.findall(r"(?m)^\s*\.extern\s+([A-Za-z_][A-Za-z0-9_]*),\s*(\d+)\s*$", text))
    lines = ["", ".sdata"]
    for name, size in sorted(symbols.items()):
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name):
            raise ValueError("Invalid external small-data symbol")
        if not isinstance(size, int) or not 0 < size <= limit:
            raise ValueError("External small data exceeds the compiler -G limit")
        if declarations.get(name) != str(size):
            raise ValueError(f"Missing or inconsistent external size: {name}")
        if re.search(r"(?m)^\s*" + re.escape(name) + r"\s*:", text):
            raise ValueError(f"External small-data symbol is already defined: {name}")
        lines.append(f".size {name},{size}")
    lines.append(".text")
    return text + "\n".join(lines) + "\n"


def unit_toolchain(unit, name=None):
    """(cc1 exe, cc1 flags, maspsx flags, maspsx as flags) for a unit/file.

    Defaults are the module-level flag lists; a CONFIG entry may override them
    with `g` (-G value), `cc1_extra`, `maspsx_version`, `maspsx_extra` and
    `cc1` (executable); UNIT_* dicts keyed `unit/name.c` override per file.
    These are the knobs tools/toolchain_probe.py sweeps."""
    cfg = CONFIG[unit]
    key = "%s/%s" % (unit, name) if name else unit
    cc1_exe = (cxx_cc1_bin() if UNIT_CXX.get(key) else
               UNIT_CC1_EXE.get(key) or cfg.get("cc1") or cc1_bin())
    g = UNIT_G.get(key, cfg.get("g"))
    cc1_extra = list(cfg.get("cc1_extra", [])) + list(UNIT_CC1.get(key, []))
    maspsx_extra = list(cfg.get("maspsx_extra", [])) + list(UNIT_MASPSX.get(key, []))
    as_extra = list(UNIT_MASPSX_AS.get(key, []))
    cc1_flags = list(CC1_FLAGS)
    as_flags = list(MASPSX_AS_FLAGS)
    if g is not None:
        cc1_flags = [("-G%d" % g) if f == "-G0" else f for f in cc1_flags]
        as_flags = [("-G%d" % g) if f == "-G0" else f for f in as_flags]
    cc1_flags += cc1_extra
    maspsx = list(MASPSX_FLAGS)
    ver = cfg.get("maspsx_version")
    if ver is not None:
        maspsx = [f for f in maspsx if not f.startswith("--aspsx-version")]
        maspsx.append("--aspsx-version=" + str(ver))
    maspsx += maspsx_extra
    as_flags += as_extra
    return cc1_exe, cc1_flags, maspsx, as_flags


def binutils_dir():
    env = os.environ.get("DRA_BINUTILS")
    if env:
        return env
    if platform.system() == "Windows":
        return os.path.join(ROOT, "bin", "windows", "binutils")
    if platform.system() == "Darwin":
        return os.path.join(ROOT, "tools", "macos", "binutils")
    return os.path.join(ROOT, "tools", "linux", "binutils")


def tool(name):
    d = binutils_dir()
    exe = os.path.join(d, "mips-linux-gnu-%s.exe" % name)
    if not os.path.exists(exe):
        exe = os.path.join(d, "mips-linux-gnu-%s" % name)
    return exe


def cpp_bin():
    env = os.environ.get("DRA_CPP")
    if env:
        return env
    if platform.system() == "Windows":
        return os.path.join(ROOT, "bin", "windows", "gcc-win", "bin", "gcc.exe")
    return "cpp"


def cc1_bin():
    env = os.environ.get("DRA_CC1")
    if env:
        return env
    if platform.system() == "Windows":
        return os.path.join(ROOT, "bin", "windows", "gcc-psx", "CC1PSX.EXE")
    return os.path.join(ROOT, "tools", "linux", "gcc-2.8.1-psx", "cc1")

def cxx_cpp_bin():
    """Find CPPPSX in the same preference order as tools/cxx_probe.py."""
    candidates = [
        os.path.join(ROOT, "bin", "cc1_revisions", "CPPPSX.EXE"),
        os.path.join(ROOT, "bin", "windows", "gcc-psx", "CPPPSX.EXE"),
        cpp_bin(),
    ]
    return next((path for path in candidates if os.path.isfile(path)), candidates[-1])


def cxx_cc1_bin():
    """The G1-proven g++ 2.95.2 PSY-Q frontend."""
    return os.path.join(ROOT, "bin", "cc1_revisions", "CC1PLPSX.EXE")




def maspsx_py():
    return os.path.join(ROOT, "external", "maspsx", "maspsx.py")


def run(cmd, stdin_devnull=False):
    kwargs = dict(cwd=ROOT, capture_output=True, text=True)
    if stdin_devnull:
        kwargs["stdin"] = subprocess.DEVNULL
    # Cygnus cc1 needs TMPDIR on Windows for -G scratch files. Give each build
    # process its own directory so focused builds of different units cannot
    # collide over the compiler's temporary filenames.
    tmpdir = (BUILD + "/tmp/%d" % os.getpid()).replace("\\", "/")
    os.makedirs(os.path.join(ROOT, tmpdir), exist_ok=True)
    kwargs["env"] = dict(os.environ, TMPDIR=tmpdir)
    r = subprocess.run(cmd, **kwargs)
    if r.returncode != 0:
        sys.stderr.write(" ".join(cmd) + "\n")
        sys.stderr.write(r.stdout)
        sys.stderr.write(r.stderr)
    return r.returncode


def sha1(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 16), b""):
            h.update(block)
    return h.hexdigest()


def obj_for(src):
    """build/us/<relpath of src under ROOT>.o"""
    rel = os.path.relpath(src, ROOT)
    obj = os.path.join(ROOT, BUILD, rel + ".o")
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    return obj


def blank_asm_files(units=None):
    """Relative paths of tracked `.s` files under asm/us/<unit> that carry no
    assembly at all (empty, or only NUL/whitespace bytes).

    Such a stub is not valid `as` input: the assembler skips it without error,
    every symbol it defined disappears, and every later address shifts.  That
    surfaces as a misleading "layout divergence" far away from the real damage
    (a stub overwritten in the working tree is easy to miss when git's stat
    cache is stale), so the build refuses to start on one."""
    asm_root = os.path.join(ROOT, "asm", "us")
    bad = []
    for unit in (units or UNITS):
        root = os.path.join(asm_root, unit)
        if not os.path.isdir(root):
            continue
        for dirpath, _dirs, files in os.walk(root):
            for name in files:
                if not name.endswith(".s"):
                    continue
                src = os.path.join(dirpath, name)
                with open(src, "rb") as f:
                    if not f.read().strip(b"\x00 \t\r\n"):
                        bad.append(os.path.relpath(src, ROOT))
    return bad


def assemble_asm(as_bin, units=None):
    """Assemble every .s under asm/us/<unit> except the per-function
    nonmatchings/ (those are pulled in by the C files' INCLUDE_ASM stubs)."""
    asm_root = os.path.join(ROOT, "asm", "us")
    blank = blank_asm_files(units)
    if blank:
        for path in blank:
            print("BUILD FAILED: %s is blank (lost asm stub)" % path)
        return -1
    count = 0
    for unit in (units or UNITS):
        root = os.path.join(asm_root, unit)
        if not os.path.isdir(root):
            continue
        for dirpath, _dirs, files in os.walk(root):
            if "nonmatchings" in dirpath.replace("\\", "/").split("/"):
                continue
            for name in files:
                if not name.endswith(".s"):
                    continue
                src = os.path.join(dirpath, name)
                obj = obj_for(src)
                cmd = [as_bin] + AS_FLAGS + ["-I", "include", "-o", obj, src]
                if run(cmd) != 0:
                    print("BUILD FAILED: assembling %s" % os.path.relpath(src, ROOT))
                    return -1
                count += 1
    return count


TAIL_SEC_RE = re.compile(r"src/(?:[^/]+/)+(\w+)\.c\.o\(\.text\.tail_(\w+)\)")


def text_tail_splits(unit):
    """{slot: [successor, ...]} the unit's linker script splits its `.text` at.

    tools/gen_splat_config.py gives the `c` subsegment that follows an
    inter-function pad a `.text.tail_<successor>` section when the successor is
    a C definition (no `.s` can carry the pad): the pad is its own `pad` entry
    and the successor's code must be linked after it.  The slot object's `.text`
    is therefore split at that successor when its generated `.s` is assembled."""
    out = {}
    ld = CONFIG[unit].get("ld")
    if not ld:
        return out
    path = os.path.join(ROOT, ld)
    if not os.path.exists(path):
        return out
    with open(path) as f:
        for line in f:
            m = TAIL_SEC_RE.search(line)
            if m:
                out.setdefault(m.group(1), []).append(m.group(2))
    return out


def split_text_sections(text, successors):
    """Split `text` (a slot's generated `.s`) at each successor's definition.

    A `.section .text.tail_<successor>, "ax"` is inserted before the successor,
    so its code lands in a new object section.  The INCLUDE_ASM macro emits a
    `.section .text` before every included stub, so those switches after a split
    are retargeted too (otherwise a later stub would pull the code back into the
    first `.text`).  Successors are handled last-to-first so each rewrite only
    touches the region belonging to its own split.  Returns None if a successor
    is not defined in `text`."""
    for succ in reversed(successors):
        name = re.escape(succ)
        match = re.search(r'(?m)^[ \t]*\.globl[ \t]+' + name
                          + r'[ \t]*(?:#[^\n]*)?$', text)
        if match is None:
            match = re.search(r'(?m)^' + name + r':[ \t]*(?:#[^\n]*)?$', text)
        include = False
        if match is None:
            # The successor can also still be an INCLUDE_ASM stub: its code is
            # pulled in by `.include "<dir>/<succ>.s"` (the macro's own
            # `.section .text` sits just above), so split before that line.
            match = re.search(r'(?m)^[ \t]*\.include[ \t]+"[^"\n]*[/\\]'
                              + name + r'\.s"[ \t]*(?:#[^\n]*)?$', text)
            include = True
        if match is None:
            return None
        section = ".text.tail_%s" % succ
        i = match.start()
        head, tail = text[:i], text[i:]
        # The G8 include wrapper preserves only explicitly marked lines.
        keep = ' # maspsx-keep' if include and 'maspsx-keep' in match.group(0) else ''
        tail = re.sub(r'(?m)^([ \t]*)(?:\.section[ \t]+\.text|\.text)'
                      r'([ \t]*(?:#[^\n]*)?)$',
                      lambda m: m.group(1) + '.section ' + section + ', "ax"' + m.group(2),
                      tail)
        text = head + '\t.section %s, "ax"%s\n' % (section, keep) + tail
    return text


SDK_INCLUDE_RE = re.compile(
    r'INCLUDE_ASM\s*\(\s*"(asm/us/([A-Za-z0-9_]+)/nonmatchings/[A-Za-z0-9_]+)"'
    r'\s*,\s*(func_[0-9A-Fa-f]{8})\s*\)\s*;'
)


def sdk_asm_includes(src, unit):
    """Return ordered SDK stubs only when the complete C file is inert.

    This is intentionally a narrow source grammar. Any definition, alias,
    preprocessor logic, or unknown statement keeps the established C pipeline.
    The SDK list is evidence metadata, not inferred from an address range.
    """
    metadata = os.path.join(ROOT, "config/us/psyq_funcs.txt")
    if not os.path.isfile(metadata):
        return None
    sdk = set()
    with open(metadata, encoding="utf-8") as stream:
        for line in stream:
            fields = line.split()
            if len(fields) == 3 and not fields[0].startswith("#") and fields[2] != "data":
                sdk.add((fields[0], fields[1]))
    with open(src, encoding="utf-8") as stream:
        source = stream.read()
    source = re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S)
    if re.search(r"\b(?:__asm__|__asm|__attribute__)\b|\basm\s*\(", source):
        return None
    # Only these known project headers are inert after the full source has
    # been checked below; an arbitrary header could itself define objects.
    source = re.sub(r'(?m)^\s*#include\s+"(?:common\.h|psx\.h|include_asm\.h)"\s*$', '', source)
    # Extern declarations may describe pointers and function prototypes, but
    # an initializer or assembler alias would affect the object and is denied.
    source = re.sub(r'(?m)^\s*extern\s+[^;{}=\n]+;\s*$', '', source)
    includes = []

    def take(match):
        if match.group(2) != unit or (unit, match.group(3)) not in sdk:
            return match.group(0)
        path = match.group(1) + "/" + match.group(3) + ".s"
        if not os.path.isfile(os.path.join(ROOT, path)):
            return match.group(0)
        includes.append(path)
        return ""

    remainder = SDK_INCLUDE_RE.sub(take, source)
    return includes if includes and not remainder.strip() else None


def sdk_asm_text(includes):
    """Emit the same include context as include/include_asm.h, in source order."""
    lines = ['.include "include/labels.inc"']
    for path in includes:
        lines += [".section .text", ".set noat", ".set noreorder",
                  '.include "%s"' % path, ".set reorder", ".set at"]
    return "\n".join(lines) + "\n"


def compile_c(cpp, cc1, as_bin, units=None, cc1_flags=None, maspsx_flags=None,
              maspsx_as_flags=None, cc1_exe=None):
    """Preprocess + cc1 + maspsx(->as) every .c under src/<unit>/.

    Flags come from unit_toolchain(unit) unless cc1_flags / maspsx_flags /
    maspsx_as_flags / cc1_exe override them (toolchain_probe.py)."""
    src_root = os.path.join(ROOT, "src")
    count = 0
    sdk_bypass = 0
    for unit in (units or UNITS):
        root = os.path.join(ROOT, source_dir(unit))
        if not os.path.isdir(root):
            continue
        # unit-level flags, optionally fully replaced by a probe override
        base = unit_toolchain(unit)
        if cc1_exe is not None:
            base = (cc1_exe,) + base[1:]
        if cc1_flags is not None:
            base = base[:1] + (list(cc1_flags),) + base[2:]
        if maspsx_flags is not None:
            base = base[:2] + (list(maspsx_flags),) + base[3:]
        if maspsx_as_flags is not None:
            base = base[:3] + (list(maspsx_as_flags),)
        splits = text_tail_splits(unit)
        for dirpath, _dirs, files in os.walk(root):
            if unit == "game":
                _dirs[:] = [d for d in _dirs if d != "stages"]
            for name in files:
                if not name.endswith(".c"):
                    continue
                src = os.path.join(dirpath, name)
                obj = obj_for(src)
                stem = obj[:-2]  # drop trailing ".o"
                i_file = stem + ".i"
                s_file = stem + ".s"

                sdk_includes = sdk_asm_includes(src, unit)
                if sdk_includes is not None:
                    text = sdk_asm_text(sdk_includes)
                    successors = splits.get(name[:-2], [])
                    if successors:
                        text = split_text_sections(text, successors)
                        if text is None:
                            print("BUILD FAILED: %s: pad successor not in SDK assembly"
                                  % os.path.relpath(src, ROOT))
                            return -1
                    with open(s_file, "w", newline="\n") as stream:
                        stream.write(text)
                    if run([as_bin] + AS_FLAGS + ["-I", "include", "-o", obj, s_file]) != 0:
                        print("BUILD FAILED: assembling SDK-only %s" % os.path.relpath(src, ROOT))
                        return -1
                    count += 1
                    sdk_bypass += 1
                    continue

                # per-file overrides (`unit/name.c`) on top of the unit flags
                key = "%s/%s" % (unit, name)
                u_cc1, u_cc1_flags, u_maspsx, u_asflags = base
                if key in UNIT_G:
                    gv = UNIT_G[key]
                    u_cc1_flags = [("-G%d" % gv) if re.fullmatch(r"-G\d+", f) else f
                                   for f in u_cc1_flags]
                    u_asflags = [("-G%d" % gv) if re.fullmatch(r"-G\d+", f) else f
                                   for f in u_asflags]
                u_cc1_flags = list(u_cc1_flags) + list(UNIT_CC1.get(key, []))
                is_cxx = bool(UNIT_CXX.get(key))
                u_cc1 = cxx_cc1_bin() if is_cxx else UNIT_CC1_EXE.get(key, u_cc1)
                if key in UNIT_MASPSX_VER:
                    u_maspsx = [f for f in u_maspsx if not f.startswith("--aspsx-version")]
                    u_maspsx = u_maspsx + ["--aspsx-version=" + str(UNIT_MASPSX_VER[key])]
                u_maspsx = u_maspsx + UNIT_MASPSX.get(key, [])
                u_asflags = u_asflags + UNIT_MASPSX_AS.get(key, [])

                # With -G > 0 or PsyQ 4.6 -O3 cc1 hoists file-scope `__asm__` (the INCLUDE_ASM
                # stubs) ahead of every function body, so the slot's C functions
                # would land *after* the asm instead of interleaved.  Wrap each
                # stub in a `__maspsx_include_asm_hack_*` function instead:
                # maspsx keeps only its `# maspsx-keep` include lines, so the
                # asm is re-emitted in source order (include/include_asm.h).
                in_func = (["-DINCLUDE_ASM_IN_FUNC"]
                           if any(re.fullmatch(r"-G[1-9]\d*", f) for f in u_cc1_flags)
                           or "-O3" in u_cc1_flags
                           else [])
                if is_cxx:
                    u_cpp = cxx_cpp_bin()
                    if os.path.basename(u_cpp).upper() == "CPPPSX.EXE":
                        cpp_cmd = [u_cpp, "-I", "include", "-I", BUILD,
                                   "-DVER_USA", "-D__cplusplus"] + in_func + [src, i_file]
                    else:
                        cpp_flags = [flag for flag in CPP_FLAGS
                                     if flag != "-D_LANGUAGE_C"]
                        cpp_cmd = [u_cpp] + cpp_flags + in_func + [
                            "-D__cplusplus", "-o", i_file, src]
                else:
                    cpp_cmd = [cpp] + CPP_FLAGS + in_func + ["-o", i_file, src]
                if run(cpp_cmd) != 0:
                    print("BUILD FAILED: preprocessing %s" % os.path.relpath(src, ROOT))
                    return -1
                if run([u_cc1] + u_cc1_flags + ["-o", s_file, i_file]) != 0:
                    print("BUILD FAILED: cc1 %s" % os.path.relpath(src, ROOT))
                    return -1
                if key in UNIT_SDATA:
                    limit = next((int(f[2:]) for f in u_cc1_flags if re.fullmatch(r"-G\d+", f)), 0)
                    with open(s_file) as stream:
                        text = append_external_sdata_metadata(stream.read(), UNIT_SDATA[key], limit)
                    with open(s_file, "w", newline="\n") as stream:
                        stream.write(text)
                # Name each `.rdata` block so the linker can place a table at
                # its retail address (UNIT_RODATA_SECTIONS, above).
                sects = UNIT_RODATA_SECTIONS.get(key)
                if sects:
                    with open(s_file, "r") as fh:
                        text = fh.read()
                    it = iter(sects)

                    def _sect(_m, it=it):
                        try:
                            name = next(it)
                        except StopIteration:
                            name = ".rodata"
                        return '\t.section %s, "a", @progbits' % name

                    text = re.sub(r"(?m)^[ \t]*\.rdata[ \t]*$", _sect, text)
                    with open(s_file, "w", newline="\n") as fh:
                        fh.write(text)
                # Pads the split owns as `pad` entries sit between two output
                # sections of this slot's object: split `.text` at the successor
                # so the linker can place its code after the pad (see
                # tools/gen_splat_config.py and text_tail_splits).
                successors = splits.get(name[:-2], [])
                if successors:
                    with open(s_file, "r") as fh:
                        text = fh.read()
                    text = split_text_sections(text, successors)
                    if text is None:
                        print("BUILD FAILED: %s: pad successor not in %s"
                              % (os.path.relpath(src, ROOT), s_file))
                        return -1
                    with open(s_file, "w", newline="\n") as fh:
                        fh.write(text)
                # maspsx --run-assembler does not propagate the assembler's
                # exit status, so an as error leaves no object and exits 0.
                # Detect it by requiring the object to exist and be rewritten
                # (do not delete it first: a concurrent link must never see it
                # missing).
                before = os.path.getmtime(obj) if os.path.exists(obj) else None
                cmd = [sys.executable, maspsx_py()] + u_maspsx + [
                    "--gnu-as-path=%s" % as_bin,
                ] + u_asflags + ["-o", obj, s_file]
                if run(cmd, stdin_devnull=True) != 0:
                    print("BUILD FAILED: maspsx/as %s" % os.path.relpath(src, ROOT))
                    return -1
                after = os.path.getmtime(obj) if os.path.exists(obj) else None
                if after is None or after == before:
                    print("BUILD FAILED: assembler rejected %s" % os.path.relpath(s_file, ROOT))
                    return -1
                count += 1
    if sdk_bypass:
        print("SDK assembly-only slots bypassing C compiler: %d" % sdk_bypass)
    return count


def auto_scripts(unit):
    """The splat undefined_{syms,funcs}_auto lists of a unit as PROVIDE()s, so
    names an object defines (asm labels) are not overridden by the retail
    numbers.  Written under build/us and returned as -T argument paths."""
    paths = []
    for kind in ("syms", "funcs"):
        p = "config/us/linkers/undefined_%s_auto.%s.txt" % (kind, unit)
        if not os.path.exists(os.path.join(ROOT, p)):
            continue
        q = os.path.join(BUILD, "undefined_%s_auto.%s.txt" % (kind, unit))
        with open(os.path.join(ROOT, q), "w") as f:
            for line in open(os.path.join(ROOT, p)):
                m = re.match(r"\s*(\w+)\s*=\s*([^;]+);", line)
                if m:
                    f.write("PROVIDE(%s = %s);\n" % (m.group(1), m.group(2).strip()))
        paths.append(q)
    return paths


LBL_RE = re.compile(r"\.L[0-9A-Fa-f]+")
# splat's address-encoded names: func_<vram>, D_<vram>, jtbl_<vram>.
SYM_RE = re.compile(r"\b(?:D|func|jtbl)_[0-9A-Fa-f]{8}\b")


def ld_objects(unit):
    """The objects the unit's splat linker script actually places."""
    objs = set()
    with open(os.path.join(ROOT, CONFIG[unit]["ld"])) as f:
        for line in f:
            m = re.match(r"\s*(build/\S+\.o)\(", line)
            if m and os.path.exists(os.path.join(ROOT, m.group(1))):
                objs.add(m.group(1))
    return sorted(objs)


def defined_symbols(unit):
    """Names the unit's linked objects define globally (objdump -t)."""
    objs = ld_objects(unit)
    if not objs:
        return set()
    out = subprocess.run([tool("objdump"), "-t"] + objs, cwd=ROOT,
                         capture_output=True, text=True).stdout
    names = set()
    for line in out.splitlines():
        if "*UND*" in line or "*ABS*" in line:
            continue
        p = line.split()
        if len(p) >= 5 and p[1].startswith("g") \
                and re.fullmatch(r"[0-9a-fA-F]{8}", p[0]) \
                and re.fullmatch(r"[0-9a-fA-F]{8}", p[-2]):
            names.add(p[-1])
    return names


def symbol_script(unit):
    """Bind splat's undefined address-encoded symbols.

    splat's default names embed the vram (`.L<vram>`, `D_<vram>`,
    `func_<vram>`, `jtbl_<vram>`).  Two gaps make the split unlinkable as-is:

      * a label used across objects (a rodata pointer `.word .L<addr>`, or a
        jump into another function's body) is a `.L` local in the defining
        object, so the reference is undefined;
      * spimdisasm sometimes emits a `D_<addr>` reference where splat later
        names the same address `func_<addr>`, so the two names never meet.

    Each name is given exactly one definition: a name the linked objects
    define globally is left to its object (no PROVIDE emitted, so it can never
    disagree with the object's value); everything else -- including `.L<addr>`
    names, which GNU as strips from the object -- is PROVIDEd to the vram its
    name encodes.  Names already in the auto lists are skipped (they are
    PROVIDEd there)."""
    syms = set()
    root = os.path.join(ROOT, "asm", "us", unit)
    for dirpath, _dirs, files in os.walk(root):
        for name in files:
            if not name.endswith(".s"):
                continue
            with open(os.path.join(dirpath, name), errors="ignore") as f:
                text = f.read()
            syms.update(LBL_RE.findall(text))
            syms.update(SYM_RE.findall(text))
    defined = defined_symbols(unit)
    auto = set()
    for kind in ("syms", "funcs"):
        p = os.path.join(ROOT, "config/us/linkers/undefined_%s_auto.%s.txt" % (kind, unit))
        if os.path.exists(p):
            auto.update(re.findall(r"^\s*(\w+)\s*=", open(p).read(), re.M))
    q = os.path.join(BUILD, "symbols.%s.ld" % unit)
    with open(os.path.join(ROOT, q), "w") as f:
        for n in sorted(syms):
            if n in auto or n in defined:
                continue
            val = n[2:] if n.startswith(".L") else n.split("_", 1)[1]
            f.write("PROVIDE(%s = 0x%s);\n" % (n, val))
    return q


def assemble_bins(unit, ld_bin):
    """The splat `bin` subsegments a linker script names (build/us/assets/*.bin.o).

    The bytes are opaque game content splat wrote to assets/ (not committed).
    For main this is assets/Ram_Reserved.bin; ld -r -b binary wraps it in an
    object whose .data the linker script places."""
    ld_script = os.path.join(ROOT, CONFIG[unit]["ld"])
    for line in open(ld_script).read().split("\n"):
        line = line.strip()
        if not (line.startswith("build/") and ".bin.o(" in line):
            continue
        obj = line[:line.index("(")]
        name = os.path.basename(obj)[:-len(".bin.o")]
        src = os.path.join(ROOT, "assets", name + ".bin")
        if not os.path.exists(src):
            print("BUILD FAILED: %s missing (run splat on the yaml to extract it)"
                  % os.path.relpath(src, ROOT))
            return 1
        os.makedirs(os.path.dirname(os.path.join(ROOT, obj)), exist_ok=True)
        if run([ld_bin, "-EL", "-r", "-b", "binary", src, "-o", os.path.join(ROOT, obj)]) != 0:
            print("BUILD FAILED: wrapping %s" % os.path.relpath(src, ROOT))
            return 1
    return 0


def elf_symbols_quick(elf):
    """{name: (vram, size)} of a linked ELF, for MISMATCH localisation."""
    out = subprocess.run([tool("objdump"), "-t", elf], cwd=ROOT,
                         capture_output=True, text=True).stdout
    syms = {}
    for line in out.splitlines():
        if "*UND*" in line or "*ABS*" in line:
            continue
        p = line.split()
        if len(p) >= 4 and re.fullmatch(r"[0-9a-fA-F]{8}", p[0]) \
                and re.fullmatch(r"[0-9a-fA-F]{8}", p[-2]):
            syms[p[-1]] = (int(p[0], 16), int(p[-2], 16))
    return syms


def diagnose_mismatch(unit):
    """First differing file offset of the built unit vs retail, and the symbol
    (from the linked ELF) whose extent contains that offset's vram."""
    cfg = CONFIG[unit]
    with open(os.path.join(ROOT, cfg["out"]), "rb") as f:
        built = f.read()
    with open(os.path.join(ROOT, cfg["target"]), "rb") as f:
        want = f.read()
    n = min(len(built), len(want))
    off = next((i for i in range(n) if built[i] != want[i]), n)
    vram = cfg["vram"] + off - cfg["file_base"]
    owner = None
    if off < n and os.path.exists(os.path.join(ROOT, cfg["elf"])):
        syms = elf_symbols_quick(os.path.join(ROOT, cfg["elf"]))
        best = None
        below = None
        for name, (a, size) in syms.items():
            if a <= vram and (below is None or a > below[0]):
                below = (a, size, name)
            if size > 0 and a <= vram < a + size \
                    and (best is None or a > best[0]):
                best = (a, size, name)
        owner = (best or below or (None, None, None))[2]
    return off, vram, owner, n, len(built), len(want)


def parse_map_symbols(unit):
    """[(name, vram, object)] from the unit's linker map, in map order.

    The map lists each output section as `build/...o(.sect)` followed by
    `0x<addr> <name>` lines, so tracking the last `build/...o(...)` header
    attributes every symbol to its defining object (its content slot)."""
    path = os.path.join(ROOT, BUILD, unit + ".map")
    if not os.path.exists(path):
        return []
    out = []
    aliases = []
    cur = None
    hdr_re = re.compile(r"^\s*(build/\S+\.o)\(")
    sym_re = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+(\S+)\s*$")
    alias_re = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+(\w+)\s*=\s*\((\w+)\s*\+\s*(0x[0-9a-fA-F]+)\)\s*$")
    with open(path, errors="ignore") as f:
        for line in f:
            m = hdr_re.match(line)
            if m:
                cur = m.group(1)
                continue
            m = sym_re.match(line)
            if m and cur:
                out.append((m.group(2), int(m.group(1), 16), cur))
            m = alias_re.match(line)
            if m:
                aliases.append((m.group(2), int(m.group(1), 16), m.group(3), int(m.group(4), 16)))
    # Only reviewed internal continuations can inherit a parent's object.
    # Absolute fallback bindings and aliases without an emitted parent do not
    # establish placement or source ownership.
    metadata = os.path.join(ROOT, "config/us/boundary_overrides.json")
    reviewed = {}
    if os.path.exists(metadata):
        with open(metadata) as f:
            reviewed = {entry["symbol"]: entry for entry in json.load(f).get("overrides", [])
                        if entry.get("unit") == unit and entry.get("kind") == "internal"
                        and "parent" in entry and "offset" in entry}
    for name, address, parent, offset in aliases:
        entry = reviewed.get(name)
        if not entry or entry["parent"] != parent or entry["offset"] != offset:
            continue
        for emitted_name, emitted_address, obj in list(out):
            if emitted_name == parent and address == emitted_address + offset:
                out.append((name, address, obj))
    return out


def _slot_of(obj, unit):
    """The content slot (source stem) an object belongs to."""
    rel = obj.replace("\\", "/")
    if rel.startswith("build/us/"):
        rel = rel[len("build/us/"):]
    for pre in (source_dir(unit) + "/", "asm/us/%s/" % unit):
        if rel.startswith(pre):
            rel = rel[len(pre):]
            break
    if rel.endswith(".o"):
        rel = rel[:-2]
    for suf in (".c", ".s"):
        if rel.endswith(suf):
            rel = rel[:-len(suf)]
    return rel


def _prefer(cur, new):
    """True when `new` is a better representative of an address than `cur`."""
    if cur is None:
        return True
    if cur.endswith(".NON_MATCHING") and not new.endswith(".NON_MATCHING"):
        return True
    if cur.startswith(".L") and not new.startswith(".L"):
        return True
    return False


def manifest_divergence(unit):
    """First manifest symbol whose linked address differs from its retail vram.

    A short/long matched function shifts every later symbol, which the
    per-symbol check_unit verdicts cannot see; comparing the map against
    config/us/functions/<unit>.txt localises the first such shift.

    Attribution is by the *built* symbol's defining object (its content slot):
    when another slot's object overruns into this one, the symbol actually
    linked at the expected vram is the probable culprit, not the manifest entry
    that happens to precede the divergent address.  Returns
    (name, built, vram, built_slot, delta, culprit, occupant) where culprit is
    (name, slot, built_size, expected_size) of the preceding entry (None if
    none), and occupant is (name, slot) of the built symbol at `vram` (None if
    that address holds no symbol)."""
    mpath = os.path.join(ROOT, "config/us/functions/%s.txt" % unit)
    if not os.path.exists(mpath):
        return None
    syms = {}
    addr_map = {}
    for name, addr, obj in parse_map_symbols(unit):
        syms.setdefault(name, (addr, obj))
        if addr not in addr_map or _prefer(addr_map[addr][0], name):
            addr_map[addr] = (name, obj)
    entries = []
    for line in open(mpath):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        m = re.match(r"(\S+)\s+([0-9A-Fa-f]+)", line)
        if m:
            entries.append((m.group(1), int(m.group(2), 16)))
    for idx, (name, vram) in enumerate(entries):
        got = syms.get(name)
        if got is None:
            continue
        addr, obj = got
        if addr != vram:
            built_slot = _slot_of(obj, unit)
            culprit = None
            if idx > 0:
                pn, pv = entries[idx - 1]
                pg = syms.get(pn)
                if pg is not None:
                    culprit = (pn, _slot_of(pg[1], unit),
                               addr - pg[0], vram - pv)
            occ = addr_map.get(vram)
            occupant = (_slot_of(occ[1], unit), occ[0]) if occ else None
            return name, addr, vram, built_slot, addr - vram, culprit, occupant
    return None


def format_divergence(div):
    """Lines describing a manifest_divergence() result."""
    name, addr, vram, built_slot, delta, culprit, occupant = div
    if occupant is not None and occupant[0] != built_slot:
        return ["  layout divergence: %s (built, slot %s) at 0x%08X where "
                "manifest expects %s (slot %s)"
                % (occupant[1], occupant[0], vram, name, built_slot)]
    lines = ["  layout divergence: %s built 0x%08X expected 0x%08X slot %s delta %+d"
             % (name, addr, vram, built_slot, delta)]
    if culprit is not None:
        cn, cslot, cbuilt, cexp = culprit
        lines.append("  likely culprit: %s slot %s %s 0x%X (built 0x%X, expected 0x%X)"
                     % (cn, cslot, "short" if cbuilt < cexp else "long",
                        abs(cexp - cbuilt), cbuilt, cexp))
    return lines


def link_unit(unit, ld_bin, objcopy_bin, skip_verify):
    cfg = CONFIG[unit]
    if assemble_bins(unit, ld_bin) != 0:
        return 1
    os.makedirs(os.path.join(ROOT, BUILD, "out"), exist_ok=True)
    cmd = [ld_bin, "-EL"]
    for p in auto_scripts(unit):
        cmd += ["-T", p]
    cmd += ["-T", symbol_script(unit), "-T", cfg["ld"],
            "-Map", os.path.join(BUILD, unit + ".map"),
            "-o", cfg["elf"],
            "--no-check-sections"]
    if run(cmd) != 0:
        print("BUILD FAILED: linking %s" % unit)
        return 1
    if run([objcopy_bin, "-O", "binary", cfg["elf"], cfg["out"]]) != 0:
        print("BUILD FAILED: objcopy %s" % unit)
        return 1
    out = os.path.basename(cfg["out"])
    if skip_verify:
        print("%s: built (verify skipped)" % out)
        return 0
    div = manifest_divergence(unit)
    if div is not None:
        for line in format_divergence(div):
            print(line)
    got = sha1(os.path.join(ROOT, cfg["out"]))
    want = cfg["sha1"]
    if got != want:
        print("%s: MISMATCH" % out)
        print("  built  %s" % got)
        print("  want   %s" % want)
        off, vram, owner, n, blen, rlen = diagnose_mismatch(unit)
        if off < n:
            print("  first diff at file offset 0x%X (vram 0x%08X): %s"
                  % (off, vram, owner or "<no symbol>"))
        else:
            print("  files differ in length (built 0x%X, retail 0x%X)"
                  % (blen, rlen))
        return 1
    print("%s: OK" % out)
    return 0


def main():
    ap = argparse.ArgumentParser(description="Build/verify the DRA units.")
    ap.add_argument("--unit", help="only this unit (default: all 14)")
    ap.add_argument("--objects-only", action="store_true",
                    help="assemble/compile objects but do not link/objcopy/verify")
    ap.add_argument("--skip-verify", action="store_true",
                    help="link + objcopy but do not SHA-1 check against retail")
    args = ap.parse_args()

    units = [args.unit] if args.unit else UNITS
    if args.unit and args.unit not in CONFIG:
        print("unknown unit %s (have: %s)" % (args.unit, ", ".join(UNITS)))
        return 2

    as_bin = tool("as")
    ld_bin = tool("ld")
    objcopy_bin = tool("objcopy")

    needed = [("as", as_bin)]
    if not args.objects_only:
        needed += [("ld", ld_bin), ("objcopy", objcopy_bin)]
    for name, path in needed:
        if not os.path.exists(path):
            print("BUILD FAILED: mips-linux-gnu-%s not found at %s" % (name, path))
            print("Set DRA_BINUTILS to a directory holding the mips binutils.")
            return 1

    cpp, cc1 = cpp_bin(), cc1_bin()
    for name, path in (("cpp", cpp), ("cc1", cc1)):
        if os.path.sep in path and not os.path.exists(path):
            print("BUILD FAILED: %s not found at %s" % (name, path))
            print("Set DRA_CPP / DRA_CC1 to override.")
            return 1

    for key, enabled in UNIT_CXX.items():
        cxx_unit = key.split("/", 1)[0]
        if not enabled or cxx_unit not in units:
            continue
        for name, path in (("CPPPSX", cxx_cpp_bin()),
                           ("CC1PLPSX", cxx_cc1_bin())):
            if os.path.sep in path and not os.path.exists(path):
                print("BUILD FAILED: %s not found at %s" % (name, path))
                return 1

    # maspsx passes an absolute --gnu-as-path to subprocess.Popen; a relative
    # one fails to launch under Windows CreateProcess.
    as_abs = os.path.abspath(as_bin)

    os.makedirs(os.path.join(ROOT, BUILD), exist_ok=True)
    n_asm = assemble_asm(as_bin, units)
    if n_asm < 0:
        return 1
    n_c = compile_c(cpp, cc1, as_abs, units)
    if n_c < 0:
        return 1
    if n_asm == 0 and n_c == 0:
        print("BUILD FAILED: no .s or .c sources found")
        return 1
    if args.objects_only:
        print("objects built (asm=%d, c=%d)" % (n_asm, n_c))
        return 0

    rc = 0
    for unit in units:
        if link_unit(unit, ld_bin, objcopy_bin, args.skip_verify) != 0:
            rc = 1
    return rc


if __name__ == "__main__":
    sys.exit(main())
