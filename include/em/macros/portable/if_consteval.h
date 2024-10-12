#pragma once

#if __cpp_if_consteval
#  define EM_IF_CONSTEVAL if consteval
#  define EM_IF_NOT_CONSTEVAL if !consteval
#else
#  include <type_traits>
#  define EM_IF_CONSTEVAL if (std::is_constant_evaluated())
#  define EM_IF_NOT_CONSTEVAL if (!std::is_constant_evaluated())
#endif
