#pragma once

// Returns nothing.
#define EM_EMPTY(...)

// Causes a preprocessor-time error. `message` should be a string literal explanation.
// But if `message` is empty (doesn't have even the quotes), has no effect.
#define EM_FAIL(message) EM_EMPTY(message##!)

// Returns `...` unchanged. Throwing in a few equivalent overloads to help with recursive macros.
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

// Appends `_END` to the end of `...`. This helps writing a certain kind of preprocessor loops.
#define EM_END(...) DETAIL_EM_END(__VA_ARGS__)
#define DETAIL_EM_END(...) __VA_ARGS__##_END

// Some constants.
#define EM_COMMA(...) ,
#define EM_LPAREN(...) (
#define EM_RPAREN(...) )
#define EM_SYMBOL_AND(...) &&
#define EM_SYMBOL_OR(...) ||
