#pragma once

// Detect legacy MSVC preprocessor:
//   (At most one is true at the same time.)
//   M_IS_LEGACY_MSVC_PREPROCESSOR - old MSVC preprocessor.
//   M_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION - Clang pretends to be the old MSVC preprocessor, with its own quirks.
//   Neither - sane preprocessor.
//
// Detect __VA_OPT__ support:
//   M_HAS_VA_OPT

#if defined(_MSC_VER) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL == 1)
#  ifdef __clang__
#    define M_IS_LEGACY_MSVC_PREPROCESSOR 0
#    define M_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION 1
#  else
#    define M_IS_LEGACY_MSVC_PREPROCESSOR 1
#    define M_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION 0
#  endif
#else
#  define M_IS_LEGACY_MSVC_PREPROCESSOR 0
#  define M_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION 0
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#  if M_IS_LEGACY_MSVC_PREPROCESSOR
#    define M_HAS_VA_OPT 0
#  elif _MSVC_LANG >= 202000 // Not including `language_version.h` to avoid circular dependency.
#    define M_HAS_VA_OPT 1
#  else
#    define M_HAS_VA_OPT 0
#  endif
#else
#  if __cplusplus >= 202000 // Not including `language_version.h` to avoid circular dependency.
#    define M_HAS_VA_OPT 1
#  else
#    define M_HAS_VA_OPT 0
#  endif
#endif
