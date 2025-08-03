#pragma once

#include "em/macros/meta/common.h"

// Various conditional macros.
// The syntax style used here, which is `MACRO(cond)(a)(b)`, can cause problems when used inside of more complex macros.
// If this happens, we'll probably have to create alternative versions with worse syntax. (I'd keep both? Not sure.)


// --- Emptiness:

// Usage: `EM_IF_NONEMPTY(cond)(a)(b)`.
// Returns `a` if `cond` isn't empty, or to `b` if it is empty. All parts can contain commas.
#define EM_IF_NONEMPTY(...) EM_CAT(DETAIL_EM_IF_THEN_, __VA_OPT__(1))
#define DETAIL_EM_IF_THEN_(...) DETAIL_EM_IF_ELSE_1
#define DETAIL_EM_IF_THEN_1(...) __VA_ARGS__ DETAIL_EM_IF_ELSE_
#define DETAIL_EM_IF_ELSE_(...)
#define DETAIL_EM_IF_ELSE_1(...) __VA_ARGS__

// Usage: `EM_IF_EMPTY(cond)(a)(b)`.
// A negated version of `EM_IF_NONEMPTY`, for convenience (including convenience of implementing other macros).
#define EM_IF_EMPTY(...) EM_CAT(DETAIL_EM_IF_NOT_THEN_, __VA_OPT__(1))
#define DETAIL_EM_IF_NOT_THEN_(...) __VA_ARGS__ DETAIL_EM_IF_ELSE_
#define DETAIL_EM_IF_NOT_THEN_1(...) DETAIL_EM_IF_ELSE_1

// Usage: `EM_FALLBACK_IF_EMPTY(a)(b)`. Same as `EM_IF_NONEMPTY(a)(a)(b)`.
// Returns `a` if it's not empty, otherwise `b`.
#define EM_FALLBACK_IF_EMPTY(...) EM_IF_NONEMPTY(__VA_ARGS__)(__VA_ARGS__)


// --- Commas:

// Usage: `EM_IF_COMMA(cond)(a)(b)`.
// Returns `a` if `cond` contains at least one comma, or `b` otherwise. `a` and `b` are allowed to contain commas.
#define EM_IF_COMMA(...) DETAIL_EM_IF_COMMA(__VA_ARGS__ x)
#define DETAIL_EM_IF_COMMA(unused, ...) EM_CAT(DETAIL_EM_IF_THEN_, __VA_OPT__(1))

// Usage: `EM_IF_CAT_ADDS_COMMA(x, ...)(a)(b)`.
// Concats `x` and `...`. If that creates a new comma, then returns `a`. Otherwise `b`.
// `...`, `a`, and `b` all can contain commas. Existing commas in `...` are ignored, we only check if a new one was added.
// This is good for checking if `...` starts with a specific word, by creating a `#define FOO_word ,` and passing `FOO_` as `x`.
#define EM_IF_CAT_ADDS_COMMA(x, ...) EM_IF_COMMA(EM_CAT(x, EM_VA_FIRST(__VA_ARGS__)))


// --- 0 and 1:

// Usage: `EM_IF_01(cond)(a)(b)`.
// `cond` can be either `1` or `0`, then returns `a` or `b` respectively.
// Other values of `cond` are illegal. `a` and `b` are allowed to contain commas, but `cond` isn't.
#define EM_IF_01(cond) EM_CAT(DETAIL_EM_IF_01_, cond)
#define DETAIL_EM_IF_01_0(...) DETAIL_EM_IF_ELSE_1
#define DETAIL_EM_IF_01_1(...) __VA_ARGS__ DETAIL_EM_IF_ELSE_


// --- Truthy and falsey:

// Usage: `EM_IF_TRUTHY(cond)(a)(b)`.
// `1` and empty string are truthy, `0` and other non-empty strings are falsey.
// Returns `a` if the condition is truthy, `b` otherwise. All parts are allowed to contain commas. `cond` must start with a word, since we'll concat it.
#define EM_IF_TRUTHY(...) EM_IF_EMPTY(EM_CAT(DETAIL_EM_IF_TRUTHY_, __VA_ARGS__)())
#define DETAIL_EM_IF_TRUTHY_()
#define DETAIL_EM_IF_TRUTHY_1()

// Usage: `EM_TRUTHY_OR_FALLBACK(a)(b)`.
// If `a` is `1`, `0`, or an empty string, returns that. Otherwise returns `b`.
// This should be used as a condition for `EM_IF_TRUTHY`. This gives `a` priority over `b`. If `a` is undefined, then `b` gets used.
#define EM_TRUTHY_OR_FALLBACK(...) EM_IF_EMPTY(EM_CAT(DETAIL_EM_TRUTHY_OR_FALLBACK_, __VA_ARGS__)())(__VA_ARGS__)
#define DETAIL_EM_TRUTHY_OR_FALLBACK_()
#define DETAIL_EM_TRUTHY_OR_FALLBACK_0()
#define DETAIL_EM_TRUTHY_OR_FALLBACK_1()

// Given `1` or empty string, returns `1`. Otherwise (for `0` or any other string) returns `0`.
#define EM_IS_TRUTHY(...) EM_IF_TRUTHY(__VA_ARGS__)(1)(0)
// Same, but negates the result.
#define EM_IS_FALSEY(...) EM_IF_TRUTHY(__VA_ARGS__)(0)(1)


// --- Any common value:

// Usage: `EM_IF_EMPTY_OR_01(cond)(a)(b)`.
// If `cond` is empty, `0`, or `1`, returns `a`, otherwise `b`.
// This is intended to check if the macro is defined, as those are the most common values.
#define EM_IF_EMPTY_OR_01(...) EM_IF_EMPTY(EM_CAT(DETAIL_EM_IF_EMPTY_OR_01_, __VA_ARGS__)())
#define DETAIL_EM_IF_EMPTY_OR_01_()
#define DETAIL_EM_IF_EMPTY_OR_01_0()
#define DETAIL_EM_IF_EMPTY_OR_01_1()

// Returns `1` if `...` is empty, `0`, or `1`. Otherwise returns `0`.
#define EM_IS_EMPTY_OR_01(...) EM_IF_EMPTY_OR_01(__VA_ARGS__)(1)(0)
