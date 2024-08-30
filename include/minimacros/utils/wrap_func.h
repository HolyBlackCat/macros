#pragma once

#include <minimacros/utils/overload.h>
#include <minimacros/utils/returns.h>

#define M_FUNC(...) \
    [](auto &&... _m_params) M_RETURNS(__VA_ARGS__(decltype(_m_params)(_m_params)...))

#define M_MEMBER(...) \
    ::minm::Overload{M_MEMBER_FUNC(__VA_ARGS__), M_MEMBER_VAR(__VA_ARGS__)}

#define M_MEMBER_FUNC(...) \
    [](auto && _m_obj, auto &&... _m_params) M_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...))

#define M_MEMBER_VAR(...) \
    [](auto && _m_obj) M_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__)

#if M_SHORT_MACROS || M_SHORT_MACROS_WRAP_FUNC
#define FUNC M_FUNC
#define MEMBER M_MEMBER
#define MEMBER_FUNC M_MEMBER_FUNC
#define MEMBER_VAR M_MEMBER_VAR
#endif
