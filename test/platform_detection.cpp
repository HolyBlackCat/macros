// #error Don't forget to check HAVE_... here (have compiler version, cpp stdlib version, etc; if false, don't print them and spaces before them)
// #error also don't forget to check all the HAS_ (use approx ranges)
// #error write tests by redefining some system macros (don't forget apple clang)


// #error Add intel compiler? Maybe don't even expose version numbers, just a string "Blah compiler X.Y.Z" (+ ", like" + "Clang x.y.z ...", prepend it if it's set)

#include <em/macros/platform/compiler.h>
#include <em/macros/platform/preprocessor.h>
#include <em/macros/platform/stdlib.h>
#include <em/macros/platform/summary.h>

// Compiler.
#if defined(__clang__)
static_assert(EM_IS_CLANG_VERSION(== __clang_major__));
static_assert(EM_IS_CLANG_VERSION(== __clang_major__, __clang_minor__));
static_assert(EM_IS_CLANG_VERSION(== __clang_major__, __clang_minor__, __clang_patchlevel__));
static_assert(!EM_IS_CLANG_VERSION(== __clang_major__, __clang_minor__, 9));

static_assert(!EM_IS_GCC_VERSION(== __clang_major__));
static_assert(!EM_IS_APPLE_CLANG_VERSION(== __clang_major__));
static_assert(!EM_IS_MSVC_VERSION(== __clang_major__));
#elif defined(__GNUC__)
static_assert(EM_IS_GCC_VERSION(== __GNUC__));
static_assert(EM_IS_GCC_VERSION(== __GNUC__, __GNUC_MINOR__));
static_assert(EM_IS_GCC_VERSION(== __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__));
static_assert(!EM_IS_GCC_VERSION(== __GNUC__, __GNUC_MINOR__, 9));

static_assert(!EM_IS_CLANG_VERSION(== __GNUC__));
static_assert(!EM_IS_APPLE_CLANG_VERSION(== __GNUC__));
static_assert(!EM_IS_MSVC_VERSION(== __GNUC__));
#elif defined(_MSC_VER)
static_assert(EM_IS_MSVC_VERSION(== _MSC_VER));
static_assert(EM_IS_MSVC_VERSION(== _MSC_VER, _MSC_FULL_VER % 100000));
static_assert(!EM_IS_MSVC_VERSION(== _MSC_VER,42));

static_assert(!EM_IS_GCC_VERSION(== _MSC_VER));
static_assert(!EM_IS_CLANG_VERSION(== _MSC_VER));
static_assert(!EM_IS_APPLE_CLANG_VERSION(== _MSC_VER));
#endif

// Make sure all those are defined.
#if defined(__clang__)
#  if defined(__apple_build_version__)
static_assert(EM_IS_ACTUAL_MSVC == 0 && EM_IS_ACTUAL_GCC == 0 && EM_IS_ACTUAL_CLANG == 1 && EM_IS_GCC_LIKE == 1 && EM_IS_CLANG_LIKE == 1 && EM_IS_MSVC_LIKE == 0 && EM_IS_APPLE_CLANG == 1);
#  elif defined(_MSC_VER)
static_assert(EM_IS_ACTUAL_MSVC == 0 && EM_IS_ACTUAL_GCC == 0 && EM_IS_ACTUAL_CLANG == 1 && EM_IS_GCC_LIKE == 0 && EM_IS_CLANG_LIKE == 1 && EM_IS_MSVC_LIKE == 1 && EM_IS_APPLE_CLANG == 0);
#  else
static_assert(EM_IS_ACTUAL_MSVC == 0 && EM_IS_ACTUAL_GCC == 0 && EM_IS_ACTUAL_CLANG == 1 && EM_IS_GCC_LIKE == 1 && EM_IS_CLANG_LIKE == 1 && EM_IS_MSVC_LIKE == 0 && EM_IS_APPLE_CLANG == 0);
#  endif
#elif defined(__GNUC__)
static_assert(EM_IS_ACTUAL_MSVC == 0 && EM_IS_ACTUAL_GCC == 1 && EM_IS_ACTUAL_CLANG == 0 && EM_IS_GCC_LIKE == 1 && EM_IS_CLANG_LIKE == 0 && EM_IS_MSVC_LIKE == 0 && EM_IS_APPLE_CLANG == 0);
#elif defined(_MSC_VER)
static_assert(EM_IS_ACTUAL_MSVC == 1 && EM_IS_ACTUAL_GCC == 0 && EM_IS_ACTUAL_CLANG == 0 && EM_IS_GCC_LIKE == 0 && EM_IS_CLANG_LIKE == 0 && EM_IS_MSVC_LIKE == 1 && EM_IS_APPLE_CLANG == 0);
#endif

