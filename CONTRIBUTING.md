# Contributing

Work on the US release only. Preserve complete byte identity and actual source-object placement for the executable and all thirteen overlays. Read `AGENTS.md`, `PLAN.md` and `docs/CODEGEN_MODEL.md` before changing source.

Use natural, defined C or genuine native C++ where its ABI is established. Keep PsyQ routines symbolized in assembly. Do not add register pins, fake arguments, assembly output patches, uninitialized reads or undefined overflow to force matches. Existing assisted source is explicitly counted and remains subject to review.

Probe one concrete source/codegen hypothesis at a time with `tools/decomp_session.py`; inspect complete frames, initialization, real caller/callee signatures, emitted tables, relocations and siblings. Preserve failed attempts and their cap. Compiler settings are reproduction evidence, not automatically original-object provenance.

Freeze writers, run `python tools/verify.py`, then `python tools/game_progress.py --save --require-verified`. A private function match alone earns no source credit. The parent owns shared headers, profiles, version config and full linked gates. Historical scratch packets stay in the original workspace and are not silently imported as accepted source.

Changes to retained assembly boundaries, aliases or data ownership must update the matching `config/us/split/` recipe and generated hash in the same transaction. See [split generation](docs/SPLIT_GENERATION.md). The generator reads retail bytes and preserves the reviewed symbol bindings; it must never be used to rewrite compiler-produced source output or force a function match.
