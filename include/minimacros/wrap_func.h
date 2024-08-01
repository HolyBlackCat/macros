#pragma once

#include <minimacros/overload.h>

#define M_FUNC(...) \
    [](auto &&... _m_params) \
        noexcept(noexcept(__VA_ARGS__(decltype(_m_params)(_m_params)...))) \
        -> decltype(__VA_ARGS__(decltype(_m_params)(_m_params)...)) \
        { return __VA_ARGS__(decltype(_m_params)(_m_params)...); }

#define M_MEMBER(...) \
    ::MiniMacros::Overload{M_MEMBER_FUNC(__VA_ARGS__), M_MEMBER_VAR(__VA_ARGS__)}

#define M_MEMBER_FUNC(...) \
    [](auto && _m_obj, auto &&... _m_params) \
        noexcept(noexcept(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...))) \
        -> decltype(decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...)) \
        { return decltype(_m_obj)(_m_obj)__VA_ARGS__(decltype(_m_params)(_m_params)...); }

#define M_MEMBER_VAR(...) \
    [](auto && _m_obj) \
        noexcept(noexcept(decltype(_m_obj)(_m_obj)__VA_ARGS__))/* Should usually be true, but just in case.*/ \
        -> decltype(decltype(_m_obj)(_m_obj)__VA_ARGS__) \
        { return decltype(_m_obj)(_m_obj)__VA_ARGS__; }
