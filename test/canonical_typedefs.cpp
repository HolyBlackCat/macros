#include <minimacros/utils/canonical_typedefs.h>

M_CANONICAL_TYPEDEFS( (template <typename T, typename U> struct), my_basic_string,
    (my_string, my_basic_string<char, char>)
    (my_wstring, my_basic_string<wchar_t, wchar_t>)
)
