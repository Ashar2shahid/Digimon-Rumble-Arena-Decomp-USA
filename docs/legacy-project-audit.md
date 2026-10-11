# Legacy decompilation audit and migration history

The isolated audit and first-import sections below describe earlier checkpoints. The canonical workspace now integrates the complete verified mixed source/assembly tree, uses `src/<unit>/<slot>.c` with `config/us/` and `config/us/linkers/`, and verifies its own complete outputs. Initial small WSL sources are archived under `analysis/pre-migration/20261007-canonical-import`. Current progress is `config/us/progress.json`, with SDK, assisted source and source-quality limitations separated.

The migration preserved nine newer resident functions missing from the older source, including three hidden inside its E000 data fragment. It restored 133 resident and four movie SDK C bodies to symbolized assembly. Loader `func_80027A0C` now matches under the canonical PsyQ 4.6 slot compiler. Two inherited C++ functions needed explicit canonical symbol aliases; the tightened gate checks their actual defining objects and placement. All these statements refer to the editable canonical tree, not changes to D: or the immutable audit snapshot.

The older project at `D:\Decompiles\Digimon Rumble Arena\Digimon Rumble Arena` targets the same USA revision as this repository: both identify `SLUS_014.04` by SHA-1 `179a3f7ae84762f9f60dc1ba97994eb7e673582e` ([current revision record](findings.md), old `README.md`). Its source is a large pool of candidate replacements for our individual assembly functions, provided each candidate is adapted and checked in this build.

## What the old source contains

The count below intersects address-qualified names in old `src/` with `func` rows in `config/us/functions/*.txt`. C definitions use the old project's own definition pattern (`tools/progress.py`); C++ definitions use its `.set func_..., mangled_name` aliases. A brace scan classifies C bodies. These are **source representations**, not a count of independently imported or verified functions here.

| Representation | Functions |
| --- | ---: |
| Nonempty C without inline `asm` | 1,464 |
| C with inline assembly or register pinning | 264 |
| Empty C bodies | 52 |
| C++ definitions with assembler aliases in `.c` slots | 33 |
| K&R-style C definition (`title/65A4.c:326`) | 1 |
| `INCLUDE_ASM` placeholders | 2,105 |
| **Total manifest `func` rows** | **3,919** |

Thus 1,780 functions have ordinary C definitions, one has a K&R C definition, and 33 have C++ alias definitions. The 2,105 placeholders still assemble retail-derived instructions. Experimental sources in `tools/cc1_panel/` and generated drafts are separate from the linked `src/` definitions. An empty C body may reproduce a real no-op function; it provides little behavior to reuse. Examples of the distinctions are old `src/engine/B800.c:12` (empty body), `src/engine/B800.c:64` (pinned registers), and `src/engine/C000.c:17` (`INCLUDE_ASM`).

The old `README.md` displays **1,814/3,919 (46.29%)**, but explicitly calls its generated progress block a legacy snapshot. Its numerator happens to equal the 1,780 + 1 + 33 source representations above. Use the manifest/source classification and fresh build result below for this audit, rather than inferring coverage from the badge or from the statement that all units build.

## Fit with this project

Of the 1,814 old source definitions, **1,809** align by unit and address with entries in our `analysis/us/<unit>/functions.csv` inventories. Five require split or placement review: `main` functions `80038800`, `80040000`, `80053E44`, `800583EC`, and `movie` function `80065D30`. Of the initial 22 verified C functions, before this import pass, 13 also have old C bodies. Six are `INCLUDE_ASM` in the older tree (`8001B928`, `8001B94C`, `8001BEC8`, `8001D1C8`, `8001F260`, `8001F278`), and three (`8001D874`, `8001D97C`, `8001DA64`) have no old source entry. Up to **1,796** directly aligned old source definitions are therefore new candidates for this repository, before suitability and byte matching are checked. The old `src/engine/B800.c:37`, `C000.c:9`, `src/battle/9DF4.c:110`, and `E324.c:70` show shared implementations; our `include/types.h` expresses several layouts more clearly. Signatures can differ even for matching instructions: old `func_8006F10C` is declared `void` (`src/battle/9DF4.c:157`), while ours returns the updated flags.

