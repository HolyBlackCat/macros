#pragma once

#include "em/macros/detail/enable_short_macros.h"

// Use this as a body of lambda expressions: (or of functions with trailing return type)
//   [](auto x) EM_RETURNS(x.foo())
// Double parentheses in `decltype(...)` won't usually matter, but it's a good idea to have them e.g. in case you return a global variable.
#define EM_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype((__VA_ARGS__)) {return __VA_ARGS__;}

// Same as `EM_RETURNS`, but also allows specifying a custom `requires`. It can optionally be parenthesized (must do this if it contains commas).
// Note that we insert another pair of parentheses in the expansion, to allow things like `!x` which don't contain commas but aren't allowed in `requires`
//   without parentheses.
#define EM_RETURNS_REQ(req_, ...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype((__VA_ARGS__)) requires(req_) {return __VA_ARGS__;}

// An alternative version that doesn't choke when used for class member functions that are themselves NOT templated,
//   and need to be SFINAE-disabled for some template arguments of the enclosing class.
// I'm not entirely sure why compilers don't choke on `noexcept` here (I tested the big three) while at the same time choking when
//   trying to `decltype()` the return type like in `EM_RETURNS()`.
// Need the `(...)` after `return` here (but in `EM_RETURNS(...)` they don't matter).
#define EM_SOFT_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype(auto) requires requires{__VA_ARGS__;} {return (__VA_ARGS__);}

#define EM_SOFT_RETURNS_REQ(req_, ...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype(auto) requires (req_) && requires{__VA_ARGS__;} {return (__VA_ARGS__);}

#if EM_ENABLE_SHORT_MACROS(RETURNS)
#define RETURNS EM_RETURNS
#define SOFT_RETURNS EM_SOFT_RETURNS
#endif
