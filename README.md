# Digimon Rumble Arena — USA Decompilation

[![Source checks](https://github.com/Ashar2shahid/Digimon-Rumble-Arena-Decomp-USA/actions/workflows/source-checks.yml/badge.svg?branch=main)](https://github.com/Ashar2shahid/Digimon-Rumble-Arena-Decomp-USA/actions/workflows/source-checks.yml)
[![Platform](https://img.shields.io/badge/platform-PlayStation-003791)](#game-version)
[![Version](https://img.shields.io/badge/version-USA_SLUS__014.04-blue)](#game-version)
[![Progress](https://img.shields.io/badge/reviewed_source-58.91%25-blue)](#progress)
[![License](https://img.shields.io/badge/license-see_notices-lightgrey)](LICENSE)

A work-in-progress matching decompilation of **Digimon Rumble Arena** for the original PlayStation, targeting the **USA release (`SLUS_014.04`)**.

Recovered C and C++ source, together with retained assembly, reproduces the retail executable and all thirteen code overlays byte for byte. The project aims to recover readable game code while preserving the original program's behavior and binary layout.

This repository does not distribute game files or compiler binaries. A build requires your own game files and the matching toolchain dependencies.

## Progress

| Component | Reviewed source functions | Progress | Binary verification |
| --- | ---: | ---: | --- |
| Whole game | 2,179 / 3,699 | **58.91%** | 14 / 14 binaries match |
| Executable (`SLUS_014.04`) | 743 / 988 | 75.20% | Matches |
| Code overlays | 1,436 / 2,711 | 52.97% | All 13 match |

These figures count game functions with reviewed source free of assembly and register constraints. They include 2,095 C functions, 50 empty functions and 34 native C++ implementations. An additional 215 functions use assisted source; 1,305 remain in assembly. The figures are a snapshot of [the progress report](config/us/progress.json), rather than a measurement of code or data bytes.

PsyQ SDK routines remain symbolized assembly. Their 655 classified entries are excluded from game-source progress.

All fourteen binaries pass complete byte and symbol-placement checks, and all 92 tooling tests pass. GitHub Actions checks Python syntax and source order; full retail verification requires local game files and toolchains. See [verification results](docs/verification/disc_build.json).

Original translation-unit boundaries and compiler provenance remain under investigation. Binary matching does not establish those properties or certify modified runtime layouts; the current evidence is described in [the code-generation model](docs/CODEGEN_MODEL.md).

## Game version

| Property | Value |
| --- | --- |
| Platform | Sony PlayStation |
| Region | USA |
| Executable | `SLUS_014.04` |
| Executable load address | `0x80010000` |
| Entry point | `0x8003DD50` |

The game stores its code overlays in the `A.VFS` archive. Overlay builds use the inflated binaries as verification targets.

| Overlay | Load address | Purpose | Source directory |
| --- | --- | --- | --- |
| `movie.bin` | `0x800643C0` | Movie playback | `src/movie/` |
| `title.bin` | `0x800643C0` | Title screen and menus | `src/title/` |
| `game.bin` | `0x800643C0` | Battle logic | `src/battle/` |
| `st00.bin`–`st09.bin` | `0x800D3B00` | Battle stages | `src/battle/stages/` |

## Building

The supported build environment is **Windows x64**, **Python 3.13** and **Git for Windows**. Setup requires an internet connection to download pinned tools and a disc image of the **USA release (`SLUS_014.04`)**. Supported image formats are a 2048-byte ISO, a raw 2352-byte BIN, or a single-data-track CUE with its referenced BIN.

### 1. Clone and install Python dependencies

```powershell
git clone https://github.com/Ashar2shahid/Digimon-Rumble-Arena-Decomp-USA.git
cd Digimon-Rumble-Arena-Decomp-USA
python -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install -r requirements.txt
```

Keep the virtual environment active for the remaining commands. Python must be available as `python`, and Git as `git`, on `PATH`.

### 2. Install the matching toolchain

```powershell
python tools/setup_toolchain.py
```

The installer downloads the exact compiler and binutils versions, applies the tracked maspsx patch, and verifies all eighteen installed files against [the toolchain manifest](docs/toolchain_manifest.json). No previous decompilation workspace is required. Existing files with unexpected hashes are preserved and reported as errors.

### 3. Extract the USA game inputs

Replace the example path with the location of your disc image:

```powershell
python tools/setup_game.py "D:\Games\Digimon Rumble Arena (USA).cue"
```

An `.iso` or `.bin` path can be used instead. CUE input requires its referenced BIN in the same directory.

Setup extracts `SLUS_014.04`, unpacks the thirteen code overlays from `A.VFS`, and verifies every target before installing it. The executable's required SHA-1 is `179a3f7ae84762f9f60dc1ba97994eb7e673582e`; unsupported revisions and altered overlays are rejected. The disc image is never modified.

### 4. Generate, build and verify

```powershell
.\decomp.ps1 generate
.\decomp.ps1 build
.\decomp.ps1 compare
```

- `generate` reads instruction and data bytes from the verified game inputs and reconstructs the retained assembly using the reviewed split recipes in `config/us/split/`. Symbol names, relocation bindings, section ownership and alignment are preserved. Recovered source files are not overwritten.
- `build` compiles and links the executable and all thirteen overlays, then checks complete output bytes and symbol placement against retail.
- `compare` validates the existing verification records and rejects changed inputs or outputs.

Outputs are written to `build/us/out/`. Game inputs, generated assembly, tool binaries and download caches remain excluded from version control.

### Progress and tests

```powershell
.\decomp.ps1 report
.\decomp.ps1 test
```

`report` updates `config/us/progress.json` from verified builds. `test` runs the tooling tests. To validate installed tools or the generated split without changing files:

```powershell
python tools/setup_toolchain.py --verify
python tools/generate_game.py --check
```

GNU Make is optional; equivalent targets are `make generate`, `make`, `make compare`, `make report` and `make test`. Linux builds have not been validated.

## Repository layout

```text
config/us/             Split configurations, symbols and progress
config/us/linkers/     Reviewed linker scripts
src/engine/            Resident executable sources
src/battle/            Battle overlay sources
src/battle/stages/     Stage overlay sources
src/title/             Title and menu sources
src/movie/             Movie playback sources
include/               Shared types and interfaces
tools/                 Build, verification and decompilation tools
docs/                  Research notes and verification evidence
```

Local dependencies and outputs reside in `bin/`, `external/maspsx/`, `disks/us/`, `assets/us/bin/`, `asm/us/` and `build/us/`; they are excluded from version control. Address-based function names and source-slot filenames are retained until their identities and original object boundaries are established.

## Toolchain

The installer supplies the tools selected by the verified US build profiles:

| Build stage | Tools |
| --- | --- |
| C preprocessing | Windows GCC 15.2.0, used only as a preprocessor |
| C compilation | PSX GCC 2.8.1 / 2.7.2 and recorded PsyQ 4.0, 4.5 and 4.6 frontend selections |
| C++ compilation | The recorded PSY-Q native C++ frontend and preprocessor |
| Assembly translation | Pinned maspsx runtime with the tracked DRA patch |
| Assembly and linking | GNU Binutils 2.45 for `mips-linux-gnu` |
| Retained assembly generation | Rabbitizer 1.16.2 and the reviewed retail-backed split recipes |

Compiler selection and flags are applied automatically by [the build pipeline](tools/build_dra.py). The default target flags include `-O2 -mips1 -mcpu=3000 -funsigned-char -G0`, with recorded source-slot overrides. These reproduce the current US build; original compiler and translation-unit provenance remain under review.

Download sources, pinned revisions, hashes and patch details are documented in [toolchain setup](docs/TOOLCHAIN_SETUP.md). The generation format and ownership rules are documented in [split generation](docs/SPLIT_GENERATION.md).

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the workflow and matching criteria.

Contributions should recover readable, defined C or native C++, preserve caller and callee contracts, and pass complete executable and overlay verification. Shared interfaces, emitted data and linker changes require review alongside the recovered functions. PsyQ SDK routines should remain symbolized assembly.

## Acknowledgments

[ReGame Labs' Japanese-version decompilation](https://github.com/ReGame-Labs/dtbe_decomp) provides valuable reference code and conventions. This project adopts a similar source layout while preserving the USA release's addresses, targets and verified reproduction profiles.

Maintained by [Ashar2shahid](https://github.com/Ashar2shahid).

## License

See [LICENSE](LICENSE) and [third-party notices](docs/THIRD_PARTY_NOTICES.md) for the applicable terms and attribution. Original game content is not included.
