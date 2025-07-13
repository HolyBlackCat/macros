#pragma once

#include <type_traits> // IWYU pragma: keep, needed in the macros below.

#include "em/macros/portable/always_inline.h"

// Synthesizes operators for a enum of flags: `&`, `|`, and `~`. Also multiplication by a bool.
#define EM_FLAG_ENUM(name_) EM_FLAG_ENUM_CUSTOM(, name_)

// Same, but works at class scope.
#define EM_FLAG_ENUM_IN_CLASS(name_) EM_FLAG_ENUM_CUSTOM(friend, name_)

// Same, but lets you specify a custom decl-specifier-seq.
#define EM_FLAG_ENUM_CUSTOM(prefix_, name_) \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator&(name_ a, name_ b) {return name_(::std::underlying_type_t<name_>(a) & ::std::underlying_type_t<name_>(b));} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator|(name_ a, name_ b) {return name_(::std::underlying_type_t<name_>(a) | ::std::underlying_type_t<name_>(b));} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator~(name_ a) {return name_(~::std::underlying_type_t<name_>(a));} \
    [[maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ &operator&=(name_ &a, name_ b) {return a = a & b;} \
    [[maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ &operator|=(name_ &a, name_ b) {return a = a | b;} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator*(name_ a, bool b) {return b ? a : name_{};} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator*(bool a, name_ b) {return a ? b : name_{};} \
    [[maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ &operator*=(name_ &a, bool b) {return a = a * b;} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator<<(name_ a, int b) {return name_(::std::underlying_type_t<name_>(a) << b);} \
    [[nodiscard, maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ operator>>(name_ a, int b) {return name_(::std::underlying_type_t<name_>(a) >> b);} \
    [[maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ &operator<<=(name_ &a, int b) {return a = a << b;} \
    [[maybe_unused]] EM_ALWAYS_INLINE prefix_ constexpr name_ &operator>>=(name_ &a, int b) {return a = a >> b;} \
