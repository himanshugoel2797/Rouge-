#include "stdafx.h"
#include "GraphicsObjectContext.h"

#include "ShaderBlob.h"

#include "State\GraphicsObjectContextState.h"

#include "State\ContextState.h"
#include "State\DeferredContextState.h"
#include "State\RTVState.h"
#include "State\Texture2DState.h"
#include "State\BufferState.h"
#include "State\ShaderObjectState.h"
#include "State\BufferLayoutState.h"

#include "WICTextureLoader.h"

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

Texture2D* GraphicsObjectContext::CreateTexture2D(int w, int h, int mips, Format fmt, Binding binding, Usage use, AccessType access) {
	Texture2D *tex = new Texture2D();

	D3D11_TEXTURE2D_DESC tex2d_desc;
	memset(&tex2d_desc, 0, sizeof(tex2d_desc));

	tex2d_desc.Width = w;
	tex2d_desc.Height = h;
	tex2d_desc.MipLevels = mips;
	tex2d_desc.Format = (DXGI_FORMAT)fmt;
	tex2d_desc.SampleDesc.Count = 1;
	tex2d_desc.Usage = (D3D11_USAGE)use;
	tex2d_desc.BindFlags = (unsigned int)binding;
	tex2d_desc.CPUAccessFlags = (unsigned int)access;
	tex2d_desc.MiscFlags = 0;

	d_ptr->dev->CreateTexture2D(&tex2d_desc, NULL, &tex->d_ptr->tex);

	return tex;
}

Texture2D* GraphicsObjectContext::LoadTexture2D(std::wstring file) {
	Texture2D *tex = new Texture2D();

	auto res = CreateWICTextureFromFile(d_ptr->dev,
		d_ptr->devCtxt,
		file.c_str(),
		&tex->d_ptr->tex,
		&tex->d_ptr->srv
	);

	return tex;
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
	ID3DBlob *blob = NULL;
	ShaderBlob *rBlob = NULL;
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

	auto extn = filename.find_last_of(L'.');
	auto extn_s = filename.substr(extn, 10);

	if (extn_s.compare(L".hlsl") == 0) {
		D3DCompileFromFile(filename.c_str(), NULL, NULL, fname.c_str(), target.c_str(), flags, 0, &blob, NULL);
		rBlob = new ShaderBlob(blob);
	}
	else if (extn_s.compare(L".cso") == 0) {
		rBlob = new ShaderBlob(filename);
	}

	switch (sType) {
	case ShaderObject::ShaderType::Vertex:
		d_ptr->dev->CreateVertexShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->vs);
		break;
	case ShaderObject::ShaderType::Fragment:
		d_ptr->dev->CreatePixelShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->ps);
		break;
	case ShaderObject::ShaderType::Domain:
		d_ptr->dev->CreateDomainShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->ds);
		break;
	case ShaderObject::ShaderType::Hull:
		d_ptr->dev->CreateHullShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->hs);
		break;
	case ShaderObject::ShaderType::Geometry:
		d_ptr->dev->CreateGeometryShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->gs);
		break;
	case ShaderObject::ShaderType::Compute:
		d_ptr->dev->CreateComputeShader(rBlob->GetBufferPointer(), rBlob->GetBufferSize(), NULL, &obj->d_ptr->cs);
		break;
	}

	obj->d_ptr->blob = rBlob;

	return obj;
}

void GraphicsObjectContext::SetShader(ShaderObject *sObj) {
	switch (sObj->d_ptr->sType) {
	case ShaderObject::ShaderType::Vertex:
		d_ptr->devCtxt->VSSetShader(sObj->d_ptr->vs, NULL, 0);
		break;
	case ShaderObject::ShaderType::Fragment:
		d_ptr->devCtxt->PSSetShader(sObj->d_ptr->ps, NULL, 0);
		break;
	case ShaderObject::ShaderType::Domain:
		d_ptr->devCtxt->DSSetShader(sObj->d_ptr->ds, NULL, 0);
		break;
	case ShaderObject::ShaderType::Hull:
		d_ptr->devCtxt->HSSetShader(sObj->d_ptr->hs, NULL, 0);
		break;
	case ShaderObject::ShaderType::Geometry:
		d_ptr->devCtxt->GSSetShader(sObj->d_ptr->gs, NULL, 0);
		break;
	case ShaderObject::ShaderType::Compute:
		d_ptr->devCtxt->CSSetShader(sObj->d_ptr->cs, NULL, 0);
		break;
	}
}

Buffer* GraphicsObjectContext::CreateBuffer(Usage usage, Binding binding, AccessType access, unsigned int size) {

	Buffer *b = new Buffer();

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));

	switch (usage) {
	case Usage::Default:
		desc.Usage = D3D11_USAGE_DEFAULT;
		break;
	case Usage::Immutable:
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	case Usage::Dynamic:
		desc.Usage = D3D11_USAGE_DYNAMIC;
		break;
	case Usage::Staging:
		desc.Usage = D3D11_USAGE_STAGING;
		break;
	}

	desc.BindFlags = (int)binding;
	desc.CPUAccessFlags = (int)access;
	desc.ByteWidth = size;

	auto res = d_ptr->dev->CreateBuffer(&desc, NULL, &b->d_ptr->buffer);

	return b;
}

void* GraphicsObjectContext::MapBuffer(Buffer *buf, MapType mapType, bool async) {
	D3D11_MAPPED_SUBRESOURCE subres;
	auto res = d_ptr->devCtxt->Map(buf->d_ptr->buffer, 0, (D3D11_MAP)mapType, async ? D3D11_MAP_FLAG_DO_NOT_WAIT : 0, &subres);
	return subres.pData;
}

void RougePP::Graphics::GraphicsObjectContext::UnmapBuffer(Buffer * buf, void * ptr)
{
	d_ptr->devCtxt->Unmap(buf->d_ptr->buffer, 0);
}

void RougePP::Graphics::GraphicsObjectContext::SetVertexBuffer(unsigned int slot, Buffer * buf, unsigned int *offset, unsigned int *stride)
{
	d_ptr->devCtxt->IASetVertexBuffers(slot, 1, &buf->d_ptr->buffer, stride, offset);
}

void GraphicsObjectContext::CompileBufferLayout(BufferLayout *bufLayout, ShaderObject *vshader) {
	auto arr = bufLayout->d_ptr->layouts.data();
	d_ptr->dev->CreateInputLayout(arr, (unsigned int)bufLayout->d_ptr->layouts.size(), vshader->d_ptr->blob->GetBufferPointer(), vshader->d_ptr->blob->GetBufferSize(), &bufLayout->d_ptr->inputLayout);
}

void RougePP::Graphics::GraphicsObjectContext::SetBufferLayout(BufferLayout * bufLayout)
{
	if (bufLayout->d_ptr->inputLayout == NULL) {
		//TODO: Error
	}

	d_ptr->devCtxt->IASetInputLayout(bufLayout->d_ptr->inputLayout);
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

void RougePP::Graphics::GraphicsObjectContext::Draw(int count, int start)
{
	d_ptr->devCtxt->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d_ptr->devCtxt->Draw(count, start);
}