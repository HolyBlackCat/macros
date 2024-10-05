#pragma once

// `EM_NO_UNIQUE_ADDRESS` is the portable replacement for `[[no_unique_address]]`.
//   On MSVC it prepends `msvc::` to the attribute name (because the unprefixed version has no effect at the moment, because MSVC ABI is dumb).
//   Pre-C++20 expands to nothing.

// Not including `platform/language_version.h` for simplicity.
#ifdef _MSC_VER
#  if _MSVC_LANG >= 202000
#    define EM_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]] // MSVC strikes again!
#  else
#    define EM_NO_UNIQUE_ADDRESS
#  endif
#else
#  if __cplusplus >= 202000
#    define EM_NO_UNIQUE_ADDRESS [[no_unique_address]]
#  else
#    define EM_NO_UNIQUE_ADDRESS
#  endif
#endif
