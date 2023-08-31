#pragma once

#ifdef CVT_BUILD_DLL
    #ifdef CVT_WIN
        #define CVT_API __declspec(dllexport)
    #else
        #define CVT_API extern
    #endif
#else
    #ifdef CVT_WIN
        #define CVT_API __declspec(dllimport)
    #else
        #define CVT_API extern
    #endif
#endif

// Suppress IntelliSense's C warnings on Windows
#ifdef CVT_WIN
    #pragma warning(disable:6011)
    #pragma warning(disable:6387)
#endif