Start with small, nearby plain-C functions, then compare each candidate's full emitted function bytes and address in our builder. Useful first groups are the wrappers around `src/engine/B800.c:17-34`, the accessors and constructors around `src/engine/C800.c:77-95`, and the getters, setters, and flag operations around `src/battle/9DF4.c:115-175` and `src/battle/E324.c:70-86`. Keep the initial 22 verified implementations unless a replacement provides a concrete benefit and passes the same gate. Copy only the needed source and dependencies; the old slot files, primitive `include/common.h` types, linker configuration, and build scripts are not drop-in replacements for this repository.

## Verification and reusable methods

The isolated audit at [`analysis/legacy-audit/20261007T124110254143Z`](../analysis/legacy-audit/20261007T124110254143Z/result.json) copied inputs into this workspace without changing the D: source. Its `source-order` check exited 0; its [build log](../analysis/legacy-audit/20261007T124110254143Z/build.log) and result report byte-identical SHA-1 outputs for `SLUS_014.04` and all 13 overlays (14/14). This validates that the older tree builds its mixed C/C++/assembly configuration against this revision. It does **not** make each `INCLUDE_ASM` placeholder a decompilation, or show that a source body will match after being moved into our different build.

The old project supplies practical techniques worth adapting:

- Its `docs/CC1_REVISIONS.md` records the default PSY-Q `cc1psx` **GCC 2.8.1 SN32 BUILD 4.0.0010** plus 78 file-specific override keys and compiler experiments. `tools/build_dra.py` also opts selected `.c` slots into C++. Compiler selection depends on old slot boundaries, so test an override on the exact imported function and its neighbors before applying it here.
- Its `docs/VERIFICATION.md` checks symbol resolution, object `.text` size, function overrun, and source order before the full unit gate. A missing `.s` file or a relocation-masked function comparison alone is insufficient: a wrong symbol, shifted function, or excess bytes may still appear to pass. The final gate must compare the **entire linked output without masked bytes**, including exact function placement and all following sections, to the known retail hash.
- Its `docs/EXTRACTION_FIX.md` documents a raw MODE2/2352 trap: reading 2,048-byte payloads contiguously inserts 304 framing bytes per sector and truncates long files. Use sector-wise logical extraction and the known executable SHA-1 before trusting addresses or comparisons. Our [revision findings](findings.md) independently describe this layout.
- Its `docs/LIBRARY_INVENTORY.md` separates the contiguous Psy-Q library tail of `main` (`0x8003DEEC`–`0x8005EE1C`) from game logic and identifies SDK functions against library objects. Preserve that distinction when prioritizing source imports and interpreting compiler evidence; matching a library object is different from recovering game source.

The old build's per-file compiler and C++ settings, source order, and full-output comparison explain why the source is valuable. The next step for any candidate is still a focused import into this repository followed by our own exact-byte verification.

## Historical first independently verified imports

The first pass adapted 63 additional functions into the former `src/engine/legacy_recovered.c` (17 functions, 656 bytes), `src/battle/legacy_recovered.c` (30 functions, 932 bytes), and `src/title/legacy_recovered.c` (16 functions, 216 bytes). These were ordinary C without inline assembly or register pinning. With the initial 22 functions, that small-tree checkpoint had **85 verified C functions covering 2,380 of 934,552 configured text bytes (0.2547%)**. A complete build checked all fourteen outputs; `config/us/progress.json` retains the historical WSL checkpoint.

The initial loader attempt, `func_80027A0C`, clarified the filename argument and the allocated buffer's eight-byte header skip, but had one compiler instruction mismatch. Its historical draft is `analysis/us/main/loader_candidate.c`. That mismatch was subsequently resolved in canonical `src/engine/18000.c`; the current gate verifies the compiled function as part of main.
