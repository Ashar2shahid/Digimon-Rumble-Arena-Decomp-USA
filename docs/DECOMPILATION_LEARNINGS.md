## Shared dispatchers need the smallest real object prefix

**Problem.** A private printer wrapper matched while its shared destructor cast every printer to a40B record. A raw registration scan found a real20B glyph printer and an unsigned color callback. Byte matching concealed both a storage-domain and callback-type conflict.

**Resolution.** Declare the genuine12Binitial subobject in both20B/40B records, type actual stack storage, and reconcile registered callback signatures across alltables/targets/callers. Repair constructors and downstream pointer/color reads coherently. A pointer initialized by a constructor does not establish initialization of untouched cursor or flags fields.

**Validation.** Six slots/133bodies preserve allocated data, runtime relocations and realpublic metadata; all14complete outputs and placements pass. Independent table/constructor/caller review closes the20B/40B domain. Oldtextflag initialization and unrelated signed positions stay explicit audit debt.

**Evidence.** [Parent printer review](../analysis/us/main/jp_printer_api/PARENT_REVIEW.md), [independent review](../analysis/us/main/jp_printer_api/independent_review/AUDIT.md), [complete gate](../analysis/us/wave9_gate_jp_printer_api.json).

---

## Initialized native bitfields can coexist with unspecified padding

**Problem.** A stepper constructor clears six one-bit fields on an uncleared heap allocation while preserving the other26bits. Modeling the allocation unit as a raw u32 makes an early whole-word C read indeterminate. Assuming cleared heap storage would conceal the problem.

**Resolution.** Primary writers/readers and the JP class establish six genuine u32bitfields with unnamed padding. Use a shared nativeC++ definition across actual consumers and read only initialized named members. This does not authorize reads of uninitialized matrix words or GPU tags. Real inlineu8 getters can preserve the source conversions independently of optimizer mask merging.

**Validation.** Two new leaves and all60existing source siblings match under unchanged nativeC++ settings; allocated object data, runtime relocations and public symbols equal baseline. All14complete outputs/placements pass. Constructor/caller review establishes the field lifetime. Other legacy layout debt, original-object provenance and modified runtime remain separate audits.

**Evidence.** [Parent stepper review](../analysis/us/main/jp_stepper_flags/PARENT_REVIEW.md), [frozen primary/caller audit](../analysis/us/main/jp_stepper_flags/frozen/AUDIT.md), [complete gate](../analysis/us/wave9_gate_jp_stepper_flags.json).

---

## Rounded stack space is not a declared object extent

**Problem.** A loading-screen initializer and caller were byte-exact with a20-byte local, but the custom draw callback reads a caption word at+14. Stack rounding happened to reserve24bytes; that does not give the20-byte C object an extra member.

**Resolution.** The actual loading base is20bytes, and this caller uses a genuine24-byte derived record containing the caption field. All four custom load paths initialize that field before drawing. Recover the derived container from its base-first-member pointer before reading its named member; do not form a byte-pointer read beyond the declared base subobject. Shared pointer/callback declarations must cover every current source consumer.

**Validation.** The rejected20-byte hypothesis is retained. The corrected initializer and dispatcher transactions preserve all allocated object bytes, runtime relocations and real public metadata across mainF000/game9DF4/game697BC, then pass all14 complete output gates. Existing assisted697BC constraints and unrelated packet-layout debt remain separate. Evidence: [initializer review](../analysis/us/main/jp_loading_init/PARENT_REVIEW.md), [dispatcher review](../analysis/us/main/jp_loading_update/PARENT_REVIEW.md).

---

# Decompilation learnings

This journal records concrete DRA USA observations. Examples are minimal illustrations of the recovered contract, not transcriptions of original source. “Exact” means exact under the named current build/probe conditions; it does not prove the original compiler/object provenance. See the [code-generation model](CODEGEN_MODEL.md) for the acceptance levels.

## Preserved argument registers can conceal false matching APIs

**Problem.** Existing game79B68 called3049C with one C argument, while retail passes its original a1 as the clip index. The existing3084C callback declaration similarly omitted the original node in a1, consumed by20430 as pose data. Matching bytes and incidental live registers did not establish truthful interfaces.

**Resolution.** Read the complete caller and callee, pass the real second argument explicitly, reconcile shared C/C++ declarations, and preserve the actual signed object adjustment through target unsigned addressing. All25 character MOP assets have33clips, covering the known query indices22..27. Existing79B68 pins remain assisted and gain no source credit.

**Evidence.** [Query parent review](../analysis/us/main/jp_animator_leaf/PARENT_REVIEW.md), [callback parent review](../analysis/us/main/jp_animator_callback/PARENT_REVIEW.md), [accepted seven gates](../analysis/us/jp_parallel_integration.json). Larger animation routines remain private because matching bytes do not resolve positive blending on zero-frame clips.

## A byte-written GPU tag needs initialized backing storage

**Problem.** Packet allocators write tag byte3, but retained SDK AddPrim reads all four bytes before masking the lower24bits. A narrow write alone would leave an indeterminate read in a direct C translation.

**Resolution.** Trace the actual arena's lifetime and initial image. This184320-byte arena lies inside the executable load, initially allzero; later packet reuse retains initialized representation. Typed game packet writes and opaque SDK calls preserve the real16/24-byte layouts without adding SDK C or stack padding reads.

**Evidence.** [Box review](../analysis/us/main/jp_box/PARENT_REVIEW.md) and immutable frozen arena/object audits. Darken's word-punning draft remains unresolved; the arena proof does not excuse unrelated aliasing or arithmetic.

## Internal linker aliases preserve active metadata without source assembly

**Finding.** Reviewed30628/30930/3097C are live-frame continuations, already excluded from standalone inventory. Ordinary parent-relative assignments inside the .main output section retain section association, STT_FUNC and the active ASM aliases' real size0. Six actual private links preserve text and shift aliases correctly with their parents by0x100. Top-level assignments instead become ABS and are excluded by current ELF readers.

