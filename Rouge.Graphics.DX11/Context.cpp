#include "stdafx.h"
#include "Context.h"
#include "State/ContextState.h"

#include <d3d11.h>
#include <amd_ags.h>

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

int Context::InitCtxt(HWND hWnd, std::wstring app_name, int app_ver, int eng_ver)
{
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;	//TODO: MSAA
	scd.Windowed = !this->d_ptr->isFullscreen;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };
	D3D_FEATURE_LEVEL selFeatureLevel;

	AGSContext *agsCtxt;
	if (agsInit(&agsCtxt, NULL, NULL) == AGS_SUCCESS) {
		AGSDX11DeviceCreationParams creationParams;
		AGSDX11ExtensionParams extParams;
		AGSDX11ReturnedParams retParams;

		memset(&creationParams, 0, sizeof(creationParams));
		creationParams.pAdapter = NULL;
		creationParams.DriverType = D3D_DRIVER_TYPE_HARDWARE;
		creationParams.Flags = (this->d_ptr->isDebug ? D3D11_CREATE_DEVICE_DEBUG : NULL);
		creationParams.pFeatureLevels = featureLevels;
		creationParams.FeatureLevels = 1;
		creationParams.SDKVersion = D3D11_SDK_VERSION;
		creationParams.pSwapChainDesc = &scd;

		memset(&extParams, 0, sizeof(extParams));
		extParams.uavSlot = 7;
		extParams.appVersion = app_ver;
		extParams.pAppName = app_name.c_str();
		extParams.engineVersion = eng_ver;
		extParams.pEngineName = L"Rouge++ PreAlpha";

		if (agsDriverExtensionsDX11_CreateDevice(agsCtxt, &creationParams, &extParams, &retParams) == AGS_SUCCESS) {
			d_ptr->swapchain = retParams.pSwapChain;
			d_ptr->dev = retParams.pDevice;
			d_ptr->devCtxt = retParams.pImmediateContext;
			selFeatureLevel = retParams.FeatureLevel;

			return 0;
		}

		return -1;
	}
	else {
		auto res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, (this->d_ptr->isDebug ? D3D11_CREATE_DEVICE_DEBUG : NULL), featureLevels, 1, D3D11_SDK_VERSION, &scd, &d_ptr->swapchain, &d_ptr->dev, &selFeatureLevel, &d_ptr->devCtxt);
		if (res == S_OK)
			return 0;
		//TODO: Error!
		return res;
	}
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