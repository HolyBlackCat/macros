#pragma once

#include "em/macros/platform/preprocessor.h"
#include "em/macros/meta/common.h"

// EM_EXPECT_EMPTY(...)      - triggers compilation error if `...` is not empty
// EM_EXPECT_NONEMPTY(...)   - triggers compilation error if `...` is empty, expands to nothing
// EM_NONEMPTY_IDENTITY(...) - triggers compilation error if `...` is empty, expands to ...

// Triggers compilation error if `...` is NOT empty.
#define EM_EXPECT_EMPTY(...) DETAIL_EM_EXPECT_EMPTY(__VA_ARGS__)
#define DETAIL_EM_EXPECT_EMPTY()

// Triggers compilation error if `...` is empty, expands to `...`.
#define EM_NONEMPTY_IDENTITY(...) EM_EXPECT_NONEMPTY(__VA_ARGS__) __VA_ARGS__

#if EM_HAS_VA_OPT
// Triggers compilation error if `...` is empty, expands to nothing.
#define EM_EXPECT_NONEMPTY(...) EM_CAT(DETAIL_EM_EXPECT_NONEMPTY_, __VA_OPT__(1))(x)
#define DETAIL_EM_EXPECT_NONEMPTY_()
#define DETAIL_EM_EXPECT_NONEMPTY_1(x)
#else
#define EM_EXPECT_NONEMPTY(...) DETAIL_EM_EXPECT_NONEMPTY_CHECK(DETAIL_EM_EXPECT_NONEMPTY_ __VA_ARGS__()) )
#define DETAIL_EM_EXPECT_NONEMPTY_() DETAIL_EM_EXPECT_NONEMPTY_1
#define DETAIL_EM_EXPECT_NONEMPTY_CHECK(...) DETAIL_EM_EXPECT_NONEMPTY_CHECK0(__VA_ARGS__)
#define DETAIL_EM_EXPECT_NONEMPTY_CHECK0(...) DETAIL_EM_EXPECT_NONEMPTY_CHECK_##__VA_ARGS__
#define DETAIL_EM_EXPECT_NONEMPTY_CHECK_DETAIL_EM_EXPECT_NONEMPTY_1 DETAIL_EM_EXPECT_NONEMPTY(x) DETAIL_EM_EXPECT_NONEMPTY_EMPTY(
#define DETAIL_EM_EXPECT_NONEMPTY_CHECK_DETAIL_EM_EXPECT_NONEMPTY_ DETAIL_EM_EXPECT_NONEMPTY_EMPTY(
#define DETAIL_EM_EXPECT_NONEMPTY()
#define DETAIL_EM_EXPECT_NONEMPTY_EMPTY(...)
#endif
