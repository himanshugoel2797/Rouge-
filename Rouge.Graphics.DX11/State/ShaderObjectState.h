#pragma once

#include <d3d11.h>
#include "ShaderBlob.h"

struct RougePP::Graphics::ShaderObject::ShaderObjectState {
	ShaderType sType;
	ShaderBlob *blob;
	union {
		ID3D11VertexShader *vs;
		ID3D11PixelShader *ps;
		ID3D11DomainShader *ds;
		ID3D11HullShader *hs;
		ID3D11GeometryShader *gs;
		ID3D11ComputeShader *cs;
	};
};