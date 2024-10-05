#include <minimacros/portable/force_inline.h>

EM_FORCE_INLINE void force_inline() {}

static_assert([]() EM_FORCE_INLINE_LAMBDA {return true;}());
