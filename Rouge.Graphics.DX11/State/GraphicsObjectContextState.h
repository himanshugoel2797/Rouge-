#pragma once

#include <d3d11.h>

struct RougePP::Graphics::GraphicsObjectContext::GraphicsObjectContextState {
	ID3D11DeviceContext *devCtxt;
	ID3D11Device *dev;
};