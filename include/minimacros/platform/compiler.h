#pragma once

#include <minimacros/utils/common.h>
#include <minimacros/meta/compare_versions.h>

// Compiler detection.
//
// * GCC:                 M_IS_GCC_LIKE    M_IS_ACTUAL_GCC
// * Clang:               M_IS_GCC_LIKE    M_IS_ACTUAL_CLANG   M_IS_CLANG_LIKE
// * Apple Clang:         M_IS_GCC_LIKE    M_IS_APPLE_CLANG    M_IS_CLANG_LIKE
// * Clang in MSVC mode:  M_IS_MSVC_LIKE   M_IS_ACTUAL_CLANG   M_IS_CLANG_LIKE
// * MSVC:                M_IS_MSVC_LIKE   M_IS_ACTUAL_MSVC

//
// Strings:
//   M_STRING_COMPILER                 - name
//   M_STRING_COMPILER_VERSION[_LONG]  - version (GCC/Clang: X.Y.Z, _LONG: with date (GCC) or commit hash (Clang); MSVC: 19XX, _LONG: 19XXyyyyy).
//
// Version number:
//   M_COMPILER_VERSION:
//     For GCC and Clang, 6 digits: 2 major, 2 minor, 2 patchlevel.
//     For MSVC, 4+5 digits: 19XXyyyyy
//
// Version number checks:
//   (Doesn't check minor versions if you don't specify them.) (Always false if wrong compiler.) (Can use any comparison operator, not only `==`.)
//   M_IS_GCC_VERSION(== 14)           M_IS_GCC_VERSION(== 14,2)             M_IS_GCC_VERSION(== 14,2,1)
//   M_IS_CLANG_VERSION(== 18)         M_IS_CLANG_VERSION(== 18,1)           M_IS_CLANG_VERSION(== 18,1,5)
//   M_IS_APPLE_CLANG_VERSION(== 18)   M_IS_APPLE_CLANG_VERSION(== 18,1)     M_IS_APPLE_CLANG_VERSION(== 18,1,5)
//   M_IS_MSVC_VERSION(== 1938)        M_IS_MSVC_VERSION(== 1938,33133)
//
//   Note, Apple Clang always returns false from `M_IS_CLANG_VERSION`, use `M_IS_APPLE_CLANG_VERSION`


// Compiler name.
#if defined(_MSC_VER)
#  define M_IS_MSVC_LIKE 1
#  ifdef __clang__
#    define M_STRING_COMPILER "Clang (with MSVC ABI)"
#    define M_IS_ACTUAL_CLANG 1
#    define M_IS_CLANG_LIKE 1
#  else
#    define M_STRING_COMPILER "MSVC"
#    define M_IS_ACTUAL_MSVC 1
#  endif
#elif defined(__GNUC__)
#  define M_IS_GCC_LIKE 1
#  ifdef __clang__
#    ifdef __apple_build_version__
#      define M_STRING_COMPILER "Apple Clang"
#      define M_IS_APPLE_CLANG 1
#    else
#      ifdef _WIN32
#        define M_STRING_COMPILER "MinGW Clang"
#      else
#        define M_STRING_COMPILER "Clang"
#      endif
#      define M_IS_ACTUAL_CLANG 1
#    endif
#    define M_IS_CLANG_LIKE 1
#  else
#    ifdef _WIN32
#      define M_STRING_COMPILER "MinGW GCC"
#    else
#      define M_STRING_COMPILER "GCC"
#    endif
#    define M_IS_ACTUAL_GCC 1
#  endif
#else
#  define M_STRING_COMPILER "Unknown compiler"
#endif

#ifndef M_IS_ACTUAL_CLANG
#define M_IS_ACTUAL_CLANG 0
#endif
#ifndef M_IS_ACTUAL_GCC
#define M_IS_ACTUAL_GCC 0
#endif
#ifndef M_IS_ACTUAL_MSVC
#define M_IS_ACTUAL_MSVC 0
#endif
#ifndef M_IS_APPLE_CLANG
#define M_IS_APPLE_CLANG 0
#endif
#ifndef M_IS_CLANG_LIKE
#define M_IS_CLANG_LIKE 0
#endif
#ifndef M_IS_GCC_LIKE
#define M_IS_GCC_LIKE 0
#endif
#ifndef M_IS_MSVC_LIKE
#define M_IS_MSVC_LIKE 0
#endif

// Version:
#if defined(__clang__)
#  define M_STRING_COMPILER_VERSION M_STR(__clang_major__) "." M_STR(__clang_minor__) "." M_STR(__clang_patchlevel__)
#  define M_STRING_COMPILER_VERSION_LONG __clang_version__
#  define M_COMPILER_VERSION (__clang_major__*10000 + __clang_minor__*100 + __clang_patchlevel__)
#  ifdef __apple_build_version__ // We don't stringify this macro because it's included in __apple_build_version__. We also don't read the value of this macro because it doesn't add any new information compared to the x.y.z clang version. The numbers are the major one are differnet, but they advance at the same time, so whatever.
#    define M_IS_APPLE_CLANG_VERSION(...) M_COMPARE_VERSION3(100, 100, M_COMPILER_VERSION, __VA_ARGS__)
#  else
#    define M_IS_CLANG_VERSION(...) M_COMPARE_VERSION3(100, 100, M_COMPILER_VERSION, __VA_ARGS__)
#  endif
#elif defined(__GNUC__)
// Can't reuse this in Clang, because there it reports an ancient GCC version.
#  define M_STRING_COMPILER_VERSION M_STR(__GNUC__) "." M_STR(__GNUC_MINOR__) "." M_STR(__GNUC_PATCHLEVEL__)
#  define M_STRING_COMPILER_VERSION_LONG __VERSION__
#  define M_COMPILER_VERSION (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#  define M_IS_GCC_VERSION(...) M_COMPARE_VERSION3(100, 100, M_COMPILER_VERSION, __VA_ARGS__)
#elif defined(_MSC_VER)
#  define M_STRING_COMPILER_VERSION M_STR(_MSC_VER)
#  define M_STRING_COMPILER_VERSION_LONG M_STR(_MSC_FULL_VER)
#  define M_COMPILER_VERSION _MSC_FULL_VER // Divide by 100000 to get _MSC_VER.
#  define M_IS_MSVC_VERSION(...) M_COMPARE_VERSION2(100000, M_COMPILER_VERSION, __VA_ARGS__)
#else
#  define M_STRING_COMPILER_VERSION ""
#  define M_STRING_COMPILER_VERSION_LONG ""
#  define M_COMPILER_VERSION 0
#endif

#ifndef M_IS_APPLE_CLANG_VERSION
#define M_IS_APPLE_CLANG_VERSION(...) 0
#endif
#ifndef M_IS_CLANG_VERSION
#define M_IS_CLANG_VERSION(...) 0
#endif
#ifndef M_IS_GCC_VERSION
#define M_IS_GCC_VERSION(...) 0
#endif
#ifndef M_IS_MSVC_VERSION
#define M_IS_MSVC_VERSION(...) 0
#endif
