#include "stdafx.h"
#include "GraphicsObjectContext.h"
#include "State\GraphicsObjectContextState.h"

#include "State\ContextState.h"
#include "State\DeferredContextState.h"
#include "State\RTVState.h"
#include "State\Texture2DState.h"
#include "State\ShaderObjectState.h"

#include <d3d11.h>
#include <D3DCompiler.h>

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

GRAPH_DllVisible ShaderObject * RougePP::Graphics::GraphicsObjectContext::CreateShader(std::wstring filename, ShaderObject::ShaderType sType, std::string fname)
{
	ShaderObject *obj = new ShaderObject();
	ID3DBlob *blob;
	obj->d_ptr->sType = sType;
	int flags = 0;
	std::string target;

	switch (sType) {
	case ShaderObject::ShaderType::Vertex:
		target = "vs_5_0";
		break;
	case ShaderObject::ShaderType::Fragment:
		target = "ps_5_0";
		break;
	case ShaderObject::ShaderType::Domain:
		target = "ds_5_0";
		break;
	case ShaderObject::ShaderType::Hull:
		target = "hs_5_0";
		break;
	case ShaderObject::ShaderType::Geometry:
		target = "gs_5_0";
		break;
	case ShaderObject::ShaderType::Compute:
		target = "cs_5_0";
		break;
	}

#ifdef _DEBUG
	flags = D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else
	flags = D3DCOMPILE_SKIP_VALIDATION;
#endif

	D3DCompileFromFile(filename.c_str(), NULL, NULL, fname.c_str(), target.c_str(), flags, 0, &blob, NULL);

	switch (sType) {
	case ShaderObject::ShaderType::Vertex:
		d_ptr->dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->vs);
		break;
	case ShaderObject::ShaderType::Fragment:
		d_ptr->dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->ps);
		break;
	case ShaderObject::ShaderType::Domain:
		d_ptr->dev->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->ds);
		break;
	case ShaderObject::ShaderType::Hull:
		d_ptr->dev->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->hs);
		break;
	case ShaderObject::ShaderType::Geometry:
		d_ptr->dev->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->gs);
		break;
	case ShaderObject::ShaderType::Compute:
		d_ptr->dev->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &obj->d_ptr->cs);
		break;
	}

	blob->Release();

	return obj;
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

void RougePP::Graphics::GraphicsObjectContext::SetViewports(int num, RougePP::Math::Vector4 * vp)
{
	D3D11_VIEWPORT *vprt = new D3D11_VIEWPORT[num];
	memset(vprt, 0, sizeof(D3D11_VIEWPORT) * num);
	for (int i = 0; i < num; i++) {
		vprt[i].TopLeftX = vp[i].Values[0];
		vprt[i].TopLeftY = vp[i].Values[1];
		vprt[i].Width = vp[i].Values[2];
		vprt[i].Height = vp[i].Values[3];
	}
	d_ptr->devCtxt->RSSetViewports(num, vprt);
	delete[] vprt;
}
