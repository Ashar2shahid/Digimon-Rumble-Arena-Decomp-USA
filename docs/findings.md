# Disc and code findings

Verified against the local image during initial setup on 2026-10-07. These findings apply to the supplied USA revision.

Checkpoint `20261008T225343Z` reaches1,960/3,604 unconstrained functions (54.3840%). Real RGB callers bound components to bytes; scheduler wrapping is explicit and its third count argument is forwarded. Original zlib1.1.3 source supplies code/block allocation helpers and Adler-32. Debug factories return constructed pointers, and an optional overlay path is a%s string, not merely a flag. All14 outputs and76 tests pass. [Accepted evidence](../analysis/us/parallel_waves22_28_integration.json).

Checkpoint `20261008T222348Z` reaches1,948/3,596 unconstrained game functions (54.1713%). VFS callbacks explicitly distinguish a forwarded opaque word from device reason codes; iterator wrappers forward actual destructor parameters. A complete104-byte insertion replaces a falsely separate20-byte C fragment. Two MD5 packing helpers are independent entries, while their exact source/library provenance remains unproved. Renderer startup uses shared renderer/handle layouts, and gameplay constructors use seven real base arguments with a pointer result. All14 outputs and76 tests pass. [Accepted evidence](../analysis/us/parallel_waves17_21_integration.json).

Continued recovery at checkpoint `20261008T214417Z` reaches 1,926/3,589 unconstrained functions. New renderer tables preserve exact linked pointers and rodata alignment; a hidden resource/packet code region adds seventeen genuine entries, and BST review adds two. The shared resource object is 0x524 bytes with separate +0x10 and +0x14 tables. Full-width accessor returns and a real third update argument are established from consumers. An earlier masked local jump match failed the full link; natural scope placement repaired it, and the private checker now detects such errors. All fourteen outputs pass, with 76 tooling tests. [Detailed evidence](../analysis/us/parallel_waves9_16_integration.json).

## Revision and extraction

| Item | Evidence |
| --- | --- |
| Game | Digimon Rumble Arena, USA |
| Boot executable | `SYSTEM.CNF`: `cdrom:\SLUS_014.04;1` |
| Image | Raw MODE2/2352 BIN, one track in the CUE |
| ISO volume | `SLUS_01404` |
| BIN size | 266,827,344 bytes |
| BIN SHA-1 | `5d1185699ca2787c8ec1945f0abd14103e7145be` |
| Executable SHA-1 | `179a3f7ae84762f9f60dc1ba97994eb7e673582e` |
| Build string | RAM `0x80010028`: `build0112161615`; date interpretation remains an inference |

The normal Mode 2 Form 1 payload starts 24 bytes into each sector and has 2,048 bytes. A.STR and A.XAP contain Form 2 sectors, so their movie/audio streams are left on the original image by default. `tools/extract_disc.py --streams` preserves full 2,336-byte XA sectors including subheaders and EDC; interpreting these as ordinary 2,048-byte files would lose data.

A.VFS uses a VFS2 header, a zlib-compressed directory table, 12-byte directory entries, and sector-relative file offsets. Some payloads start with `ZP00`, an uncompressed-size field, and zlib data. The archive's `.bin` files must be decompressed before analyzing their machine code.

## Memory map

Addresses below are start-inclusive and end-exclusive.

| Region | RAM span | Basis |
| --- | --- | --- |
| Resident rodata and tables | `0x80010000â€“0x8001AE18` | EXE load address; strings and tables precede the first code prologue |
| Resident text | `0x8001AE18â€“0x8005EE1C` | Instruction inspection; byte-identical assembly rebuild |
| Resident data / small globals | `0x8005EE1Câ€“0x800643C0` | Data after code; overlay slot begins at the following address |
| Main overlay slot | starts `0x800643C0` | Loader code in `func_8001CE40` and `func_8002A010`; game/title/movie references agree |
| Game overlay bytes | `0x800643C0â€“0x800D3AFC` | Decompressed game.bin size `0x6F73C` |
| Stage overlay slot | starts `0x800D3B00` | game `func_8006E648` loads `/bin/st%02d.bin` here |
| Largest stage bytes, st00 | `0x800D3B00â€“0x800DA5FC` | Decompressed st00.bin size `0x6AFC` |
| Resident BSS clear | `0x800DA600â€“0x8011C528` | Startup loop at entry `0x8003DD50` |

