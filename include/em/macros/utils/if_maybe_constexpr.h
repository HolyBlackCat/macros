#pragma once

namespace em::detail::Macros::IfMaybeConstexpr
{
    template <bool X> constexpr bool identity = X;
}

// If `cond_` is truthy, runs `then_`, otherwise runs `else_`.
// If `cond_` can be evaluated at compile-time, will not evaluate the other branch.
// `then_` and `else_` must be parenthesized, they are blocks of code (e.g. will usually end with `;` or `}`).
// `cond_` can naturally be parenthesized, but doesn't have to be.
// Example:
//     EM_IF_ELSE_MAYBE_CONSTEXPR(
//         cond(),
//         (
//             foo();
//         ),
//         (
//             bar();
//         )
//     )
// Note that right now *references* to `std::true_type` and `std::false_type` are not considered constexpr enough, those must be by value.
// Keep the arguments short, use lambdas or helper functions. Both branches are duplicated, and the condition is triplicated (but only evaluated once).
// This is a macro rather than a function to allow NRVO in the branches, for example.
#define EM_IF_ELSE_MAYBE_CONSTEXPR(cond_, then_, else_) \
    if constexpr (requires{::em::detail::Macros::IfMaybeConstexpr::identity<cond_ ? true : false>;}) /* Need `?true:false` here because `bool` template arguments don't invoke the `explicit operator bool`. */ \
    { \
        if constexpr (cond_) \
        { \
            DETAIL_EM_IF_MAYBE_CONSTEXPR_IDENTITY then_ \
        } \
        else \
        { \
            DETAIL_EM_IF_MAYBE_CONSTEXPR_IDENTITY else_ \
        } \
    } \
    else \
    { \
        if (cond_) \
        { \
            DETAIL_EM_IF_MAYBE_CONSTEXPR_IDENTITY then_ \
        } \
        else \
        { \
            DETAIL_EM_IF_MAYBE_CONSTEXPR_IDENTITY else_ \
        } \
    }


#define DETAIL_EM_IF_MAYBE_CONSTEXPR_IDENTITY(...) __VA_ARGS__
