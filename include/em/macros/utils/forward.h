#pragma once

#include "em/macros/detail/enable_short_macros.h"

#include <type_traits>

namespace em::detail::Macros
{
    template <typename T> requires std::is_reference_v<T> || std::is_void_v<T>
    using FwdType = T;

    template <typename T, typename U> struct FwdTypeEx {using type = T &&;};
    template <typename T, typename U> struct FwdTypeEx<T, const U &> {using type = const T &&;}; // When forwarding a non-ref class member in a const member function, don't try to remove constness from it.
    template <typename T> struct FwdTypeEx<T, T> {using type = T;}; // When forwarding a prvalue, don't materialize it.

    template <typename T>
    using FwdNonRefAsConst = std::conditional_t<std::is_reference_v<T>, T, const T &&>;
}

namespace em::Meta
{
    // This is defined in `<em/meta/void.h>`. You can optionally use that.
    struct VoidPlaceholder;
}

// Mostly equivalent to `std::forward<decltype(x)>(x)`, but rejects non-references (except it accepts void, because it's easy to support).
#define EM_FWD(...) ::em::detail::Macros::FwdType<decltype(__VA_ARGS__)>(__VA_ARGS__)

// Mostly equivalent to `EM_FWD`, but additionally moves non-reference variables.
// Also acts as a no-op for prvalues instead of rejecting them (which isn't very useful, but still).
// This isn't a part of the default macro because it decltypes the argument twice, which seems lowkey too expensive.
#define EM_FWD_EX(...) static_cast<typename ::em::detail::Macros::FwdTypeEx<decltype(__VA_ARGS__),decltype((__VA_ARGS__))>::type>(__VA_ARGS__)

// If `...` is a non-reference (which can be a variable or a temporary), returns a const rvalue reference to it.
// Otherwise just forwards the argument.
// NOTE: If you apply this to a prvalue and save the result to a reference, the lifetime extension works correctly.
#define EM_FWD_NONREF_AS_CONST(...) static_cast<::em::detail::Macros::FwdNonRefAsConst<decltype(__VA_ARGS__)>>(__VA_ARGS__)

// Returns a variable from a function, perfectly forwarding its type (which can be a non-reference, lvalue or rvalue reference).
// The function return type should probably be set to `decltype(auto)`, and same for the variable you're returning.
// Additionally, if you use `VoidPlaceholder` from `<em/meta/void.h>`, recognizes that and returns `void` in that case.
#define EM_RETURN_VARIABLE(...) \
    do { \
        if constexpr (::std::is_same_v<::std::remove_cvref_t<decltype(__VA_ARGS__)>, ::em::Meta::VoidPlaceholder>) \
        { return; } \
        else if constexpr (::std::is_rvalue_reference_v<decltype(__VA_ARGS__)>) \
        { return decltype(__VA_ARGS__)(__VA_ARGS__); } /* To avoid including `<utility>` for `std::move` or our header for `EM_FWD(...)`. */\
        else \
        { return __VA_ARGS__; } \
    } while (false)

// Same, but with no special handling for `VoidPlaceholder`.
#define EM_RETURN_VARIABLE_NONVOID(...) \
    do { \
        if constexpr (::std::is_rvalue_reference_v<decltype(__VA_ARGS__)>) \
        { return decltype(__VA_ARGS__)(__VA_ARGS__); }\
        else \
        { return __VA_ARGS__; } \
    } while (false)


#if EM_ENABLE_SHORT_MACROS(FWD)
#define FWD EM_FWD
#define FWD_EX EM_FWD_EX
// `EM_FWD_NONREF_AS_CONST` is too specific, I don't want to add it here.
#endif
