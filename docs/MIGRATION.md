# US repository migration

Origin: accepted US commit76773bf and checkpoint20261010T155411Z (3500 build inputs),2179/3699 natural source. Frozen private proposals for CDA8, CD0/DA4 and SDKmemmove are excluded. The decompilation goal remains paused.

The JP conventions adopted are engine/battle/stage source groups, lower-case versioned config/build/disc/asset/assembly directories, a root Makefile, contribution guidance and an external-dependency directory. USA addresses, logical binary IDs, slot filenames, compiler profile keys and matched statements are retained.

`tools/project_layout.py` maps logical binary IDs to physical source trees. Game scanning explicitly excludes the nested stage directories. Linker object selectors and assembly include paths follow the new locations. Exact period compiler binaries and flags are unchanged. The main executable remains SLUS_014.04; overlay load addresses are the US addresses, not copied JP addresses.

`docs/import_manifest.json` records every original source and local build dependency hash. Historical originating metrics are in `docs/verification/`. Fresh verification records are generated under build/us; imported evidence is never misrepresented as proof of the new paths.

The original repository is unchanged. Scratch/hypothesis histories remain there. This separate repository is initialized with its own Git history and repository-local Ashar2shahid identity. No remote repository is created or pushed.

The reviewed generated assembly and compiler binaries remain ignored local dependencies. Bootstrap can reconstruct this local copy from the accepted original workspace by verified hashes. General clean-disc regeneration and cross-platform toolchain packaging remain future work.

Fresh checkpoint in this separate project: `analysis/checkpoints/20261011T073051Z`. All fourteen allocated-section byte and placement comparisons passed against the accepted original build. Three automatic objcopy symbols for Ram_Reserved.bin contain absolute input paths, so their names change with the folder; their values, sizes and section metadata remain identical. All other public symbol metadata is unchanged. See `docs/verification/migration.json`.
