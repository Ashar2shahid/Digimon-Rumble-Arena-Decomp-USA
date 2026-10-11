# External dependencies

Install the exact Windows compiler and assembler dependencies with `python tools/setup_toolchain.py`. The installer downloads pinned public inputs, applies [the DRA maspsx patch](maspsx-dra.patch), and verifies the resulting file hashes against [the manifest](../docs/toolchain_manifest.json).

The patched maspsx runtime is installed locally in `external/maspsx/`, with its upstream license. Compiler and binutils executables are installed under `bin/`. Download caches, tool binaries and generated game assembly are excluded from version control. See [toolchain setup](../docs/TOOLCHAIN_SETUP.md) for sources and component versions.

m2c and decomp-permuter are optional research tools and are not needed to build the game. Their existing workbench integrations require separate local setup.
