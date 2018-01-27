#include "stdafx.h"
#include "Context.h"
#include "State/ContextState.h"

#include <d3d11.h>

using namespace RougePP::Graphics;


Context::Context() : d_ptr(new ContextState())
{
}

Context::~Context()
{
}

bool Context::IsFullscreen() 
{
	return this->d_ptr->isFullscreen;
}

bool Context::IsDebug() 
{
	return this->d_ptr->isDebug;
}

void Context::SetFullscreen(bool enable)
{
	this->d_ptr->isFullscreen = enable;
}

void Context::SetDebug(bool enable)
{
	this->d_ptr->isDebug = enable;
}

int Context::InitCtxt(HWND hWnd) 
{
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;	//TODO: MSAA
	scd.Windowed = !this->d_ptr->isFullscreen;

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };
	D3D_FEATURE_LEVEL selFeatureLevel;
	auto res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, (this->d_ptr->isDebug ? D3D11_CREATE_DEVICE_DEBUG : NULL), featureLevels, 1, D3D11_SDK_VERSION, &scd, &d_ptr->swapchain, &d_ptr->dev, &selFeatureLevel, &d_ptr->devCtxt);

	if (res == S_OK)
		return 0;

	//TODO: Error!
	return res;
}

int Context::Release()
{
	d_ptr->swapchain->Release();
	d_ptr->dev->Release();
	d_ptr->devCtxt->Release();
	return 0;
}

void Context::Present() {
	d_ptr->swapchain->Present(0, 0);
}