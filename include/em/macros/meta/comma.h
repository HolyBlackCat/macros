#pragma once

#include "em/macros/meta/check_emptiness.h"

// Manipulate leading and trailing commas.

// Add a leading/trailing comma if the argument is not empty.
#define EM_ADD_LEADING_COMMA(...) __VA_OPT__(,) __VA_ARGS__
#define EM_ADD_TRAILING_COMMA(...) __VA_ARGS__ __VA_OPT__(,)

// Given `, ...`, removes the leading `,`.
// If the argument is empty, returns nothing.
// Otherwise, if the argument doesn't start with a `,`, fails.
#define EM_REMOVE_LEADING_COMMA(...) DETAIL_EM_REMOVE_LEADING_COMMA(__VA_ARGS__)
#define DETAIL_EM_REMOVE_LEADING_COMMA(x, ...) EM_EXPECT_EMPTY(x) __VA_ARGS__
