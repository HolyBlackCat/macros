#pragma once

#include <minimacros/utils/overload.h>
#include <minimacros/utils/returns.h>

#define EM_FUNC(...) \
    [](auto &&... _m_params) EM_RETURNS(__VA_ARGS__(decltype(_m_params)(_m_params)...))

#define EM_MEMBER(...) \
    ::minm::Overload{EM_MEMBER_FUNC(__VA_ARGS__), EM_MEMBER_VAR(__VA_ARGS__)}

#define EM_MEMBER_FUNC(...) \
    [](auto && _m_obj, auto &&... _m_params) EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...))

#define EM_MEMBER_VAR(...) \
    [](auto && _m_obj) EM_RETURNS(decltype(_m_obj)(_m_obj)__VA_ARGS__)

#if EM_SHORT_MACROS || EM_SHORT_MACROS_WRAP_FUNC
#define FUNC EM_FUNC
#define MEMBER EM_MEMBER
#define MEMBER_FUNC EM_MEMBER_FUNC
#define MEMBER_VAR EM_MEMBER_VAR
#endif
