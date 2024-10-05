#pragma once

#include <em/macros/platform/compiler.h>
#include <em/macros/platform/language_version.h>
#include <em/macros/platform/os.h>
#include <em/macros/platform/preprocessor.h>
#include <em/macros/platform/stdlib.h>
#include <em/macros/meta/common.h>

#define EM_STRING_PLATFORM_SUMMARY \
    /* OS */\
    EM_STRING_OS \
    ", " \
    /* Compiler */\
    EM_STRING_COMPILER \
        DETAIL_EM_PLATFORM_SUMMARY_COMPILER_VERSION \
    ", " \
    /* C++ standard library */\
    EM_STRING_CPP_STDLIB \
        DETAIL_EM_PLATFORM_SUMMARY_CPP_STDLIB_VERSION \
    /* Preprocessor flavor (optional), automatically prepends comma if non-empty */\
    DETAIL_EM_PLATFORM_SUMMARY_PREPROCESSOR ", " \
    /* C++ version */\
    "C++" DETAIL_EM_PLATFORM_SUMMARY_CPP

#if EM_COMPILER_VERSION
#define DETAIL_EM_PLATFORM_SUMMARY_COMPILER_VERSION " " EM_STRING_COMPILER_VERSION
#else
#define DETAIL_EM_PLATFORM_SUMMARY_COMPILER_VERSION
#endif

#if EM_CPP_STDLIB_VERSION
#define DETAIL_EM_PLATFORM_SUMMARY_CPP_STDLIB_VERSION " " EM_STRING_CPP_STDLIB_VERSION
#else
#define DETAIL_EM_PLATFORM_SUMMARY_CPP_STDLIB_VERSION
#endif

#if EM_IS_ACTUAL_MSVC
#if EM_IS_LEGACY_MSVC_PREPROCESSOR
#define DETAIL_EM_PLATFORM_SUMMARY_PREPROCESSOR ", Legacy preprocessor"
#else
#define DETAIL_EM_PLATFORM_SUMMARY_PREPROCESSOR ", Modern preprocessor"
#endif
#else
#define DETAIL_EM_PLATFORM_SUMMARY_PREPROCESSOR
#endif

// Convert `EM_CPP_STANDARD` to a string (it's normally an expression).
// Update when C++ updates.
#if EM_CPP_STANDARD == 26
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "26"
#elif EM_CPP_STANDARD == 23
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "23"
#elif EM_CPP_STANDARD == 20
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "20"
#elif EM_CPP_STANDARD == 17
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "17"
#elif EM_CPP_STANDARD == 14
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "14"
#elif EM_CPP_STANDARD == 11
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "11"
#elif EM_CPP_STANDARD == 98
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "98"
#else
#define DETAIL_EM_PLATFORM_SUMMARY_CPP "?? (" EM_STR(EM_CPP_STANDARD_DATE) ")"
#endif
