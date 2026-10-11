#!/usr/bin/env python3
"""Per-function byte check for one DRA unit.

Builds the unit the same way tools/build_dra.py does (assemble the split asm,
compile src/<unit>/*.c through cpp -> cc1 -> maspsx -> as, link with the splat
linker script, objcopy to a raw image), then compares every entry listed in
config/us/functions/<unit>.txt against the retail slice:

    off = vram - load_base + (0x800 if unit == main else 0)

Each entry is compared from ITS OWN symbol: the built address comes from the
linked ELF symbol table (so an entry that changed size does not shift the
verdicts of the ones after it), while the retail slice comes from the entry's
retail vram.  Words that the relocatable object relocates (jal/j targets, %hi/
%lo of addresses) are masked: they depend on the link layout, not on the code,
and in an in-progress tree the layout can differ from retail.

`build_raw` and `verdicts` are importable so tools/toolchain_probe.py can
build with overridden compiler settings and reuse the same comparison.

Usage: python tools/check_unit.py <unit>
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_dra as B  # noqa: E402

DATA_SECTIONS = (".text", ".data", ".rodata", ".bss")


def elf_symbols(elf):
    """{name: (vram, size)} of the defined symbols of a linked ELF."""
    out = subprocess.run([B.tool("objdump"), "-t", elf], cwd=B.ROOT,
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


def unit_objects(unit):
    objs = []
    for sub in ("asm/us", "src"):
        root = os.path.join(B.ROOT, "build/us", sub, unit)
        for dirpath, _dirs, files in os.walk(root):
            for name in files:
                if name.endswith(".o"):
                    objs.append(os.path.relpath(os.path.join(dirpath, name), B.ROOT)
                                .replace("\\", "/"))
    return sorted(objs)


def _objdump_multi(args, objs):
    return subprocess.run([B.tool("objdump")] + args + objs, cwd=B.ROOT,
                          capture_output=True, text=True).stdout


def object_symbols(objs):
    """Symbol table + relocation offsets of every built object of the unit.

    Returns (syms, relocs): syms maps name -> (object, section, offset, size)
    for symbols in a data/code section; relocs maps (object, section) -> set of
    relocation offsets, so the check can mask words whose value is a link
    address rather than codegen."""
    syms = {}
    cur = None
    for line in _objdump_multi(["-t"], objs).splitlines():
        m = re.match(r"^(.*?):\s+file format ", line)
        if m:
            cur = m.group(1).strip()
            continue
        p = line.split()
        if cur and len(p) >= 5 and re.fullmatch(r"[0-9a-fA-F]{8}", p[0]) \
                and p[-3] in DATA_SECTIONS and re.fullmatch(r"[0-9a-fA-F]{8}", p[-2]):
            syms.setdefault(p[-1], (cur, p[-3], int(p[0], 16), int(p[-2], 16)))
    relocs = {}
    cur = None
    sect = None
    for line in _objdump_multi(["-r"], objs).splitlines():
        m = re.match(r"^(.*?):\s+file format ", line)
        if m:
            cur = m.group(1).strip()
            sect = None
            continue
        m = re.match(r"RELOCATION RECORDS FOR \[(\S+)\]", line)
        if m:
            sect = m.group(1)
            continue
        p = line.split()
        if cur and sect and len(p) >= 2 and re.fullmatch(r"[0-9a-fA-F]{8}", p[0]):
            relocs.setdefault((cur, sect), set()).add(int(p[0], 16))
    return syms, relocs


def build_raw(unit, cpp_flags=None, cc1_exe=None, cc1_flags=None,
              maspsx_flags=None, maspsx_as_flags=None, cpp_exe=None):
    """Assemble/compile the unit, link it, objcopy to raw; return (raw, elf).

    The compiler knobs default to build_dra's per-unit settings and are what
    toolchain_probe.py overrides."""
    as_bin = B.tool("as")
    ld_bin = B.tool("ld")
    objcopy_bin = B.tool("objcopy")
    for name, path in (("as", as_bin), ("ld", ld_bin), ("objcopy", objcopy_bin)):
        if not os.path.exists(path):
            print("check_unit: mips-linux-gnu-%s not found at %s" % (name, path))
            return None, None

    os.makedirs(os.path.join(B.ROOT, B.BUILD), exist_ok=True)
    if B.assemble_asm(as_bin, [unit]) < 0:
        return None, None
    if B.compile_c(cpp_exe or B.cpp_bin(), B.cc1_bin(), os.path.abspath(as_bin), [unit],
                   cc1_flags=cc1_flags, maspsx_flags=maspsx_flags,
                   maspsx_as_flags=maspsx_as_flags, cc1_exe=cc1_exe) < 0:
        return None, None
    if B.assemble_bins(unit, ld_bin) != 0:
        return None, None

    cfg = B.CONFIG[unit]
    cmd = [ld_bin, "-EL"]
    for p in B.auto_scripts(unit):
        cmd += ["-T", p]
    cmd += ["-T", B.symbol_script(unit), "-T", cfg["ld"],
            "-Map", os.path.join(B.BUILD, unit + ".map"),
            "-o", cfg["elf"], "--no-check-sections"]
    if B.run(cmd) != 0:
        print("check_unit: linking %s failed" % unit)
        return None, None
    if B.run([objcopy_bin, "-O", "binary", cfg["elf"], cfg["out"]]) != 0:
        print("check_unit: objcopy %s failed" % unit)
        return None, None
    with open(os.path.join(B.ROOT, cfg["out"]), "rb") as f:
        return f.read(), cfg["elf"]


def verdicts(unit, raw, elf):
    """[{name, vram, size, ok, detail}] for every entry of the unit."""
    cfg = B.CONFIG[unit]
    with open(os.path.join(B.ROOT, cfg["target"]), "rb") as f:
        retail = f.read()
    elf_syms = elf_symbols(os.path.join(B.ROOT, elf))
    obj_syms, relocs = object_symbols(unit_objects(unit))

    # GNU as drops symbols whose names start with `.L` (splat's alternate
    # entries), so they have no symbol table entry; size them from the next
    # symbol and assume they did not move.
    defined_addrs = sorted({a for a, s in elf_syms.values() if s > 0})

    def size_at(vram):
        nxt = next((a for a in defined_addrs if a > vram), None)
        return (nxt - vram) if nxt is not None else 0

    # vram-ordered entries (for detecting a function shorter than retail); a
    # function is only compared against its `func` successor, never a data one.
    entries = []
    for line in open(os.path.join(B.ROOT, "config/us/functions/%s.txt" % unit)):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        m = re.match(r"(\S+)\s+([0-9A-Fa-f]+)\s*(\S*)", line)
        if m:
            kind = m.group(3) or ("func" if m.group(1).startswith("func_") else "data")
            entries.append((m.group(1), int(m.group(2), 16), kind))

    truncated = len(raw) < len(retail)
    last_in_image = None
    for i, (nm, vr, kd) in enumerate(entries):
        if vr - cfg["vram"] + cfg["file_base"] < len(raw):
            last_in_image = i

    out = []
    for idx, (name, vram, kind) in enumerate(entries):
        sym = elf_syms.get(name)
        if sym is not None:
            built_vram, size = sym
        else:
            built_vram, size = vram, size_at(vram)
        if size == 0:
            out.append(dict(name=name, vram=vram, size=0, ok=False,
                            detail="MISSING (no symbol)"))
            continue
        # a function the built image stops inside is genuinely truncated; a
        # retail gap after a function is not evidence of a short function
        short = 0
        if truncated and idx == last_in_image:
            short = len(retail) - (vram - cfg["vram"] + cfg["file_base"])
        built_off = built_vram - cfg["vram"] + cfg["file_base"]
        retail_off = vram - cfg["vram"] + cfg["file_base"]
        got = raw[built_off:built_off + size]
        want = retail[retail_off:retail_off + size]

        # Mask the words the object relocates: their value is a link address
        # (jal/j target, %hi/%lo of an address), which moves with the layout.
        masked = set()
        osym = obj_syms.get(name)
        if osym is not None:
            obj, sect, ooff, _osz = osym
            for r in relocs.get((obj, sect), ()):
                if ooff <= r < ooff + size:
                    base = r - ooff
                    # I-format (lui/addiu/lw/sw/...): only the immediate moves with
                    # the link layout, so the register fields must still match — a
                    # whole-word mask used to hide wrong-register codegen (e.g.
                    # title/A660 func_80070240).  J-format (j/jal) carries its target
                    # in the low 26 bits, so mask the whole word there.
                    op = want[base + 3] >> 2 if base + 3 < len(want) else 0
                    if op in (0x02, 0x03):
                        masked.update(range(base, min(base + 4, size)))
                    else:
                        # I-format, little-endian: the patched imm16 lives in bytes
                        # base+0/base+1, while base+2/base+3 hold rt/rs/opcode — the
                        # register choice — which must still be *compared*.  (Masking
                        # base+2..4, as this did before, hid wrong-register codegen;
                        # caught by PinSt05.)
                        masked.update(range(base, min(base + 2, size)))

        diff = None
        for i in range(min(len(got), len(want))):
            if i not in masked and got[i] != want[i]:
                diff = i
                break
        if short and not diff and len(got) == size:
            out.append(dict(name=name, vram=vram, size=size, ok=False, retail_off=retail_off,
                            detail="size=0x%X off=0x%X retail is 0x%X: function is 0x%X short"
                                   % (size, retail_off, short, short - size)))
        elif len(got) != size or diff is not None:
            d = diff if diff is not None else min(len(got), len(want))
            out.append(dict(name=name, vram=vram, size=size, ok=False, retail_off=retail_off,
                            detail="size=0x%X off=0x%X first diff at +0x%X (vram 0x%08X): "
                                   "got %s want %s"
                                   % (size, retail_off, d, vram + d,
                                      got[d:d + 1].hex() or "--", want[d:d + 1].hex() or "--")))
        else:
            note = ""
            # A compiled function *shorter* than its retail region still passes the
            # prefix compare (and a split-owned pad can legitimately absorb 4/8/12
            # bytes), so surface the shortfall as a note rather than a failure.
            region = size_at(vram)
            if region and size < region:
                note = "  [SHORT vs retail region 0x%X]" % region
            out.append(dict(name=name, vram=vram, size=size, ok=True,
                            detail="0x%X bytes%s" % (size, note)))
    return out


def report(unit, results, verbose=True):
    ok_all = True
    n_ok = 0
    for r in results:
        if r["ok"]:
            n_ok += 1
            if verbose:
                print("%s: OK (%s)" % (r["name"], r["detail"]))
        else:
            ok_all = False
            print("%s: MISMATCH %s" % (r["name"], r["detail"]))
    print("%s: %s (%d/%d functions OK)"
          % (unit, "ALL OK" if ok_all else "FAILED", n_ok, len(results)))
    return ok_all


def check(unit, verbose=True, **kw):
    raw, elf = build_raw(unit, **kw)
    if raw is None:
        return False
    return report(unit, verdicts(unit, raw, elf), verbose)


def main():
    if len(sys.argv) != 2 or sys.argv[1] not in B.CONFIG:
        print("usage: python tools/check_unit.py <%s>" % "|".join(B.UNITS))
        return 2
    return 0 if check(sys.argv[1]) else 1


if __name__ == "__main__":
    sys.exit(main())
