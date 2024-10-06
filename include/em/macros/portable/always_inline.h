#pragma once

// Those macros force inlining.
// Not including `platform/language_version.h` for simplicity.

// Example: `EM_ALWAYS_INLINE void foo()`
#ifndef EM_ALWAYS_INLINE
#if defined(_MSC_VER) && !defined(__clang__)
// GCC warns if there's no normal `inline` as well ("might not be inlinable").
// Not sure if it matters on all compilers, but marking `inline` everywhere just in case.
#define EM_ALWAYS_INLINE inline __forceinline
#else
#define EM_ALWAYS_INLINE inline __attribute__((__always_inline__))
#endif
#endif

// Example: `[]() EM_ALWAYS_INLINE_LAMBDA {...}`.
#ifndef EM_ALWAYS_INLINE_LAMBDA
#if defined(_MSC_VER) && !defined(__clang__)
#define EM_ALWAYS_INLINE_LAMBDA [[msvc::forceinline]] // MSVC doesn't like `__forceinline` on lambdas.
#else
#define EM_ALWAYS_INLINE_LAMBDA __attribute__((__always_inline__))
#endif
#endif
