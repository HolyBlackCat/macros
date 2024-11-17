#pragma once

#include "em/macros/meta/classify_list.h"
#include "em/macros/meta/common.h"
#include "em/macros/meta/optional_parens.h"

// Macros to get elements from lists by their indices.


// --- Those fail if the index is out of range:

// Returns ith element in a `(a)(b)(c)` sequence. There can be junk at the end of the sequence, it's ignored.
#define EM_SEQ_AT(i, ...) EM_CAT(EM_SEQ_AT,i)(__VA_ARGS__)
#define EM_SEQ_AT0(...) DETAIL_EM_SEQ_AT0 __VA_ARGS__ ) // Reimplementing `EM_SEQ_FIRST` because `EM_CODEGEN` starts choking if we instead call that here.
#define DETAIL_EM_SEQ_AT0(...) __VA_ARGS__ EM_EMPTY(
#define EM_SEQ_AT1(...) EM_SEQ_AT0(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT2(...) EM_SEQ_AT1(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT3(...) EM_SEQ_AT2(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT4(...) EM_SEQ_AT3(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT5(...) EM_SEQ_AT4(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT6(...) EM_SEQ_AT5(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT7(...) EM_SEQ_AT6(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT8(...) EM_SEQ_AT7(EM_EMPTY __VA_ARGS__)

// Returns ith element in a `a, b, c` sequence.
#define EM_VA_AT(i, ...) EM_CAT(EM_VA_AT,i)(__VA_ARGS__)
#define EM_VA_AT0(x, ...) x
#define EM_VA_AT1(p1, x, ...) x
#define EM_VA_AT2(p1, p2, x, ...) x
#define EM_VA_AT3(p1, p2, p3, x, ...) x
#define EM_VA_AT4(p1, p2, p3, p4, x, ...) x
#define EM_VA_AT5(p1, p2, p3, p4, p5, x, ...) x
#define EM_VA_AT6(p1, p2, p3, p4, p5, p6, x, ...) x
#define EM_VA_AT7(p1, p2, p3, p4, p5, p6, p7, x, ...) x
#define EM_VA_AT8(p1, p2, p3, p4, p5, p6, p7, p8, x, ...) x

// Returns all elements starting from ith, in a `a, b, c` sequence.
#define EM_VA_SKIP(i, ...) EM_CAT(EM_VA_SKIP,i)(__VA_ARGS__)
#define EM_VA_SKIP0(...) __VA_ARGS__
#define EM_VA_SKIP1(p1, ...) __VA_ARGS__
#define EM_VA_SKIP2(p1, p2, ...) __VA_ARGS__
#define EM_VA_SKIP3(p1, p2, p3, ...) __VA_ARGS__
#define EM_VA_SKIP4(p1, p2, p3, p4, ...) __VA_ARGS__
#define EM_VA_SKIP5(p1, p2, p3, p4, p5, ...) __VA_ARGS__
#define EM_VA_SKIP6(p1, p2, p3, p4, p5, p6, ...) __VA_ARGS__
#define EM_VA_SKIP7(p1, p2, p3, p4, p5, p6, p7, ...) __VA_ARGS__
#define EM_VA_SKIP8(p1, p2, p3, p4, p5, p6, p7, p8, ...) __VA_ARGS__


// Returns ith element in `(a)(b)(c)` or `a, b, c` list. Automatically detects the list type.
#define EM_VA_OR_SEQ_AT(i, ...) EM_CAT4(EM_, EM_CLASSIFY_LIST(__VA_ARGS__), _AT, i)(__VA_ARGS__)


// --- Those return nothing if the index is out of range:

