#pragma once

#include "em/macros/meta/common.h"

// This file must be used together with `em/meta/detect_bases.h`. That file is in a different repository.
//
// Use `EM_DETECTABLE_BASE(...)` from this file to mark your base classes, and use that file to detect them.

// Place this in a class to make it detectable as a base.
// `p_tag_` is an arbitrary tag struct, parenthesized. You can have multiple macros in the same class, if the tags are different.
// `p_self_type_` is the enclosing class type, parenthesized. You can get it from `EM_TYPEDEF_ENCLOSING_CLASS()`.
#define EM_DETECTABLE_BASE(p_tag_, p_self_type_) \
    template < \
        /* The tag. */\
        typename _em_DetectBases_Tag, \
        /* The derived type we're finding the bases for. */\
        typename _em_DetectBases_Derived, \
        /* Selects the stateful list tag to append to. */\
        template <typename _em_Tag, typename _em_Base, typename _em_Derived> typename _em_DetectBases_SelectListTag, \
        /* Stop if the tag is wrong. */\
        ::std::enable_if_t<::std::is_same_v<_em_DetectBases_Tag, EM_IDENTITY p_tag_>, std::nullptr_t> = nullptr, \
        /* Write the base to the list. */\
        decltype((::em::Meta::Stateful::List::PushBack<_em_DetectBases_SelectListTag<_em_DetectBases_Tag, EM_IDENTITY p_self_type_, _em_DetectBases_Derived>, EM_IDENTITY p_self_type_>{}, nullptr)) = nullptr, \
        /* Finally, disable this overload. */\
        ::std::enable_if_t<::em::Meta::always_false<_em_DetectBases_Derived>, ::std::nullptr_t> = nullptr \
    > \
    friend constexpr void _adl_em_DetectBase(void *) {}
