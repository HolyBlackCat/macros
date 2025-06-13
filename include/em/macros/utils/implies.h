#pragma once

namespace em::detail::Macros
{
    template <typename T>
    concept BoolLike = requires(T &&t) {(T &&)t ? true : false;};

    struct Implies
    {
        template <BoolLike T>
        friend constexpr bool operator|(T &&lhs, Implies)
        {
            return !bool((T &&)lhs);
        }
    };
}

// The implication operator. Usage: `a EM_IMPLIES b`.
//
// Similar to `a <= b`, except converts both operands to `bool` and short-circuits (if lhs is false, the rhs is not evaluated).
//
// Has some weird precedence. `A || B  EM_IMPLIES  C || D` parses as `A || (B EM_IMPLIES C || D)`, and similary with `&&`.
// Note that in the implementation, the left operator has to be `|`, because Clang chokes on overloaded `&&` and `||` in requires-clauses and concepts,
//   and `|` is the next best thing. It has the lowest precedence higher than `&&` and `||`.
// And the second operator has to stay `||` for short-circuiting reasons, and to work in concepts and requires-clauses.
#define EM_IMPLIES |::em::detail::Macros::Implies{}||
