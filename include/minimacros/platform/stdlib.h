#pragma once

#include <minimacros/meta/compare_versions.h>
#include <minimacros/utils/common.h>

// C++ stadnard library detection.
//
// Strings:
//   Name: M_STRING_CPP_STDLIB
//   Version: M_STRING_CPP_STDLIB_VERSION
//   Version date: M_STRING_CPP_STDLIB_DATE - libstdc++: YYYYmmDD; MSVC STL: YYYYmm (then 'L'), libc++: empty (M_CPP_STDLIB_DATE == 0).
//
// Bools:
//   M_IS_LIBSTDCXX, M_IS_LIBCPP, M_IS_MSVC_STL, M_IS_CPP_STDLIB_MISSING (all can be false if the C++ standard library exists but is unknown).
//
// Version numbers:
//   M_CPP_STDLIB_VERSION - libstdc++: major version; libc++: 6 digits: 2 major, 2 minor, 2 patch; MSVC STL: 3 digits (14x)
//   M_CPP_STDLIB_DATE - libstdc++: YYYYmmDD; MSVC STL: YYYYmm (then 'L'), libc++: 0
//
// Version number checks:
//   (Doesn't check minor versions if you don't specify them.) (Always false if wrong compiler.) (Can use any comparison operator, not only `==`.)
// * libstdc++:
//     M_IS_LIBSTDCXX_VERSION(== 14)
//     M_IS_LIBSTDCXX_DATE(== YYYY)   M_IS_LIBSTDCXX_DATE(== YYYY,mm)   M_IS_LIBSTDCXX_DATE(== YYYY,mm,DD)
// * libc++:
//     M_IS_LIBCXX_VERSION(== 18)     M_IS_LIBCXX_VERSION(== 18,1)      M_IS_LIBCXX_VERSION(== 18,1,0)
// * MSVC STL:
//     M_IS_MSVC_STL_VERSION(== 143)
//     M_IS_MSVC_STL_DATE(== 2023)    M_IS_MSVC_STL_DATE(== 2023,8)

#if __has_include(<version>)
#include <version>
#elif __has_include(<ciso646>) // Removed in C++20. `<iso646.h>` doesn't define the C++ macros.
#include <ciso646>
#else
#define M_IS_CPP_STDLIB_MISSING 1
#endif

#if defined(_GLIBCXX_RELEASE)
#  define M_IS_LIBSTDCXX 1
#  define M_STRING_CPP_STDLIB "libstdc++"
#  define M_CPP_STDLIB_VERSION _GLIBCXX_RELEASE
#  define M_CPP_STDLIB_DATE __GLIBCXX__
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_CPP_STDLIB_VERSION)
#  define M_STRING_CPP_STDLIB_DATE M_STR(M_CPP_STDLIB_DATE)
#  define M_IS_LIBSTDCXX_VERSION(...) M_COMPARE_VERSION1(M_CPP_STDLIB_VERSION, __VA_ARGS__)
#  define M_IS_LIBSTDCXX_DATE(...) M_COMPARE_VERSION3(100, 100, M_CPP_STDLIB_DATE, __VA_ARGS__)
#elif defined(_LIBCPP_VERSION)
#  define M_IS_LIBCPP 1
#  define M_STRING_CPP_STDLIB "libc++"
#  define M_CPP_STDLIB_VERSION _LIBCPP_VERSION
#  define M_CPP_STDLIB_DATE 0
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_CPP_STDLIB_VERSION)
#  define M_STRING_CPP_STDLIB_DATE ""
#  define M_IS_LIBCPP_VERSION(...) M_COMPARE_VERSION3(100, 100, M_CPP_STDLIB_VERSION, __VA_ARGS__)
#elif defined(_MSVC_STL_VERSION)
#  define M_IS_MSVC_STL 1
#  define M_STRING_CPP_STDLIB "MSVC STL"
#  define M_CPP_STDLIB_VERSION _MSVC_STL_VERSION
#  define M_CPP_STDLIB_DATE _MSVC_STL_UPDATE
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_CPP_STDLIB_VERSION)
#  define M_STRING_CPP_STDLIB_DATE M_STR(M_CPP_STDLIB_DATE)
#  define M_IS_MSVC_STL_VERSION(...) M_COMPARE_VERSION1(M_CPP_STDLIB_VERSION, __VA_ARGS__)
#  define M_IS_MSVC_STL_DATE(...) M_COMPARE_VERSION2(100, M_CPP_STDLIB_DATE, __VA_ARGS__)
#else
#  define M_STRING_CPP_STDLIB "Unknown C++ standard library"
#  define M_CPP_STDLIB_VERSION 0
#  define M_CPP_STDLIB_DATE 0
#  define M_STRING_CPP_STDLIB_VERSION ""
#  define M_STRING_CPP_STDLIB_DATE ""
#endif

#ifndef M_IS_CPP_STDLIB_MISSING
#define M_IS_CPP_STDLIB_MISSING 0
#endif
#ifndef M_IS_LIBCPP
#define M_IS_LIBCPP 0
#endif
#ifndef M_IS_LIBCPP_VERSION
#define M_IS_LIBCPP_VERSION(...) 0
#endif
#ifndef M_IS_LIBSTDCXX
#define M_IS_LIBSTDCXX 0
#endif
#ifndef M_IS_LIBSTDCXX_DATE
#define M_IS_LIBSTDCXX_DATE(...) 0
#endif
#ifndef M_IS_LIBSTDCXX_VERSION
#define M_IS_LIBSTDCXX_VERSION(...) 0
#endif
#ifndef M_IS_MSVC_STL
#define M_IS_MSVC_STL 0
#endif
#ifndef M_IS_MSVC_STL_DATE
#define M_IS_MSVC_STL_DATE(...) 0
#endif
#ifndef M_IS_MSVC_STL_VERSION
#define M_IS_MSVC_STL_VERSION(...) 0
#endif
