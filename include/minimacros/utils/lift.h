#pragma once

#include <minimacros/utils/overload.h>
#include <minimacros/utils/returns.h>

// Those macros "lift" potentially overloaded functions (and other things),
// converting them to lambdas that can be easily passed around.

// Lift a function. `EM_FUNC(foo)` -> `foo(...)`.
#define EM_FUNC(...) \
    [](auto &&... _m_params) EM_RETURNS(__VA_ARGS__(decltype(_m_params)(_m_params)...))

// Lift a member function or variable (see `EM_MEMBER_FUNC`, `EM_MEMBER_VAR`).
// `EM_MEMBER(.foo)` or `EM_MEMBER(->foo)`.
#define EM_MEMBER(...) \
    ::minm::Overload{EM_MEMBER_FUNC(__VA_ARGS__), EM_MEMBER_VAR(__VA_ARGS__)}

// Lift a member function: `EM_MEMBER_FUNC(.foo)` -> `x.foo(...)`, or `EM_MEMBER_FUNC(->foo)` -> `x->foo(...)`.
#define EM_MEMBER_FUNC(...) \
    [](auto &&_m_obj, auto &&... _m_params) EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...))

// Lift a member variable: `EM_MEMBER_VAR(.foo)` -> `x.foo`, or `EM_MEMBER_VAR(->foo)` -> `x->foo`.
#define EM_MEMBER_VAR(...) \
    [](auto &&_m_obj) EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__)

// Lift unary operator: `EM_UNARY(+)`.
#define EM_UNARY(...) [](auto &&_m_obj) EM_RETURNS(__VA_ARGS__ decltype(_m_obj)(_m_obj))
// Lift binary operator: `EM_BINARY(/)`.
#define EM_BINARY(...) [](auto &&_m_a, auto &&_m_b) EM_RETURNS(decltype(_m_a)(_m_a) __VA_ARGS__ decltype(_m_b)(_m_b))

#if EM_SHORT_MACROS || EM_SHORT_MACROS_LIFT
#define FUNC EM_FUNC
#define MEMBER EM_MEMBER
#define MEMBER_FUNC EM_MEMBER_FUNC
#define MEMBER_VAR EM_MEMBER_VAR
#define UNARY EM_UNARY
#define BINARY EM_BINARY
#endif
