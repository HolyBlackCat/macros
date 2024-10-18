#pragma once

#include "em/macros/meta/classify_list.h"
#include "em/macros/meta/common.h"


// Macros get elements from lists by index.


// Given `(a)...`, returns `a`.
// If you want to return 2th+ element, use
#define EM_SEQ_AT0(...) DETAIL_EM_SEQ_AT0 __VA_ARGS__ )
#define DETAIL_EM_SEQ_AT0(...) __VA_ARGS__ EM_EMPTY(

// Given `(a)(b)...`, returns `b`, and so on.
#define EM_SEQ_AT1(...) EM_SEQ_AT0(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT2(...) EM_SEQ_AT1(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT3(...) EM_SEQ_AT2(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT4(...) EM_SEQ_AT3(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT5(...) EM_SEQ_AT4(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT6(...) EM_SEQ_AT5(EM_EMPTY __VA_ARGS__)
#define EM_SEQ_AT7(...) EM_SEQ_AT6(EM_EMPTY __VA_ARGS__)


// Given `a, ...` (or just `a`) returns `a`.
#define EM_VA_AT0(x, ...) x
// Given `a, b, ...` (or just `a, b`) returns `b`, and so on..
#define EM_VA_AT1(p1, x, ...) x
#define EM_VA_AT2(p1, p2, x, ...) x
#define EM_VA_AT3(p1, p2, p3, x, ...) x
#define EM_VA_AT4(p1, p2, p3, p4, x, ...) x
#define EM_VA_AT5(p1, p2, p3, p4, p5, x, ...) x
#define EM_VA_AT6(p1, p2, p3, p4, p5, p6, x, ...) x
#define EM_VA_AT7(p1, p2, p3, p4, p5, p6, p7, x, ...) x


// Returns ith element in `(a)(b)(c)` or `a, b, c` list. Automatically detects the list type.
#define EM_VA_OR_SEQ_AT(i, ...) EM_CAT4(EM_, EM_CLASSIFY_LIST(__VA_ARGS__), _AT, i)(__VA_ARGS__)
