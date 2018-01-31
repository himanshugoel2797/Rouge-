#include "stdafx.h"
#include "ShaderObject.h"
#include "State\ShaderObjectState.h"

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace RougePP::Graphics;

ShaderObject::ShaderObject() : d_ptr(new ShaderObjectState())
{
}

ShaderObject::~ShaderObject()
{
	delete this->d_ptr->blob;

	switch (d_ptr->sType) {
	case ShaderType::Vertex:
		d_ptr->vs->Release();
		break;
	case ShaderType::Fragment:
		d_ptr->ps->Release();
		break;
	case ShaderType::Domain:
		d_ptr->ds->Release();
		break;
	case ShaderType::Hull:
		d_ptr->hs->Release();
		break;
	case ShaderType::Geometry:
		d_ptr->gs->Release();
		break;
	case ShaderType::Compute:
		d_ptr->cs->Release();
		break;
	}
}

ShaderObject::ShaderType ShaderObject::Type() {
	return d_ptr->sType;
}