#include <minimacros/forward.h>

#include <type_traits>

struct A {};

struct B
{
    B() = default;
    B(const B &) = delete;
    B &operator=(const B &) = delete;
};

A x;
A &y = x;
A &&z = A{};
// Forwarding lvalue references.
static_assert(std::is_same_v<decltype(M_FWD(y)), A &>);
// Forwarding rvalue references.
static_assert(std::is_same_v<decltype(M_FWD(z)), A &&>);

// Weird usecases:

// Forwarding a non-reference variable moves it (for consistency with `std::forward`).
static_assert(std::is_same_v<decltype(M_FWD(x)), A &&>);
// Forwarding a prvalue does nothing (the move is elided).
static_assert(std::is_same_v<decltype(M_FWD(B{})), B>);
