#pragma once

#include <minimacros/meta/check_emptiness.h>
#include <minimacros/platform/preprocessor.h>

// Version comparison macros. Will usually be used as an implementation detail of other macros.
//
// Lets say you have a version number of the form XyyyZZ, e.g. 300405. Then:
//   M_COMPARE_VERSION3(1000,100, 300405, == 3))     // Matches 3.x.x, i.e. 3_____
//   M_COMPARE_VERSION3(1000,100, 300405, == 3,4))   // Matches 3.4.x, i.e. 3004__
//   M_COMPARE_VERSION3(1000,100, 300405, == 3,4,5)) // Matches 3.4.5, i.e. 300405 exactly
// Where 1000 and 100 are the factors. Those let you configure how many digits to use for the version parts (other than the leftmost one).
// You can use any comparison operator, not only `==`.
// We similarly have macros for 2-component versions, e.g:
//   M_COMPARE_VERSION2(1000,     3004,   == 3)
//   M_COMPARE_VERSION2(1000,     3004,   == 3,4)
// And a generate case for one variable: M_COMPARE_VERSION1(42, == 42)
//
// Usually you'd wrap this into a macro, such as `FOO(== 3,4,5)` or `FOO(300405, == 3,4,5)`.

#define M_COMPARE_VERSION1(n, x) (n M_NONEMPTY_IDENTITY(x))
#if !M_IS_LEGACY_MSVC_PREPROCESSOR
#define M_COMPARE_VERSION2(a, n, ...) DETAIL_M_COMPARE_VERSION2(__VA_ARGS__, DETAIL_M_COMPARE_VERSION2_2, DETAIL_M_COMPARE_VERSION2_1, x)(a, n, __VA_ARGS__)
#define M_COMPARE_VERSION3(a, b, n, ...) DETAIL_M_COMPARE_VERSION3(__VA_ARGS__, DETAIL_M_COMPARE_VERSION3_3, DETAIL_M_COMPARE_VERSION3_2, DETAIL_M_COMPARE_VERSION3_1, x)(a, b, n, __VA_ARGS__)
#else
#define M_COMPARE_VERSION2(a, n, ...) DETAIL_M_COMPARE_VERSION2 DETAIL_M_COMPARE_VERSION_DEFER(__VA_ARGS__, DETAIL_M_COMPARE_VERSION2_2, DETAIL_M_COMPARE_VERSION2_1, x)(a, n, __VA_ARGS__)
#define M_COMPARE_VERSION3(a, b, n, ...) DETAIL_M_COMPARE_VERSION3 DETAIL_M_COMPARE_VERSION_DEFER(__VA_ARGS__, DETAIL_M_COMPARE_VERSION3_3, DETAIL_M_COMPARE_VERSION3_2, DETAIL_M_COMPARE_VERSION3_1, x)(a, b, n, __VA_ARGS__)
#define DETAIL_M_COMPARE_VERSION_DEFER
#endif
#define DETAIL_M_COMPARE_VERSION2(a, b, c, ...) c
#define DETAIL_M_COMPARE_VERSION2_1(a, n, x) ((n)/(a) M_NONEMPTY_IDENTITY(x))
#define DETAIL_M_COMPARE_VERSION2_2(a, n, x, y) ((n) M_NONEMPTY_IDENTITY(x)*(a)+(y))
#define DETAIL_M_COMPARE_VERSION3(a, b, c, d, ...) d
#define DETAIL_M_COMPARE_VERSION3_1(a, b, n, x) ((n)/(b)/(a) M_NONEMPTY_IDENTITY(x))
#define DETAIL_M_COMPARE_VERSION3_2(a, b, n, x, y) ((n)/(b) M_NONEMPTY_IDENTITY(x)*(a)+(y))
#define DETAIL_M_COMPARE_VERSION3_3(a, b, n, x, y, z) ((n) M_NONEMPTY_IDENTITY(x)*(a)*(b)+(y)*(b)+(z))
