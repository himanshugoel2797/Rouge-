#pragma once

#ifdef BUILD_DX11_BACKEND
	#define GRAPH_DllVisible   __declspec( dllexport )  
#else
	#define GRAPH_DllVisible __declspec( dllimport )
#endif