**Limits.** Correct parent and offset metadata is required for source-object map ownership. Historical detached alias tails' artificial sizes are not active symbol metadata. A size0 diagnostic MISSING result applies to both old and proposed representations; never invent sizes or function credit to clear it. Inline alias generation was rejected by automatic review and did not run. The safer linker proposal remains private until the larger source/domain transaction is accepted.

**Evidence.** [Alias audit and actual links](../analysis/us/main/jp_animator_aliases/AUDIT.md).

## Table field widths do not determine argument comparison widths

**Problem.** The button setter stores its new index with SH but compares existing zero-extended halfwords against the entire incoming signed32 word. Narrowing its argument to u16 would change behavior for negative values and values above65535. Typed two-row indexing also needs evidence that player/slot are in range.

**Resolution.** Keep the s32 index argument, narrow only the store, and preserve the full-word comparison. Actual title menu6D100 builds six CBF0 children;2C93C/2D1F4 assigns their indices0..5, and only their649C8 vtable dispatches CD28, which passes literal players0/1. This establishes the live menu's subscript domain independently of persisted button values. Shared SaveConfig storage24C agrees with the MD5payload23C and16-byte digest, while the retained36-byte default table supplies3/0/2/5/4/1.

**Validation.** Reset/setter, all old siblings and both consumer slots pass. Parent separately compares the original shipped-profile F000 object against the PsyQ46 candidate: allallocated bytes, runtime relocations and real public metadata match. A same-profile ASM baseline alone would not establish that compiler transition. Fourteen complete byte/placement checks pass. The options wrapper's two register-materialization differences remain private; no source coercion was adopted.

**Evidence.** [Independent button contracts](../analysis/us/main/jp_save_independent_audit.md), [original-profile object comparison](../analysis/us/main/jp_save/parent_F000_object_audit.json), [accepted batches](../analysis/us/jp_next_integration.json).

## Reuse JP source by contract, with whole-family checks

**Problem.** The JP executable shares many engine functions with USA, but equal numeric addresses stop identifying equivalent functions in later regions. JP heapInit is3A38C while USA is3A368. A private natural SEP destructor also showed a local jump difference caused by the preceding constrained constructor, rather than its own source.

**Resolution.** Pin the external source and license, map complete primary bodies and callers, and reuse algorithms after reconciling USA widths and interfaces. Test related bodies together under a whole-slot compiler hypothesis. The natural SEP pair preserves every allocated byte and sibling under PsyQ46; no register constraints are needed. Vector dot products use representable signed64 individual products followed by unsigned low-word sums. A rotation constructor's real matrix-pointer return requires shared declarations even when callers discard it. Native C++ consumers require C linkage guards.

**Validation.** The first five JP-reference gates recover18 bodies and remove constraints from2 bodies. A sixth gate accepts three further vector routines and three matrix constructors, including typed48-byte stage storage and explicit wrapping height adjustment. Every complete executable and overlay remains identical. Equal addresses and these reproduction profiles do not prove original object boundaries. The fresh static moved-link audit still finds123 failures/179 checks, so source recovery and relocation recovery remain separate.

**Evidence.** [JP batch record](../analysis/us/jp_resume_integration.json), [math gate](../analysis/us/wave9_gate_jp_math_core.json), [independent math contracts](../analysis/us/main/jp_math_core_independent_audit.md), [current static relocation audit](../analysis/us/main/jp_resume_current_movement/AUDIT.md).

## GP-relative source requires real data ownership

**Problem.** The RNG's two-word twist table is gp+0x274. Treating a small extern declaration as ownership or changing the enclosing2500-byte state into a small scalar gives misleading code generation. Its true unsigned return also conflicts with older signed or implicit-int consumer declarations.

**Resolution.** Emit the actual8-byte table from natural C, split only those bytes from retained resident data, and place its.sdata between the unchanged0x5580-byte prefix and0x18-byte suffix. Share the complete624-word state plus signed index through all18 consumers; explicitly preserve each old signed result interpretation. Reset625 initializes all words through default4357 before any twist read, and seed multiplication wraps in u32. Corrupt negative indices remain outside the valid state contract.

**Validation.** RNG472 bytes and reset/seed/MD5Final siblings match under the whole-slot PsyQ46/G8/AS2.80 reproduction setting. All14 binaries and placement checks pass. Absolute linker assertions and an independent object/map audit prove the table address6439C,8-byte extent and adjacent symbols. The source compiler emits GLOBAL NOTYPE size0 rather than the old GLOBAL OBJECT size8; document this metadata difference instead of postprocessing assembly/objects. Original-object provenance and modified runtime remain open.

**Evidence.** [Independent RNG contracts](../analysis/us/main/jp_rng_independent_audit.md), [linked table audit](../analysis/us/main/jp_rng/linked_data_audit.json), [accepted follow-ups](../analysis/us/jp_followups_integration.json).

## Explicit caller forwarding can establish a real unused parameter

**Problem.** C5A14 never reads incoming a1, suggesting a one-argument update. Its callerBCE04 explicitly saves incoming a1 and restores it into the call delay slot. Removing that argument shortens the caller and loses the retail frame.

**Resolution.** Retain the evidenced second opaque parameter in a consistent two-argument declaration/definition. This differs from adding an argument solely to preserve a register: two immutable primary caller instructions establish the forwarding. Countdown arithmetic uses unsigned word wrap; the real deleting callback receives the signed halfword-adjusted object and mode3. The complete14 gate validates the new update and its typed caller.

**Evidence.** [Caller and update audit](../analysis/us/game/wave50_game_update_parent_contract_audit.json), [accepted source checkpoint](../analysis/us/parallel_waves49_50_integration.json).

## Search every consumer before accepting a pointer-return API

**Problem.** A title-only inspection missed another gameplay consumer and five stage declarations of2E6B0. The stage call also treated the display-environment accessor as an integer return.

