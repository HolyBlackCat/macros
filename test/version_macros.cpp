#include <minimacros/meta/compare_versions.h>

static_assert(M_COMPARE_VERSION2(1000,     3004,   == 3));
static_assert(M_COMPARE_VERSION2(1000,     3004,   == 3,4));
static_assert(M_COMPARE_VERSION3(1000,100, 300405, == 3));
static_assert(M_COMPARE_VERSION3(1000,100, 300405, == 3,4));
static_assert(M_COMPARE_VERSION3(1000,100, 300405, == 3,4,5));
