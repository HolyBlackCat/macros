#pragma once

// Identify the current OS.
// This isn't particularly extensive, and only covers the common platforms.

// Use `EM_STRING_OS` to get the OS name as a string.
// We also define following macros to 0 or 1:
//
//   on Windows:     EM_IS_WINDOWS                                   EM_IS_WINDOWS_OR_CYGWIN
//   on Linux:       EM_IS_LINUX      EM_IS_UNIX
//   on MacOS:       EM_IS_MACOS
//   on Android:     EM_IS_ANDROID    EM_IS_UNIX   EM_IS_SMARTPHONE
//   on IPhone:      EM_IS_IPHONE     EM_IS_UNIX   EM_IS_SMARTPHONE
//
//   on Cygwin:      EM_IS_LINUX      EM_IS_UNIX     EM_IS_CYGWIN   EM_IS_WINDOWS_OR_CYGWIN
//   on MSYS Cygwin: EM_IS_LINUX      EM_IS_UNIX     EM_IS_CYGWIN   EM_IS_WINDOWS_OR_CYGWIN   EM_IS_MSYS_CYGWIN
//
//   on an unknown unix:             EM_IS_UNIX
//   on a completely unknown OS: no macros
//
// Some notes:
// * Android is technically Linux too, but I only define EM_IS_UNIX and not EM_IS_LINUX, this sounds less confusing to me.
//   Not sure if I should rename EM_IS_LINUX to "gnu linux", since I want it to be true for musl linux too, and is that still gnu?
// * Cygwin reports EM_IS_LINUX and EM_IS_UNIX, but not EM_IS_WINDOWS. Check EM_IS_CYGWIN and EM_IS_WINDOWS_OR_CYGWIN.

// To override the detection, define one of those macros.
// Don't attempt to override by defining generic macros, such as `EM_IS_SMARTPHONE` (in this case use `EM_IS_ANDROID` or `EM_IS_IPHONE`).
#if defined(EM_IS_WINDOWS) || defined(EM_IS_LINUX) || defined(EM_IS_CYGWIN) || defined(EM_IS_MSYS_CYGWIN) || defined(EM_IS_ANDROID) || defined(EM_IS_MACOS) || defined(EM_IS_IPHONE) || defined(EM_IS_UNIX)
#define EM_OVERRIDING_OS_DETECTION 1
#else
#define EM_OVERRIDING_OS_DETECTION 0
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wundef"
#endif

#if EM_OVERRIDING_OS_DETECTION ? EM_IS_WINDOWS : defined(_WIN32)
#  define EM_STRING_OS "Windows"
#  define EM_IS_WINDOWS 1
#  define EM_IS_WINDOWS_OR_CYGWIN 1
#elif EM_OVERRIDING_OS_DETECTION ? EM_IS_LINUX || EM_IS_CYGWIN || EM_IS_MSYS_CYGWIN : defined(__linux__) && !defined(__ANDROID__)
#  define EM_IS_LINUX 1
#  define EM_IS_UNIX 1
#  if EM_OVERRIDING_OS_DETECTION ? EM_IS_CYGWIN || EM_IS_MSYS_CYGWIN : defined(__CYGWIN__)
#    define EM_IS_CYGWIN 1
#    define EM_IS_WINDOWS_OR_CYGWIN 1
#    if EM_OVERRIDING_OS_DETECTION ? EM_IS_MSYS_CYGWIN : defined(__MSYS__)
#      define EM_STRING_OS "MSYS (Cygwin)"
#      define EM_IS_MSYS_CYGWIN 1
#    else
#      define EM_STRING_OS "Cygwin"
#    endif
#  else
#    define EM_STRING_OS "Linux"
#  endif
#elif EM_OVERRIDING_OS_DETECTION ? EM_IS_ANDROID : defined(__ANDROID__)
#  define EM_STRING_OS "Android"
#  define EM_IS_ANDROID 1
#  define EM_IS_UNIX 1
#  define EM_IS_SMARTPHONE 1
#elif EM_OVERRIDING_OS_DETECTION ? EM_IS_MACOS || EM_IS_IPHONE : defined(__APPLE__) // This branch isn't particularly well-tested.
#  ifdef __is_target_os
#    define DETAIL_M_TARGET_OS(x) __is_target_os(x)
#  else
#    define DETAIL_M_TARGET_OS(x) 0
#  endif
#  if EM_OVERRIDING_OS_DETECTION ? EM_IS_IPHONE : DETAIL_M_TARGET_OS(ios)
#    define EM_STRING_OS "IPhone"
#    define EM_IS_IPHONE 1
#    define EM_IS_SMARTPHONE 1
#  else
#    define EM_STRING_OS "MacOS"
#    define EM_IS_MACOS 1
#  endif
#  define EM_IS_APPLE 1
#elif EM_OVERRIDING_OS_DETECTION ? EM_IS_UNIX : defined(__unix__)
#  define EM_STRING_OS "Unknown Unix"
#  define EM_IS_UNIX 1
#else
#  define EM_STRING_OS "Unknown OS"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifndef EM_IS_ANDROID
#define EM_IS_ANDROID 0
#endif
#ifndef EM_IS_APPLE
#define EM_IS_APPLE 0
#endif
#ifndef EM_IS_CYGWIN
#define EM_IS_CYGWIN 0
#endif
#ifndef EM_IS_IPHONE
#define EM_IS_IPHONE 0
#endif
#ifndef EM_IS_LINUX
#define EM_IS_LINUX 0
#endif
#ifndef EM_IS_MACOS
#define EM_IS_MACOS 0
#endif
#ifndef EM_IS_MSYS_CYGWIN
#define EM_IS_MSYS_CYGWIN 0
#endif
#ifndef EM_IS_SMARTPHONE
#define EM_IS_SMARTPHONE 0
#endif
#ifndef EM_IS_UNIX
#define EM_IS_UNIX 0
#endif
#ifndef EM_IS_WINDOWS
#define EM_IS_WINDOWS 0
#endif
#ifndef EM_IS_WINDOWS_OR_CYGWIN
#define EM_IS_WINDOWS_OR_CYGWIN 0
#endif