// Returns ith element in a `(a)(b)(c)` sequence. There can be junk at the end of the sequence, it's ignored.
// If the index is out of range, returns nothing.
#define EM_SEQ_TRY_AT(i, ...) EM_CAT(EM_SEQ_TRY_AT,i)(__VA_ARGS__)
#define EM_SEQ_TRY_AT0(...) EM_TRY_ONLY_PARENS(__VA_ARGS__)
#define EM_SEQ_TRY_AT1(...) EM_SEQ_TRY_AT0(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT2(...) EM_SEQ_TRY_AT1(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT3(...) EM_SEQ_TRY_AT2(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT4(...) EM_SEQ_TRY_AT3(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT5(...) EM_SEQ_TRY_AT4(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT6(...) EM_SEQ_TRY_AT5(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT7(...) EM_SEQ_TRY_AT6(EM_TRY_SKIP_PARENS(__VA_ARGS__))
#define EM_SEQ_TRY_AT8(...) EM_SEQ_TRY_AT7(EM_TRY_SKIP_PARENS(__VA_ARGS__))

// Returns ith element in a `a, b, c` sequence.
// If the index is out of range, returns nothing.
#define EM_SEQ_TRY_AT(i, ...) EM_CAT(EM_SEQ_TRY_AT,i)(__VA_ARGS__)
#define EM_VA_TRY_AT0(x, ...) x // Same as `EM_VA_AT0`.
#define EM_VA_TRY_AT1(x, ...) __VA_OPT__(EM_VA_TRY_AT0(__VA_ARGS__))
#define EM_VA_TRY_AT2(x, ...) __VA_OPT__(EM_VA_TRY_AT1(__VA_ARGS__))
#define EM_VA_TRY_AT3(x, ...) __VA_OPT__(EM_VA_TRY_AT2(__VA_ARGS__))
#define EM_VA_TRY_AT4(x, ...) __VA_OPT__(EM_VA_TRY_AT3(__VA_ARGS__))
#define EM_VA_TRY_AT5(x, ...) __VA_OPT__(EM_VA_TRY_AT4(__VA_ARGS__))
#define EM_VA_TRY_AT6(x, ...) __VA_OPT__(EM_VA_TRY_AT5(__VA_ARGS__))
#define EM_VA_TRY_AT7(x, ...) __VA_OPT__(EM_VA_TRY_AT6(__VA_ARGS__))
#define EM_VA_TRY_AT8(x, ...) __VA_OPT__(EM_VA_TRY_AT7(__VA_ARGS__))

// Returns all elements starting from ith, in a `a, b, c` sequence.
// If the index is out of range, returns nothing.
#define EM_VA_TRY_SKIP(i, ...) EM_CAT(EM_VA_TRY_SKIP,i)(__VA_ARGS__)
#define EM_VA_TRY_SKIP0(...) __VA_ARGS__
#define EM_VA_TRY_SKIP1(x, ...) __VA_OPT__(EM_VA_TRY_SKIP0(__VA_ARGS__))
#define EM_VA_TRY_SKIP2(x, ...) __VA_OPT__(EM_VA_TRY_SKIP1(__VA_ARGS__))
#define EM_VA_TRY_SKIP3(x, ...) __VA_OPT__(EM_VA_TRY_SKIP2(__VA_ARGS__))
#define EM_VA_TRY_SKIP4(x, ...) __VA_OPT__(EM_VA_TRY_SKIP3(__VA_ARGS__))
#define EM_VA_TRY_SKIP5(x, ...) __VA_OPT__(EM_VA_TRY_SKIP4(__VA_ARGS__))
#define EM_VA_TRY_SKIP6(x, ...) __VA_OPT__(EM_VA_TRY_SKIP5(__VA_ARGS__))
#define EM_VA_TRY_SKIP7(x, ...) __VA_OPT__(EM_VA_TRY_SKIP6(__VA_ARGS__))
#define EM_VA_TRY_SKIP8(x, ...) __VA_OPT__(EM_VA_TRY_SKIP7(__VA_ARGS__))


// Returns ith element in `(a)(b)(c)` or `a, b, c` list. Automatically detects the list type. Returns nothing if out of range.
#define EM_VA_OR_SEQ_TRY_AT(i, ...) EM_CAT4(EM_, EM_CLASSIFY_LIST(__VA_ARGS__), _TRY_AT, i)(__VA_ARGS__)
