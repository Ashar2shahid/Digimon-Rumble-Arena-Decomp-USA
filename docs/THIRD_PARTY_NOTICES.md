# VFS2 format-reference attribution

The archive layout used by `tools/extract_vfs.py` was documented in DarkChaosBlast's `digimon_vfs2.bms`, distributed in bigger0gamer/TrueOGEdition at commit `7c24704f7153dde8f1efced484915ccc2357bb35`.

The repository's license notice is preserved below. Other downloaded tools retain their own license files under `.tools`; they are not vendored into project source.

MIT License

Copyright (c) 2025 Yuri Bacon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Earlier Rumble Arena source

The canonical `src/`, `include/`, `config/us/`, `config/us/linkers/`, `tools/build_dra.py`, `tools/check_unit.py`, `tools/check_source_order.py` and PSY-Q format parser adapt the user's project at `D:\Decompiles\Digimon Rumble Arena\Digimon Rumble Arena`. That project's `LICENSE` declares CC0 1.0 Universal; a copy is retained in [licenses/legacy-source-CC0.txt](licenses/legacy-source-CC0.txt). The parser was adapted from its `scratch/psyq_lib.py`; its format comment credits [ttkb-oss/psy-k](https://github.com/ttkb-oss/psy-k). The audit snapshot records hashes of source files and compiler inputs. Canonical verification independently compares complete linked outputs with the user's extracted retail binaries.

The native canonical build uses the earlier project's patched maspsx, retained locally under `external/maspsx/` with its upstream license. The initial WSL assembly-oracle workflow retains its separately pinned tools under `.tools/`. Tool/compiler binaries, SDK libraries, disc-derived assembly and assets remain local ignored dependencies; importing their build configuration does not assign the source license to those binaries.

## zlib 1.1.3

The altered `inflate_trees_dynamic` helper in `src/engine/2D800.c` and the `inflate_trees_bits` and `inflate_trees_fixed` helpers in `src/engine/2E000.c` derive from `inftrees.c`, Copyright (C) 1995-1998 Mark Adler, under the same original zlib notice.

`include/zlib_113.h` and the identified inflate helpers in `src/engine/2B034.c`, `src/engine/2B800.c`, `src/engine/2C800.c`, `src/engine/2D800.c` and `src/engine/2E000.c` adapt the original zlib 1.1.3 declarations and algorithms to the game's address symbols and 32-bit target layout. They are altered source, not an unmodified upstream distribution. Copyright (C) 1995-1998 Jean-loup Gailly and Mark Adler. The original notice is retained in [licenses/ZLIB-1.1.3.txt](licenses/ZLIB-1.1.3.txt). The altered `inflate_flush` body in `src/engine/2E000.c` derives from `infutil.c`, Copyright (C) 1995-1998 Mark Adler. zlib is distinct from the Sony SDK and carries its own source license.

## ReGame Labs JP source refresh

Five additional component helpers in `src/engine/16800.c` and `include/game_matrix_components.h` adapt `src/engine/math/matrix_ops.c`. The two promoted signed camera getters in `src/engine/12000.c` adapt `src/engine/gfx/camera.c`. Button reset/setter functions in `src/engine/E800.c` and `src/engine/F000.c`, their `include/game_save_config.h` API and consumer declarations adapt `src/engine/game/save_data.c`. USA word-backed storage, access widths, default table, caller indices and full-width comparison behavior were checked independently. These additions share the pinned ReGame Labs MIT notice below.

The six vector/matrix routines in `src/engine/14000.c` and `src/engine/15000.c`, with declarations in `include/game_math.h`, also adapt `src/engine/math/vector.c` and `src/engine/math/matrix.c` from this pinned snapshot. USA signed64 product widths, word wrapping, matrix initialization and consumer layouts were independently checked. The Mersenne Twister generator and its two-word owned table in `src/engine/27810.c`, and the shared state API in `include/game_random.h`, adapt `src/engine/math/random.c`; USA initialization routes, unsigned recurrence and each consumer's result interpretation were reviewed independently.

The full-width/path helpers in `src/engine/26000.c` and `src/engine/26800.c` additionally adapt `src/engine/lib/string.c` from the same pinned snapshot. The ten math helpers in `src/engine/16800.c` and `src/engine/17000.c` and their API in `include/game_vector_words.h` adapt `src/engine/math/vector_ops.c`, `quaternion_ops.c` and `sin_cos.c`. USA access widths and modulo arithmetic were independently checked; retained tables remain disc-derived assembly. They share the ReGame Labs MIT notice below.

The MD5 final/update routines in `src/engine/27810.c` and `src/engine/28800.c`, their declarations in `include/game_md5.h`, the merge-sort routines in `src/engine/28800.c`, and the natural SEP constructor/destructor in `src/engine/B800.c` adapt [dtbe_decomp](https://github.com/ReGame-Labs/dtbe_decomp/tree/e6cbb24be615ef2f5e31b6e938117a976a8518ec) at commit `e6cbb24be615ef2f5e31b6e938117a976a8518ec`. Source references are `src/engine/lib/md5.c`, `src/engine/lib/list.c`, `include/engine/lib/md5.h`, and `src/engine/sound/sound_control.c`. Types, symbols and defined arithmetic were adjusted and independently audited against USA callers and complete linked outputs. Copyright (c) 2026 ReGame Labs. The current MIT notice is retained in [licenses/REGAME-DTBE-20261010-MIT.txt](licenses/REGAME-DTBE-20261010-MIT.txt). This attribution is separate from the older heap snapshot below.

## ReGame Labs heap source (older snapshot)

The heap algorithms in `src/engine/2A814.c` and types in `include/game_heap.h` adapt [src/engine/heap.c](https://github.com/ReGame-Labs/dtbe_decomp/blob/a54d64ecd4053cdcb96df1f6d3c53ab457dd24a5/src/engine/heap.c) and [include/heap.h](https://github.com/ReGame-Labs/dtbe_decomp/blob/a54d64ecd4053cdcb96df1f6d3c53ab457dd24a5/include/heap.h) from ReGame-Labs/dtbe_decomp at commit `a54d64ecd4053cdcb96df1f6d3c53ab457dd24a5`. Addresses and declarations were adjusted to the USA executable and independently checked against its instructions. Copyright (c) 2026 juandav. The complete MIT notice is retained in [licenses/REGAME-DTBE-MIT.txt](licenses/REGAME-DTBE-MIT.txt).
