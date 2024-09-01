#pragma once

// Identify the current OS.
// This isn't particularly extensive, and only covers the common platforms.

// Use `M_STRING_OS` to get the OS name as a string.
// We also define following macros to 0 or 1:
//
//   on Windows:     M_IS_WINDOWS                                   M_IS_WINDOWS_OR_CYGWIN
//   on Linux:       M_IS_LINUX      M_IS_UNIX
//   on MacOS:       M_IS_MACOS
//   on Android:     M_IS_ANDROID    M_IS_UNIX   M_IS_SMARTPHONE
//   on IPhone:      M_IS_IPHONE     M_IS_UNIX   M_IS_SMARTPHONE
//
//   on Cygwin:      M_IS_LINUX      M_IS_UNIX     M_IS_CYGWIN   M_IS_WINDOWS_OR_CYGWIN
//   on MSYS Cygwin: M_IS_LINUX      M_IS_UNIX     M_IS_CYGWIN   M_IS_WINDOWS_OR_CYGWIN   M_IS_MSYS_CYGWIN
//
//   on an unknown unix:             M_IS_UNIX
//   on a completely unknown OS: no macros
//
// Some notes:
// * Android is technically Linux too, but I only define M_IS_UNIX and not M_IS_LINUX, this sounds less confusing to me.
//   Not sure if I should rename M_IS_LINUX to "gnu linux", since I want it to be true for musl linux too, and is that still gnu?
// * Cygwin reports M_IS_LINUX and M_IS_UNIX, but not M_IS_WINDOWS. Check M_IS_CYGWIN and M_IS_WINDOWS_OR_CYGWIN.

// To override the detection, define one of those macros.
// Don't attempt to override by defining generic macros, such as `M_IS_SMARTPHONE` (in this case use `M_IS_ANDROID` or `M_IS_IPHONE`).
#if defined(M_IS_WINDOWS) || defined(M_IS_LINUX) || defined(M_IS_CYGWIN) || defined(M_IS_MSYS_CYGWIN) || defined(M_IS_ANDROID) || defined(M_IS_MACOS) || defined(M_IS_IPHONE) || defined(M_IS_UNIX)
#define M_OVERRIDING_OS_DETECTION 1
#else
#define M_OVERRIDING_OS_DETECTION 0
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wundef"
#endif

#if M_OVERRIDING_OS_DETECTION ? M_IS_WINDOWS : defined(_WIN32)
#  define M_STRING_OS "Windows"
#  define M_IS_WINDOWS 1
#  define M_IS_WINDOWS_OR_CYGWIN 1
#elif M_OVERRIDING_OS_DETECTION ? M_IS_LINUX || M_IS_CYGWIN || M_IS_MSYS_CYGWIN : defined(__linux__) && !defined(__ANDROID__)
#  define M_IS_LINUX 1
#  define M_IS_UNIX 1
#  if M_OVERRIDING_OS_DETECTION ? M_IS_CYGWIN || M_IS_MSYS_CYGWIN : defined(__CYGWIN__)
#    define M_IS_CYGWIN 1
#    define M_IS_WINDOWS_OR_CYGWIN 1
#    if M_OVERRIDING_OS_DETECTION ? M_IS_MSYS_CYGWIN : defined(__MSYS__)
#      define M_STRING_OS "MSYS (Cygwin)"
#      define M_IS_MSYS_CYGWIN 1
#    else
#      define M_STRING_OS "Cygwin"
#    endif
#  else
#    define M_STRING_OS "Linux"
#  endif
#elif M_OVERRIDING_OS_DETECTION ? M_IS_ANDROID : defined(__ANDROID__)
#  define M_STRING_OS "Android"
#  define M_IS_ANDROID 1
#  define M_IS_UNIX 1
#  define M_IS_SMARTPHONE 1
#elif M_OVERRIDING_OS_DETECTION ? M_IS_MACOS || M_IS_IPHONE : defined(__APPLE__) // This branch isn't particularly well-tested.
#  ifdef __is_target_os
#    define DETAIL_M_TARGET_OS(x) __is_target_os(x)
#  else
#    define DETAIL_M_TARGET_OS(x) 0
#  endif
#  if M_OVERRIDING_OS_DETECTION ? M_IS_IPHONE : DETAIL_M_TARGET_OS(ios)
#    define M_STRING_OS "IPhone"
#    define M_IS_IPHONE 1
#    define M_IS_SMARTPHONE 1
#  else
#    define M_STRING_OS "MacOS"
#    define M_IS_MACOS 1
#  endif
#  define M_IS_APPLE 1
#elif M_OVERRIDING_OS_DETECTION ? M_IS_UNIX : defined(__unix__)
#  define M_STRING_OS "Unknown Unix"
#  define M_IS_UNIX 1
#else
#  define M_STRING_OS "Unknown OS"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifndef M_IS_ANDROID
#define M_IS_ANDROID 0
#endif
#ifndef M_IS_APPLE
#define M_IS_APPLE 0
#endif
#ifndef M_IS_CYGWIN
#define M_IS_CYGWIN 0
#endif
#ifndef M_IS_IPHONE
#define M_IS_IPHONE 0
#endif
#ifndef M_IS_LINUX
#define M_IS_LINUX 0
#endif
#ifndef M_IS_MACOS
#define M_IS_MACOS 0
#endif
#ifndef M_IS_MSYS_CYGWIN
#define M_IS_MSYS_CYGWIN 0
#endif
#ifndef M_IS_SMARTPHONE
#define M_IS_SMARTPHONE 0
#endif
#ifndef M_IS_UNIX
#define M_IS_UNIX 0
#endif
#ifndef M_IS_WINDOWS
#define M_IS_WINDOWS 0
#endif
#ifndef M_IS_WINDOWS_OR_CYGWIN
#define M_IS_WINDOWS_OR_CYGWIN 0
#endif
