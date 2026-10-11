# This file is used by the original compiler/assembler.
# Defines the expected assembly macros.
#
# The macro set is the same one include/macro.inc defines for the split's
# standalone .s files (same 8 macros, same gte_macros.inc include).  Delegating
# shares macro.inc's _MACRO_INC_GUARD, so a splat-generated .s which starts with
# `.include "macro.inc"` can also be pulled into a C translation unit (the
# inter-function pad objects, INCLUDE_RODATA) without redefining the macros.
.include "include/macro.inc"
