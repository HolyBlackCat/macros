#pragma once

#include "em/macros/detail/enable_short_macros.h"
#include "em/macros/meta/common.h"
#include "em/macros/meta/elem_by_index.h"

// Those are used by `utils/codegen.h` and `utils/cvref.h`.

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

// When a placeholder is used inside of `(...)`, those `(...)` must be preceded by `EM_P`.
#define EM_P(...) )(DETAIL_EM_CGBITS_LPAREN, __VA_ARGS__ )(DETAIL_EM_CGBITS_RPAREN,
// Those are individual `(` and `)` parentheses. This is useful for nested loops, where `EM_P` starts to choke.
#define EM_LP )(DETAIL_EM_CGBITS_LPAREN,
#define EM_RP )(DETAIL_EM_CGBITS_RPAREN,

// Escapes the argument. In particular, escapes all `_i_`, `_P_`, `_LP_`, `_RP_` in it.
// When in a nested loop, this forces them to be expanded by the second most nested loop, rather than the most-nested loop.
// You can nest them: `_E_(_E_(...))` delays the expansion to the third most nested loop.
#define EM_E(...) DETAIL_EM_ESCAPE((__VA_ARGS__)())
#define DETAIL_EM_ESCAPE(...) DETAIL_EM_ESCAPE_0 __VA_ARGS__
#define DETAIL_EM_ESCAPE_0(...) __VA_ARGS__ DETAIL_EM_ESCAPE_A
#define DETAIL_EM_ESCAPE_A(...) __VA_OPT__(DETAIL_EM_ESCAPE_BODY(__VA_ARGS__) DETAIL_EM_ESCAPE_B)
#define DETAIL_EM_ESCAPE_B(...) __VA_OPT__(DETAIL_EM_ESCAPE_BODY(__VA_ARGS__) DETAIL_EM_ESCAPE_A)
#define DETAIL_EM_ESCAPE_BODY(...) )(DETAIL_EM_CGBITS_RPAREN,)(DETAIL_EM_CGBITS_LPAREN, __VA_ARGS__

#if EM_ENABLE_SHORT_MACROS(CODEGEN)
#define _P_(...) )(DETAIL_EM_CGBITS_LPAREN,__VA_ARGS__)(DETAIL_EM_CGBITS_RPAREN, // Can't use `EM_P`, must write this directly.
#define _LP_ EM_LP
#define _RP_ EM_RP
#define _E_(...) DETAIL_EM_ESCAPE((__VA_ARGS__)()) // Can't use `EM_E(...)`, must write this directly.
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
#define DETAIL_EM_CGBITS_1(...) EM_TRY_EXPAND_PARENS(EM_VA_AT0(__VA_ARGS__))
#define DETAIL_EM_CGBITS_2(...) EM_TRY_EXPAND_PARENS(EM_VA_AT1(__VA_ARGS__))
#define DETAIL_EM_CGBITS_3(...) EM_TRY_EXPAND_PARENS(EM_VA_AT2(__VA_ARGS__))
#define DETAIL_EM_CGBITS_4(...) EM_TRY_EXPAND_PARENS(EM_VA_AT3(__VA_ARGS__))
#define DETAIL_EM_CGBITS_5(...) EM_TRY_EXPAND_PARENS(EM_VA_AT4(__VA_ARGS__))
#define DETAIL_EM_CGBITS_6(...) EM_TRY_EXPAND_PARENS(EM_VA_AT5(__VA_ARGS__))
#define DETAIL_EM_CGBITS_7(...) EM_TRY_EXPAND_PARENS(EM_VA_AT6(__VA_ARGS__))
#define DETAIL_EM_CGBITS_8(...) EM_TRY_EXPAND_PARENS(EM_VA_AT7(__VA_ARGS__))
#define DETAIL_EM_CGBITS_1_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT0(__VA_ARGS__))
#define DETAIL_EM_CGBITS_2_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT1(__VA_ARGS__))
#define DETAIL_EM_CGBITS_3_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT2(__VA_ARGS__))
#define DETAIL_EM_CGBITS_4_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT3(__VA_ARGS__))
#define DETAIL_EM_CGBITS_5_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT4(__VA_ARGS__))
#define DETAIL_EM_CGBITS_6_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT5(__VA_ARGS__))
#define DETAIL_EM_CGBITS_7_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT6(__VA_ARGS__))
#define DETAIL_EM_CGBITS_8_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT7(__VA_ARGS__))
