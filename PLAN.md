# Digimon Rumble Arena: session plan

## Disc-based public setup

The public Windows build now starts from the supported USA disc image. `setup_toolchain.py` installs 18 exact hash-pinned public tools; `setup_game.py` extracts and verifies all 14 retail targets; `generate_game.py` reconstructs 3,035 reviewed assembly/asset inputs using `config/us/split/` metadata. It does not rewrite recovered source or compiler output. The historical splat configurations are research inputs, not the authoritative public generation recipe.

An isolated source-only checkout and this project both pass all fourteen complete byte/placement gates and strict allocated-section and public-symbol comparisons. All 92 tests pass. Three automatic objcopy path labels change only by build folder, with identical metadata. Coverage remains 2,179/3,699; decompilation remains paused. See `docs/verification/disc_build.json`, `docs/TOOLCHAIN_SETUP.md` and `docs/SPLIT_GENERATION.md`. Future retained assembly ownership changes must update the corresponding recipe before the complete linked gate. Latest verified checkpoint: `analysis/checkpoints/20261011T090424Z`, with 3,517 hash-checked inputs.

## Separate US project checkpoint

This repository imports the accepted US work into the JP-style directory conventions. A fresh build in this folder passed all fourteen complete binary and placement gates; all 88 tests passed. Coverage remains 2,179/3,699 (58.9078%). The local checkpoint is `analysis/checkpoints/20261011T073051Z`. See `docs/MIGRATION.md` and `docs/verification/migration.json` for import provenance and validation.

The decompilation goal remains paused. The older session notes below describe the originating project. Private drafts and scratch evidence mentioned there remain in that project and are not accepted source in this repository.

## Current state

USA `SLUS_014.04`; executable plus thirteen overlays. All 14 complete byte and placement gates are current. Verified unconstrained source **2,179/3,699 (58.9078%)**: 2,095 ordinary C bodies, 50 empty bodies and 34 native C++ aliases; 215 assisted bodies, 1,305 game ASM functions, and 655 excluded SDK entries. Original object/compiler provenance, remaining semantic/ABI/data audits and modified runtime integrity remain open.

Latest checkpoint `analysis/checkpoints/20261010T155411Z`: **3500 inputs** copied and hash-checked. The1408B wrapped inflate3AA78 and real56B emitted jump table pass a fresh full14 gate, strict data/public audit and selected private+0x100 link. Prior batch recovered seven bodies through ten gates with88 tests. Details: `analysis/us/jp_inflate_wrapped_integration.json` and `analysis/us/jp_sync_cd_integration.json`. Cumulative JP-informed resume:109 recovered bodies minus one retained-ASM correction, five constraint removals and76 full14 gates. The100% goal is paused at the user's request; resume from this verified checkpoint.

## Phases

1. Verified executable/overlay baseline and retained older matching source â€” done.
2. SDK assembly separation and source-quality accounting â€” done; ambiguous boundaries remain under review.
3. **CURRENT: recover game source in families, with ABI and original-object compiler review.**
4. Recover typed game data, cross-overlay contracts and relocations.
5. Validate modified layouts and runtime behavior; audit completion inventory.

## One next action

Review and integrate the complete260B CD0/DA4 frame boundary with the zero-credit truthful SDK memmove shared interface repair, then notify the CD worker to probe natural complete CD0. Frozen packets and independent boundary review are ready; canonical18058 includes the accepted allocator API repair. GPT-6.1 Sol medium worker continues exact private fast decoderCDA8 under a proposed uniformPsyQ46 profile with truthful8B huft types and2E000 declaration closure. Root owns canonical headers, profiles, data, linker and full14 gates. Wrapped inflateAA78 is accepted for actual33498/w15 successful initialized application streams; raw-nowrap remains held because reset reads an uninitialized checksum before its output is discarded. Data split now preserves every original alignment directive through a second boundary at physically aligned19F88. Fourteen internal NOTYPE labels, owned table pointers and HI/LO move correctly in a real private+0x100 link; this does not certify arbitrary modified/native runtime behavior.

Private negatives remain held: main10800 reset20240 delay-slot mismatch/modelDestroy native-class closure; mainD800 winner-track1D750 three scheduling negatives and unresolved full character domain; st09D445C five register-allocation negatives; st09D6818 vertex padding read by retained GTE helper. No profile changes, synthetic initialization or leaf-only ABI shortcuts are justified by these failures. Inflate requires valid actual output capacity;33498 advertising0x7fffffff does not prove that capacity. Malformed assets, resumed OOM, complete corpus-size certification and modified-runtime integrity remain separate open requirements.

