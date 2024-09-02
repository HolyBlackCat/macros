#pragma once

// Returns `...` unchanged. Throwing a few equivalent overloads to help with recursive macros.
#define M_IDENTITY(...) __VA_ARGS__
#define M_IDENTITY_A(...) __VA_ARGS__
#define M_IDENTITY_B(...) __VA_ARGS__
#define M_IDENTITY_C(...) __VA_ARGS__
#define M_IDENTITY_D(...) __VA_ARGS__

// Converts something to a string a preprocessing time.
#define M_STR(...) DETAIL_M_STR(__VA_ARGS__)
#define DETAIL_M_STR(...) #__VA_ARGS__

// Concatenates N tokens.
#define M_CAT(x, y) DETAIL_M_CAT(x, y)
#define M_CAT3(x, y, z) DETAIL_M_CAT3(x, y, z)
#define M_CAT4(x, y, z, w) DETAIL_M_CAT4(x, y, z, w)

#define DETAIL_M_CAT(x, y) x##y
#define DETAIL_M_CAT3(x, y, z) x##y##z
#define DETAIL_M_CAT4(x, y, z, w) x##y##z##w

// Appends `_end` to the end of `...`. This helps writing a certain kind of preprocessor loops.
#define M_END(...) DETAIL_M_END(__VA_ARGS__)
#define DETAIL_M_END(...) __VA_ARGS__##_end
