#pragma once

namespace minm::detail
{
    template <typename T, typename U> struct ForwardType {using type = T &&;};
    template <typename T> struct ForwardType<T, T> {using type = T;};
}

// Mostly equivalent to `std::forward<decltype(x)>(x)`, but with extra features:
// * Forwarding a prvalue does nothing (the move is elided, returns the same prvalue).
// * Forwarding a `void` does nothing, returns `void`.
// And just like `std::forward<decltype(x)>(x)`, forwarding a non-reference variable moves it.
#define EM_FWD(...) static_cast<typename ::minm::detail::ForwardType<decltype(__VA_ARGS__),decltype((__VA_ARGS__))>::type>(__VA_ARGS__)

#if EM_SHORT_MACROS || EM_SHORT_MACROS_FORWARD
#define FWD EM_FWD
#endif