Accepted this continuation: primitive swap26C38, SEP setter1B740, font getter31FA0 with actual four-byte pointer ownership, directory lookup33A20, stepper2D260/2D298, printer328CC/32900, complete queue349A8, sprite cleanup2D830 and CD dispatcher346A4. Renew-handle interfaces were repaired with no new source credit. Shared printer and sprite cleanup ABIs now cover real overlay consumers. Queue349F4 is an internal relative label; complete linked metadata stays identical. PsyQ remains symbolized assembly.

Held animator30584/308DC needs empty-clip closure; inverse24CA8 reads uninitialized matrix padding; handle36C64 payload initialization remains unproved. XA35C10/35C68 nonvolatile drafts do not preserve asynchronous writes. PrimitiveDD84/DD5C/DDC4 retain global-address CSE mismatches; negative probes are saved. Logger336A0 has incompatible callbacks. GameADA50 currently has uncleared owner flags; no credit unless initialization closes. Existing text-constructor flags and older signed position/layout debt remain separate audits.

## Resume instructions

Read `AGENTS.md` and `docs/CODEGEN_MODEL.md`, then search only the relevant entries in `docs/DECOMPILATION_LEARNINGS.md`. Use `tools/decomp_session.py` for BRIEF, m2c, a hypothesis and durable RESULT; cap manual cycles at ten recorded probes. Use `tools/difficult_functions` to requeue by a new finding. GPT-6.1 Sol medium workers get isolated verified snapshots and disjoint source ownership; the parent owns integration, shared interfaces/profiles and full gates. Source matching never requires SDK C, target-guided assembly edits, register pins, fake arguments or undefined behavior.

## Session log (newest first; UTC)

- **2026-10-10T15:54Z: wrapped inflate checkpoint.** One1408B recovered body, no inventory change, one full14 gate, genuine56B table ownership and14NOTYPE labels. Data alignment failure corrected by additionalphysicalsectionboundary; strictdata/public andselected+0x100link pass. Natural2179/3699. Checkpoint `analysis/checkpoints/20261010T155411Z`,3500 inputs. Details `analysis/us/jp_inflate_wrapped_integration.json`. Raw-nowrap remains held.

- **2026-10-10T15:44Z: sync/thread/CD checkpoint.** Seven recovered bodies, one inventory addition, ten full14 gates,88 tests. Natural2178/3699. Checkpoint `analysis/checkpoints/20261010T154401Z`,3500 inputs. Actual allocator callback/shared free APIs repaired; selected GP data+alias move proved privately. AA78 raw-nowrap and emittedtable integration pending. Details `analysis/us/jp_sync_cd_integration.json`.

- **2026-10-10T15:01Z: thread boundary checkpoint.** Complete112B frame joins80+32B fragments, inventory+1/source0, one full14 gate, honest sizes/internal relative label and obsolete absolute local-label fallback removal. Natural2171/3698. Checkpoint `analysis/checkpoints/20261010T150132Z`,3499 inputs. Details `analysis/us/jp_thread_boundary_integration.json`.

- **2026-10-10T14:57Z: dynamic/thread/init checkpoint.** Three recovered bodies, no inventory changes, three full14 gates,84 tests. Natural2171/3697. Checkpoint `analysis/checkpoints/20261010T145727Z`,3499 inputs. Details `analysis/us/jp_dynamic_thread_init_integration.json`.

- **2026-10-10T14:38Z: loading/inflate/constraints checkpoint.** Three recovered bodies, three assisted-to-natural conversions, three retained constructor references symbolized, no inventory changes, five full14 gates,84 tests. Natural2168/3697. Checkpoint `analysis/checkpoints/20261010T143841Z`, 3498 inputs. Details `analysis/us/jp_loading_inflate_integration.json`.

- **2026-10-10T14:19Z: camera/stage/loading checkpoint.** Five recovered bodies, three table pointers symbolized, no inventory changes, five full14 gates, 84 tests. Natural2162/3697. Checkpoint `analysis/checkpoints/20261010T141908Z`, 3498 inputs. Details `analysis/us/jp_camera_stage_integration.json`.

- **2026-10-10T14:00Z: completed storage/flags batch.** 11 recovered bodies, one inventory correction, 11 full14 gates, 84 tests. Natural2157/3697. Checkpoint `analysis/checkpoints/20261010T140054Z`, 3496 inputs. Details `analysis/us/jp_storage_flags_integration.json`.


