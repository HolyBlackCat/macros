#pragma once

#define M_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }

#if M_SHORT_MACROS || M_SHORT_MACROS_RETURNS
#define RETURNS M_RETURNS
#endif
