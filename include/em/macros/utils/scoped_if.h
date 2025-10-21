#pragma once

#include "em/macros/meta/common.h"

// `EM_SCOPED_IF(...)` acts exactly like `if (...)`, except that if you declare a variable in `...`, it will not be visible in the `else` branch.
// Doesn't work at compile-time due to the use of `goto`, and also can't act as `if constexpr`.
// Using this macro only makes sense if you declare a variable in the condition, AND there is an else branch.
// Like if the plain `if`, you can have a custom condition after the variable, separated with `;`.
// Like if the plain `if`, you can do `else EM_SCOPED_IF_(...)` and have an `else-if` chain.
// You're allowed to not declare a variable in the condition, and/or omit the `else` branch, but then using this macro makes no sense.
#define EM_SCOPED_IF(.../*decl*/) \
    DETAIL_EM_SCOPED_IF(__COUNTER__, __VA_ARGS__)

#define DETAIL_EM_SCOPED_IF(counter_, .../*decl*/) \
    DETAIL_EM_SCOPED_IF_LOW(EM_CAT(__em_scoped_if_flag_, counter_), EM_CAT(__em_scoped_if_label1_, counter_), EM_CAT(__em_scoped_if_label2_, counter_), __VA_ARGS__)

#define DETAIL_EM_SCOPED_IF_LOW(flag_, label1_, label2_, .../*decl*/) \
    if (bool flag_ = false) {} \
    else \
        label2_: \
        if (!flag_) \
            if (__VA_ARGS__) \
            { \
                goto label1_; \
            } \
            else \
                if (true) \
                { \
                    flag_ = true; \
                    goto label2_; \
                } \
                else \
                    label1_:
/*
                {
                    // then
                }
        else
        {
            // else
        }
*/
