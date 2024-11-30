#pragma once

#include "em/macros/meta/common.h"

// `EM_IF_NONEMPTY(cond)(a)(b)` expands to `a` if `cond` isn't empty, or to `b` if it is empty. All parts can contain commas.
#define EM_IF_NONEMPTY(...) EM_CAT(DETAIL_EM_IF_NONEMPTY_, __VA_OPT__(1))
#define DETAIL_EM_IF_NONEMPTY_(...) DETAIL_EM_IF_ELSE_1
#define DETAIL_EM_IF_NONEMPTY_1(...) __VA_ARGS__ DETAIL_EM_IF_ELSE_
#define DETAIL_EM_IF_ELSE_(...)
#define DETAIL_EM_IF_ELSE_1(...) __VA_ARGS__

// If `...` isn't empty, returns it unchanged. Otherwise returns `fallback`.
// `fallback` can contain delayed commas.
#define EM_FALLBACK_IF_EMPTY(fallback, ...) EM_IF_NONEMPTY(__VA_ARGS__)(__VA_ARGS__)(fallback)

// `EM_IF_COMMA(cond)(a)(b)` expands to `a` if `cond` contains at least one comma, or to `b` otherwise. `a` and `b` are allowed to contain commas.
#define EM_IF_COMMA(...) DETAIL_EM_IF_COMMA(__VA_ARGS__ x)
#define DETAIL_EM_IF_COMMA(unused, ...) EM_CAT(DETAIL_EM_IF_NONEMPTY_, __VA_OPT__(1))
