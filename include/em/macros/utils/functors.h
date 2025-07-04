#pragma once

#include "em/macros/meta/codegen.h"
#include "em/macros/meta/common.h"
#include "em/macros/portable/tiny_func.h"
#include "em/macros/portable/warnings.h"

// Declares a simple functor object named `name_`, of a unique class.
// `...` is a parenthesized parameter list and everything that follows (the function body or `EM_RETURNS(...)`).
// `deduced_targs_` is either empty, or `()` (which is same as empty), or a parenthesized `template <....>` template argument list.
//   Those template arguments are always deduced and can't be specified manually, for those use `EM_SIMPLE_FUNCTOR_EXT()`.
// The class is intentionally named, with the name prefixed with `Fn_`. This allows e.g. forward-declaring it for tag-invoke purposes.
#define EM_SIMPLE_FUNCTOR(name_, deduced_targs_, ...) EM_SIMPLE_FUNCTOR_EXT(name_, (), (EM_1), deduced_targs_, __VA_ARGS__)
// This version allows you to make template functors. Pass the parenthesized template argument list to `template_head_`,
//   e.g. `(template <typename T>)`, and pass the arguments to `type_pattern_`, e.g. `(EM_1<T>)`.
// Those template arguments are the ones that must be specified explicitly, as opposed to `deduced_targs_` that are always deduced.
// Here `type_pattern_` has other uses too (not only templates). It is a parenthesized string to be used as the object type,
//   which should contain `EM_1`, which will be replaced with the type name, e.g. `(SomeWrapper<EM_1>)`.
#define EM_SIMPLE_FUNCTOR_EXT(name_, template_head_, type_pattern_, deduced_targs_, ...) \
    EM_IDENTITY template_head_ \
    struct EM_CAT(Fn_, name_) \
    { \
        /* Template arguments? */\
        EM_EXPAND_PARENS_OR_NOTHING(deduced_targs_) \
        /* Some attributes. */\
        EM_SILENCE_UNUSED_ATTRIBUTE( [[nodiscard]] ) \
        EM_TINY \
        /* This has to be either `static` or `const`. Making it `static` sounds better. */\
        /* Forcing either `static` or `const` prevents the use of the explicit `this` parameters, but I don't think they are very useful here? */\
        /* We can always add a `Self` typedef to help with recursion. */\
        static constexpr auto operator() __VA_ARGS__ \
    }; \
    EM_IDENTITY template_head_ \
    inline constexpr EM_CODEGEN((EM_CAT(Fn_, name_)),, EM_UNWRAP_CODE(type_pattern_)) name_{};
