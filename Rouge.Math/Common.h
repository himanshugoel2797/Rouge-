#pragma once

#ifdef ROUGEMATH_EXPORTS
	#define RMATH_DllVisible   __declspec( dllexport )  
#else
	#define RMATH_DllVisible __declspec( dllimport )
#endif