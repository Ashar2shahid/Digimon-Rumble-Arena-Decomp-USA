# PS1 references from decomp.dev

Checked the live [decomp.dev tracker](https://decomp.dev/) with its **PlayStation** filter on 2026-10-07. It listed 28 projects; the 13 game projects below reported **100.00% decompiled**. This records their published progress, not an independent rebuild of every project. Completion applies to each report's configured revision, categories, and binaries. Some projects exclude SDK code, and matching source can still need naming and typing work.

| Game / tracked project | Decompiled | Fully linked shown |
| --- | ---: | ---: |
| [Digimon World 3 / 2003](https://decomp.dev/ReGame-Labs/dw3_decomp) | 100.00% | Not shown |
| [Parasite Eve](https://decomp.dev/khasinski/parasite-eve-decomp) | 100.00% | 100.00% |
| [Parasite Eve II](https://decomp.dev/GabeRealB/parasite-eve-2-decomp) | 100.00% | Not shown |
| [Digimon World 2](https://decomp.dev/Wyrelade/Digimon-World-2-Decomp) | 100.00% | Not shown |
| [Legend of Mana](https://decomp.dev/celophi/lom-decomp) | 100.00% | 100.00% |
| [Digimon: Digital Card Battle](https://decomp.dev/ReGame-Labs/dcb_decomp) | 100.00% | Not shown |
| [LSD: Dream Emulator](https://decomp.dev/brian-oblivion/lsddecomp) | 100.00% | Not shown |
| [Need for Speed: High Stakes](https://decomp.dev/Caesar0007/NFSHS-PSX-decomp) | 100.00% | Not shown |
| [Digimon World](https://decomp.dev/jype0/dw_decomp) | 100.00% | Not shown |
| [Brave Fencer Musashi](https://decomp.dev/Druthulu/BFM-decomp) | 100.00% | 100.00% |
| [Kaze no Notam](https://decomp.dev/aaaaaaaaaaway/kaze-no-notam-decomp) | 100.00% | 100.00% |
| [Serial Experiments Lain](https://decomp.dev/Y0oshi/lain-psx-decompiled) | 100.00% | 100.00% |
| [Rage Racer](https://decomp.dev/khasinski/rage-racer-decomp) | 100.00% | 95.34% |

“Not shown” is an absent field, not zero. Silent Hill was **99.99%**, Symphony of the Night **69.53%**, and the Tony Hawk's Pro Skater 2 competition demo **97.61%**, so they were not included in the 100% list. A port's playability is a separate outcome from matching decompilation.

## Methods to reuse

**Discover the compiler from the binary.** Digimon World uses a CodeWarrior PlayStation compiler wrapper, while Digimon World 2 documents PSX GCC 2.8.1 and differing small-data/assembler settings for resident code and overlays. Shared branding does not imply a shared compiler. Our Rumble Arena reference also needs multiple GCC revisions and C++ compilation. [Digimon World build instructions](https://github.com/jype0/dw_decomp), [Digimon World 2 compiler and status](https://github.com/Wyrelade/Digimon-World-2-Decomp).

**Inventory overlays before measuring progress.** Digimon World 3 builds the executable, 21 overlays, and stage modules, and compares every configured binary. Its USA and European versions have distinct inputs and reports. For Rumble Arena, our independently identified inventory is one resident executable and 13 overlays; shared RAM addresses must remain qualified by module. [Digimon World 3 build and comparison workflow](https://github.com/ReGame-Labs/dw3_decomp).

**Use a fresh, complete output comparison as the acceptance gate.** Parasite Eve makes a full module checksum a prerequisite for source credit and separates instruction-based implementations, SDK assembly, and source constraints in its accounting. We should likewise count compiled source only after placement and complete output bytes pass. Keep register pinning and inline instructions visible when importing older work. [Parasite Eve progress and matching policy](https://github.com/khasinski/parasite-eve-decomp).

**Identify SDK code separately.** Digimon World 2's reported game functions exclude Psy-Q libraries, while its scheduler documents a small assembly requirement for changing the stack. This makes the denominator and assembly provenance essential to interpreting “100%.” Rumble Arena's resident SDK region should have its own category. [Digimon World 2 progress definition](https://github.com/Wyrelade/Digimon-World-2-Decomp).

**Treat exact matching and source quality as separate milestones.** Parasite Eve also requires meaningful names, types, and subsystem placement before calling a file finished. In our project, matching address-named C and raw field offsets are a starting point for reconstructing objects and interfaces. [Parasite Eve source-quality policy](https://github.com/khasinski/parasite-eve-decomp).

## Applied to this disc

The supplied image is **Digimon Rumble Arena USA, SLUS_014.04**. Its local [revision and memory map](findings.md), [prior-project audit](legacy-project-audit.md), and verified build establish the starting point. Reuse verified source and compiler experiments from the user's prior Rumble Arena project, then recover loader/archive structures, adjusted object dispatch, and cross-overlay interfaces. Preserve the original image and extracted binary hashes; maintain ordinary C coverage separately from the verified mixed C/C++/assembly reference tree.
