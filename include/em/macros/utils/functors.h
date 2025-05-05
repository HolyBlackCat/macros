#pragma once

#include "em/macros/meta/codegen.h"
#include "em/macros/meta/common.h"
#include "em/macros/portable/tiny_func.h"
#include "em/macros/portable/warnings.h"

// Declares a simple functor object named `name_`, of a unique class.
// `...` is a parenthesized parameter list and everything that follows (the function body or `EM_RETURNS(...)`).
// The class is intentionally named, with the name prefixed with `Fn_`. This allows e.g. forward-declaring it for tag-invoke purposes.
#define EM_SIMPLE_FUNCTOR(name_, ...) EM_SIMPLE_FUNCTOR_EXT(name_, (EM_1), __VA_ARGS__)
// This version also accepts `type_pattern_`, which is a parenthesized string to be used as the object type,
//   which should contain `EM_1`, which will be replaced with the type name, e.g. `(SomeWrapper<EM_1>)`.
// This version also allows you to make template functors. Pass the parenthesized template argument list to `template_head_`,
//   e.g. `(template <typename T>)`, and pass the arguments to `type_pattern_`, e.g. `(EM_1<T>)`.
#define EM_SIMPLE_FUNCTOR_EXT(name_, template_head_, type_pattern_, ...) \
    EM_IDENTITY template_head_ \
    struct EM_CAT(Fn_, name_) \
    { \
        EM_SILENCE_UNUSED_ATTRIBUTE( [[nodiscard]] ) \
        EM_TINY \
        auto operator() __VA_ARGS__ \
    }; \
    EM_IDENTITY template_head_ \
    inline constexpr EM_CODEGEN((EM_CAT(Fn_, name_)),, EM_UNWRAP_CODE(type_pattern_)) name_{};
