#pragma once

#include "em/macros/portable/always_inline.h"
#include "em/macros/portable/artificial.h"

// Use this to mark tiny functions that should be inlined and shouldn't appear in the debugger.
#ifndef EM_TINY
#define EM_TINY EM_ALWAYS_INLINE EM_ARTIFICIAL
#endif

// Use this to mark tiny lambdas that should be inlined and shouldn't appear in the debugger.
#ifndef EM_TINY_LAMBDA
#define EM_TINY_LAMBDA EM_ALWAYS_INLINE_LAMBDA EM_ARTIFICIAL
#endif
