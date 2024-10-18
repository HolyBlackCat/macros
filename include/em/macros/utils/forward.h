#pragma once

#include "em/macros/detail/enable_short_macros.h"

#include <type_traits>

namespace em::detail::Macros
{
    template <typename T> requires std::is_reference_v<T> || std::is_void_v<T>
    using FwdType = T;

    template <typename T, typename U> struct FwdTypeEx {using type = T &&;};
    template <typename T> struct FwdTypeEx<T, T> {using type = T;};
}

// Mostly equivalent to `std::forward<decltype(x)>(x)`, but rejects non-references (except it accepts void, because it's easy to support).
#define EM_FWD(...) ::em::detail::Macros::FwdType<decltype(__VA_ARGS__)>(__VA_ARGS__)

// Mostly equivalent to `EM_FWD`, but additionally moves non-reference variables.
// This isn't a part of the default macro because it decltypes the argument twice, which seems lowkey too expensive.
#define EM_FWD_EX(...) static_cast<typename ::em::detail::Macros::FwdTypeEx<decltype(__VA_ARGS__),decltype((__VA_ARGS__))>::type>(__VA_ARGS__)

#if EM_ENABLE_SHORT_MACROS(FWD)
#define FWD EM_FWD
#define FWD_EX EM_FWD_EX
#endif
