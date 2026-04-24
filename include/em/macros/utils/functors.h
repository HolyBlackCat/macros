#pragma once

#include "em/macros/meta/codegen.h"
#include "em/macros/meta/common.h"
#include "em/macros/meta/loops.h"
#include "em/macros/portable/tiny_func.h"
#include "em/macros/portable/warnings.h"
#include "em/macros/utils/forward.h"
#include "em/macros/utils/returns.h"

// Declares a simple functor object named `name_`, of a newly created class named `Fn_##name_`.
// `...` is a parenthesized parameter list and everything that follows (the function body or `EM_RETURNS(...)`).
// `deduced_targs_and_extras_` is either empty, or `()` (which is same as empty), or a parenthesized `template <....>` template argument list.
//   Those template arguments are always deduced and can't be specified manually (for those use `EM_SIMPLE_FUNCTOR_EXT()`).
//   Additionally, `deduced_targs_and_extras_` can contain things before (or instead of) the `template <....>`, that will be inserted at class scope.
// The class is intentionally named, with the name prefixed with `Fn_`. This allows e.g. forward-declaring it for tag-invoke purposes.
// You can overload the functor by stacking `EM_OVERLOAD deduced_targs_and_extras_, ...` at the end.
//   Those repeat the last two arguments.
// NOTE: When wrapping this macro, the `/*deduced_targs_and_extras_,*/ ...` must be passed as `EM_IMPLICIT_SEQ((__VA_ARGS__))` to propagate overloads correctly.
#define EM_SIMPLE_FUNCTOR(name_, /*deduced_targs_and_extras_,*/ ...) EM_SIMPLE_FUNCTOR_EXT(name_, /*template_head*/, /*type_pattern*/, EM_IMPLICIT_SEQ((__VA_ARGS__)))
// This version allows adding template arguments that can be specified by the user. It also allows tweaking the functor variable type.
// `name_` is the functor name.
// `template_head_` is either empty, or `()` (which is same as empty), or a parenthesized `template <....>` template argument list.
//   Those template arguments must be manually specified by the user.
//   When setting those, must also set `type_pattern_`, see below.
// `type_pattern_` determines how the type of the `name_` variable is formed. Can be empty to use the default value `(EM_1)`, where `EM_1` is the placeholder for the class we're generating.
//   When `template_head_` is specified, this must be set e.g. to `(EM_1<T>)` to pass the template arguments.
//   This can also be used to wrap the functor in some custom class to give it extra properties.
// `deduced_targs_and_extras_` has the same meaning as in `EM_SIMPLE_FUNCTOR()`.
//   It's either empty, or `()` (which is same as empty), or a parenthesized `template <....>` template argument list.
//   Those template arguments must be manually specified by the user.
// `...` has the same meaning as in `EM_SIMPLE_FUNCTOR()`. It's the parenthesized argument list, and everything that follows.
#define EM_SIMPLE_FUNCTOR_EXT(name_, template_head_, type_pattern_, /*deduced_targs_and_extras_,*/ ...) \
    EM_EXPAND_PARENS_OR_NOTHING(template_head_) \
    struct EM_CAT(Fn_, name_) \
    { \
        /* Need `__VA_OPT__(,)` in case everything got grouped into `deduced_targs_and_extras_` because of `EM_IDENTITY(...)` forwarding the arguments, or whatever. */\
        EM_CODEGEN((__VA_ARGS__),, \
            /* Template arguments? */\
            /* Note that `EM_EXPAND_PARENS_OR_NOTHING` is implied in `EM_1` */\
            EM_1 \
            /* Some attributes. */\
            EM_SILENCE_UNUSED_ATTRIBUTE( [[nodiscard]] ) \
            EM_TINY \
            /* This has to be either `static` or `const`. Making it `static` sounds better. */\
            /* Forcing either `static` or `const` prevents the use of the explicit `this` parameters, but I don't think they are very useful here? */\
            /* We can always add a `Self` typedef to help with recursion. */\
            static constexpr auto operator() EM_2_PLUS \
        ) \
    }; \
    EM_EXPAND_PARENS_OR_NOTHING(template_head_) \
    inline constexpr EM_CODEGEN((EM_CAT(Fn_, name_)),, EM_UNWRAP_CODE(EM_FALLBACK_IF_EMPTY(type_pattern_)((EM_1)))) name_{};

#define EM_OVERLOAD )(


// Creates a function named `name_##_` (with a trailing underscore added), that does `using original_namespace::name_;` and calls the original `name_()`.
// This has the effect of calling `name_()` with ADL customization enabled.
// This macro is intended to be used in a detail namespace, and the resulting function is intended for internal use.
// This is useful if you want to make an ADL-enabled call, but can't do that directly, because you can't hide `using ...;` inside of your function,
//   because you need it in `EM_RETURNS()`, and can't leave it outside of your function because the name conflicts with the name of your functor
//   (not a function, so overloading doesn't save you), or just because you don't want to pollute your namespace.
#define EM_WRAP_ADL_FUNCTION(original_namespace_, name_) \
    /* Adding an extra namespace to prevent the `using` from being visible outside, */\
    /* because in that case it would be too easy to make a typo and call it instead */\
    /* of `name_##_()`, which would silently disable ADL. */\
    namespace adl_wrap \
    { \
        using original_namespace_::name_; \
        \
        EM_SILENCE_UNUSED_ATTRIBUTE( [[nodiscard]] ) \
        EM_TINY \
        constexpr auto EM_CAT(name_,_)(auto &&... params) EM_RETURNS(name_(EM_FWD(params)...)) \
    } \
    using adl_wrap::EM_CAT(name_,_);
