#pragma once

#include <minimacros/platform/compiler.h>
#include <minimacros/platform/language_version.h>
#include <minimacros/platform/os.h>
#include <minimacros/platform/preprocessor.h>
#include <minimacros/platform/stdlib.h>
#include <minimacros/utils/common.h>

#define M_STRING_PLATFORM_SUMMARY \
    /* OS */\
    M_STRING_OS \
    ", " \
    /* Compiler */\
    M_STRING_COMPILER \
        DETAIL_M_PLATFORM_SUMMARY_COMPILER_VERSION \
    ", " \
    /* C++ standard library */\
    M_STRING_CPP_STDLIB \
        DETAIL_M_PLATFORM_SUMMARY_CPP_STDLIB_VERSION \
    /* Preprocessor flavor (optional), automatically prepends comma if non-empty */\
    DETAIL_M_PLATFORM_SUMMARY_PREPROCESSOR ", " \
    /* C++ version */\
    "C++" DETAIL_M_PLATFORM_SUMMARY_CPP

#if M_COMPILER_VERSION
#define DETAIL_M_PLATFORM_SUMMARY_COMPILER_VERSION " " M_STRING_COMPILER_VERSION
#else
#define DETAIL_M_PLATFORM_SUMMARY_COMPILER_VERSION
#endif

#if M_CPP_STDLIB_VERSION
#define DETAIL_M_PLATFORM_SUMMARY_CPP_STDLIB_VERSION " " M_STRING_CPP_STDLIB_VERSION
#else
#define DETAIL_M_PLATFORM_SUMMARY_CPP_STDLIB_VERSION
#endif

#if M_IS_ACTUAL_MSVC
#if M_IS_LEGACY_MSVC_PREPROCESSOR
#define DETAIL_M_PLATFORM_SUMMARY_PREPROCESSOR ", Legacy preprocessor"
#else
#define DETAIL_M_PLATFORM_SUMMARY_PREPROCESSOR ", Modern preprocessor"
#endif
#else
#define DETAIL_M_PLATFORM_SUMMARY_PREPROCESSOR
#endif

// Convert `M_CPP_STANDARD` to a string (it's normally an expression).
// Update when C++ updates.
#if M_CPP_STANDARD == 26
#define DETAIL_M_PLATFORM_SUMMARY_CPP "26"
#elif M_CPP_STANDARD == 23
#define DETAIL_M_PLATFORM_SUMMARY_CPP "23"
#elif M_CPP_STANDARD == 20
#define DETAIL_M_PLATFORM_SUMMARY_CPP "20"
#elif M_CPP_STANDARD == 17
#define DETAIL_M_PLATFORM_SUMMARY_CPP "17"
#elif M_CPP_STANDARD == 14
#define DETAIL_M_PLATFORM_SUMMARY_CPP "14"
#elif M_CPP_STANDARD == 11
#define DETAIL_M_PLATFORM_SUMMARY_CPP "11"
#elif M_CPP_STANDARD == 98
#define DETAIL_M_PLATFORM_SUMMARY_CPP "98"
#else
#define DETAIL_M_PLATFORM_SUMMARY_CPP "?? (" M_STR(M_CPP_STANDARD_DATE) ")"
#endif
