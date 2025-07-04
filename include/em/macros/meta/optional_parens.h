#pragma once

#include "em/macros/meta/common.h"

// Those macros help you work with parentheses, especially optional parentheses.

// Given `(a)...`, returns `a`.
// If you want the elements after the first, use `em/macros/meta/indexing.h`.
// In some cases you want to reimplement this instead of calling directly. E.g. `EM_SEQ_AT0` has to reimplement this, or `EM_CODEGEN` starts choking.
#define EM_SEQ_FIRST(...) DETAIL_EM_SEQ_FIRST __VA_ARGS__ )
#define DETAIL_EM_SEQ_FIRST(...) __VA_ARGS__ EM_EMPTY(


// If `...` is empty, returns empty. Otherwise it must be parenthesized, and we remove parentheses.
#define EM_EXPAND_PARENS_OR_NOTHING(...) __VA_OPT__(EM_IDENTITY __VA_ARGS__)


// If `...` starts with `(...)`, expands them, i.e. `(a)b` -> `a b`. Otherwise leaves the argument unchanged.
#define EM_TRY_EXPAND_PARENS(...) DETAIL_EM_TRY_EXPAND_PARENS(DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY __VA_ARGS__)
#define DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY(...) DETAIL_EM_TRY_EXPAND_PARENS_EXPANDED __VA_ARGS__
#define DETAIL_EM_TRY_EXPAND_PARENS(...) DETAIL_EM_TRY_EXPAND_PARENS_(__VA_ARGS__)
#define DETAIL_EM_TRY_EXPAND_PARENS_(...) DETAIL_EM_TRY_EXPAND_PARENS_##__VA_ARGS__
#define DETAIL_EM_TRY_EXPAND_PARENS_DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY
#define DETAIL_EM_TRY_EXPAND_PARENS_DETAIL_EM_TRY_EXPAND_PARENS_EXPANDED


// Given `bar` or `(foo)bar`, returns `bar`.
#define EM_TRY_SKIP_PARENS(...) DETAIL_EM_PARENS_NO_FIRST(DETAIL_EM_PARENS_BAKE_MACRO(DETAIL_EM_PARENS_GRAB __VA_ARGS__))
// Given `bar` or `(foo)bar`, returns empty or `foo` respectively.
#define EM_TRY_ONLY_PARENS(...) EM_SEQ_FIRST(DETAIL_EM_PARENS_BAKE_MACRO(DETAIL_EM_PARENS_GRAB __VA_ARGS__))

#define DETAIL_EM_PARENS_NO_FIRST(...) DETAIL_EM_PARENS_NO_FIRST_(__VA_ARGS__)
#define DETAIL_EM_PARENS_NO_FIRST_(x, ...) __VA_ARGS__
#define DETAIL_EM_PARENS_GRAB(...) DETAIL_EM_PARENS_GRABBED(__VA_ARGS__),
#define DETAIL_EM_PARENS_BAKE_MACRO(...) DETAIL_EM_PARENS_BAKE_MACRO_(__VA_ARGS__)
#define DETAIL_EM_PARENS_BAKE_MACRO_(...) DETAIL_EM_PARENS_BAKE_##__VA_ARGS__
#define DETAIL_EM_PARENS_BAKE_DETAIL_EM_PARENS_GRAB (),
#define DETAIL_EM_PARENS_BAKE_DETAIL_EM_PARENS_GRABBED
