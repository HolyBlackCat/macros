#pragma once

namespace minm::detail
{
    template <typename T, typename U> struct ForwardType {using type = T &&;};
    template <typename T> struct ForwardType<T, T> {using type = T;};
}

#define M_FWD(...) static_cast<typename ::minm::detail::ForwardType<decltype(__VA_ARGS__),decltype((__VA_ARGS__))>::type>(__VA_ARGS__)

#if M_SHORT_MACROS || M_SHORT_MACROS_FORWARD
#define FWD M_FWD
#endif
