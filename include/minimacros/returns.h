#pragma once

#define M_RETURNS(...) \
    noexcept(noexcept(__VA_ARGS__)) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }
