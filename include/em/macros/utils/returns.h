#pragma once

#include "em/macros/detail/enable_short_macros.h"

// Use this as a body of lambda expressions: (or of functions with trailing return type)
//   [](auto x) EM_RETURNS(x.foo())
// Double parentheses in `decltype(...)` won't usually matter, but it's a good idea to have them e.g. in case you return a global variable.
#define EM_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype((__VA_ARGS__)) {return __VA_ARGS__;}

// An alternative version that doesn't choke when used for class member functions that are themselves NOT templated,
//   and need to be SFINAE-disabled for some template arguments of the enclosing class.
// I'm not entirely sure why compilers don't choke on `noexcept` here (I tested the big three) while at the same choking when
//   trying to `decltype()` the return type like in `EM_RETURNS()`.
// Need the `(...)` after `return` here (but in `EM_RETURNS(...)` they don't matter).
#define EM_REQ_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype(auto) requires requires{__VA_ARGS__;} {return (__VA_ARGS__);}

#if EM_ENABLE_SHORT_MACROS(RETURNS)
#define RETURNS EM_RETURNS
#define REQ_RETURNS EM_REQ_RETURNS
#endif
