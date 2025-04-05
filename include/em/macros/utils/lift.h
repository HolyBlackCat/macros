#pragma once

#include "em/macros/detail/enable_short_macros.h"
#include "em/macros/detail/overload.h" // IWYU pragma: keep - we need this for `EM_MEMBER()` below.
#include "em/macros/portable/always_inline.h"
#include "em/macros/portable/artificial.h"
#include "em/macros/utils/forward.h"
#include "em/macros/utils/returns.h"

// Those macros "lift" potentially overloaded functions (and other things),
// converting them to lambdas that can be easily passed around.

#ifndef DETAIL_EM_LIFT_LAMBDA_ATTRS
#define DETAIL_EM_LIFT_LAMBDA_ATTRS EM_ALWAYS_INLINE_LAMBDA EM_ARTIFICIAL
#endif

// Lift an expression. Produces a lambda with no arguments.
// Here we intentionally don't use `EM_RETURNS` to avoid duplication, we don't win anything by being SFINAE-friendly since the lambda itself has no arguments.
#define EM_EXPR(...) \
    [&]() DETAIL_EM_LIFT_LAMBDA_ATTRS -> decltype(auto) {return (__VA_ARGS__);}

// Lift a function. `EM_FUNC(foo)` -> `foo(...)`.
#define EM_FUNC(...) \
    [](auto &&... _m_params) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(__VA_ARGS__(EM_FWD(_m_params)...))

// Lift a member function or variable (see `EM_MEMBER_FUNC`, `EM_MEMBER_VAR`).
// `EM_MEMBER(.foo)` or `EM_MEMBER(->foo)`.
#define EM_MEMBER(...) \
    em::detail::Macros::Overload{EM_MEMBER_FUNC(__VA_ARGS__), EM_MEMBER_VAR(__VA_ARGS__)}

// Lift a member function: `EM_MEMBER_FUNC(.foo)` -> `x.foo(...)`, or `EM_MEMBER_FUNC(->foo)` -> `x->foo(...)`.
#define EM_MEMBER_FUNC(...) \
    [](auto &&_m_obj, auto &&... _m_params) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(EM_FWD(_m_obj)__VA_ARGS__(EM_FWD(_m_params)...))

// Lift a member variable: `EM_MEMBER_VAR(.foo)` -> `x.foo`, or `EM_MEMBER_VAR(->foo)` -> `x->foo`.
#define EM_MEMBER_VAR(...) \
    [](auto &&_m_obj) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(EM_FWD(_m_obj)__VA_ARGS__)

// Lift unary operator: `EM_UNARY(+)`.
#define EM_UNARY(...) [](auto &&_m_obj) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(__VA_ARGS__ EM_FWD(_m_obj))
// Lift binary operator: `EM_BINARY(/)`.
#define EM_BINARY(...) [](auto &&_m_a, auto &&_m_b) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(EM_FWD(_m_a) __VA_ARGS__ EM_FWD(_m_b))

#if EM_ENABLE_SHORT_MACROS(LIFT)
#define EXPR EM_EXPR
#define FUNC EM_FUNC
#define MEMBER EM_MEMBER
#define MEMBER_FUNC EM_MEMBER_FUNC
#define MEMBER_VAR EM_MEMBER_VAR
#define UNARY EM_UNARY
#define BINARY EM_BINARY
#endif