**Resolution.** Search the whole source tree and reconcile all seven descriptor-builder slots plus five display-accessor declarations. Audit the retained builder's actual reads: only source bytes0..7 are consumed, and both title path words are initialized before each call. Three resident selectors/wrappers and two title source improvements land together with coherent pointer interfaces and explicit address-word adapters into the untouched legacy consumer.

**Evidence.** [Resident/title contract audit](../analysis/us/main/wave49_resident_title_api_parent_contract_audit.json), [frozen consumer and data evidence](../analysis/us/title/wave48_api_parent_evidence.json).

---

## Shared pointer contracts and moved-link checks

**Problem.** The actor query was declared as an integer or a no-argument function across older matching slots. A position helper omitted the live output argument, and an apparent sector entry was actually a destructor epilogue. Retail byte matches alone concealed these source and relocation problems.

**Resolution.** Audit register flow at the callee and all discovered consumers. The shared actor-query header declares resource/owner arguments and pointer returns in both C and native C++ slots. Pass the three-word output explicitly, preserve unsigned word wrapping, and form adjusted destructor addresses through the target's unsigned address representation. Recover complete frames and bind interior aliases relative to their emitted parent.

**Validation.** Eighteen actor-query slots pass their original profiles and the complete fourteen-output gate. A separate real link with a four-byte gap moves the destructor, its epilogue alias, a later counter alias, the vtable pointer and destructor call together. All228 inspected symbolic function pointers in resident readonly assembly data remain correct;129 point to moved targets. Canonical objects and outputs are untouched. This is a scoped static relocation proof; cross-overlay relinking, opaque pointers and modified runtime behavior remain open.

**Evidence.** [Actor contract audit](../analysis/us/game/wave43_actor_queries_parent_contract_audit.json), [shared header](../include/game_actor_queries.h), [moved-link report](../analysis/us/main/wave43_shifted_aliases/report.json), [pointer-table report](../analysis/us/main/wave43_shifted_aliases/pointer_table_report.json), [accepted checkpoint](../analysis/us/parallel_waves41_45_integration.json).

---

## Numeric callbacks can match retail while breaking moved builds

**Problem.** A conservative moved-link scan found two readonly words that remained at the old addresses of emitted game callbacks. Adjacent initializer/finalizer words hid two more genuine frames inside a sector-derived assembly collection.

**Resolution.** Replace independently verified numerical callback pointers with normal symbol references. Recover the two 36-byte wrappers from the complete frame boundaries, preserve all375 primary words across the split, and count two adjacent72/280-byte retained routines as genuine assembly entries. The continuation at31000 remains an assembly collection rather than a falsely recovered whole function.

**Validation.** Four successive complete fourteen-unit gates validate symbolization, natural counter unpins, list dispatch and callback recovery. In a separate real moved link, all232 inspected symbolic resident pointers follow their actual targets;133 targets move. This establishes the repaired pointer relationships only. Numerical pointers elsewhere, original objects and runtime behavior remain open.

**Evidence.** [Initial failures](../analysis/us/main/wave43_shifted_aliases/raw_function_pointer_candidates.json), [callback boundary audit](../analysis/us/main/wave45_init_callbacks_parent_contract_audit.json), [repaired pointer audit](../analysis/us/main/wave45_shifted_aliases/pointer_table_report.json).

---

## Typed outputs need real storage, and constructors need coherent consumers

**Problem.** Old motion declarations mixed pointer and integer returns, a caller supplied a false third argument, and several three-word outputs used declared byte arrays. A native base constructor also had incompatible declarations across43 consumers.

**Resolution.** Use shared C-linkage interfaces for actual pointer arguments/results; forward meaningful arguments only. Replace motion stack byte arrays with typed word arrays and byte views for existing consumers. Replay the constructor migration over the captured motion inputs instead of overwriting changed files or skipping conflicts. Preserve distinct priority-list types, the natural native constructor alias and the accepted list dispatcher.

**Validation.** Parent diagnostics pass all31 motion slots and42 constructor source slots; the declaration-only43rd compiles. Three successive complete fourteen-unit gates validate motion, constructor and eight true assembly-entry boundaries. Only the constructor gains source credit. Existing unrelated legacy arithmetic and assisted bodies are not semantically certified by these comparisons.

**Evidence.** [Typed motion audit](../analysis/us/game/wave45_motion_api_parent_contract_audit.json), [Merged constructor audit](../analysis/us/main/wave48_constructor_api_parent_contract_audit.json), [Primary boundary audit](../analysis/us/main/wave47_prefix_boundaries_parent_contract_audit.json).

---

## A moved-link audit can expose a hidden split frame

**Problem.** A loop branch in the31000 continuation resolves an external local label through a retail-address fallback. Retail output matches, but moving the parent four bytes leaves the branch pointing four bytes before its real loop.

**Resolution.** Recover the entire 208-byte30F84 frame and represent31000 as its internal+0x7C alias. The join preserves all52 primary instruction words and passes all14 retail byte/placement checks. A repeat actual four-byte moved link decodes the loop target as80030FA8, equal to the moved parent+0x20; the formerly fixed80030FA4 target is eliminated for this branch. This is scoped static evidence; overlay relinks and runtime modifications remain open.

**Evidence.** [Original moved-branch failure](../analysis/us/main/wave48_shifted_aliases/split_frame_branch_review.json), [joined frame audit](../analysis/us/main/wave48_complete_tim_frame_parent_contract_audit.json), [repaired actual moved target](../analysis/us/main/wave49_join_shifted_aliases/joined_frame_branch_review.json).

---

## Audit transitive vector reads before accepting a private match


**Problem.** A stage update initializes three words in a four-word stack vector and matches all184 retail bytes. Its immediate collision wrapper appears to consume only three coordinates. On collision success, a nested helper swaps four words and reads the unwritten fourth word.

**Resolution.** Trace the complete reachable call path: D5C54 →73010 →76518 →76758 →769FC. Initial z=0 does not make the swap unreachable: the collision-success branch jumps directly to it. Initializing the fourth word gives188 bytes and breaks the match. Preserve the exact draft as diagnostic evidence and retain retail assembly; a private score-zero result cannot override the defined-source policy.

