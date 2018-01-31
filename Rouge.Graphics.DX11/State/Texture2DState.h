#pragma once
#include "Texture2D.h"

#include <d3d11.h>

struct RougePP::Graphics::Texture2D::Texture2DState {
	ID3D11Texture2D * tex;
};