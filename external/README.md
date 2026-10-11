# Local external dependencies

The matching snapshot uses the earlier project's patched maspsx, copied locally into `maspsx/` with its upstream license. Upstream is https://github.com/mkst/maspsx, but replacing this patched copy requires a complete build audit. Toolchains are local under `bin/`. None are committed. Bootstrap hashes identify the exact local versions.

m2c and decomp-permuter are optional diagnostic tools. Their configured original workbench paths require local setup before use; they are not required by the full build. Preserve their upstream licenses when installing them. No untested submodules are declared as if already installed.
