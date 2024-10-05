#pragma once

// Returns `...` unchanged. Throwing a few equivalent overloads to help with recursive macros.
#define EM_IDENTITY(...) __VA_ARGS__
#define EM_IDENTITY_A(...) __VA_ARGS__
#define EM_IDENTITY_B(...) __VA_ARGS__
#define EM_IDENTITY_C(...) __VA_ARGS__
#define EM_IDENTITY_D(...) __VA_ARGS__

// Converts something to a string a preprocessing time.
#define EM_STR(...) DETAIL_EM_STR(__VA_ARGS__)
#define DETAIL_EM_STR(...) #__VA_ARGS__

// Concatenates N tokens.
#define EM_CAT(x, y) DETAIL_EM_CAT(x, y)
#define EM_CAT3(x, y, z) DETAIL_EM_CAT3(x, y, z)
#define EM_CAT4(x, y, z, w) DETAIL_EM_CAT4(x, y, z, w)

#define DETAIL_EM_CAT(x, y) x##y
#define DETAIL_EM_CAT3(x, y, z) x##y##z
#define DETAIL_EM_CAT4(x, y, z, w) x##y##z##w

// Appends `_end` to the end of `...`. This helps writing a certain kind of preprocessor loops.
#define EM_END(...) DETAIL_EM_END(__VA_ARGS__)
#define DETAIL_EM_END(...) __VA_ARGS__##_end
