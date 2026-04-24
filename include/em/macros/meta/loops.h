#pragma once

#include "em/macros/meta/common.h"

// Some tech based on loops.

// Given `(a)(b)(c)`, returns `a)(b)(c`.
// If given 1 or 0 elements, returns empty.
// This can be used to forward macro arguments from one macro to another, by wrapping them in `EM_IMPLICIT_SEQ((...))`.
// This can't handle removing more than one set of parentheses, e.g. `((a))((b))` -> `a))((b`.
#define EM_IMPLICIT_SEQ(seq) EM_IDENTITY( DETAIL_EM_IMPLICIT_SEQ_LOOP_0 EM_LPAREN EM_IDENTITY( DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_A EM_END(DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_A seq) ) )

// `EM_END(DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_A seq)` converts `seq` from e.g. `(a)(b)(c)` to `(1)(a)(1)(b)(1)(c)()`.
// We must do it in a separate loop, rather than directly in `DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_A()`,
//   because adding extra information at the end requires wrapping everything in another macro.
#define DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_A(...) (1)(__VA_ARGS__)DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_B
#define DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_B(...) (1)(__VA_ARGS__)DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_A
#define DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_A_END ()
#define DETAIL_EM_IMPLICIT_SEQ_ANNOTATE_B_END ()

// `DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_A seq` converts `seq` from e.g. `(1)(a)(1)(b)(1)(c)()` to `1)a)1)b)1)c))`.
// We call the resulting sequence `a)b)c)` a "guide".
#define DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_A(...) __VA_ARGS__) __VA_OPT__(DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_B)
#define DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_B(...) __VA_ARGS__) DETAIL_EM_IMPLICIT_SEQ_MAKE_GUIDE_A

#define DETAIL_EM_IMPLICIT_SEQ_LOOP_0(...) __VA_OPT__(DETAIL_EM_IMPLICIT_SEQ_LOOP_0_(__VA_ARGS__))
#define DETAIL_EM_IMPLICIT_SEQ_LOOP_0_(...) DETAIL_EM_IMPLICIT_SEQ_LOOP_B(
#define DETAIL_EM_IMPLICIT_SEQ_LOOP_A(...) __VA_OPT__(DETAIL_EM_IMPLICIT_SEQ_LOOP_A_(__VA_ARGS__))
#define DETAIL_EM_IMPLICIT_SEQ_LOOP_A_(...) )( DETAIL_EM_IMPLICIT_SEQ_LOOP_B(
#define DETAIL_EM_IMPLICIT_SEQ_LOOP_B(...) __VA_ARGS__ DETAIL_EM_IMPLICIT_SEQ_LOOP_A(