**Evidence.** [Parent fourth-word audit](../analysis/us/st02/wave38_parent_fourth_word_audit.json), [private refinement audit](../analysis/workers/sol_wave9_objects/analysis/us/st02/wave38_fourth_word_audit.json).

---

## Re-test an inherited ABI workaround with the actual return type

**Problem.** A constructor caller used a deliberately false64-bit return declaration to reserve registers. That comment had become accepted lore without a current experiment.

**Resolution.** The retail constructor returns self in v0. Changing its declaration to void* alone preserves all90 source siblings under the existing compiler. Ordinary field stores then reproduce the constructor caller and remove a second caller's v1 pin. Restore natural credit only after the truthful declarations and all complete linked outputs pass.

**Evidence.** [Return repair audit](../analysis/us/game/wave38_return_parent_contract_audit.json), [captured gate](../analysis/us/wave9_gate_wave38_return_repair.json).

---

## Check relative aliases against emitted parents

**Problem.** A reviewed internal alias was correctly placed in the linker map but the verifier ignored assignment lines and rejected its ownership. Treating every assignment as placement would incorrectly accept absolute fallback symbols.

**Resolution.** Accept an assignment only when reviewed boundary metadata names the same parent/offset, the parent is emitted by a source object, and its actual emitted address plus offset equals the alias value. Three regressions cover a shifted parent, wrong/missing bindings, and absolute or unreviewed aliases.

**Evidence.** [Counter boundary audit](../analysis/us/main/wave34_counter_parent_contract_audit.json), [map regressions](../tests/test_map_internal_aliases.py), [repaired complete gate](../analysis/us/wave9_gate_wave34_counter_repaired.json).

---

## Prove pointer and bounded arithmetic contracts through real consumers

**Problem.** A debug field was labeled an overlay flag, but the callee forwarded its word directly into a%s formatter. Five no-argument factories were written as void despite consumers using their returned object. RGB arithmetic looks unsafe over arbitrary signed inputs, while both real callers mask each component to255.

**Resolution.** Read format data and trace argument flow. `/bin/%s.bin` proves the optional field is a string; preserve actual pointer returns through allocation, construction, callback and consumer. Shared0x30 module and0x20 base layouts keep types compatible. For RGB, record the actual bounded0..255 domain and aligned four-byte output; saturation/hue arithmetic is defined there. For the task cursor, explicitly convert throughu32 to model retail wrap without relying on signed overflow. Every affected old sibling remains exact before the full link.

**Evidence.** [Module/factory contracts](../analysis/us/main/wave27_debug_module_contract_audit.json), [RGB caller bounds](../analysis/us/main/wave23_color_contract_audit.json), [task word wrapping](../analysis/us/main/wave23_tasks_contract_audit.json), [linked acceptance](../analysis/us/parallel_waves22_28_integration.json).

---

## Published library source can explain an inlined tail

**Problem.** The zlib block constructor built252 bytes with an out-of-line reset call; retail had292. Published zlib1.1.3 places reset before new in the same original translation unit, whereas sector-layout source split them across files.

**Resolution.** Keep the original reset logic visible through an ordinary local inline helper. The existing compiler elides impossible old-mode frees aftermode0, emits the original reset tail and removes the helper without any force-inline attribute or profile change. Independent Adler-32 recovery preserves original16-byte unrolling and unsigned5552-byte chunk arithmetic. Original copyright/altered-source notices remain. Published source supports source visibility; it does not certify retail game object/compiler settings.

**Evidence.** [Block constructor](../analysis/us/main/wave25_zlib_contract_audit.json), [Adler-32](../analysis/us/main/wave26_adler_contract_audit.json), [zlib license](licenses/ZLIB-1.1.3.txt), [accepted checkpoint](../analysis/us/parallel_waves22_28_integration.json).

---

## A callback word needs a proven meaning, and unused real arguments still count

**Problem.** A VFS runtime hook forwarded an incoming target word, while a separate device hook received explicit reason codes. Treating both as no-argument callbacks, or naming the opaque word as a reason, concealed actual forwarding. No-op callbacks also served fields whose callers passed a real argument.

**Resolution.** Trace the saved hook and every call site. Use one truthful target-word notification interface where the same no-op serves both roles; keep each site's pointer, reason or opaque meaning explicit. Likewise preserve a caller's actual unused context/destructor arguments. Genuine variadic formatting is supported by the wrapper's argument-home forwarding and format strings; variadic declarations are unjustified without that evidence. Repair types, then probe every affected sibling and run the full link.

**Evidence.** [VFS contracts](../analysis/us/main/wave20_vfs_contract_audit.json), [iterator forwarding](../analysis/us/main/wave18_iterator_contract_audit.json), [debug formatter attempts](../analysis/us/main/wave20_parent_formatter_attempts.json), [linked acceptance](../analysis/us/parallel_waves17_21_integration.json).

---

## Count complete routines after boundary review

**Problem.** An already matching twenty-byte list initializer was an internal block of a104-byte insertion. Two MD5 helpers had complete natural source but were still generic assembly rows, which the game-function count excluded.

**Resolution.** Compare each contiguous word against primary bytes and inspect callers/live frames. Represent the full insertion once, preserve nonemitting internal aliases, and retire the fragment's old credit. Promote genuine independently called helpers only after reviewing their boundaries. Recovering23 complete bodies while retiring one fragment yields22 net source functions; denominator corrections are recorded separately.

**Evidence.** [Insertion and typed sort](../analysis/us/main/wave20_sort_contract_audit.json), [MD5 entries](../analysis/us/main/wave21_md5_inventory_audit.json), [actual inventory delta](../analysis/us/parallel_waves17_21_integration.json).

---

## Local jump relocations must resolve to the right instruction

**Problem.** The earlier private checker masked the 26 target bits at jump relocations. An 84-byte BST lookup therefore appeared exact while its loop-exit jump skipped the retail NOP. The full linked build rejected it.

