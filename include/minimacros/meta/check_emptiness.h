#pragma once

#include <minimacros/platform/preprocessor.h>
#include <minimacros/meta/common.h>

// EM_EXPECT_EMPTY(...)      - triggers compilation error if `...` is not empty
// EM_EXPECT_NONEMPTY(...)   - triggers compilation error if `...` is empty, expands to nothing
// EM_NONEMPTY_IDENTITY(...) - triggers compilation error if `...` is empty, expands to ...

// Triggers compilation error if `...` is NOT empty.
#define EM_EXPECT_EMPTY(...) DETAIL_M_EXPECT_EMPTY(__VA_ARGS__)
#define DETAIL_M_EXPECT_EMPTY()

// Triggers compilation error if `...` is empty, expands to `...`.
#define EM_NONEMPTY_IDENTITY(...) EM_EXPECT_NONEMPTY(__VA_ARGS__) __VA_ARGS__

#if EM_HAS_VA_OPT
// Triggers compilation error if `...` is empty, expands to nothing.
#define EM_EXPECT_NONEMPTY(...) EM_CAT(DETAIL_M_EXPECT_NONEMPTY_, __VA_OPT__(1))(x)
#define DETAIL_M_EXPECT_NONEMPTY_()
#define DETAIL_M_EXPECT_NONEMPTY_1(x)
#else
#define EM_EXPECT_NONEMPTY(...) DETAIL_M_EXPECT_NONEMPTY_CHECK(DETAIL_M_EXPECT_NONEMPTY_ __VA_ARGS__()) )
#define DETAIL_M_EXPECT_NONEMPTY_() DETAIL_M_EXPECT_NONEMPTY_1
#define DETAIL_M_EXPECT_NONEMPTY_CHECK(...) DETAIL_M_EXPECT_NONEMPTY_CHECK0(__VA_ARGS__)
#define DETAIL_M_EXPECT_NONEMPTY_CHECK0(...) DETAIL_M_EXPECT_NONEMPTY_CHECK_##__VA_ARGS__
#define DETAIL_M_EXPECT_NONEMPTY_CHECK_DETAIL_M_EXPECT_NONEMPTY_1 DETAIL_M_EXPECT_NONEMPTY(x) DETAIL_M_EXPECT_NONEMPTY_EMPTY(
#define DETAIL_M_EXPECT_NONEMPTY_CHECK_DETAIL_M_EXPECT_NONEMPTY_ DETAIL_M_EXPECT_NONEMPTY_EMPTY(
#define DETAIL_M_EXPECT_NONEMPTY()
#define DETAIL_M_EXPECT_NONEMPTY_EMPTY(...)
#endif
