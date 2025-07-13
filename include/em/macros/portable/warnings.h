#pragma once

#include "em/macros/meta/common.h"
#include "em/macros/meta/if_else.h"
#include "em/macros/platform/compiler.h"

// Wrap the pragmas.
#if EM_IS_ACTUAL_MSVC
#define EM_DIAGNOSTICS_PUSH _Pragma("warning(push)")
#define EM_DIAGNOSTICS_POP  _Pragma("warning(pop)")
#define EM_DIAGNOSTICS_IGNORE(id) _Pragma(EM_STR(warning(disable: id))) // id = 1234
#else
#define EM_DIAGNOSTICS_PUSH _Pragma("GCC diagnostic push")
#define EM_DIAGNOSTICS_POP  _Pragma("GCC diagnostic pop")
#define EM_DIAGNOSTICS_IGNORE(name) _Pragma(EM_STR(GCC diagnostic ignored name)) // name = "-Wfoo"
#endif


// --- Silencing diagnostics in a block of code:

// Usage `EM_SILENCE_DIAGNOSTIC(id)(code)`.
// Returns `code`, but silences all warnings of kind `id` in it (which is a string literal on GCC/Clang or a numeric ID on MSVC).
// If `id` is empty, returns `code` unchanged.
#define EM_SILENCE_DIAGNOSTIC(...) __VA_OPT__(EM_DIAGNOSTICS_PUSH EM_DIAGNOSTICS_IGNORE(__VA_ARGS__)) EM_CAT(DETAIL_EM_SILENCE_DIAGNOSTIC_, __VA_OPT__(1))
#define DETAIL_EM_SILENCE_DIAGNOSTIC_(...) __VA_ARGS__
#define DETAIL_EM_SILENCE_DIAGNOSTIC_1(...) __VA_ARGS__ EM_DIAGNOSTICS_POP

// This applies conditionally, and is designed to work with the compiler detection macros from `em/macros/platform/compiler.h`.
// Note, using `EM_IDENTITY` to properly expand what is essentially nested `if`s.
#define EM_SILENCE_DIAGNOSTIC_IF(cond_, ...) EM_IDENTITY(EM_IF_01(cond_)(EM_SILENCE_DIAGNOSTIC(__VA_ARGS__))(EM_IDENTITY))


// --- Predefined warning IDs:
//
// Those can be empty for the compilers that don't have them. `EM_SILENCE_DIAGNOSTIC()` handles that out of the box.
//
// The `SILENCE_...(...)` warnings below accept a block of code, and paste it with the warning silenced.

// Using a deprecated entity.
#if EM_IS_ACTUAL_MSVC
#define EM_WARNING_ID_DEPRECATED 4996 // 'X': was declared deprecated
#else
#define EM_WARNING_ID_DEPRECATED "-Wdeprecated-declarations"
#endif
#define EM_SILENCE_DEPRECATION EM_SILENCE_DIAGNOSTIC(EM_WARNING_ID_DEPRECATED)

// A stupid GCC warning that fires for non-template friends every time you do friend injection in stateful metaprogramming.
// Wrap friend declarations (not definitions) in this.
#if EM_IS_ACTUAL_GCC
#define EM_WARNING_ID_NON_TEMPLATE_FRIEND "-Wnon-template-friend"
#else
#define EM_WARNING_ID_NON_TEMPLATE_FRIEND
#endif
#define EM_SILENCE_NON_TEMPLATE_FRIEND EM_SILENCE_DIAGNOSTIC(EM_WARNING_ID_NON_TEMPLATE_FRIEND)

// This warns about ignored attributes. In particular, `[[nodiscard]]` on void functions.
#if EM_IS_CLANG_LIKE
#define EM_WARNING_ID_UNUSED_ATTRIBUTE "-Wignored-attributes"
#elif EM_IS_GCC_LIKE
#define EM_WARNING_ID_UNUSED_ATTRIBUTE "-Wattributes"
#else
#define EM_WARNING_ID_UNUSED_ATTRIBUTE
#endif
#define EM_SILENCE_UNUSED_ATTRIBUTE EM_SILENCE_DIAGNOSTIC(EM_WARNING_ID_UNUSED_ATTRIBUTE)
