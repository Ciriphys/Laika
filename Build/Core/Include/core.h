#pragma once

#ifdef LKA_BUILD_DLL
    #ifdef LKA_WIN
        #define LKA_API __declspec(dllexport)
    #else
        #define LKA_API extern
    #endif
#else
    #ifdef LKA_WIN
        #define LKA_API __declspec(dllimport)
    #else
        #define LKA_API extern
    #endif
#endif

// Suppress IntelliSense's C warnings on Windows
#ifdef LKA_WIN
    #pragma warning(disable:6011)
    #pragma warning(disable:6031)
    #pragma warning(disable:6308)
    #pragma warning(disable:6387)
#endif