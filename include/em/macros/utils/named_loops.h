#pragma once

#include "em/macros/detail/enable_short_macros.h"
#include "em/macros/meta/common.h"

/* Implements named loops, allowing you to break/continue from nested loops.
Example:

for (int i = 0; i < 3; i++) EM_LOOP_NAME(my_loop)
{
    for (int j = 0; j < 3; j++)
    {
        if (i == 1 && j == 1)
            EM_BREAK(my_loop); // or: EM_CONTINUE(my_loop);
    }
}

Define `EM_KEYWORD_MACROS` to allow `break(my_loop);` and `continue(my_loop);` instead of `EM_BREAK`/`EM_CONTINUE`.

*/

#define EM_LOOP_NAME(name) \
    /* The variable in the conditions prevents `EM_BREAK/EM_CONTINUE` from being used outside of the loop with the matching name. */\
    if ([[maybe_unused]] constexpr bool _namedloop_InvalidBreakOrContinue = false) \
    { \
        [[maybe_unused]] EM_CAT(_namedloop_break_,name): break; \
        [[maybe_unused]] EM_CAT(_namedloop_continue_,name): continue; \
    } \
    else

#define EM_BREAK(name) goto EM_CAT(_namedloop_break_,name)
#define EM_CONTINUE(name) goto EM_CAT(_namedloop_continue_,name)

#if EM_ENABLE_SHORT_MACROS(NAMED_LOOPS)
#define LOOP_NAME EM_LOOP_NAME
#define BREAK EM_BREAK
#define CONTINUE EM_CONTINUE
#endif

#if EM_ENABLE_KEYWORD_MACROS(NAMED_LOOPS)

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif

#define break(x) EM_BREAK(x)
#define continue(x) EM_CONTINUE(x)

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
