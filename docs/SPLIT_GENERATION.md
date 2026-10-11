# Retail-backed split generation

`python tools/generate_game.py` reconstructs the reviewed retained assembly from the supported USA executable and thirteen inflated overlays. Run `tools/setup_game.py` on your disc image first and install `requirements.txt`. The generator uses Rabbitizer 1.16.2 with R3000GTE decoding, GNU mode, pseudo-move disabled and named COP0 registers disabled.

The checked-in `config/us/split/*.json` recipes preserve the accepted split's sections, labels, symbol sizes, alignment and source ownership. They contain no cached instruction words, string contents or numeric game-data payloads. The operation records are:

| Record | Meaning |
| --- | --- |
| `i, address[, operand]` | Decode one retail instruction; bind a reviewed symbolic immediate, branch or jump target when present |
| `d, address, width` | Read a literal byte, halfword or word from retail |
| `p, address, expression` | Emit a reviewed symbolic pointer word |
| `bytes, address, length` | Read a literal data range, including original string terminators |
| String scaffold | Preserve section, label, size and alignment directives |

Addresses are translated using each binary's actual load address and file-header offset. Historical disassembly comments can be section-relative or use a different endian presentation; they do not determine extraction offsets. The main header reads the original first 2048 bytes with `.incbin`. The active reserved-RAM asset is extracted from the executable's reviewed range; inactive historical databins are not build dependencies.

All target SHA-1 values, extraction ranges and generated text hashes are checked before any output is written. Changed local assembly and unrecognized assembly files are preserved and reported as errors. An exact legacy accepted file can be replaced by its audited regenerated representation; arbitrary modified files cannot. `--check` verifies the generated outputs without writing. Generation records are stored under `build/us/`.

Recipes are the authoritative build-generation description for this snapshot. The older splat configurations remain research inputs: several inherited slot names, offsets and type annotations need normalization before they can regenerate the reviewed layout. Running splat directly would lose accepted boundary, data and symbol changes. No compiler-produced C/C++ assembly is rewritten by this generator, and no recovered source or canonical linker script is regenerated.

Changes to retained assembly boundaries, aliases or data ownership must update the relevant reviewed recipe and expected generated hash as part of the same transaction. Check sibling objects, emitted data and global metadata, then run the complete fourteen-binary byte and placement gate. Do not change target instructions to force a C match. SDK routines remain symbolized assembly and do not earn game-source credit.
