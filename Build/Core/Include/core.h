#pragma once

#ifdef CVT_BUILD_DLL
	#define CVT_API __declspec(dllexport)
#else
	#define CVT_API  __declspec(dllimport)
#endif