The PS-X EXE header specifies load address `0x80010000`, payload size `0x10C800`, and entry `0x8003DD50`. Its header GP is zero; startup explicitly initializes `$gp` to **`0x80064128`**. It contains a large zero-filled area covering overlay/BSS memory; this is not additional decompiled code. The header stack address is `0x801FFFF0`; SYSTEM.CNF says `0x801FFF00`, and startup derives its stack from runtime data. Do not merge these into one guessed value.

Game, title, and movie code share the same load address. Stage modules share a second address. Keep each module's symbols separate even when two functions have identical RAM addresses. A successful independent rebuild checks the configured placement but does not establish that every heuristic function split is a real source-level function.

## What the first source reveals

- The resident engine has circular doubly linked lists. `func_8001B898` initializes a sentinel; `func_8001B928` inserts before it; `func_8001B94C` counts nodes; `func_8001B974` searches a value at offset `0x8`.
- `func_8001B488` initializes a partial object with list links, a value, two zeroed fields, and a table pointer at offset `0x14`.
- Game functions operate on a flags word at object offset `0x2C8`. Matched functions set bit 2, read bits 4 and 8, and set bit 3. Gameplay meanings are unknown.
- `func_8006ECD4` loads a table at object offset `0x1C`, reads a signed object adjustment from table offset `0x20`, and calls the pointer at `0x24` with an adjusted object address. This suggests C++ method dispatch or an equivalent callback scheme; it is not proof of an original class name.
- `func_80037010` uses 624-word state, a twist, and tempering shifts characteristic of a Mersenne Twister generator. This is an algorithm inference from its disassembly, not yet a matching recovered C function.
- The binary contains zlib 1.1.3 strings and Sony SDK library strings. They help locate library regions but do not establish one compiler version for the whole game.
- `func_80027A0C` in `src/engine/18000.c` now has byte-matching C. It compares/caches a filename, obtains a resource size, allocates and reads its bytes, passes the buffer after an eight-byte header to `func_80028004`, frees the buffer and calls a completion routine. The address-one guard (`D_1`) remains a source-level interpretation question. The match required the PsyQ 4.6 slot compiler; no register pinning or inline instructions were added.

## Next concrete targets

| Priority | Function / region | Why |
| --- | --- | --- |
| 1 | `func_80027A0C` and its callers in main | Matching C is recovered; establish the header format, filename cache contract and address-one guard meaning |
| 1 | `func_80033298` and directory helpers in main | Typed `func_800333CC` now matches; recover mount registration, directory records and allocation ownership |
| 2 | `func_8006E648` in game | Stage loader, ten-way stage dispatch, and stage object creation; links the overlays to gameplay |
| 2 | `func_8006ECD4` and its callers | Resolve adjusted object pointers and callback-table types before decompiling larger methods |
| 3 | Game state at `0x2C8`, object construction | Identify flags through reads and writes rather than guessing names |
| 3 | `func_80037010` in main | Recover RNG state and seed behavior for deterministic gameplay checks |

The initial small WSL project had 85 matching functions, including 63 adapted from the earlier project. That tree is now an archived diagnostic reference. The canonical migration integrated the older complete mixed source/assembly tree and retained the additional verified game functions, including three list helpers the old splitter had hidden inside a data fragment. Current per-unit counts and fresh-build evidence are in `config/us/progress.json`; the source inventory separates ordinary C, empty bodies, C++ aliases, assisted source, documented source hacks, and SDK.

The old loader draft's one-instruction scheduling difference was resolved by the canonical slot compiler. Earlier drafts remain historical analysis, not an indication that the current loader is unmatched.

Two inherited movie implementations were removed from recovered source: `func_80064514` read an uninitialized temporary to influence allocation, and `func_800648D0` used a dead signed increment/decrement. Their original symbolized assembly keeps movie byte-identical. Clean defined C drafts and actual mismatches are retained in `analysis/us/movie/sol_attempts.json`; these functions remain unfinished game recovery.

