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

All fourteen binaries pass complete byte and symbol-placement checks, and all 88 tooling tests pass. GitHub Actions checks Python syntax and source order; full retail verification requires local game files and toolchains. See [verification results](docs/verification/migration.json).

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

### Requirements

- Windows and Python.
- The supported USA game executable and inflated overlays.
- The compiler, assembler and reviewed assembly inputs identified by [the dependency manifest](docs/import_manifest.json).

**Reproducibility:** the current snapshot builds from an existing, verified dependency set. Automated setup from a disc image alone is not yet supported. Generated assembly includes reviewed boundary and data-ownership changes that a standard splat run would not preserve. Linux builds have not been validated.

### Dependency setup

If you have the original verified US workspace, restore its dependencies with the following command. Replace the placeholder with that workspace's location:

```powershell
python tools/bootstrap_local.py --from "D:\path\to\original-us-workspace"
```

The bootstrap validates input hashes before restoring missing files and refuses to overwrite changed dependencies. See [migration notes](docs/MIGRATION.md) and [external dependencies](external/README.md) for details.

### Build and verify

Run from the repository root after restoring the required dependencies:

```powershell
.\decomp.ps1 generate
.\decomp.ps1 build
.\decomp.ps1 compare
```

`generate` checks dependency availability. `build` compiles, links and verifies the executable and all overlays. `compare` validates the recorded outputs against the current inputs.

Generate the progress report and run the tooling tests with:

```powershell
.\decomp.ps1 report
.\decomp.ps1 test
```

GNU Make provides equivalent targets: `make generate`, `make`, `make compare`, `make report` and `make test`.

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

The build preserves the compiler revisions and flags that currently reproduce the US binaries. The baseline uses `-O2 -mips1 -mcpu=3000 -funsigned-char -G0`, with recorded overrides for individual source slots. A locally patched maspsx translator handles compiler output before assembly and linking.

Effective settings are defined in [the build pipeline](tools/build_dra.py) and documented in [the code-generation model](docs/CODEGEN_MODEL.md). Split configurations are under `config/us/`; the reviewed assembly is maintained as a local dependency.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the workflow and matching criteria.

Contributions should recover readable, defined C or native C++, preserve caller and callee contracts, and pass complete executable and overlay verification. Shared interfaces, emitted data and linker changes require review alongside the recovered functions. PsyQ SDK routines should remain symbolized assembly.

## Acknowledgments

[ReGame Labs' Japanese-version decompilation](https://github.com/ReGame-Labs/dtbe_decomp) provides valuable reference code and conventions. This project adopts a similar source layout while preserving the USA release's addresses, targets and verified reproduction profiles.

Maintained by [Ashar2shahid](https://github.com/Ashar2shahid).

## License

See [LICENSE](LICENSE) and [third-party notices](docs/THIRD_PARTY_NOTICES.md) for the applicable terms and attribution. Original game content is not included.
