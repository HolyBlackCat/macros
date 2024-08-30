#pragma once

// Use this as a body of lambda expressions: (or of functions with trailing return type)
//   [](auto x) M_RETURNS(x.foo())
// Double parentheses in `decltype(...)` won't usually matter, but it's a good idea to have them e.g. in case you return a global variable.
#define M_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype((__VA_ARGS__)) {return __VA_ARGS__;}

#if M_SHORT_MACROS || M_SHORT_MACROS_RETURNS
#define RETURNS M_RETURNS
#endif
