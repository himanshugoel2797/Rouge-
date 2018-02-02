#pragma once

#include "Common.h"

#include <string>
#include <memory>
#include <windows.h>


namespace RougePP::Graphics {
	class Context
	{
	private:
		struct ContextState;
		std::unique_ptr<ContextState> d_ptr;

	public:
		GRAPH_DllVisible Context();
		GRAPH_DllVisible ~Context();

		GRAPH_DllVisible bool IsFullscreen();
		GRAPH_DllVisible bool IsDebug();

		GRAPH_DllVisible void SetFullscreen(bool enable);
		GRAPH_DllVisible void SetDebug(bool enable);

		GRAPH_DllVisible int InitCtxt(HWND hWnd, std::wstring app_name, int app_ver, int eng_ver);
		GRAPH_DllVisible int Release();

		GRAPH_DllVisible void Present();

		const int DeferredContextCount = 64;

		friend class Texture2D;
		friend class RTV;
		friend class DeferredContext;
		friend class GraphicsObjectContext;
	};
}