## Small globals, rendering and call interfaces

The startup GP value is represented by the real data symbol `D_80064128`. Clean counter, renderer-pointer and cursor helpers use GP-relative references to existing four-byte globals. For selected translation units, the build supplies non-emitting `.sdata`/`.size` metadata before maspsx so it can recognize those external small symbols. Their definitions remain in resident data; the resulting source objects have empty `.sdata` sections. Classification is per translation unit: a symbol accessed through GP in one slot can still need absolute addressing in another.

`include/render_context.h` models two SDK `DISPENV` structures at offsets `0` and `0x14`, followed by two SDK `DRAWENV` structures at `0x28` and `0x84`. Display pointers are at `0xE0/0xE4`, drawing pointers at `0xE8/0xEC`, an optional display override at `0xF0`, and the active buffer index at `0xF4`. Unknown state words remain named by offset. The color helper writes `DRAWENV.r0/g0/b0`; screen helpers write `DISPENV.screen`. Aggregate `RECT` copies naturally reproduce the original unaligned load/store sequences using the SDK layout, without forced packing. The typed helpers passed the complete main gate; the larger initialization and synchronization drafts remain unmatched assembly.

Five matched wrappers now explicitly declare and forward the incoming object/list arguments their assembly already used. This preserves original instructions while removing reliance on undeclared arguments surviving in registers. List and callback-table field names remain provisional where their gameplay meaning is unknown.

`func_8001F6F8` and `func_8001F790` are internal fifth-case targets of `jtbl_80010400` and `jtbl_80010418`. Their parent functions initialize `a2`, which the targets consume. The manifest marks them `internal` and `config/us/boundary_overrides.json` protects the correction during regeneration. The apparent entry at `0x8001F800` is also corrected: it is the return delay slot of `func_8001F79C`; the next actual entry is `func_8001F804`. The renamed `10004.c` slot contains its matching typed RECT clipping. Display clearing at `func_8001F79C` matches under PsyQ 4.6. Other inherited split boundaries still require review.

The accepted `func_800333CC` validates the 16-byte VFS2 header and calls an SDK disc-position conversion candidate (`CdPosToInt` or `DsPosToInt`). It stores the resulting LBA plus one as the directory sector and the LBA plus the header's data offset as the payload sector, truncates the entry count to the mount's 16-bit field, and returns the full count times 32. The old `func_80033458` fragment is its internal error callback/epilogue, now preserved by a non-emitting alias. The callback's existing error string at `D_8001940C` is symbolized without changing its bytes. The natural C and allocator-callback setter match under PsyQ 4.6 `-G8`. The SDK conversion name and the remaining runtime layout are provisional.

## Formatting, handles and RNG

Fourteen additional formatting/handle helpers in `src/engine/27000.c` now match. The formatting context has a cursor, flags, field width and conversion code; recovered helpers append bytes, pad strings, convert unsigned octal/hex values and reverse the output span. The fixed-width hex helper reads its eight digits before writing them. The signed-decimal helper remains assembly pending a defined representation of its edge cases.

Handle records are 16 bytes: next/previous links, a value pointer and a tag containing a 12-bit record index plus a 20-bit generation. Allocation moves a record from the free list to the active list and increments the generation. Lookup/release validate the index and full tag. The free-list counter crosses the old sector boundary: `func_80036FE0` is the complete 48-byte function, and `func_80037000` is its internal continuation alias. The constructor remains assembly because its reads of freshly allocated tag bits need an initialization-contract review.

The RNG state contains 624 unsigned words followed by a signed index. `func_800371E8` resets the index to 625; `func_800371F8` seeds the state with the unsigned recurrence `69069u * previous` and stores the completed loop index, 624. Both are matching C. `func_80037010` remains assembly after natural generator drafts failed to match; neither experimental assembler settings nor unverified C were retained. The adjacent MD5 finalization and transform code also remains unfinished assembly.

