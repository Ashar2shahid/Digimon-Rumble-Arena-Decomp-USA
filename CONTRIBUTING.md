# Contributing

Work on the US release only. Preserve complete byte identity and actual source-object placement for the executable and all thirteen overlays. Read `AGENTS.md`, `PLAN.md` and `docs/CODEGEN_MODEL.md` before changing source.

Use natural, defined C or genuine native C++ where its ABI is established. Keep PsyQ routines symbolized in assembly. Do not add register pins, fake arguments, assembly output patches, uninitialized reads or undefined overflow to force matches. Existing assisted source is explicitly counted and remains subject to review.

Probe one concrete source/codegen hypothesis at a time with `tools/decomp_session.py`; inspect complete frames, initialization, real caller/callee signatures, emitted tables, relocations and siblings. Preserve failed attempts and their cap. Compiler settings are reproduction evidence, not automatically original-object provenance.

Freeze writers, run `python tools/verify.py`, then `python tools/game_progress.py --save --require-verified`. A private function match alone earns no source credit. The parent owns shared headers, profiles, version config and full linked gates. Historical scratch packets stay in the original workspace and are not silently imported as accepted source.

The repository-local author identity is Ashar2shahid with GitHub's verified-account-ID noreply address. This config affects only this repository; authenticating or signing commits remains the user's normal GitHub setup.
