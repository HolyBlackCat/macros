#pragma once

#include "em/macros/detail/enable_short_macros.h"
#include "em/macros/meta/elem_by_index.h"

// Those are used by `utils/codegen.h` and `utils/cvref.h`.

// When a placeholder is used inside of `(...)`, those `(...)` must be preceded by `EM_P`.
#define EM_P(...) )(DETAIL_EM_CGBITS_LPAREN,__VA_ARGS__)(DETAIL_EM_CGBITS_RPAREN,
// Numbered placeholders.
#define EM_1 )(DETAIL_EM_CGBITS_1,
#define EM_2 )(DETAIL_EM_CGBITS_2,
#define EM_3 )(DETAIL_EM_CGBITS_3,
#define EM_4 )(DETAIL_EM_CGBITS_4,
#define EM_5 )(DETAIL_EM_CGBITS_5,
#define EM_6 )(DETAIL_EM_CGBITS_6,
#define EM_7 )(DETAIL_EM_CGBITS_7,
#define EM_8 )(DETAIL_EM_CGBITS_8,
// Those silently return nothing if out of range, instead of failing.
#define EM_1_OPT )(DETAIL_EM_CGBITS_1_OPT,
#define EM_2_OPT )(DETAIL_EM_CGBITS_2_OPT,
#define EM_3_OPT )(DETAIL_EM_CGBITS_3_OPT,
#define EM_4_OPT )(DETAIL_EM_CGBITS_4_OPT,
#define EM_5_OPT )(DETAIL_EM_CGBITS_5_OPT,
#define EM_6_OPT )(DETAIL_EM_CGBITS_6_OPT,
#define EM_7_OPT )(DETAIL_EM_CGBITS_7_OPT,
#define EM_8_OPT )(DETAIL_EM_CGBITS_8_OPT,

#if EM_ENABLE_SHORT_MACROS(CODEGEN)
#define _P_(...) )(DETAIL_EM_CGBITS_LPAREN,__VA_ARGS__)(DETAIL_EM_CGBITS_RPAREN, // Can't use `EM_P`, must write this directly.
#define _1_ EM_1
#define _2_ EM_2
#define _3_ EM_3
#define _4_ EM_4
#define _5_ EM_5
#define _6_ EM_6
#define _7_ EM_7
#define _8_ EM_8
#define _1_OPT_ EM_1_OPT
#define _2_OPT_ EM_2_OPT
#define _3_OPT_ EM_3_OPT
#define _4_OPT_ EM_4_OPT
#define _5_OPT_ EM_5_OPT
#define _6_OPT_ EM_6_OPT
#define _7_OPT_ EM_7_OPT
#define _8_OPT_ EM_8_OPT
#endif

#define DETAIL_EM_CGBITS_LPAREN(...) (
#define DETAIL_EM_CGBITS_RPAREN(...) )
#define DETAIL_EM_CGBITS_1(...) EM_VA_OR_SEQ_AT(0, __VA_ARGS__)
#define DETAIL_EM_CGBITS_2(...) EM_VA_OR_SEQ_AT(1, __VA_ARGS__)
#define DETAIL_EM_CGBITS_3(...) EM_VA_OR_SEQ_AT(2, __VA_ARGS__)
#define DETAIL_EM_CGBITS_4(...) EM_VA_OR_SEQ_AT(3, __VA_ARGS__)
#define DETAIL_EM_CGBITS_5(...) EM_VA_OR_SEQ_AT(4, __VA_ARGS__)
#define DETAIL_EM_CGBITS_6(...) EM_VA_OR_SEQ_AT(5, __VA_ARGS__)
#define DETAIL_EM_CGBITS_7(...) EM_VA_OR_SEQ_AT(6, __VA_ARGS__)
#define DETAIL_EM_CGBITS_8(...) EM_VA_OR_SEQ_AT(7, __VA_ARGS__)
#define DETAIL_EM_CGBITS_1_OPT(...) EM_VA_OR_SEQ_TRY_AT(0, __VA_ARGS__)
#define DETAIL_EM_CGBITS_2_OPT(...) EM_VA_OR_SEQ_TRY_AT(1, __VA_ARGS__)
#define DETAIL_EM_CGBITS_3_OPT(...) EM_VA_OR_SEQ_TRY_AT(2, __VA_ARGS__)
#define DETAIL_EM_CGBITS_4_OPT(...) EM_VA_OR_SEQ_TRY_AT(3, __VA_ARGS__)
#define DETAIL_EM_CGBITS_5_OPT(...) EM_VA_OR_SEQ_TRY_AT(4, __VA_ARGS__)
#define DETAIL_EM_CGBITS_6_OPT(...) EM_VA_OR_SEQ_TRY_AT(5, __VA_ARGS__)
#define DETAIL_EM_CGBITS_7_OPT(...) EM_VA_OR_SEQ_TRY_AT(6, __VA_ARGS__)
#define DETAIL_EM_CGBITS_8_OPT(...) EM_VA_OR_SEQ_TRY_AT(7, __VA_ARGS__)
