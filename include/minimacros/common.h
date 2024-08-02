#pragma once

// Converts something to a string a preprocessing time.
#define M_STR(...) DETAIL_M_STR(__VA_ARGS__)
#define DETAIL_M_STR(...) #__VA_ARGS__

// Concatenates N tokens.
#define M_CAT(x, y) DETAIL_M_CAT(x, y)
#define M_CAT3(x, y, z) DETAIL_M_CAT3(x, y, z)
#define M_CAT4(x, y, z, w) DETAIL_M_CAT4(x, y, z, w)

#define DETAIL_M_CAT(x, y) x##y
#define DETAIL_M_CAT3(x, y, z) x##y##z
#define DETAIL_M_CAT4(x, y, z, w) x##y##z##w
