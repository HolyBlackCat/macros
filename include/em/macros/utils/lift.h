#pragma once

#include <em/macros/portable/artificial.h>
#include <em/macros/portable/force_inline.h>
#include <em/macros/detail/overload.h>
#include <em/macros/utils/returns.h>

// Those macros "lift" potentially overloaded functions (and other things),
// converting them to lambdas that can be easily passed around.

#ifndef DETAIL_EM_LIFT_LAMBDA_ATTRS
#define DETAIL_EM_LIFT_LAMBDA_ATTRS EM_FORCE_INLINE_LAMBDA EM_ARTIFICIAL
#endif

// Lift a function. `EM_FUNC(foo)` -> `foo(...)`.
#define EM_FUNC(...) \
    [](auto &&... _m_params) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(__VA_ARGS__(decltype(_m_params)(_m_params)...))

// Lift a member function or variable (see `EM_MEMBER_FUNC`, `EM_MEMBER_VAR`).
// `EM_MEMBER(.foo)` or `EM_MEMBER(->foo)`.
#define EM_MEMBER(...) \
    em::detail::Macros::Overload{EM_MEMBER_FUNC(__VA_ARGS__), EM_MEMBER_VAR(__VA_ARGS__)}

// Lift a member function: `EM_MEMBER_FUNC(.foo)` -> `x.foo(...)`, or `EM_MEMBER_FUNC(->foo)` -> `x->foo(...)`.
#define EM_MEMBER_FUNC(...) \
    [](auto &&_m_obj, auto &&... _m_params) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...))

// Lift a member variable: `EM_MEMBER_VAR(.foo)` -> `x.foo`, or `EM_MEMBER_VAR(->foo)` -> `x->foo`.
#define EM_MEMBER_VAR(...) \
    [](auto &&_m_obj) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__)

// Lift unary operator: `EM_UNARY(+)`.
#define EM_UNARY(...) [](auto &&_m_obj) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(__VA_ARGS__ decltype(_m_obj)(_m_obj))
// Lift binary operator: `EM_BINARY(/)`.
#define EM_BINARY(...) [](auto &&_m_a, auto &&_m_b) DETAIL_EM_LIFT_LAMBDA_ATTRS EM_RETURNS(decltype(_m_a)(_m_a) __VA_ARGS__ decltype(_m_b)(_m_b))

#if EM_SHORT_MACROS || EM_SHORT_MACROS_LIFT
#define FUNC EM_FUNC
#define MEMBER EM_MEMBER
#define MEMBER_FUNC EM_MEMBER_FUNC
#define MEMBER_VAR EM_MEMBER_VAR
#define UNARY EM_UNARY
#define BINARY EM_BINARY
#endif