**Resolution.** Parse relocation kind and defined symbol section/value. Compare same-section `R_MIPS_26` targets relative to the function; preserve opcode/register bits for every relocation. External targets still require the complete link. Declaring the lookup key before the loop naturally moved the compiler's scope-end label before the NOP and matched the retail target, without changing emitted ASM or flags.

**Evidence.** [Diagnostic audit](../analysis/us/main/wave12_probe_relocation_repair.json), [real bad/fixed object tests](../tests/test_probe_slot_relocations.py), [natural lookup repair](../analysis/us/main/wave10c_tree_e1f4_nop_label_audit.json), [complete acceptance](../analysis/us/parallel_waves9_16_integration.json).

---

## Sector boundaries can hide complete compiled code

**Problem.** The nominal D800 data slice was 512 instruction words: a preceding function's tail, fifteen genuine functions, then a final body continuing into the next sector. Two other nominal entries were fragments inside live frames.

**Resolution.** Audit every offset/address/word against immutable retail, direct entry references, branch flow, prologues and epilogues. Join complete comparison references and keep genuine internal aliases. Move source-slot starts to actual complete boundaries while retaining historical basenames. This review added seventeen genuine entries; a separate BST review added two. Boundary review changes the denominator independently from source recovery.

**Evidence.** [Boundary audit](../analysis/us/main/wave9_object_boundary_audit.json), [inventory delta](../analysis/us/parallel_waves9_16_integration.json), [complete inventory gate](../analysis/us/wave9_gate_object_inventory.json).

---

## Narrow loads can have promoted full-width return contracts

**Problem.** Resource accessors load unsigned halfwords, but their callers compare, negate and subtract directly from the full return register. A `u16` return declaration introduced a caller-side mask absent from retail. A wrapper also preserved a real third update argument that older C omitted.

**Resolution.** Keep stored fields `u16` and declare the observed promoted return `s32`. Trace argument lineage through both wrapper branches and direct callers. Use one shared 0x524-byte resource object: its +0x10 sixteen-byte table and +0x14 eight-byte table are distinct fields. Old exact instruction bytes did not establish compatible interfaces.

**Evidence.** [Promoted returns](../analysis/us/main/wave14_promoted_resource_returns_audit.json), [forwarded update argument](../analysis/us/main/wave11_resource_return_contract_audit.json), [shared layout](../analysis/us/main/wave12_resource_state_contract_audit.json), [header](../include/game_resources.h).

---

## Generated table placement must preserve surrounding alignment phase

**Problem.** Two renderer switches gained complete natural C and compiler-generated five-entry tables. Splitting the original rodata at a four-byte offset changed later eight-byte alignment when the remainder became a new section.

**Resolution.** Preserve exactly ten generated code pointers and the original four-byte zero gap. Begin the later remainder at a verified eight-byte boundary; retain its strings, words and alignment directives verbatim. Independently check linked pointer words, gap, following label and aliases, then all output bytes. Function probes alone cannot establish table or layout correctness.

**Evidence.** [Renderer contracts](../analysis/us/main/wave9_renderer_contract_audit.json), [linked table checker](../analysis/us/check_wave9_renderer_tables.py), [checked values](../analysis/us/main/wave9_renderer_linked_tables.json).

---

## Call wrappers must model values forwarded through unchanged registers

**Problem.** Several older matching wrappers declared only the argument they changed, or discarded a pointer return that their assembly callers consumed. Byte identity preserved live registers but left the C interface incomplete.

**Resolution.** Follow register lineage through the entire wrapper and callee. `BDF4` forwards its node to `BEB4` and returns its owner; `BF34` conditionally queues the allocation in that owner's second list via `C210`. Gameplay `6F06C`, `6F09C`, `6F0CC` and `7AFCC` also forward a real second node argument. Shared pointer declarations and explicit forwarding preserve all affected sibling bytes and complete linked outputs. Keep overlay identity with a symbol: title's same-address `6F09C` has a separate contract.

**Evidence.** [Deferred-object audit](../analysis/us/main/wave8_deferred_contract_audit.json), [shared resident types](../include/deferred_objects.h), [gameplay wrappers](../include/game_deferred.h), [linked acceptance](../analysis/us/parallel_wave8_integration.json).

---

## Large globals and shared layouts affect `-G8` addressing

**Problem.** A VFS flag was declared as a scalar alias while the actual global is a 0xAA0-byte runtime object; three source slots also declared incompatible types for that same object.

**Symptom.** `main:func_80034940` compiled 52/48 bytes with the scalar, 44/48 with a nonvolatile enclosing object, and exactly 48 with the established volatile flags and large object. Callback +8 and user +0xC are copied into request records and consumed by a four-argument dispatcher.

**Resolution.** Use one shared target layout, keep unreviewed storage opaque, preserve the established qualifier, and type fields from their consumers. Do not select volatility solely for a match; a specific IRQ writer is still unlocated. All existing and new C bodies in the three slots remain exact under unchanged profiles, followed by a complete fourteen-unit gate.

**Evidence.** [VFS contracts](../analysis/us/main/wave7_vfs_contract_audit.json), [shared layout](../include/game_vfs.h), [linked acceptance](../analysis/us/parallel_wave7_integration.json).

---

## Recovery sessions must accept their first source hypothesis

**Problem.** The session wrapper validated every probe as a fresh ASM-only task, so replacing its stub with the first C body caused rejection before invoking the compiler.

**Resolution.** Fresh briefs still require a recoverable stub; an existing recovery session instead validates its recorded complete assembly, boundary and compiler metadata after source replacement. The original assembly hash must remain unchanged. Count a rejected pre-compiler request separately from a compiler attempt.

**Evidence.** [Session helper](../tools/decomp_session.py), [first-C and stale-ASM regression cases](../tests/test_decomp_session.py), [72-test result](../analysis/us/parallel_wave7_tests.log).

---

## A live call register is not an argument — `func_800774EC`

**Problem.** A caller of `func_800774EC` had a scaled value in `a2`; an earlier source declaration made the call variadic and passed that value as a third argument to preserve code generation.

