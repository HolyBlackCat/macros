#pragma once

namespace em::detail::Macros
{
    template <typename T>
    concept BoolLike = requires(T &&t) {(T &&)t ? true : false;};

    struct Implies
    {
        template <BoolLike T>
        friend constexpr bool operator||(T &&lhs, Implies)
        {
            return !bool((T &&)lhs);
        }
    };
}

#define EM_IMPLIES ||::em::detail::Macros::Implies{}||