// C++ standard library.
constexpr bool is_libstdcxx
#ifdef _GLIBCXX_RELEASE
    = true;
static_assert(EM_IS_LIBSTDCXX_VERSION(== _GLIBCXX_RELEASE));
static_assert(EM_IS_LIBSTDCXX_DATE(== __GLIBCXX__/10000));
static_assert(EM_IS_LIBSTDCXX_DATE(== __GLIBCXX__/10000, __GLIBCXX__/100%100));
static_assert(EM_IS_LIBSTDCXX_DATE(== __GLIBCXX__/10000, __GLIBCXX__/100%100, __GLIBCXX__%100));
static_assert(EM_IS_LIBSTDCXX);
static_assert(!EM_IS_LIBCPP);
static_assert(!EM_IS_MSVC_STL);
static_assert(!EM_IS_CPP_STDLIB_MISSING);
#else
    = false;
static_assert(!EM_IS_LIBSTDCXX_VERSION(== 42));
static_assert(!EM_IS_LIBSTDCXX_DATE(== 42));
#endif
constexpr bool is_libcpp
#ifdef _LIBCPP_VERSION
    = true;
static_assert(EM_IS_LIBCPP_VERSION(== _LIBCPP_VERSION/10000));
static_assert(EM_IS_LIBCPP_VERSION(== _LIBCPP_VERSION/10000, _LIBCPP_VERSION/100%100, _LIBCPP_VERSION%100));
static_assert(!EM_IS_LIBSTDCXX);
static_assert(EM_IS_LIBCPP);
static_assert(!EM_IS_MSVC_STL);
static_assert(!EM_IS_CPP_STDLIB_MISSING);
#else
    = false;
static_assert(!EM_IS_LIBCPP_VERSION(== 42));
#endif
constexpr bool is_msvc_stl
#ifdef _MSVC_STL_VERSION
    = true;
static_assert(EM_IS_MSVC_STL_VERSION(== _MSVC_STL_VERSION));
static_assert(EM_IS_MSVC_STL_DATE(== _MSVC_STL_UPDATE/100));
static_assert(EM_IS_MSVC_STL_DATE(== _MSVC_STL_UPDATE/100,_MSVC_STL_UPDATE%100));
static_assert(!EM_IS_LIBSTDCXX);
static_assert(!EM_IS_LIBCPP);
static_assert(EM_IS_MSVC_STL);
static_assert(!EM_IS_CPP_STDLIB_MISSING);
#else
    = false;
static_assert(!EM_IS_MSVC_STL_VERSION(== 42));
static_assert(!EM_IS_MSVC_STL_DATE(== 42));
#endif

static_assert(EM_IS_LIBSTDCXX == is_libstdcxx);
static_assert(EM_IS_LIBCPP == is_libcpp);
static_assert(EM_IS_MSVC_STL == is_msvc_stl);

// Preprocessor flavor.
#ifdef _MSC_VER
#  ifdef _MSVC_TRADITIONAL
#    if _MSVC_TRADITIONAL
static_assert(EM_IS_LEGACY_MSVC_PREPROCESSOR == 1 && EM_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION == 0);
#    else
static_assert(EM_IS_LEGACY_MSVC_PREPROCESSOR == 0 && EM_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION == 0);
#    endif
#  elif defined(__clang__)
static_assert(EM_IS_LEGACY_MSVC_PREPROCESSOR == 0 && EM_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION == 1);
#  endif
#else
static_assert(EM_IS_LEGACY_MSVC_PREPROCESSOR == 0 && EM_IS_LEGACY_MSVC_PREPROCESSOR_CLANG_IMITATION == 0);
#endif
