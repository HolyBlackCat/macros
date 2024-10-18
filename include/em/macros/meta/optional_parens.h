#pragma once

// Those macros help you work with optional parentheses.

// If `...` starts with `(...)`, expands them, i.e. `(a)b` -> `a b`. Otherwise leaves the argument unchanged.
#define EM_TRY_EXPAND_PARENS(...) DETAIL_EM_TRY_EXPAND_PARENS(DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY __VA_ARGS__)
#define DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY(...) DETAIL_EM_TRY_EXPAND_PARENS_EXPANDED __VA_ARGS__
#define DETAIL_EM_TRY_EXPAND_PARENS(...) DETAIL_EM_TRY_EXPAND_PARENS_(__VA_ARGS__)
#define DETAIL_EM_TRY_EXPAND_PARENS_(...) DETAIL_EM_TRY_EXPAND_PARENS_##__VA_ARGS__
#define DETAIL_EM_TRY_EXPAND_PARENS_DETAIL_EM_TRY_EXPAND_PARENS_IDENTITY
#define DETAIL_EM_TRY_EXPAND_PARENS_DETAIL_EM_TRY_EXPAND_PARENS_EXPANDED