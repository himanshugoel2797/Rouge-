#include "stdafx.h"
#include "Texture2D.h"

#include "State/Texture2DState.h"
#include "State/ContextState.h"

#include "Context.h"

using namespace RougePP::Graphics;

Texture2D* Texture2D::BackBuffer(Context * ctxt)
{
	Texture2D* tex = new Texture2D();
	auto res = ctxt->d_ptr->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tex->d_ptr->tex);
	return tex;
}

Texture2D::Texture2D() : d_ptr(new Texture2DState())
{
	d_ptr->srv = NULL;
	d_ptr->tex = NULL;
}

Texture2D::~Texture2D()
{
	if (d_ptr->tex != NULL)
		d_ptr->tex->Release();

	if (d_ptr->srv != NULL)
		d_ptr->srv->Release();
}
