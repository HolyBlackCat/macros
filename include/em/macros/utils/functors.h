#pragma once

#include "em/macros/meta/codegen.h"
#include "em/macros/meta/common.h"
#include "em/macros/portable/tiny_func.h"
#include "em/macros/portable/warnings.h"
#include "em/macros/utils/forward.h"
#include "em/macros/utils/returns.h"

// Declares a simple functor object named `name_`, of a unique class.
// `...` is a parenthesized parameter list and everything that follows (the function body or `EM_RETURNS(...)`).
// `deduced_targs_and_extras_` is either empty, or `()` (which is same as empty), or a parenthesized `template <....>` template argument list.
//   Those template arguments are always deduced and can't be specified manually, for those use `EM_SIMPLE_FUNCTOR_EXT()`.
//   Additionally, `deduced_targs_and_extras_` can contain things before (or instead of) the `template <....>`, that will be inserted at class scope.
// The class is intentionally named, with the name prefixed with `Fn_`. This allows e.g. forward-declaring it for tag-invoke purposes.
#define EM_SIMPLE_FUNCTOR(name_, deduced_targs_and_extras_, ...) EM_SIMPLE_FUNCTOR_EXT(name_, (), (EM_1), deduced_targs_and_extras_, __VA_ARGS__)
// This version allows you to make template functors. Pass the parenthesized template argument list to `template_head_`,
//   e.g. `(template <typename T>)`, and pass the arguments to `type_pattern_`, e.g. `(EM_1<T>)`.
// Those template arguments are the ones that must be specified explicitly, as opposed to `deduced_targs_and_extras_` that are always deduced.
// Here `type_pattern_` has other uses too (not only templates). It is a parenthesized string to be used as the object type,
//   which should contain `EM_1`, which will be replaced with the type name, e.g. `(SomeWrapper<EM_1>)`.
#define EM_SIMPLE_FUNCTOR_EXT(name_, template_head_, type_pattern_, deduced_targs_and_extras_, ...) \
    EM_IDENTITY template_head_ \
    struct EM_CAT(Fn_, name_) \
    { \
        /* Template arguments? */\
        EM_EXPAND_PARENS_OR_NOTHING(deduced_targs_and_extras_) \
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
