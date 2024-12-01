#pragma once

#include "em/macros/meta/common.h"

#include <type_traits>

// A macro to determine the type of the enclosing class.

namespace em::detail::Macros::EnclosingClass
{
    template <typename Key>
    struct Read
    {
        friend constexpr auto _adl_em_EnclosingClass(Read<Key>);
    };

    template <typename Key, typename Value>
    struct Write
    {
        friend constexpr auto _adl_em_EnclosingClass(Read<Key>) {return Value{};}
    };

    constexpr void _adl_em_EnclosingClass() {} // Dummy ADL target.

    template <typename T>
    using Type = std::remove_pointer_t<decltype(_adl_em_EnclosingClass(Read<T>{}))>;
}

// Declares a typedef named `self_`, pointing to the enclosing class.
// You can have several of those in a class if the names are different.
#define EM_TYPEDEF_ENCLOSING_CLASS(self_) \
    struct EM_CAT(_adl_em_EnclosingClassTag, self_); \
    friend auto _em_detail_EnclosingClassHelper(EM_CAT(_adl_em_EnclosingClassTag, self_)) \
    -> decltype(void(::em::detail::Macros::EnclosingClass::Write<EM_CAT(_adl_em_EnclosingClassTag, self_), decltype(this)>{})); \
    using self_ = ::em::detail::Macros::EnclosingClass::Type<EM_CAT(_adl_em_EnclosingClassTag, self_)>;