**Symptom.** The 0x24-byte retail callee reads the entity through its first argument and forwards the unchanged `a1` delta to `func_8007F4D4`. Neither callee consumes `a2`. The caller independently stores `-scaled` at `self+0x3B8` in the call delay slot.

**Resolution.** Model two real arguments and keep the store as its own operation. Re-probe the caller after correcting the declaration; preserving an incidental live register is not a valid API contract.

```c
extern void func_800774EC(u8 *self, s32 delta);
/* self->word_3B8 = -scaled; */
func_800774EC(self, -0x8000);
```

**Evidence.** [Wave 3 contract audit](../analysis/us/game/wave3_774EC_contract_audit.json), [callee source](../src/battle/12398.c), [caller source](../src/battle/40E5C.c). The audit inspected retail assembly; it supports the ABI correction, not a claim about the original object profile.

## A compiler family can match neighboring functions without defining their object

**Problem.** Stage06 has three one-function PsyQ4.6 reproduction ranges; a broader compiler change might appear to remove the isolated profiles.

**Resolution.** Compare every current source-bearing slot with both compiler families. PsyQ4.6 preserves all16 bodies in1FA4 and all three isolated constructors, but regresses two of seven bodies inCA4 and two of three in186C. Two other slots match both families and cannot distinguish them. Keep the current ranges pending original-object evidence; a broad switch would regress verified source. None of these private probes changes linked credit or certifies provenance.

**Evidence.** [Complete source-slot comparison](../analysis/us/st06/wave44_profile_range_review.md), [hashes and individual probe references](../analysis/us/st06/wave44_profile_range_review.json).

---

## Compiler families are range evidence, not original-object proof

**Problem.** Natural source with correct contracts can show a repeated scheduling, delay-slot, or address-materialization diff under the shipped GCC 2.8.1 profile.

**Symptom.** The build's recorded comparisons include `title/E6AC.c`, where the shipped compiler adds a `nop` around a return-load delay slot while PsyQ 4.6 reproduces the retail shape, and `title/12AF0.c`, where three bodies become exact under ESA/PsyQ 4.5 without recorded sibling regressions. The controller `main/17804.c` has its own PsyQ 4.6, `-G8` private evidence. These are different code-generation families in one reconstructed project.

**Resolution.** Record the exact profile and compare all neighboring source bodies and generated data. Treat a slot/range override, especially one isolating one function, as a byte-verified working hypothesis until original object boundaries and uniform settings are audited. The nominal sector slot is not established as a retail translation unit. No DW2 flag set transfers automatically to DRA.

```text
candidate profile = compiler binary + full cc1 flags + -G + maspsx/as version
claim = exact bytes for tested range; original object/settings still pending
```

