#pragma once

// Wraps non-standard `__has_...(...)` macros, returning zero if not available.

#ifdef __has_attribute
#define M_HAS_ATTRIBUTE(...) __has_attribute(__VA_ARGS__)
#else
#define M_HAS_ATTRIBUTE(...) 0
#endif

#ifdef __has_builtin
#define M_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
#define M_HAS_BUILTIN(...) 0
#endif
