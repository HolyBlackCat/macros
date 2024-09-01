#pragma once

#include <minimacros/utils/common.h>

// Provides an interface for Clang's attribute `preferred_name`.
// For example, if you have this:
//     template <typename T> struct my_basic_string;
//     using my_string = my_basic_string<char>;
//     using my_wstring = my_basic_string<wchar_>;
// You can rewrite it using this macro:
//     M_CANONICAL_TYPEDEFS( (template <typename T> struct), my_basic_string,
//         (my_string, my_basic_string<char>)
//         (my_wstring, my_basic_string<wchar_t>)
//     )
// On compilers other than Clang those are equivalent.
// On Clang, this causes those typedefs to be used in the error message when possible, making them less verbose.
// This can also affect how type name strings are determined by various libraries that use `__PRETTY_FUNCTION__` internally.

#define M_CANONICAL_TYPEDEFS(type_, name_, aliases_) \
    M_IDENTITY type_ name_; \
    M_END(DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_A aliases_) \
    DETAIL_M_CANONICAL_TYPEDEFS(type_, name_, aliases_)

#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_BODY(name_, ...) using name_ = __VA_ARGS__;
// Adding `M_IDENTITY()` here to keep the legacy MSVC preprocessor happy.
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_A(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_BODY M_IDENTITY()(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_B
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_B(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_BODY M_IDENTITY()(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_A
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_A_end
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_USING_B_end

#if defined(__has_attribute) && (!defined(M_ENABLE_CANONICAL_TYPEDEFS) || M_ENABLE_CANONICAL_TYPEDEFS)
#if __has_attribute(__preferred_name__)
#define DETAIL_M_CANONICAL_TYPEDEFS(type_, name_, aliases_) \
    M_IDENTITY type_ \
        M_END(DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_A aliases_) \
        name_; \
    DETAIL_M_CANONICAL_TYPEDEFS_CLANG_WORKAROUND(aliases_)

#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_BODY(name_, ...) __attribute__((__preferred_name__(name_)))
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_A(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_BODY(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_B
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_B(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_BODY(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_A
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_A_end
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_ATTR_B_end

#ifdef __clang__ // Workaround for bug: https://github.com/llvm/llvm-project/issues/106358

#define DETAIL_M_CANONICAL_TYPEDEFS_CLANG_WORKAROUND(aliases_) \
    M_END(DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_A aliases_)

namespace minm::detail::CanonicalTypedefs
{
    template <typename T>
    constexpr bool always_true = true;
}

#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_BODY(name_, ...) static_assert(::minm::detail::CanonicalTypedefs::always_true<__VA_ARGS__>);
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_A(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_BODY(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_B
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_B(...) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_BODY(__VA_ARGS__) DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_A
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_A_end
#define DETAIL_M_CANONICAL_TYPEDEFS_LOOP_TOUCH_B_end

#else // no workaround needed
#define DETAIL_M_CANONICAL_TYPEDEFS_CLANG_WORKAROUND(aliases_)
#endif

#else // this attribute is not supported
#define DETAIL_M_CANONICAL_TYPEDEFS(type_, name_, aliases_)
#endif

#else // no __has_attribute
#define DETAIL_M_CANONICAL_TYPEDEFS(type_, name_, aliases_)
#endif
