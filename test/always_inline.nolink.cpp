#include "em/macros/portable/always_inline.h"

EM_ALWAYS_INLINE void always_inline() {}

static_assert([]() EM_ALWAYS_INLINE_LAMBDA {return true;}());
