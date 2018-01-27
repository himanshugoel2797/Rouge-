#include "stdafx.h"
#include "GraphicsObjectContext.h"
#include "State\GraphicsObjectContextState.h"

#include "State\ContextState.h"
#include "State\DeferredContextState.h"
#include "State\RTVState.h"
#include "State\Texture2DState.h"

using namespace RougePP::Graphics;

GraphicsObjectContext::GraphicsObjectContext(Context *ctxt) : d_ptr(new GraphicsObjectContextState())
{
	d_ptr->devCtxt = ctxt->d_ptr->devCtxt;
	d_ptr->dev = ctxt->d_ptr->dev;
}

GraphicsObjectContext::GraphicsObjectContext(Context *ctxt, DeferredContext *dctxt) : d_ptr(new GraphicsObjectContextState())
{
	d_ptr->devCtxt = dctxt->d_ptr->def;
	d_ptr->dev = ctxt->d_ptr->dev;
}


GraphicsObjectContext::~GraphicsObjectContext()
{
}

RTV* GraphicsObjectContext::CreateRTV(Texture2D *tex) {
	RTV* ret = new RTV();
	d_ptr->dev->CreateRenderTargetView(tex->d_ptr->tex, NULL, &ret->d_ptr->rtv);
	return ret;
}

void GraphicsObjectContext::ClearRTV(RTV *rtv, RougePP::Math::Vector4 col) {
	float clearCol[4];
	col.ToFloatArray(clearCol);

	d_ptr->devCtxt->ClearRenderTargetView(rtv->d_ptr->rtv, clearCol);
}

void GraphicsObjectContext::SetRenderTargets(int num, RTV **rtvs) {
	if (num == 1) {
		d_ptr->devCtxt->OMSetRenderTargets(1, &(*rtvs)->d_ptr->rtv, NULL);
	}
	else {
		ID3D11RenderTargetView **dx_rtvs = new ID3D11RenderTargetView*[num];
		for (int i = 0; i < num; i++)
			dx_rtvs[i] = rtvs[i]->d_ptr->rtv;

		d_ptr->devCtxt->OMSetRenderTargets(num, dx_rtvs, NULL);
		delete[] dx_rtvs;
	}
}