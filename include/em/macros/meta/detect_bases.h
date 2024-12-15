#pragma once

#include "em/macros/meta/common.h"
#include "em/meta/qualifiers.h"
#include "em/meta/stateful/list.h"

// This file requires the `em/meta` repository to function.

// This lets you detect bases of a class. The bases must be marked with the `EM_DETECTABLE_BASE(...)` macro, see below.
// Then you can list those bases using `em::Macros::DetectBases::{All,Virtual,NonVirtual}Bases{Flat,Direct}{,AndSelf}`,
//   which return `em::Meta::TypeList<...>`.
// `Flat` recursively returns bases of bases too. `AndSelf` includes the self type at the end of the list.
// Not all combinations are implemented: `Direct` is only implemented for `NonVirtual`. It doesn't make much sense for other variants anyway.
//
// Most often you'll be using it like this: first iterate over `VirtualBasesFlatAndSelf`, then recursively iterate over `NonVirtualBasesDirect`.

namespace em::Macros::DetectBases
{
    namespace detail
    {
        template <typename Tag, typename T, template <typename Tag_, typename Base, typename Derived> typename Pred>
        constexpr void _adl_em_DetectBase(void *) {} // A dummy ADL target.

        // Populates a stateful list with bases of `T`.
        // `Tag` is whatever tag was passed to `EM_DETECTABLE_BASE()`.
        // `SelectListTag` must return a tag of a stateful list that we're filling. Or it can SFINAE-fail to skip this base.
        // `SelectListTag` MUST check that `Base` is a base of `Derived`, otherwise you can get various junk into the list.
        // `SelectListTag` receives the same `Tag_` as you pass into `Tag`.
        template <typename Tag, typename T, template <typename Tag_, typename Base, typename Derived> typename SelectListTag>
        constexpr auto Detect() -> decltype(void(_adl_em_DetectBase<Tag, T, SelectListTag>((T *)nullptr))) {}

        // Returns true if `Base` is a virtual base of `Derived`. (False if both types are the same.)
        // Inspired by this implementation: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2985r0.html#usercode
        // TODO: Migrate this to `std::is_virtual_base_of` when that becomes available. Note that it will automatically reject the same type,
        //   which here we have to do manually.
        // This currently returns false for ambiguous virtual bases, while `std::is_virtual_base_of` will return true, which will be better.
        //   But this does handle inaccessible virtual bases correctly, because C-style casts can handle that.
        template <typename Base, typename Derived>
        concept IsVirtualBase =
            !Meta::same_ignoring_cv<Base, Derived> &&
            requires(const volatile Derived *d){(const volatile Base *)d;} &&
            !requires(const volatile Base *b){(const volatile Derived *)b;};

        // All bases recursively, but not self.
        template <typename Tag, typename Derived>
        struct TagAllBases {};
        template <typename Tag, typename Base, typename Derived> requires (!std::is_same_v<Base, Derived>) && std::is_base_of_v<Base, Derived>
        using SelectTagAllBases = TagAllBases<Tag, Derived>;

        // All virtual bases recursively, but not self.
        template <typename Tag, typename Derived>
        struct TagVirtualBases {};
        template <typename Tag, typename Base, typename Derived> requires IsVirtualBase<Base, Derived>
        using SelectTagVirtualBases = TagVirtualBases<Tag, Derived>;

        // All non-virtual bases recursively, but not self.
        template <typename Tag, typename Derived>
        struct TagNonVirtualBases {};
        template <typename Tag, typename Base, typename Derived> requires (!std::is_same_v<Base, Derived>) && std::is_base_of_v<Base, Derived> && (!IsVirtualBase<Base, Derived>)
        using SelectTagNonVirtualBases = TagNonVirtualBases<Tag, Derived>;
    }

    // A flat list of all bases, including indirect ones, excluding self. Never contains repetitions.
    template <typename Tag, typename T>
    using AllBasesFlat = decltype((detail::Detect<Tag, T, detail::SelectTagAllBases>()), Meta::Stateful::List::Elems<detail::TagAllBases<Tag, T>>{});
    // Same, but includes `T` as the last type in the list.
    template <typename Tag, typename T>
    using AllBasesFlatAndSelf = Meta::list_append_types<AllBasesFlat<Tag, T>, T>;

    // A flat list of all virtual bases, including indirect ones, excluding self. Naturally never contains repetitions.
    template <typename Tag, typename T>
    using VirtualBasesFlat = decltype((detail::Detect<Tag, T, detail::SelectTagVirtualBases>()), Meta::Stateful::List::Elems<detail::TagVirtualBases<Tag, T>>{});
    // Same, but includes `T` as the last type in the list.
    template <typename Tag, typename T>
    using VirtualBasesFlatAndSelf = Meta::list_append_types<VirtualBasesFlat<Tag, T>, T>;

    // A flat list of all non-virtual bases, including indirect ones, excluding self. Never contains repetitions.
    template <typename Tag, typename T>
    using NonVirtualBasesFlat = decltype((detail::Detect<Tag, T, detail::SelectTagNonVirtualBases>()), Meta::Stateful::List::Elems<detail::TagNonVirtualBases<Tag, T>>{});
    // Same, but includes `T` as the last type in the list.
    template <typename Tag, typename T>
    using NonVirtualBasesFlatAndSelf = Meta::list_append_types<NonVirtualBasesFlat<Tag, T>, T>;


    namespace detail
    {
        template <typename Tag, typename T, typename U = T> struct SubtractBases {};
        template <typename Tag, typename T, typename ...U> struct SubtractBases<Tag, T, Meta::TypeList<U...>> {using type = Meta::list_subtract<T, NonVirtualBasesFlat<Tag, U>...>;};
    }

    // Direct non-virtual bases, excluding self.
    template <typename Tag, typename T>
    using NonVirtualBasesDirect = typename detail::SubtractBases<Tag, NonVirtualBasesFlat<Tag, T>>::type;
}

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
