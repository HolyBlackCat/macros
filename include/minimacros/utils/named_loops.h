#pragma once

#include <minimacros/meta/common.h>

/* Implements named loops, allowing you to break/continue from nested loops.
Example:

for (int i = 0; i < 3; i++) M_LOOP_NAME(my_loop)
{
    for (int j = 0; j < 3; j++)
    {
        if (i == 1 && j == 1)
            M_BREAK(my_loop); // or: M_CONTINUE(my_loop);
    }
}

Define `M_KEYWORD_MACROS` to allow `break(my_loop);` and `continue(my_loop);` instead of `M_BREAK`/`M_CONTINUE`.

*/

#define M_LOOP_NAME(name) \
    /* The variable in the conditions prevents `M_BREAK/M_CONTINUE` from being used outside of the loop with the matching name. */\
    if ([[maybe_unused]] constexpr bool _namedloop_InvalidBreakOrContinue = false) \
    { \
        [[maybe_unused]] M_CAT(_namedloop_break_,name): break; \
        [[maybe_unused]] M_CAT(_namedloop_continue_,name): continue; \
    } \
    else

#define M_BREAK(name) goto M_CAT(_namedloop_break_,name)
#define M_CONTINUE(name) goto M_CAT(_namedloop_continue_,name)

#if M_SHORT_MACROS || M_SHORT_MACROS_NAMED_LOOPS
#define LOOP_NAME M_LOOP_NAME
#define BREAK M_BREAK
#define CONTINUE M_CONTINUE
#endif

#if M_KEYWORD_MACROS || M_KEYWORD_MACROS_NAMED_LOOPS

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif

#define break(x) M_BREAK(x)
#define continue(x) M_CONTINUE(x)

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
