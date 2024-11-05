#pragma once

#include "em/macros/meta/common.h"

// If `x` is empty, returns `...`. Otherwise returns `x` unchanged.
// `x` can contain commas. If they're getting expanded to early, wrap the first argument in `EM_IDENTITY(...)`.
#define EM_FALLBACK_IF_EMPTY(x, ...) DETAIL_EM_FALLBACK_IF_EMPTY((__VA_ARGS__), x)
#define DETAIL_EM_FALLBACK_IF_EMPTY(y, ...) EM_CAT(DETAIL_EM_FALLBACK_IF_EMPTY_,__VA_OPT__(1))(y, __VA_ARGS__)
#define DETAIL_EM_FALLBACK_IF_EMPTY_(y, ...) EM_IDENTITY y
#define DETAIL_EM_FALLBACK_IF_EMPTY_1(y, ...) __VA_ARGS__
