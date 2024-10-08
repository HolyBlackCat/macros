#pragma once

#include "em/macros/meta/common.h"
#include "em/macros/meta/compare_versions.h"

// Compiler detection.
//
// * GCC:                 EM_IS_GCC_LIKE    EM_IS_ACTUAL_GCC
// * Clang:               EM_IS_GCC_LIKE    EM_IS_ACTUAL_CLANG   EM_IS_CLANG_LIKE
// * Apple Clang:         EM_IS_GCC_LIKE    EM_IS_APPLE_CLANG    EM_IS_CLANG_LIKE
// * Clang in MSVC mode:  EM_IS_MSVC_LIKE   EM_IS_ACTUAL_CLANG   EM_IS_CLANG_LIKE
// * MSVC:                EM_IS_MSVC_LIKE   EM_IS_ACTUAL_MSVC

//
// Strings:
//   EM_STRING_COMPILER                 - name
//   EM_STRING_COMPILER_VERSION[_LONG]  - version (GCC/Clang: X.Y.Z, _LONG: with date (GCC) or commit hash (Clang); MSVC: 19XX, _LONG: 19XXyyyyy).
//
// Version number:
//   EM_COMPILER_VERSION:
//     For GCC and Clang, 6 digits: 2 major, 2 minor, 2 patchlevel.
//     For MSVC, 4+5 digits: 19XXyyyyy
//
// Version number checks:
//   (Doesn't check minor versions if you don't specify them.) (Always false if wrong compiler.) (Can use any comparison operator, not only `==`.)
//   EM_IS_GCC_VERSION(== 14)           EM_IS_GCC_VERSION(== 14,2)             EM_IS_GCC_VERSION(== 14,2,1)
//   EM_IS_CLANG_VERSION(== 18)         EM_IS_CLANG_VERSION(== 18,1)           EM_IS_CLANG_VERSION(== 18,1,5)
//   EM_IS_APPLE_CLANG_VERSION(== 18)   EM_IS_APPLE_CLANG_VERSION(== 18,1)     EM_IS_APPLE_CLANG_VERSION(== 18,1,5)
//   EM_IS_MSVC_VERSION(== 1938)        EM_IS_MSVC_VERSION(== 1938,33133)
//
//   Note, Apple Clang always returns false from `EM_IS_CLANG_VERSION`, use `EM_IS_APPLE_CLANG_VERSION`


// Compiler name.
#if defined(_MSC_VER)
#  define EM_IS_MSVC_LIKE 1
#  ifdef __clang__
#    define EM_STRING_COMPILER "Clang (with MSVC ABI)"
#    define EM_IS_ACTUAL_CLANG 1
#    define EM_IS_CLANG_LIKE 1
#  else
#    define EM_STRING_COMPILER "MSVC"
#    define EM_IS_ACTUAL_MSVC 1
#  endif
#elif defined(__GNUC__)
#  define EM_IS_GCC_LIKE 1
#  ifdef __clang__
#    ifdef __apple_build_version__
#      define EM_STRING_COMPILER "Apple Clang"
#      define EM_IS_APPLE_CLANG 1
#    else
#      ifdef _WIN32
#        define EM_STRING_COMPILER "MinGW Clang"
#      else
#        define EM_STRING_COMPILER "Clang"
#      endif
#      define EM_IS_ACTUAL_CLANG 1
#    endif
#    define EM_IS_CLANG_LIKE 1
#  else
#    ifdef _WIN32
#      define EM_STRING_COMPILER "MinGW GCC"
#    else
#      define EM_STRING_COMPILER "GCC"
#    endif
#    define EM_IS_ACTUAL_GCC 1
#  endif
#else
#  define EM_STRING_COMPILER "Unknown compiler"
#endif

#ifndef EM_IS_ACTUAL_CLANG
#define EM_IS_ACTUAL_CLANG 0
#endif
#ifndef EM_IS_ACTUAL_GCC
#define EM_IS_ACTUAL_GCC 0
#endif
#ifndef EM_IS_ACTUAL_MSVC
#define EM_IS_ACTUAL_MSVC 0
#endif
#ifndef EM_IS_APPLE_CLANG
#define EM_IS_APPLE_CLANG 0
#endif
#ifndef EM_IS_CLANG_LIKE
#define EM_IS_CLANG_LIKE 0
#endif
#ifndef EM_IS_GCC_LIKE
#define EM_IS_GCC_LIKE 0
#endif
#ifndef EM_IS_MSVC_LIKE
#define EM_IS_MSVC_LIKE 0
#endif

// Version:
#if defined(__clang__)
#  define EM_STRING_COMPILER_VERSION EM_STR(__clang_major__) "." EM_STR(__clang_minor__) "." EM_STR(__clang_patchlevel__)
#  define EM_STRING_COMPILER_VERSION_LONG __clang_version__
#  define EM_COMPILER_VERSION (__clang_major__*10000 + __clang_minor__*100 + __clang_patchlevel__)
#  ifdef __apple_build_version__ // We don't stringify this macro because it's included in __apple_build_version__. We also don't read the value of this macro because it doesn't add any new information compared to the x.y.z clang version. The numbers are the major one are differnet, but they advance at the same time, so whatever.
#    define EM_IS_APPLE_CLANG_VERSION(...) EM_COMPARE_VERSION3(100, 100, EM_COMPILER_VERSION, __VA_ARGS__)
#  else
#    define EM_IS_CLANG_VERSION(...) EM_COMPARE_VERSION3(100, 100, EM_COMPILER_VERSION, __VA_ARGS__)
#  endif
#elif defined(__GNUC__)
// Can't reuse this in Clang, because there it reports an ancient GCC version.
#  define EM_STRING_COMPILER_VERSION EM_STR(__GNUC__) "." EM_STR(__GNUC_MINOR__) "." EM_STR(__GNUC_PATCHLEVEL__)
#  define EM_STRING_COMPILER_VERSION_LONG __VERSION__
#  define EM_COMPILER_VERSION (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#  define EM_IS_GCC_VERSION(...) EM_COMPARE_VERSION3(100, 100, EM_COMPILER_VERSION, __VA_ARGS__)
#elif defined(_MSC_VER)
#  define EM_STRING_COMPILER_VERSION EM_STR(_MSC_VER)
#  define EM_STRING_COMPILER_VERSION_LONG EM_STR(_MSC_FULL_VER)
#  define EM_COMPILER_VERSION _MSC_FULL_VER // Divide by 100000 to get _MSC_VER.
#  define EM_IS_MSVC_VERSION(...) EM_COMPARE_VERSION2(100000, EM_COMPILER_VERSION, __VA_ARGS__)
#else
#  define EM_STRING_COMPILER_VERSION ""
#  define EM_STRING_COMPILER_VERSION_LONG ""
#  define EM_COMPILER_VERSION 0
#endif

#ifndef EM_IS_APPLE_CLANG_VERSION
#define EM_IS_APPLE_CLANG_VERSION(...) 0
#endif
#ifndef EM_IS_CLANG_VERSION
#define EM_IS_CLANG_VERSION(...) 0
#endif
#ifndef EM_IS_GCC_VERSION
#define EM_IS_GCC_VERSION(...) 0
#endif
#ifndef EM_IS_MSVC_VERSION
#define EM_IS_MSVC_VERSION(...) 0
#endif
