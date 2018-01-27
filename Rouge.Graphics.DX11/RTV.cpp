#include "stdafx.h"
#include "RTV.h"
#include "State/RTVState.h"
#include "State/ContextState.h"
#include "State/Texture2DState.h"

#include <d3d11.h>

using namespace RougePP::Graphics;


RTV::RTV() : d_ptr(new RTVState())
{
}

RTV::~RTV()
{
	d_ptr->rtv->Release();
}
