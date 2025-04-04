#pragma once

// `EM_PLACEHOLDER_VARIABLE` expands to `_` if the compiler supports the placeholder names, or to a unique name otherwise.
// In the latter case we use `__COUNTER__`. Alternatively we could use `__LINE__`. The counter-based approach technically violates ODR,
//   but I haven't heard of it causing issues in practice, so hopefully it's fine? Especially for a fallback strategy for old compilers.
// The line-based approach doesn't have that issue, but it might have collisions in macros, or if the user likes ugly oneliners.

#if __cpp_placeholder_variables
#define EM_PLACEHOLDER_VARIABLE _
#else
#define EM_PLACEHOLDER_VARIABLE DETAIL_EM_PLACEHOLDER_VARIABLE(__COUNTER__)
// Reimplementing `EM_CAT()` to avoid including that header.
#define DETAIL_EM_PLACEHOLDER_VARIABLE(_counter) DETAIL_EM_PLACEHOLDER_VARIABLE_(_counter)
#define DETAIL_EM_PLACEHOLDER_VARIABLE_(_counter) _em_placeholder_##_counter
#endif
