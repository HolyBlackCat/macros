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

// The implication operator. Usage: `a EM_IMPLIES b`.
//
// Similar to `a <= b`, except converts both operands to `bool` and short-circuits (if lhs is false, the rhs is not evaluated).
//
// Has same precedence as `||`, which is lower than everything other than `? :` and assignment, and equal to only other `||`.
// Can have strange precedence next to `||`, e.g. `a || b EM_IMPLIES c || d` is parsed as `((a || b) EM_IMPLIES c) || d`.
//
// On Clang this doesn't work in concepts and requires-clauses, there it must be wrapped in `bool(...)`.
// Otherwise Clang complains that `atomic constraint must be of type 'bool' (found '::detail::Implies')`.
#define EM_IMPLIES ||::em::detail::Macros::Implies{}||
