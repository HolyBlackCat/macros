#pragma once

#include "em/macros/meta/common.h"
#include "em/macros/portable/placeholder_variables.h"

#include <exception>
#include <utility>

namespace em::detail::Macros::ScopeGuard
{
    template <typename F>
    class Guard
    {
        F func;

      public:
        constexpr Guard(F &&func) : func(std::move(func)) {}

        Guard(const Guard &) = delete;
        Guard &operator=(const Guard &) = delete;

        constexpr ~Guard()
        {
            func();
        }
    };

    template <typename F>
    class GuardOnSuccess
    {
        F func;

        int num_exceptions = std::uncaught_exceptions();

      public:
        constexpr GuardOnSuccess(F &&func) : func(std::move(func)) {}

        GuardOnSuccess(const GuardOnSuccess &) = delete;
        GuardOnSuccess &operator=(const GuardOnSuccess &) = delete;

        constexpr ~GuardOnSuccess()
        {
            if (num_exceptions == std::uncaught_exceptions())
                func();
        }
    };

    template <typename F>
    class GuardOnThrow
    {
        F func;

        int num_exceptions = std::uncaught_exceptions();

      public:
        constexpr GuardOnThrow(F &&func) : func(std::move(func)) {}

        GuardOnThrow(const GuardOnThrow &) = delete;
        GuardOnThrow &operator=(const GuardOnThrow &) = delete;

        constexpr ~GuardOnThrow()
        {
            if (num_exceptions < std::uncaught_exceptions())
                func();
        }
    };
}

// Usage: `EM_FINALLY{ ... };`. Calls the code block when exiting the current scope.
#define EM_FINALLY            ::em::detail::Macros::ScopeGuard::Guard          EM_PLACEHOLDER_VARIABLE = [&]() -> void
// Usage: `EM_FINALLY_ON_SUCCESS{ ... };`. Calls the code block when exiting the current scope NOT because of an exception.
#define EM_FINALLY_ON_SUCCESS ::em::detail::Macros::ScopeGuard::GuardOnSuccess EM_PLACEHOLDER_VARIABLE = [&]() -> void
// Usage: `EM_FINALLY_ON_THROW{ ... };`. Calls the code block when exiting the current scope because of an exception.
#define EM_FINALLY_ON_THROW   ::em::detail::Macros::ScopeGuard::GuardOnThrow   EM_PLACEHOLDER_VARIABLE = [&]() -> void
