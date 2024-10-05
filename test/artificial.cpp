#include <em/macros/portable/artificial.h>

EM_ARTIFICIAL inline void foo() {}
static_assert([]() EM_ARTIFICIAL {return true;}());
