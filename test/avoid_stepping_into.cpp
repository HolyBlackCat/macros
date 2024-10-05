#include <minimacros/portable/avoid_stepping_into.h>

EM_AVOID_STEPPING_INTO inline void foo() {}
static_assert([]() EM_AVOID_STEPPING_INTO {return true;}());
