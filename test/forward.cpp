#include "em/macros/utils/forward.h"

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
static_assert(std::is_same_v<decltype(EM_FWD(y)), A &>);
// Forwarding rvalue references.
static_assert(std::is_same_v<decltype(EM_FWD(z)), A &&>);

// Extended forward:

// Forwarding lvalue references.
static_assert(std::is_same_v<decltype(EM_FWD_EX(y)), A &>);
// Forwarding rvalue references.
static_assert(std::is_same_v<decltype(EM_FWD_EX(z)), A &&>);

// Forwarding a non-reference variable moves it (for consistency with `std::forward`).
static_assert(std::is_same_v<decltype(EM_FWD_EX(x)), A &&>);
// Forwarding a prvalue does nothing (the move is elided).
static_assert(std::is_same_v<decltype(EM_FWD_EX(B{})), B>);
// Forwarding a void does nothing. This isn't particularly important, but why not.
static_assert(std::is_same_v<decltype(EM_FWD_EX(void())), void>);
