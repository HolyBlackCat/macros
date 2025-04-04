#include "em/macros/utils/finally.h"

static_assert([]{
    int ret = 0;

    {
        EM_FINALLY{ret += 42;};
    }

    return ret;
}() == 42);
