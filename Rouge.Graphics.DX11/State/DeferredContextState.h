#pragma once
#include "../DeferredContext.h"

#include <d3d11.h>

struct RougePP::Graphics::DeferredContext::DeferredContextState {
	ID3D11DeviceContext *def;
};