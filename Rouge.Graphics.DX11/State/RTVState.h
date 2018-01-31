#pragma once
#include "RTV.h"

#include <d3d11.h>

struct RougePP::Graphics::RTV::RTVState {
	ID3D11RenderTargetView * rtv;
};