**Evidence.** [Compiler and C++ slot map](../tools/build_dra.py), [controller private audit](../analysis/us/main/root_wave5_pad_final_contract.json), [upstream original-object criterion](https://github.com/Wyrelade/Digimon-World-2-Decomp/issues/5).

## MIPS word wrap needs defined source arithmetic

**Problem.** Retail `addu`, `addiu`, and low-word products wrap at 32 bits, while overflow of signed C arithmetic is undefined.

**Symptom.** In the wave 4 `func_80027888` control calculation, the counter and mode-2 subtraction wrap; a product is reduced to its signed low word before signed division. A game position update in `func_8008EBA0` used signed `+= facing * 0xC0` and `-= 0x20`, which could overflow at extreme coordinates despite a plausible byte match.

**Resolution.** Express the 32-bit machine step through unsigned arithmetic, then interpret the resulting word as signed where the algorithm requires it. Keep signed division only after the low-word conversion; re-probe because changing types can alter code generation.

```c
u32 next = (u32)position + (u32)delta;
position = (s32)next;
```

**Evidence.** [Wave 4 resident audit](../analysis/us/main/root_wave4_contract_audit.json), [wave 4 game audit](../analysis/us/game/wave4_new_game_contract_audit.json), [retail game body](../asm/us/game/nonmatchings/28514/func_8008EBA0.s). This is a semantic correction supported by retail operations, not a license to add casts without testing.

## Natural write order recovered a 604-byte controller state machine

**Problem.** `func_800275FC` had a historical split at `func_80027800` and a six-byte alignment request whose initialization order affected the emitted code.

**Symptom.** Retail has one 0x25C-byte function with a live frame through the +0x204 alias. Phase 1 writes `00 01 FF FF FF FF` at `self+0x92` and passes that buffer as the second alignment-call argument; phase 2 waits for raw state 6. Earlier source forms did not reproduce the whole body.

**Resolution.** A natural six-byte header write in retail order plus `switch (mode)` reproduced 604/604 private bytes under PsyQ 4.6 `-G8`; the internal alias reproduced 88/88. The mode paths retain defined 32-bit increment wrap and the two visible SDK arguments. The later 18:28 checkpoint is the complete-build baseline for this integrated wave.

```c
request[0] = 0;
request[1] = 1;
request[2] = request[3] = request[4] = request[5] = 0xff;
/* phase 1 submits request; phase 2 waits for raw state 6 */
```

**Evidence.** [Final controller contract and private probe](../analysis/us/main/root_wave5_pad_final_contract.json), [source](../src/engine/17804.c), [retail body](../asm/us/main/nonmatchings/17804/func_800275FC.s), [complete checkpoint](../analysis/checkpoints/20261008T182817Z/checkpoint.json). The private probe is the direct function/alias proof; the checkpoint establishes complete outputs at its recorded input hashes.

## A function label may be an interior alias

**Problem.** Treating historical symbols as separate C functions can duplicate a live frame or split a delay slot.

**Symptom.** `func_80027800` lies 0x204 bytes into `func_800275FC` and uses its parent's frame; `func_800278DC` and `func_80027948` likewise lie inside the complete `func_80027888` control body. There is no independent prologue and argument setup at those labels.

**Resolution.** Recover the complete parent routine and preserve the internal symbol/size only where callers or layout require it. Check the end through the branch or return delay slot, then verify alias and neighboring addresses in the whole slot and linked output.

```text
func_800275FC: full 0x25C-byte body
func_80027800: alias at parent +0x204, not another source function
```

**Evidence.** [Wave 4 boundary audit](../analysis/us/main/root_wave4_contract_audit.json), [final controller audit](../analysis/us/main/root_wave5_pad_final_contract.json), [retail controller assembly](../asm/us/main/nonmatchings/17804/func_800275FC.s).

## Apparent title code was a pointer table

**Problem.** The manifest called `func_8007A54C` a function, and disassembly rendered its pointer words as instructions.

**Symptom.** The first words are resource addresses, with no prologue, executable control flow, or return. `func_80068C9C` passes the address (or `D_8007A564`) to `func_80068F30`, which dereferences the first word as a pointer rather than calling through it. The nominal 0xD8-byte entry belongs to adjacent data extending through 0x8007A63F, including zero words and interior data aliases.

**Resolution.** Classify the range as data for inventory, retain every pointer/zero word and alias at its retail address, and require a complete linked placement gate for representation changes. This corrects the denominator; it does not add a recovered C function.

```text
0x8007A54C -> pointer-table start
D_8007A564 -> second six-pointer table within the same data span
```

**Evidence.** [Title boundary audit](../analysis/us/title/7A54C_boundary_audit.json), [retail data bytes](../asm/us/title/nonmatchings/12AF0/func_8007A54C.s), [consumer source](../src/title/40C4.c), [complete checkpoint](../analysis/checkpoints/20261008T182817Z/checkpoint.json).

## A private match is a hypothesis until the linked gate

**Problem.** Function-only probes can mask sibling regressions, jump-table emission, `.rodata` placement, or changed aliases.

**Symptom.** A natural `game/38D84.c` wave 6 batch recorded two new 216/228-byte exact bodies and a 31/31 private whole-slot result under PsyQ 4.6 `-G0`, while six other readable drafts remained unmatched. That ledger explicitly reports no new emitted sections; it does not itself certify all linked overlays.

**Resolution.** Keep only exact natural candidates, save failed drafts and their diff reasons, inspect generated sections, then freeze source and run the 14-output byte/placement gate. Do not convert a near match into credit with target-guided assembly changes, register pins, or artificial arguments.

```text
function probe -> whole-slot probe -> emitted-data check -> linked 14-output gate
```

**Evidence.** [Wave 6 attempt ledger](../analysis/us/game/38D84_wave6/attempts.json), [checkpoint verification method](DECOMPILATION_PLAN.md), [2026-10-08 complete baseline](../analysis/checkpoints/20261008T182817Z/checkpoint.json).
# Retained dead stack reads still require defined input

**Problem.** Private exact constructors95F6C and88DD0 produce three vector words, but retained transform callees read a fourth unwritten stack word. Their downstream consumers use only three words.

**Resolution.** Dead downstream use does not remove the callee read. Keep the constructors in assembly until a defined source/callee contract is established; adding an initializer that changes retail bytes is not an accepted fix. No private score or source percentage overrides this review.

**Evidence.** [95F6C access audit](../analysis/workers/sol_wave9_game/analysis/us/game/wave29_fourth_word_contract_audit.json), [88DD0 access audit](../analysis/workers/sol_wave9_game/analysis/us/game/wave31_fourth_word_contract_audit.json), [accepted subset](../analysis/us/parallel_waves26_32_integration.json).

## Removing register constraints needs an arithmetic review

**Problem.** RendererCC2C4 matched privately after dropping pins, but the inherited `(u16_vertex <<16)>>18` expression invoked signed-shift undefined behavior for negative vertex bit patterns. Frame shifts/products also needed explicit wrapping.

**Resolution.** Interpret the vertex as signed16-bit before arithmetic right shift; use unsigned32-bit shifts/products and narrow to the target word/halfword representation. The existing compiler emits the same576 retail bytes, all55 source siblings match, and the complete14-unit gate passes. Integer/pointer adapters remain target-specific and require actual caller-domain bounds.

**Evidence.** [parent arithmetic audit](../analysis/us/game/wave33_parent_contract_audit.json), [captured linked gate](../analysis/us/wave9_gate_wave33_renderer.json).

## A zero diff after failed staging is not source evidence

**Problem.** Formatter probe004 ran against retained assembly after an edit command failed. Its zero-difference report did not measure candidate C.

**Resolution.** Require an actual source definition before reserving/compiler execution. Preserve invalid raw diagnostics with `source_candidate_valid=False` and exclude them from best-score summaries. A profile refresh needs new evidence and cannot change retail identity, boundaries or calibration; prior cycles stay recorded.

**Evidence.** [formatter attempt ledger](../analysis/us/main/wave30_parent_formatter_attempts.json), [session guard](../tools/decomp_session.py), [score accounting](../tools/update_workflow.py).


## Matrix padding and SDK transfer widths require actual access review

The natural 92-byte matrix-wrapper draft matched privately but remains withheld. Its retained copy helper writes only 18 matrix bytes, then the next helper reads the full word at +0x10. The two direct callers supply uninitialized stack storage. Hardware ignoring the upper half does not satisfy the initialized-read policy. The complete frame and relative interior alias remain accepted in ASM independently of the C draft. [Access-chain audit](../analysis/us/main/wave53_2EFDC_withheld/output_initialization_audit.json).

The accepted VFS callback's 0x200 sector transfer count is in words, corroborated by the retained DMA access and the SDK contract. Its device callback takes no arguments and callback installation returns the prior pointer. Correcting this interface required re-probing the other resident consumer; local word-size matching alone would not establish a compatible shared interface. [Contract and moved-pointer audit](../analysis/us/main/wave50_vfs_callbacks_parent_contract_audit.json). No SDK source conversion was required.


## An ignored callback argument can still be a real interface requirement

The VFS setter stores a callback and user pointer. The actual dispatcher loads that user word into a0 before calling the stored callback, establishing a one-word callback interface even though the gameplay callback ignores it. Updating that declaration and definition preserved all53 existing gameplay matches; the natural setter matched36 bytes and the complete fourteen-output gate passed. This differs from adding an argument solely to influence registers. [Reviewed transaction](../analysis/us/main/wave52_callback_setter_parent_contract_audit.json).

The renderer entry E700 was incorrectly treated as data while its E800 continuation was treated as independent ASM. Seven real callers enter E700; E800 uses saved registers and the same epilogue. Joining all88 primary words unchanged and binding E800 relative to its parent repaired its actual moved jump. The handwritten GTE body remains ASM and earns no C credit. [Boundary and movement audit](../analysis/us/main/wave55_render_frame_parent_contract_audit.json).


## Repair a real callback ABI before counting its source

The collision effect callee7C0C8 reads and writes the incoming second pointer's five words at18..28. The75BD8 dispatcher and25callback table entries establish that pointer as the other initialized collision node. Forward it consistently across every source consumer using the shared header. Twenty corrected callers retained exact source;9C224 changed register allocation and returned to complete unchanged assembly. A source-credit reduction is appropriate when the old source omitted a real input. The separately recovered9EDD8 callback uses the repaired interface. [ABI transaction](../analysis/us/game/wave66_collision_abi_parent_contract_audit.json), [new callback](../analysis/us/game/wave67_collision_callback_parent_contract_audit.json).

## Measure the whole family before choosing a reproduction compiler

Two natural22000 task/list leaves differed under shipped andESA compilers but matched under uniformPsyQ4.6, preserving all14oldC siblings. The complete16-body slot retained function placements and no allocated data changed. Keep existingG0; G8's equal result does not establish original flags. The neighboring sentinel draft still differs and remains assembly. Sector ownership, original object identity, external linked addresses and modified runtime are separate evidence levels. [Family and acceptance audit](../analysis/us/main/wave65_task_pair_parent_contract_audit.json).


## Recover the complete frame before judging relocation failures

The zlib inflate_blocks frame at3B6AC spans three former sector stubs. Its771 primary words share a0x78 frame and saved registers; continuations3B800/3C000 consume live state. Joining unchanged assembly and making both continuation aliases relative repaired25 resident cross-slot cases. The private four-byte moved link also verified all99 local branches andten switch pointers. The existing jlabel macro already exports switch labels, so the readonly table follows them without fixed-address aliases. GNU ld retains these .L labels in its map even when objdump omits them from the final symbol table; inspect both. Source slots remain layout conveniences, not original-object evidence. This transaction earns no Ccredit. [Frame and movement audit](../analysis/us/main/wave74_zlib_frame_parent_contract_audit.json).

## Reconcile interfaces before accepting a new caller

The new81B90 timer exposed a mismatched game owner-pointer getter77630 and audio1BE78 declaration. The coherent repair covers26source slots, including implicit and declaration-only users, while excluding an unrelated title overlay alias at77630. All922oldsource bodies retained exact bytes, data/tables, allocated relocations and function offsets. The parent kept a newer1BC0C resource factory when merging the shared header, then rechecked all20C000bodies and the complete14binary gate. The timer reads its tick after the existing callback and increments the stored unsigned word; cast only the old tick for signed remainder22. [API repair](../analysis/us/shared/wave71_shared_apis_parent_contract_audit.json), [timer acceptance](../analysis/us/game/wave72_game_timer_parent_contract_audit.json).
## GP-relative array bases can expose the assembler version

**Problem.** Natural primitive-buffer swap26C38 used the correct two-word endpoint arrays, but their address materialization expanded to HI16/LO16 instead of retail GP-relative `addiu`. Four private source/data variants retained all42 existing source siblings without resolving that difference.

**Finding.** The translator's ASPSX2.77 behavior disables GP address formation for `la`;2.80 enables it for genuine small-data descriptions. The existing assembly-owned arrays and truthful size8 external metadata were already sufficient. One bounded whole-slot2.80 comparison made all43 bodies exact under unchanged PsyQ46/G8/compiler flags. No data ownership or translator edit was needed.

**Validation.** Parent object audit verifies exactly eight new symbolic GP16 operands, identical other allocated bytes/relocations/public metadata and no new data. The complete executable plus13 overlays pass byte/placement checks; genuine full resident sections/public metadata remain identical. Startup/index/division domains are audited separately. This establishes current reproduction settings, not original-object provenance.

**Evidence.** [Parent review](../analysis/us/main/jp_prim_swap/PARENT_REVIEW.md), [assembler finding](../analysis/us/main/jp_prim_swap/frozen/ASPSX_FINDING.md), [linked gate](../analysis/us/wave9_gate_jp_prim_swap.json).

## Preserve physical alignment when splitting owned readonly data

**Problem.** Replacing inflate's56-byte assembly jump table with the natural switch table split the retained data at19A54, an address four modulo eight. A later unchanged `.align 3` then aligned relative to the new section rather than the original physical base, adding four bytes and shifting subsequent code. The first complete link correctly failed its placement assertions.

**Resolution.** Keep every original data byte and alignment directive. Split the suffix again at its first actual eight-byte-aligned table19F88: the1332-byte head ends there, and the remainder starts at a true aligned physical base. Ordinary linker alignment restores the original geometry; no instruction or data patch is needed. Measure emitted section alignment: this compiler table has alignment8 even though entries are four bytes and the canonical output uses SUBALIGN4.

**Validation.** Parent verifies the complete data partition, relocation and symbol ownership maps, all fourteen complete binary comparisons and all public metadata. Location-counter aliases preserve original NOTYPE metadata rather than inheriting FUNC from a parent symbol. A real private+0x100 link checks every generated table pointer, its HI/LO address and all fourteen internal labels. This is selected static movement proof, not runtime or original-object certification. [Parent review](../analysis/us/main/jp_inflate_wrapped/PARENT_REVIEW.md), [data/public audit](../analysis/us/main/jp_inflate_wrapped/parent_linked_audit.json), [shift proof](../analysis/us/main/jp_inflate_wrapped/shifted_owned_audit.json).

---
