#pragma once

// `EM_ASSUME(cond);` informs the compiler that the condition is true.
// If the condition is false during constexpr evaluation, causes a compilation error.

#ifndef EM_ASSUME
#  if __has_cpp_attribute(assume)
#    define EM_ASSUME(...) [[assume(__VA_ARGS__)]]
#  elif defined(__clang__)
#    include "em/macros/portable/if_consteval.h"
#    define EM_ASSUME(...) EM_IF_CONSTEVAL {if (__VA_ARGS__) {} else __builtin_unreachable();} else __builtin_assume(__VA_ARGS__)
#  elif defined(_MSC_VER)
#    include "em/macros/portable/if_consteval.h"
#    define EM_ASSUME(...) EM_IF_CONSTEVAL {if (__VA_ARGS__) {} else throw "Assumption is false.";} __assume(__VA_ARGS__)
#  else
#    define EM_ASSUME(...) if (__VA_ARGS__) {} else __builtin_unreachable();
#  endif
#endif
