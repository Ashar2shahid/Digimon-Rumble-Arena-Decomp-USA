# Windows toolchain setup

Use Windows x64, Python 3.10 or newer, and Git for Windows available on `PATH`. From a fresh checkout:

```powershell
python tools/setup_toolchain.py
python tools/setup_toolchain.py --verify
```

The first command downloads the exact matching toolchain. The second verifies its eighteen installed files without network access. Install the project's Python packages separately with `python -m pip install -r requirements.txt`. Game extraction is a separate step using your USA disc; this installer does not need a disc or files from an earlier decompilation workspace.

The installer uses [the manifest](toolchain_manifest.json) for individual binary hashes, complete archive hashes, archive member names and source URLs. Existing correct files and validated content-addressed downloads in `.tools/downloads` are reused. Unknown or mismatched existing files cause setup to fail and are preserved. Inspect a reported mismatch before moving it out of the way and retrying. A download hash mismatch stops installation. `--fresh-download` fetches every dependency again and validates it even when files already exist. `--root PATH` installs into an empty directory for an independent audit; the script still reads the manifest and patch from its own checkout.

The exact Windows preprocessor is GCC 15.2.0. The assembler, linker, objcopy and objdump are GNU Binutils 2.45 configured for `mips-linux-gnu`. These binaries and the default GCC 2.8.1 PSX / GCC 2.7.2 frontend are fetched from [Digimon World 2's public tool directory at commit 9979eebe5ad758fba88040ab188c6f1ce5d3b254](https://github.com/Wyrelade/Digimon-World-2-Decomp/tree/9979eebe5ad758fba88040ab188c6f1ce5d3b254/tools/windows), rather than copied from a local project. The PsyQ 4.0, 4.5 and 4.6 compilers come from [mkst/esa's historical compiler release](https://github.com/mkst/esa/releases/tag/psyq-binaries). Only the five required compiler members are extracted, including the native C++ frontend and preprocessor. `tools/build_dra.py` selects the profiles; setup does not alter them. Hash equality establishes the current reproduction toolchain, not original-object compiler provenance.

The minimal maspsx runtime consists of `maspsx.py`, `maspsx/__init__.py`, `LICENSE` and `README.md`. Its base is fetched from [the pinned public maspsx mirror](https://github.com/Wyrelade/Digimon-World-2-Decomp/tree/9979eebe5ad758fba88040ab188c6f1ce5d3b254/tools/maspsx), derived from [mkst/maspsx](https://github.com/mkst/maspsx). The tracked [DRA patch](../external/maspsx-dra.patch) adds the existing symbolic-store return delay-slot scheduling and divide-by-zero-only expansion behavior. Setup applies it in a private temporary directory and verifies each resulting file before installation. CRLF encoding is explicitly restored to reproduce the imported runtime's exact hashes. Tests and diagnostic tools are not needed to build the game and are not installed.

The upstream maspsx MIT copyright and license are retained with the runtime. GNU Binutils and modern GCC use GNU GPL licensing. Historical PsyQ distributions combine modified GNU compiler components and vendor additions; their licensing is not replaced by this repository's game-source license. These compiler packages are downloaded from the named public sources and are not committed or redistributed here. Public availability alone does not establish permission for proprietary components.

On October 11, 2026, a fresh empty installation fetched all sixteen public inputs (nine binaries, three archives and four assembler files), applied the tracked patch and verified all eighteen installed SHA-256 values against the existing accepted toolchain. No binary or assembler source was substituted. The full executable plus thirteen-overlay comparison is performed separately after game extraction and building.
