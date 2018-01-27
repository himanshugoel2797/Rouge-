#include "stdafx.h"
#include "CoreLoop.h"

#include "GraphicsObjectContext.h"

using namespace RougePP::Math;
using namespace RougePP::Runtime;
using namespace RougePP::Graphics;

GraphicsObjectContext *gctxt;

CoreLoop::CoreLoop(RougePP::Graphics::Context *ctxt, RougePP::Graphics::DeferredContext *dctxt) : Scene("CoreLoop", ctxt, dctxt)
{
	gctxt = new GraphicsObjectContext(ctxt);
	RougePP::Graphics::Texture2D* backbuffer = RougePP::Graphics::Texture2D::BackBuffer(ctxt);
	RougePP::Graphics::RTV* bb_rtv = gctxt->CreateRTV(backbuffer);
	gctxt->ClearRTV(bb_rtv, Vector4(1.0f, 0.5f, 0.5f, 1.0f));
	gctxt->SetRenderTargets(1, &bb_rtv);
}


CoreLoop::~CoreLoop()
{
}

void RougePP::Runtime::CoreLoop::Update(long frametime)
{
}

void RougePP::Runtime::CoreLoop::Render(long frametime)
{
	Context->Present();
}
