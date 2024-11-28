#pragma once

#include "em/macros/meta/common.h"

// If `...` is empty, returns `fallback` (with parentheses stripped). Otherwise returns `...` unchanged.
// `fallback` must be parenthesized.
#define EM_FALLBACK_IF_EMPTY(fallback, ...) EM_CAT(DETAIL_EM_FALLBACK_IF_EMPTY_,__VA_OPT__(1))(fallback, __VA_ARGS__)
#define DETAIL_EM_FALLBACK_IF_EMPTY_(fallback, ...) EM_IDENTITY fallback
#define DETAIL_EM_FALLBACK_IF_EMPTY_1(fallback, ...) __VA_ARGS__

// `EM_IF_EMPTY((cond),(a),(b))` expands to `a` if `cond` is empty, or to `b` if it's not empty.
#define EM_IF_EMPTY(cond, a, b) DETAIL_EM_IF_EMPTY(a, b, EM_IDENTITY cond)
#define DETAIL_EM_IF_EMPTY(a, b, .../*cond*/) EM_CAT(DETAIL_EM_IF_EMPTY_, __VA_OPT__(1))(a, b)
#define DETAIL_EM_IF_EMPTY_(a, b) EM_IDENTITY a
#define DETAIL_EM_IF_EMPTY_1(a, b) EM_IDENTITY b

// `EM_IF_COMMA((cond),(a),(b))` expands to `a` if `cond` contains at least one comma, or to `b` otherwise.
#define EM_IF_COMMA(cond, a, b) DETAIL_EM_IF_COMMA(EM_IDENTITY cond x)(a, b)
#define DETAIL_EM_IF_COMMA(...) DETAIL_EM_IF_COMMA_A(__VA_ARGS__)
#define DETAIL_EM_IF_COMMA_A(unused, ...) EM_CAT(DETAIL_EM_IF_COMMA_, __VA_OPT__(1))
#define DETAIL_EM_IF_COMMA_(a, b) EM_IDENTITY b
#define DETAIL_EM_IF_COMMA_1(a, b) EM_IDENTITY a
