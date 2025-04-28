#pragma once

#include <cstddef> // IWYU pragma: keep
#include <type_traits> // IWYU pragma: keep

// Check if the expression is truthy.
#define EM_CHECK(...) ::std::enable_if_t<__VA_ARGS__, std::nullptr_t> = nullptr
// Check if the expression is value.
#define EM_CHECK_EXPR(...) decltype(__VA_ARGS__, nullptr) = nullptr
// Check if the type is valid.
// Note `identity` instead of `identity_t`, we don't want to check that the type is default-constructible.
#define EM_CHECK_TYPE(...) decltype(::std::identity<__VA_ARGS__>{}, nullptr) = nullptr
