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
}

ShaderObject::ShaderType ShaderObject::Type() {
	return d_ptr->sType;
}