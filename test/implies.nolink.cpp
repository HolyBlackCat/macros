#include "em/macros/utils/implies.h"

static_assert(0 EM_IMPLIES 0);
static_assert(0 EM_IMPLIES 1);
static_assert(1 EM_IMPLIES 1);
static_assert(!(1 EM_IMPLIES 0));
