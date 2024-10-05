#pragma once

// Those macros prevent the debugger from stepping into functions if they are inlined.
// Not including `platform/language_version.h` for simplicity.

// Example: `EM_AVOID_STEPPING_INTO inline void foo()`. Or a lambda: `[]() EM_AVOID_STEPPING_INTO {...}`.
// The function must be marked `inline`, GCC and Clang warn otherwise.
// Not adding `inline` automatically to avoid it conflicting with `EM_FORCE_INLINE`, which also has to add it, and is more common.
#ifndef EM_AVOID_STEPPING_INTO
#if defined(_MSC_VER) && !defined(__clang__)
#define EM_AVOID_STEPPING_INTO // MSVC doesn't support this.
#else
#define EM_AVOID_STEPPING_INTO __attribute__((__artificial__))
#endif
#endif