- **2026-10-10T13:27Z: storage/flags checkpoint.**6 recovered bodies,0 inventory change,6 full14 gates,84 tests. Natural2152/3696. Checkpoint `analysis/checkpoints/20261010T132704Z`,3494 inputs. Details `analysis/us/jp_storage_flags_integration.json`.


- **2026-10-10T12:46Z: CD/heap/plane/overlay checkpoint.**8 recovered bodies minus1 truthful-ABI retained-ASM correction,1 inventory correction,7 full14 gates,84 tests. Natural2146/3696. Checkpoint `analysis/checkpoints/20261010T124631Z`,3490 inputs. Details `analysis/us/jp_cd_heap_overlay_integration.json`.

- **2026-10-10T12:07Z: JP interfaces/display/fade checkpoint.**8 bodies,1 reviewed inventory correction,7 full14 gates,84 tests. Natural2139/3695. Checkpoint `analysis/checkpoints/20261010T120705Z`,3485 inputs. Details `analysis/us/jp_interfaces_integration.json`.


- **2026-10-10T11:43Z: TMD ownership/source and console checkpoint.**16 recovered bodies,13 inventory correction,7 full14 gates,84 tests. Natural2131/3694. Checkpoint `analysis/checkpoints/20261010T114527Z`,3481 inputs. Details `analysis/us/jp_tmd_console_integration.json`.

- **2026-10-10T11:43Z: TMD ownership/source and console checkpoint.**16 recovered bodies,13 inventory correction,7 full14 gates,84 tests. Natural2131/3694. Checkpoint `analysis/checkpoints/20261010T114306Z`,3481 inputs. Details `analysis/us/jp_tmd_console_integration.json`.

- **2026-10-10T11:30Z: complete NF3 recovery.**1 new natural body,1 reviewed inventory function,2 full14 gates. Natural2116/3682. Checkpoint `analysis/checkpoints/20261010T112941Z`,3470 inputs. `analysis/us/jp_nf3_integration.json`.

- **2026-10-10T11:16Z: parallel JP math/drawing/bounds checkpoint.**13 bodies,0 inventory change, callback/shared API repairs;7 full14 gates;84 tooling tests. Natural2115/3681. Checkpoint `analysis/checkpoints/20261010T111607Z` copies/hashchecks3470inputs. Details `analysis/us/jp_parallel_integration.json`.

- **2026-10-10T10:44Z: JP components/camera/buttons checkpoint.**9 bodies and1 existing arithmetic repair,0 inventory change;4 full14 gates;84 tooling tests. Natural2102/3681. Checkpoint `analysis/checkpoints/20261010T104413Z` copies/hashchecks3469 inputs. Details `analysis/us/jp_next_integration.json`.

- **2026-10-10T09:54Z: JP follow-up checkpoint.** Six math bodies and one RNG body accepted in2 further full14 gates; cumulative25 recovered bodies and2 constraint removals. RNG shared API covers18 consumer slots and owns its real8-byte GP table.84 tooling tests; checkpoint `analysis/checkpoints/20261010T095425Z`,3466 inputs. Details `analysis/us/jp_followups_integration.json`.

- **2026-10-10T09:33Z: JP-reference checkpoint.** 18 recovered bodies,2 constraint removals,0 inventory change;5 full14 gates and84 tooling tests; checkpoint `analysis/checkpoints/20261010T093257Z`. Details `analysis/us/jp_resume_integration.json`.

- **2026-10-09T13:43:03.593694+00:00: wrapup_waves96_100 checkpoint.** 2 recovered bodies,0 constraint removals,5 inventory change;5 full14 gates; checkpoint `analysis/checkpoints/20261009T134248Z`. Details `analysis/us/wrapup_waves96_100_integration.json`.

- **2026-10-09T13:29:32.060431+00:00: parallel_waves96_98 checkpoint.** 1 recovered bodies,0 constraint removals,0 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T132917Z`. Details `analysis/us/parallel_waves96_98_integration.json`.

- **2026-10-09T13:06:57.050059+00:00: parallel_waves92_95 checkpoint.** 2 recovered bodies,1 constraint removals,0 inventory change;4 full14 gates; checkpoint `analysis/checkpoints/20261009T130642Z`. Details `analysis/us/parallel_waves92_95_integration.json`.

- **2026-10-09T13:01:06.949872+00:00: parallel_waves92_93 checkpoint.** 1 recovered bodies,1 constraint removals,0 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T130052Z`. Details `analysis/us/parallel_waves92_93_integration.json`.

