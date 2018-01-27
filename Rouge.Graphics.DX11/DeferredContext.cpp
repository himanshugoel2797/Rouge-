#include "stdafx.h"
#include "DeferredContext.h"
#include "State\DeferredContextState.h"

#include "State\ContextState.h"

#include <d3d11.h>

using namespace RougePP::Graphics;

DeferredContext::DeferredContext(Context *ctxt) : d_ptr(new DeferredContextState())
{
	ctxt->d_ptr->dev->CreateDeferredContext(0, &d_ptr->def);
}


DeferredContext::~DeferredContext()
{
	d_ptr->def->Release();
}
