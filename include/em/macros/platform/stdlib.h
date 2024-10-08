#pragma once

#include "em/macros/meta/compare_versions.h"
#include "em/macros/meta/common.h"

// C++ stadnard library detection.
//
// Strings:
//   Name: EM_STRING_CPP_STDLIB
//   Version: EM_STRING_CPP_STDLIB_VERSION
//   Version date: EM_STRING_CPP_STDLIB_DATE - libstdc++: YYYYmmDD; MSVC STL: YYYYmm (then 'L'), libc++: empty (EM_CPP_STDLIB_DATE == 0).
//
// Bools:
//   EM_IS_LIBSTDCXX, EM_IS_LIBCPP, EM_IS_MSVC_STL, EM_IS_CPP_STDLIB_MISSING (all can be false if the C++ standard library exists but is unknown).
//
// Version numbers:
//   EM_CPP_STDLIB_VERSION - libstdc++: major version; libc++: 6 digits: 2 major, 2 minor, 2 patch; MSVC STL: 3 digits (14x)
//   EM_CPP_STDLIB_DATE - libstdc++: YYYYmmDD; MSVC STL: YYYYmm (then 'L'), libc++: 0
//
// Version number checks:
//   (Doesn't check minor versions if you don't specify them.) (Always false if wrong compiler.) (Can use any comparison operator, not only `==`.)
// * libstdc++:
//     EM_IS_LIBSTDCXX_VERSION(== 14)
//     EM_IS_LIBSTDCXX_DATE(== YYYY)   EM_IS_LIBSTDCXX_DATE(== YYYY,mm)   EM_IS_LIBSTDCXX_DATE(== YYYY,mm,DD)
// * libc++:
//     EM_IS_LIBCXX_VERSION(== 18)     EM_IS_LIBCXX_VERSION(== 18,1)      EM_IS_LIBCXX_VERSION(== 18,1,0)
// * MSVC STL:
//     EM_IS_MSVC_STL_VERSION(== 143)
//     EM_IS_MSVC_STL_DATE(== 2023)    EM_IS_MSVC_STL_DATE(== 2023,8)

#if __has_include(<version>)
#include <version>
#elif __has_include(<ciso646>) // Removed in C++20. `<iso646.h>` doesn't define the C++ macros.
#include <ciso646>
#else
#define EM_IS_CPP_STDLIB_MISSING 1
#endif

#if defined(_GLIBCXX_RELEASE)
#  define EM_IS_LIBSTDCXX 1
#  define EM_STRING_CPP_STDLIB "libstdc++"
#  define EM_CPP_STDLIB_VERSION _GLIBCXX_RELEASE
#  define EM_CPP_STDLIB_DATE __GLIBCXX__
#  define EM_STRING_CPP_STDLIB_VERSION EM_STR(EM_CPP_STDLIB_VERSION)
#  define EM_STRING_CPP_STDLIB_DATE EM_STR(EM_CPP_STDLIB_DATE)
#  define EM_IS_LIBSTDCXX_VERSION(...) EM_COMPARE_VERSION1(EM_CPP_STDLIB_VERSION, __VA_ARGS__)
#  define EM_IS_LIBSTDCXX_DATE(...) EM_COMPARE_VERSION3(100, 100, EM_CPP_STDLIB_DATE, __VA_ARGS__)
#elif defined(_LIBCPP_VERSION)
#  define EM_IS_LIBCPP 1
#  define EM_STRING_CPP_STDLIB "libc++"
#  define EM_CPP_STDLIB_VERSION _LIBCPP_VERSION
#  define EM_CPP_STDLIB_DATE 0
#  define EM_STRING_CPP_STDLIB_VERSION EM_STR(EM_CPP_STDLIB_VERSION)
#  define EM_STRING_CPP_STDLIB_DATE ""
#  define EM_IS_LIBCPP_VERSION(...) EM_COMPARE_VERSION3(100, 100, EM_CPP_STDLIB_VERSION, __VA_ARGS__)
#elif defined(_MSVC_STL_VERSION)
#  define EM_IS_MSVC_STL 1
#  define EM_STRING_CPP_STDLIB "MSVC STL"
#  define EM_CPP_STDLIB_VERSION _MSVC_STL_VERSION
#  define EM_CPP_STDLIB_DATE _MSVC_STL_UPDATE
#  define EM_STRING_CPP_STDLIB_VERSION EM_STR(EM_CPP_STDLIB_VERSION)
#  define EM_STRING_CPP_STDLIB_DATE EM_STR(EM_CPP_STDLIB_DATE)
#  define EM_IS_MSVC_STL_VERSION(...) EM_COMPARE_VERSION1(EM_CPP_STDLIB_VERSION, __VA_ARGS__)
#  define EM_IS_MSVC_STL_DATE(...) EM_COMPARE_VERSION2(100, EM_CPP_STDLIB_DATE, __VA_ARGS__)
#else
#  define EM_STRING_CPP_STDLIB "Unknown C++ standard library"
#  define EM_CPP_STDLIB_VERSION 0
#  define EM_CPP_STDLIB_DATE 0
#  define EM_STRING_CPP_STDLIB_VERSION ""
#  define EM_STRING_CPP_STDLIB_DATE ""
#endif

#ifndef EM_IS_CPP_STDLIB_MISSING
#define EM_IS_CPP_STDLIB_MISSING 0
#endif
#ifndef EM_IS_LIBCPP
#define EM_IS_LIBCPP 0
#endif
#ifndef EM_IS_LIBCPP_VERSION
#define EM_IS_LIBCPP_VERSION(...) 0
#endif
#ifndef EM_IS_LIBSTDCXX
#define EM_IS_LIBSTDCXX 0
#endif
#ifndef EM_IS_LIBSTDCXX_DATE
#define EM_IS_LIBSTDCXX_DATE(...) 0
#endif
#ifndef EM_IS_LIBSTDCXX_VERSION
#define EM_IS_LIBSTDCXX_VERSION(...) 0
#endif
#ifndef EM_IS_MSVC_STL
#define EM_IS_MSVC_STL 0
#endif
#ifndef EM_IS_MSVC_STL_DATE
#define EM_IS_MSVC_STL_DATE(...) 0
#endif
#ifndef EM_IS_MSVC_STL_VERSION
#define EM_IS_MSVC_STL_VERSION(...) 0
#endif