- **2026-10-09T12:43:53.946536+00:00: parallel_waves88_91 checkpoint.** 0 recovered bodies,0 constraint removals,0 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T124340Z`. Details `analysis/us/parallel_waves88_91_integration.json`.

- **2026-10-09T12:36:20.271844+00:00: wave88_pair_apis checkpoint.** 0 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T123605Z`. Details `analysis/us/wave88_pair_apis_integration.json`.

- **2026-10-09T12:23:49.925695+00:00: parallel_waves82_86 checkpoint.** 1 recovered bodies,0 constraint removals,2 inventory change;4 full14 gates; checkpoint `analysis/checkpoints/20261009T122335Z`. Details `analysis/us/parallel_waves82_86_integration.json`.

- **2026-10-09T12:10:40.658570+00:00: parallel_waves79_81 checkpoint.** 1 recovered bodies,2 constraint removals,1 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T121027Z`. Details `analysis/us/parallel_waves79_81_integration.json`.

- **2026-10-09T11:48:34.685494+00:00: wave78_dialog_factory checkpoint.** 1 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T114821Z`. Details `analysis/us/wave78_dialog_factory_integration.json`.

- **2026-10-09T11:44:27.162744+00:00: parallel_waves76_77 checkpoint.** 0 recovered bodies,0 constraint removals,4 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T114413Z`. Details `analysis/us/parallel_waves76_77_integration.json`.

- **2026-10-09T11:33:47.307488+00:00: parallel_waves73_74 checkpoint.** 1 recovered bodies,0 constraint removals,1 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T113332Z`. Details `analysis/us/parallel_waves73_74_integration.json`.

- **2026-10-09T11:16:20.456365+00:00: parallel_waves70_72 checkpoint.** 2 recovered bodies,0 constraint removals,0 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T111606Z`. Details `analysis/us/parallel_waves70_72_integration.json`.

- **2026-10-09T11:06:23.415506+00:00: wave69_renderer_frame checkpoint.** 0 recovered bodies,0 constraint removals,1 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T110608Z`. Details `analysis/us/wave69_renderer_frame_integration.json`.

- **2026-10-09T11:02:52.557215+00:00: wave68_node_factory checkpoint.** 1 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T110238Z`. Details `analysis/us/wave68_node_factory_integration.json`.

- **2026-10-09T10:58:37.624971+00:00: parallel_waves65_67 checkpoint.** 3 recovered bodies,0 constraint removals,0 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T105823Z`. Details `analysis/us/parallel_waves65_67_integration.json`.

- **2026-10-09T10:06:47.553963+00:00: wave63_packet_count checkpoint.** 1 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T100633Z`. Details `analysis/us/wave63_packet_count_integration.json`.

- **2026-10-09T10:04:21.711208+00:00: wave62_model_refresh checkpoint.** 0 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T100407Z`. Details `analysis/us/wave62_model_refresh_integration.json`.

- **2026-10-09T10:00:55.090200+00:00: wave62_vfs_frame checkpoint.** 0 recovered bodies,0 constraint removals,1 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T100040Z`. Details `analysis/us/wave62_vfs_frame_integration.json`.

- **2026-10-09T09:57:04.642969+00:00: parallel_waves57_61 checkpoint.** 4 recovered bodies,0 constraint removals,1 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T095648Z`. Details `analysis/us/parallel_waves57_61_integration.json`.

- **2026-10-09T09:30:15.519159+00:00: wave54_game_constructors checkpoint.** 2 recovered bodies,0 constraint removals,0 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T093001Z`. Details `analysis/us/wave54_game_constructors_integration.json`.

- **2026-10-09T09:25:06.184550+00:00: wave56_text_helpers checkpoint.** 2 recovered bodies,0 constraint removals,8 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T092451Z`. Details `analysis/us/wave56_text_helpers_integration.json`.

- **2026-10-09T09:13:02.615888+00:00: parallel_waves52_55 checkpoint.** 1 recovered bodies,0 constraint removals,2 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T091248Z`. Details `analysis/us/parallel_waves52_55_integration.json`.

- **2026-10-09T09:00:00.406697+00:00: parallel_waves50_53 checkpoint.** 2 recovered bodies,1 constraint removals,3 inventory change;4 full14 gates; checkpoint `analysis/checkpoints/20261009T085946Z`. Details `analysis/us/parallel_waves50_53_integration.json`.

- **2026-10-09T08:41:58.779048+00:00: parallel_waves49_51 checkpoint.** 5 recovered bodies,1 constraint removals,0 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T084145Z`. Details `analysis/us/parallel_waves49_51_integration.json`.