The last Sol audit found that allocator query `func_8002B2DC` must return the signed scalar from `func_8003A1D4`: a caller immediately uses that value. The related total query now explicitly forwards its scalar result too, although no direct caller was found. Pointer interfaces were corrected within the audited source family. `func_80026BE4` now uses unsigned subtraction for wrapping negation, avoiding signed overflow at `INT_MIN` while retaining identical instructions. The affected private slots and complete resident executable pass. Older cross-module prototypes still need systematic review.

## Embedded zlib runtime

Seven additional routines match the [original zlib 1.1.3 source](https://zlib.net/fossils/zlib-1.1.3.tar.gz): `inflateEnd`, `inflateReset`, `inflateSetDictionary`, `inflateSyncPoint`, `inflate_blocks_reset`, `inflate_blocks_free`, and `inflate_blocks_sync_point`. `include/zlib_113.h` models the target's 56-byte stream, 24-byte inflate state and 64-byte block state, including typed allocation/release callbacks. The existing initialization wrapper also uses these types. These identified non-SDK runtime functions are recovered with the original license notice and marked adaptations.

PsyQ 4.6 `-O3` reproduces the reset logic inlined inside `inflate_blocks_free`; The dictionary helper also matches after the return-contract correction described below. The integration exposed two build issues: per-file flags were recorded but omitted from the compiler command, and this optimized compiler hoisted file-scope assembly before C. The build now applies those flags and preserves ordered assembly inclusion. The complete main build, all thirteen overlays, and the compiler-command regression check pass.

### Resumed recovery on 2026-10-08

The dictionary helper `func_8003C46C` now matches its complete 68-byte retail body. The copy routine's ignored return had been declared as a pointer; its `void` declaration, consistent with the zlib copy API and neighboring declarations, resolves the remaining register differences. All four source bodies in that slot retain their matches under the canonical PsyQ 4.6 `-O3` profile and the private Linux GCC 2.95.2 probe.

`include/game_heap.h` models the 12-byte block header and 16-byte heap state. Seven algorithms adapt the MIT-licensed ReGame Labs reference and match the USA instructions. The complete shrink/coalescing routine `func_8003A764` continues through `0x8003A830`; `func_8003A800` is its old sector-boundary alias. The following source slot starts at file offset `0x2B034`. `func_8003A000` is the common epilogue of the preceding `func_80039FB0`, retained as an internal symbol. Shared heap declarations expose signed query/error returns, byte sizes and allocation pointers.

`include/game_handles.h` shares the recovered node/pool types and APIs with their manager and resource wrappers. `func_8002BDC8` explicitly returns the pointer its gameplay/stage callers consume, and `func_8003A114` returns the handle its caller stores at object offset eight. Allocation wrappers `func_8002BE14` and `func_8002BD88` also return their pointer results explicitly. A gameplay constructor's fifth parameter is a vector pointer: its callee reads three signed words at offsets zero, four and eight. These contract corrections preserve original instructions.

The complete gate at 15:59 UTC verifies all fourteen outputs and source-object placements; `analysis/checkpoints/20261008T160008Z` preserves all 3,328 recorded build inputs. It adds 105 ordinary C bodies since the previous day's final checkpoint. The provisional count is 1,792/3,566 unconstrained functions (50.2524%), with 249 assisted source bodies, 1,525 function assembly placeholders, 317 `asm` and 56 `data` entries still awaiting inventory review. The RNG generator, MD5 finalizer and first-fit allocation drafts still mismatch and retain their original assembly.

The final resource batch adds 26 matching bodies: seven manager routines, eight node/command helpers, six loader wrappers, and five gameplay constructors/effect helpers. `func_80039354` is a complete 48-byte signed-halfword list setter whose earlier `asm` classification was corrected. Shared `game_resources.h` defines the 32-byte node and consistent caller declarations; `resource_loader.h` defines allocation callbacks and pointer-returning loaders. The stage09 constructor explicitly forwards its required initialization value, and resource lookup uses unsigned target-address arithmetic before its null guard. All affected private probes and the complete linked gate pass. Additional false splits in the remaining manager/loader assembly are documented in the attempt/audit ledgers; their reconstruction remains unfinished.

### Parallel batch on 2026-10-08

Three Sol medium workers concurrently handled distinct gameplay, title and stage source files while the parent recovered the complete file loader `func_80027D70` and TIM upload wrappers `func_80027AB0`/`func_80027B20`. Loader boundary review joined five continuation labels to their parents and identified `func_80027DD4` as the loader's return delay slot; the next real function begins at `func_80027DD8`. All reconstructed assembly ranges were checked against the held retail instructions. `game_effects.h` shares pointer arguments and return types between an effect constructor, its base and direct callers; the downstream inherited word-based interface remains under review.

The title C switches generated seven- and six-entry jump tables. Their private instruction comparisons passed, but appending these tables after the existing data shifted title text by 52 bytes. The existing per-table section mechanism now places the generated tables at `0x800648B8` and `0x800650FC`, and their linked entries match retail. This preserves the current fixed layout; movable data remains a later milestone. Four title, four gameplay and three resident bodies passed the complete gate. The seven stage attempts were unsuccessful and retain their original assembly.

The fresh fourteen-unit byte and symbol-placement gate passed at 16:23 UTC; all 40 tests pass. Checkpoint `analysis/checkpoints/20261008T162331Z` copied and hash checked all 3,330 recorded inputs. The provisional inventory is 1,803/3,569 unconstrained source functions (50.5184%), 249 assisted bodies and 1,517 function assembly placeholders, with 309 other assembly entries, 56 data entries and 16 internal symbols. PsyQ remains symbolized assembly and excluded from C progress. Integration evidence is in `analysis/us/parallel_batch_integration.json`.

### Second parallel wave

The complete resource loader `func_80027CB4`, queued-read wrapper `func_80027DD8` and completion callback `func_80027E6C` now match. The loaders compare against the held four-byte `ZP00` tag at `D_800641D4`, allocate the uncompressed header size or raw file size, decompress/copy, then release the temporary packed buffer. VFS dispatch passes buffer, byte count, pathname pointer and user pointer to the completion callback. `resource_loader.h` shares that callback type with registration setters and the loader. The result slot is cleared after queue submission exactly as in retail. `func_80028004` now explicitly forwards both destination and compressed input to its decompressor; previously the second argument relied on an undeclared argument surviving in a register.

PsyQ 4.6 `-G8` and aspsx 2.86, with non-emitting small-data metadata, reproduce the tag's GP-relative address. `func_8002802C` uses the actual symbol and no longer pins `$gp`. The later two global-pointer routines keep their established `-G0` behaviour in `src/engine/18E84.c`. Three stage06 constructors similarly occupy isolated PsyQ 4.6 ranges while adjacent source retains its proven shipped profile. These splits establish working matching profiles; original compilation-unit boundaries remain an inference. Signed subtractions in the newly recovered gameplay/title helpers use explicit unsigned wrapping before signed interpretation, preserving the target instructions.

The second wave adds eleven matching bodies and converts one constrained helper to ordinary C. The complete fourteen-unit gate passed at 16:45 UTC, and all 40 tests pass. `analysis/checkpoints/20261008T164641Z` copied and hash checked 3,337 inputs. The provisional count is 1,815/3,569 unconstrained functions (50.8546%), with 248 assisted bodies and 1,506 function assembly placeholders. The two parallel waves add 22 newly recovered bodies plus the constraint removal. Integration evidence is in `analysis/us/parallel_wave2_integration.json`; failed TIM traversal and `func_80027F0C` candidates remain readable drafts with assembly fallback.

### Third parallel wave

Sixteen additional natural C bodies passed the complete fourteen-unit byte and placement gate at 17:11 UTC, with all 40 tests passing. Checkpoint `analysis/checkpoints/20261008T171201Z` copied and hash checked 3,339 inputs. Coverage is 1,831/3,570 unconstrained functions (51.2885%), with 248 assisted bodies and 1,491 function assembly placeholders. The denominator grows because `func_80027FB0` is a genuine packed-buffer loader previously classified as data; its full 84-byte body includes the old `func_80028000` return delay slot. The next source now starts at file offset `0x18804`.

Stage07 has four new matches under ESA 4.5, while its neighboring wrapper retains the shipped compiler in a separate range. That wrapper and gameplay's `func_800774EC` now explicitly forward their arguments, preserving retail instructions. The latter takes a signed delta, which its callee adds and clamps. A proposed caller only matched when an unused extra argument forced register selection; its proper two-argument draft differs in 15 words, so it remains assembly. The gameplay switch's 21-word table occupies retail `jtbl_8006520C`, and full linking verifies its pointers. Helper audits establish a 16-byte by-value vector ABI and confirm stack configuration/vector data is consumed or copied synchronously. New vector offsets use unsigned wrapping, and a squared total uses signed 64-bit multiplication before conversion to a target word. Evidence and failed drafts are in `analysis/us/parallel_wave3_integration.json` and per-module attempt ledgers.

### Fourth parallel wave

Seventeen more bodies passed the complete fourteen-unit byte and placement gate at 17:30 UTC, with all 40 tests passing. Checkpoint `analysis/checkpoints/20261008T173202Z` copied and hash checked 3,346 inputs. Coverage is 1,848/3,571 unconstrained functions (51.7502%), with 248 assisted bodies and 1,475 function assembly placeholders. This wave adds four resident, nine gameplay and four stage00 bodies. Combined with the preceding wave, it adds 33 verified bodies.

The complete 248-byte control update matches with direct-field C, unsigned counter wrapping and low-word signed products. Its two continuation labels remain at their retail offsets. Two GPU packet helpers initialize the original length/opcode bytes and return the prior cursor while advancing its 32-bit address; the control global getter also matches. Reviewing the neighboring `func_800275FC` found a 604-byte assembly state machine wrongly classified as data and split at `func_80027800`; its prologue, shared live registers and return are now one verified assembly range, with the next source starting at file offset `0x18058`.

Stage00's four new bodies require PsyQ 4.6; three older shipped-profile leaves retain isolated ranges. A shared `game_random.h` corrects the object RNG wrapper's return and owner-pointer declarations across game/stage callers; the generator remains assembly. Audits confirm a gameplay constructor's third argument is a separate RNG context, bounded table indices are 0..2, and local vectors are copied or consumed before return. Coordinate/address calculations use defined target-word wrapping. Existing switch tables and all previous source matches remain intact. Near C++ drafts with two or more register differences retain assembly. Evidence is in `analysis/us/parallel_wave4_integration.json` and per-module attempt ledgers.

### Fifth parallel wave

The fifth parallel wave passed the complete gate at 18:27 UTC and all 41 tests. Checkpoint `analysis/checkpoints/20261008T182817Z` preserves 3,349 recorded inputs. Thirteen additional natural C bodies match: eight resident, two gameplay, one title and two stage05 functions. The complete 604-byte controller initialization state machine retains its internal label at +0x204 and passes only the verified two arguments to its SDK alignment call. A shared input header corrects getter returns and numeric repeat parameters while preserving retail bytes. Stage05 isolates a PsyQ 4.6 constructor range between shipped-profile ranges. Auditing title 7A54C proves pointer-table data, so its provisional function entry is reclassified and all 61 words, including trailing zeros, retain exact placement; resource pointers are symbolized. Coverage is 1,861/3,570 unconstrained functions (52.1289%), with 248 assisted bodies and 1,461 function assembly placeholders. The private probe now selects the active complete assembly boundary instead of historical sector fragments, covered by a regression test. Integration and contract evidence are in `analysis/us/parallel_wave5_integration.json`.

The nominal `func_80027064` still uses assembly: its natural copy draft differs in register allocation and its incidental source-entry return has no caller-proven meaning. The wave-six audit confirms stage05 `D6EBC` is an existing independent 72-byte function with a manifest row. Its missing complete assembly reference caused the private sizing diagnostic; that reference is now restored and its existing C body still matches.

## Practical lessons for this decompilation

1. **Verify revision and code inputs first.** Disc filenames are insufficient; hashes and SYSTEM.CNF establish which binary is being matched.
2. **Inspect code boundaries manually.** Splat's automatic EXE probe mistook table data near the beginning for text in this image. The real resident text begins much later at `0x8001AE18`.
3. **Treat overlays as first-class code units.** An EXE-only progress number would omit most gameplay and every stage module here.
4. **Establish an assembly rebuild before matching C.** All fourteen units now provide a reproducible baseline. Data copied from the original and instruction-preserving assembly are necessary scaffolding, not C recovery.
5. **Test compiler assumptions on representative functions.** Small constructors and list loops match the current GCC candidate. Complex methods, small globals, and GTE code still need investigation; do not infer a complete toolchain match from trivial getters.
6. **Model target behavior.** PS1 pointers and integers are 32-bit; MIPS has load and branch delay slots; GTE instructions need PS1-aware decoding. Host C layouts and modern optimizer output cannot substitute for this evidence.
7. **Use automated drafts to accelerate analysis.** Unknown struct fields, virtual calls, jump tables, BIOS trampolines, and GTE operations still require manual work. An m2c exit of zero does not mean compilable, correct, or matching C.
8. **Measure honest progress.** Rebuilding an entire binary using original data and assembly does not mean the whole game has been decompiled. The older project's 1,814 source representations included SDK C, inline assembly, pinned registers and empty bodies. Canonical progress excludes SDK and identifies source constraints; the provisional function denominator still needs split review.

Remaining scope includes thousands of function reconstructions, full object types, asset/runtime relationships, SDK and handwritten assembly decisions, cross-overlay interfaces, and runtime validation. Repacked disc output and any PC-port work are separate later milestones.

## Wave six and DW2 workflow adoption

Four additional natural C bodies passed the complete fourteen-unit gate: gameplay 9E8A4/9EACC and stage01 D4A20/D535C. Shared list declarations now follow the actual C++ ABI, and the stage01 resource call uses its verified three-argument contract. The controller-update and other unmatched drafts retain assembly. Checkpoint `analysis/checkpoints/20261008T191229Z` records 1,865/3,570 unconstrained source functions (52.2409%) and 3353 copied/hash-checked inputs.

The DW2 workflow adds focused briefs, a searchable code-generation journal, bounded hypothesis probes, isolated snapshots and scorer calibration. Three known matches score zero, deliberate code changes score above zero, and separate table-byte checks catch a corruption ignored by the code scorer. Five single-function compiler isolations are explicitly flagged for original-object provenance review; exact bytes do not settle that review. See `PLAN.md`, `docs/DW2_WORKFLOW.md`, `config/us/compiler_profiles.json` and `analysis/us/workflow/permuter_calibration/report.json`.

## Continued recovery: waves seven and eight (2026-10-08 UTC)

These two waves add eighteen unconstrained source bodies: seventeen resident/game helpers and the separately attributed zlib 1.1.3 version accessor. The canonical snapshot is **1,883/3,570 functions (52.7451% by function count)**, comprising 1,800 ordinary C bodies, 50 empty bodies and 33 C++ implementations. Another 248 bodies retain assembly/register constraints and 1,439 game functions remain assembly. All 655 Sony SDK entries stay symbolized assembly and excluded. Checkpoint `analysis/checkpoints/20261008T202711Z` preserves 3,356 copied/hash-checked build inputs; every complete executable/overlay byte and source placement agrees with retail, and all 72 tooling tests pass.

The recovered rectangle, threshold, effect, matrix and deferred-list helpers use existing reproduction profiles. Shared VFS and deferred-object layouts correct incompatible declarations. Auditing deferred callbacks exposed real arguments omitted by earlier matching source; their forwarding and pointer returns are repaired in coherent linked transactions. BF34 queues objects for later cleanup rather than freeing them immediately. A known matrix field offset alone did not prove the existing Component class was the correct owner; separate allocation/callee evidence justified a distinct minimal view. zlib source/license and retail copyright strings distinguish its C routines from Sony SDK and game-authored logic.

The CPU search for CC240 tried 200 permutations, retained one differing instruction/score 10 and left assembly intact. Stage09 and other failed candidates preserve readable drafts and measured attempt history. Source percentage remains provisional: original objects/classes, remaining legacy semantics and interfaces, non-function inventory, data/relocations and modified/runtime builds are outstanding. No original-object compiler profile is certified. Detailed acceptance: [wave seven](../analysis/us/parallel_wave7_integration.json), [wave eight](../analysis/us/parallel_wave8_integration.json).
