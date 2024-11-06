#pragma once

#include "em/macros/meta/common.h"

// If `...` is empty, returns `fallback` (with parentheses stripped). Otherwise returns `...` unchanged.
// `fallback` must be parenthesized.
#define EM_FALLBACK_IF_EMPTY(fallback, ...) EM_CAT(DETAIL_EM_FALLBACK_IF_EMPTY_,__VA_OPT__(1))(fallback, __VA_ARGS__)
#define DETAIL_EM_FALLBACK_IF_EMPTY_(fallback, ...) EM_IDENTITY fallback
#define DETAIL_EM_FALLBACK_IF_EMPTY_1(fallback, ...) __VA_ARGS__