- **2026-10-09T08:38:53.664844+00:00: parallel_waves49_50 checkpoint.** 5 recovered bodies,1 constraint removals,0 inventory change;2 full14 gates; checkpoint `analysis/checkpoints/20261009T083839Z`. Details `analysis/us/parallel_waves49_50_integration.json`.

- **2026-10-09T08:21:32.189878+00:00: wave48_complete_frame checkpoint.** 0 recovered bodies,0 constraint removals,1 inventory change;1 full14 gates; checkpoint `analysis/checkpoints/20261009T082117Z`. Details `analysis/us/wave48_complete_frame_integration.json`.

- **2026-10-09T08:12:41.104366+00:00: parallel_waves45_48 checkpoint.** 1 recovered bodies,0 constraint removals,8 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T081225Z`. Details `analysis/us/parallel_waves45_48_integration.json`.

- **2026-10-09T07:48:04.149067+00:00: parallel_waves44_46 checkpoint.** 3 recovered bodies,2 constraint removals,4 inventory change;4 full14 gates; checkpoint `analysis/checkpoints/20261009T074749Z`. Details `analysis/us/parallel_waves44_46_integration.json`.

- **2026-10-09T07:35:31.319030+00:00: parallel_waves41_45 checkpoint.** 3 recovered bodies,2 constraint removals,2 inventory change;6 full14 gates; checkpoint `analysis/checkpoints/20261009T073515Z`. Details `analysis/us/parallel_waves41_45_integration.json`.

- **2026-10-09T00:36:20.135954+00:00: parallel_waves40_43 checkpoint.** 1 recovered bodies,2 constraint removals,0 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261009T003606Z`. Details `analysis/us/parallel_waves40_43_integration.json`.

- **2026-10-09T00:29:32.241532+00:00: parallel_waves33_41 checkpoint.** 12 recovered bodies,10 constraint removals,1 inventory change;14 full14 gates; checkpoint `analysis/checkpoints/20261009T002919Z`. Details `analysis/us/parallel_waves33_41_integration.json`.

- **2026-10-08T23:55:33.050590+00:00: parallel_waves31_33_refined checkpoint.** 5 recovered bodies,0 constraint removals,1 inventory change;3 full14 gates; checkpoint `analysis/checkpoints/20261008T235519Z`. Details `analysis/us/parallel_waves31_33_refined_integration.json`.

- **2026-10-08T23:48 UTC: waves30â€“33 checkpoint.** Object toggle/factory and custom table-key comparator yieldthree fresh bodies; five renderer functions lose constraints with defined halfword/word arithmetic. Four primary-word-checked joined functions correct false sector entries. Four full14 gates pass; checkpoint `20261008T234851Z`, 3,415 inputs. The31A18 private draft remains withheld pending pointer-formation refinement.

