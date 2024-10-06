#pragma once

// If a function is marked `EM_ARTIFICIAL` and is inlined, the debugger will show the caller location rather than the callee.
// Mark small functions with this to avoid seeing them when debugging.

// Not including `platform/language_version.h` for simplicity.

// Example: `EM_ARTIFICIAL inline void foo()`. Or a lambda: `[]() EM_ARTIFICIAL {...}`.
// The function must be marked `inline`, GCC and Clang warn otherwise.
// Not adding `inline` automatically to avoid it conflicting with `EM_ALWAYS_INLINE`, which also has to add it, and is more common.
#ifndef EM_ARTIFICIAL
#if defined(_MSC_VER) && !defined(__clang__)
#define EM_ARTIFICIAL // MSVC doesn't support this.
#else
#define EM_ARTIFICIAL __attribute__((__artificial__))
#endif
#endif
