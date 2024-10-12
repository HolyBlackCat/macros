#pragma once

// `EM_ASSUME(cond);` informs the compiler that the condition is true.

#ifndef EM_ASSUME
#  if __has_cpp_attribute(assume)
#    define EM_ASSUME(...) [[assume(__VA_ARGS__)]]
#  elif defined(__clang__)
#    define EM_ASSUME(...) __builtin_assume(__VA_ARGS__)
#  elif defined(_MSC_VER)
#    define EM_ASSUME(...) __assume(__VA_ARGS__)
#  else
#    define EM_ASSUME(...) if (__VA_ARGS__) {} else __builtin_unreachable();
#  endif
#endif
