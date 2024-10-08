#pragma once

#include "em/macros/meta/compare_versions.h"

// C++ version detection.
//
//   EM_CPP_STANDARD_DATE - usually same as `__cplusplus` (but not broken on MSVC).
//     Known values: 199711, 201103, 201402, 201703, 202002, 202302
//                  C++98   C++11   C++14   C++17   C++20   C++23
//
//   EM_CPP_STANDARD - the standard version (98,11,14,17,20,23,etc), usually the two middle digits from `EM_CPP_STANDARD_DATE` (except for C++98).
//
//   EM_IS_CPP_VERSION - compare the standard version, e.g. `EM_IS_CPP_VERSION(== 23)`.

#ifdef _MSC_VER
#define EM_CPP_STANDARD_DATE _MSVC_LANG // Dang it, MSVC!
#else
#define EM_CPP_STANDARD_DATE __cplusplus
#endif

#define EM_CPP_STANDARD ((EM_CPP_STANDARD_DATE)/100%100)
#define EM_IS_CPP_VERSION(...) EM_COMPARE_VERSION1(EM_CPP_STANDARD, __VA_ARGS__)

// Fix `EM_CPP_STANDARD` 97 -> 98.
#if EM_CPP_STANDARD == 97
#undef EM_CPP_STANDARD
#define EM_CPP_STANDARD 98
#endif
