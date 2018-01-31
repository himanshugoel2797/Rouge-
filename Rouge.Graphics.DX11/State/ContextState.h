#pragma once
#include "Context.h"
#include "DeferredContext.h"

#include <queue>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <d3d11.h>

struct RougePP::Graphics::Context::ContextState {
	IDXGISwapChain * swapchain;
	ID3D11Device *dev;

	ID3D11DeviceContext *devCtxt;
	std::mutex devCtxtMutex;

	std::atomic_bool isFullscreen;
	std::atomic_bool isDebug;
};