- **2026-10-08T22:53 UTC: waves twenty-two through twenty-eight checkpoint.** Twelve bodies recover packet/task dispatch, RGB conversion, three gameplay factories/motion, four zlib helpers and a debug module constructor. Eight genuine entries increase reviewed inventory;30584/30628 are one476-byte routine. Five existing factory return contracts and optional overlay string are corrected without new credit. Shared task/base/module types and defined word arithmetic preserve old siblings. Nine full14 gates and76 tests pass; checkpoint `20261008T225343Z`, 3,385 copied inputs. Details: `analysis/us/parallel_waves22_28_integration.json`.
- **2026-10-08 22:23: waves seventeen through twenty-one checkpoint.** Scoped state, packet allocation, selection, module dispatch, iterator deletion, startup, VFS callbacks, MD5 packing/list insertion and five gameplay constructors yield22 net new source functions. Complete387E0 replaces a falsely credited38800 fragment; complete357DC replaces a sector split, and two MD5 helpers gain reviewed entries. Shared types repair pointer returns and real callback/destructor arguments. Whole20000 allocator compiler family changes with reproduction evidence only. Eleven complete14-unit gates and76 tests pass; checkpoint `20261008T222348Z`, 3,380 copied inputs. Details: `analysis/us/parallel_waves17_21_integration.json`.
- **2026-10-08 21:44: waves nine through sixteen checkpoint.** Forty-three new ordinary bodies cover renderer switches, list/tree and object wrappers, matrix setup, VFS, resource packet fields, slot state and gameplay destructors. Two BST entries and seventeen formerly hidden code entries increase the denominator by nineteen. Five resource accessors already existed at the old checkpoint and earn no new-body credit. Shared resource layout and promoted return/forwarded argument contracts are repaired; complete code bodies replace false sector fragments. Compiler-generated renderer tables and surrounding alignment are independently checked. The private relocation diagnostic now rejects a real local jump-over-NOP error; all 76 tests pass. Assisted-body attempts and unsuccessful CPU searches retain their original source/ASM. No compiler overrides added; original-object provenance remains unreviewed. Checkpoint `20261008T214417Z`, detailed acceptance `analysis/us/parallel_waves9_16_integration.json`.
- **2026-10-08: wave eight checkpoint.** Seven further bodies: two deferred-list helpers, four matrix-owner helpers in the native C++ profile and the independently licensed zlib 1.1.3 version accessor. BDF4 now forwards its node argument and pointer result; three gameplay wrappers and 7AFCC explicitly forward their real node, with compatible reviewed pointer interfaces. BF34 queues allocation in a deferred list; the prior immediate-release interpretation is corrected. Four successive full fourteen-unit gates and 72 tests pass. Checkpoint `20261008T202711Z` preserves 3,356 inputs. No compiler overrides were added. Worker drafts, measured attempts and library classification are preserved; class/object provenance and remaining legacy interfaces still require review. Details: `analysis/us/parallel_wave8_integration.json`.
- **2026-10-08 20:07: wave seven checkpoint.** Eleven ordinary C bodies: five rectangle helpers, a pointer accessor, a signed plane threshold, one gameplay effect and three VFS wrappers. Shared VFS state resolves incompatible declarations in three resident slots and types its verified callback/user fields; allocation/RNG contracts are corrected for the gameplay effect. Four successive fourteen-unit gates pass without new compiler overrides, and all 72 tests pass. Checkpoint `20261008T200759Z` preserves 3,354 build inputs. Worker failures and measured session counts are imported into the parent journal. The reviewed CC240 seed differs by one operand-order instruction; a calibrated two-job CPU search tried 200 permutations in 36.052 seconds without improving score 10. ASM is retained. The first-C-probe workflow lifecycle defect is repaired and regression tested. Details: `analysis/us/parallel_wave7_integration.json`.
- **2026-10-08 19:12: DW2 workflow adopted and checkpoint saved.** Added brief/attempt tools, ranked learning search, codegen journal/model, isolated worker snapshots, generated progress and difficult-function records. Scorer calibration: known 16/604/172-byte retail bodies score zero; register/opcode/branch mutations score above zero; independent table-byte check catches corruption ignored by the code scorer. The known controller body also matches through the new session wrapper. The real `workflow_smoke` snapshot generates m2c/briefs, searches its copied journal and independently reproduces the 604-byte match. Five single-function compiler ranges are flagged; zero original-object profiles are certified. All 71 tests pass (`analysis/us/workflow_adoption_tests.log`). The first two-job native CPU search tried 202 observed permutations in 34.7 seconds, retained score 5, and left canonical B0DC0 assembly intact (`analysis/us/workflow/permuter_batch/20261008T191154Z-35072/report.json`). No source commits were made; checkpoint `20261008T191229Z` preserves the work. Detailed workflow evidence: `analysis/us/workflow/adoption.json`.
- **2026-10-08 18:43: wave six full gate passed.** Two gameplay effects and two stage01 bodies added; shared list/resource ABI corrected. Existing 72-byte stage05 D6EBC lacked a complete private assembly sizing reference, which is restored. Unmatched controller update and near gameplay/stage drafts remain assembly. Details: `analysis/us/parallel_wave6_integration.json`.
- **2026-10-08 18:28: wave five checkpoint.** `20261008T182817Z`: 1,861/3,570 unconstrained functions, 3,349 copied/hash-checked inputs, 14 complete binaries, 41 tests. Controller initialization recovered, title pointer-table entry reclassified. Earlier dated evidence is in `docs/DECOMPILATION_PLAN.md` and `docs/findings.md`.

Full completion scope: [completion plan](docs/DECOMPILATION_PLAN.md). Workflow: [DW2 adaptation](docs/DW2_WORKFLOW.md).
