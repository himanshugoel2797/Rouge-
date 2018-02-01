#include "stdafx.h"
#include "CoreLoop.h"

#include "GraphicsObjectContext.h"
#include "ShaderObject.h"
#include "Buffer.h"
#include "BufferLayout.h"

using namespace RougePP::Math;
using namespace RougePP::Runtime;
using namespace RougePP::Graphics;

GraphicsObjectContext *gctxt;
Buffer *vertices;
BufferLayout *layout;
ShaderObject *vshader, *fshader;

CoreLoop::CoreLoop(RougePP::Graphics::Context *ctxt, RougePP::Graphics::DeferredContext *dctxt) : Scene("CoreLoop", ctxt, dctxt)
{
	gctxt = new GraphicsObjectContext(ctxt);
	RougePP::Graphics::Texture2D* backbuffer = RougePP::Graphics::Texture2D::BackBuffer(ctxt);
	RougePP::Graphics::RTV* bb_rtv = gctxt->CreateRTV(backbuffer);
	gctxt->ClearRTV(bb_rtv, Vector4(1.0f, 1.0f, 0.5f, 1.0f));
	gctxt->SetViewports(1, &Vector4(0, 0, 800, 600));
	gctxt->SetRenderTargets(1, &bb_rtv);

	vshader = gctxt->CreateShader(L"VShader.cso", ShaderObject::ShaderType::Vertex, "main");
	fshader = gctxt->CreateShader(L"PShader.cso", ShaderObject::ShaderType::Fragment, "main");

	vertices = gctxt->CreateBuffer(Usage::Dynamic, Binding::VertexBuffer, AccessType::Write, 3 * 3 * sizeof(float));

	float* verts = (float*)gctxt->MapBuffer(vertices, MapType::WriteDiscard, false);
	verts[0] = 0; verts[1] = 0.5f; verts[2] = 0;
	verts[3] = 0.45f; verts[4] = -0.5f; verts[5] = 0;
	verts[6] = -0.45f; verts[7] = -0.5f; verts[8] = 0;
	gctxt->UnmapBuffer(vertices, verts);

	gctxt->SetShader(vshader);
	gctxt->SetShader(fshader);
	
	layout = new BufferLayout();
	layout->AddLayout(BufferLayout::POSITION, 0, Format::R32_G32_B32_FLOAT, 0, 0, BufferLayout::InputType::PerVertex, 0);
	gctxt->CompileBufferLayout(layout, vshader);

	unsigned int off = 0, stride = 12;
	gctxt->SetVertexBuffer(0, vertices, &off, &stride);
	gctxt->SetBufferLayout(layout);
}


CoreLoop::~CoreLoop()
{
}

void RougePP::Runtime::CoreLoop::Update(long frametime)
{
}

void RougePP::Runtime::CoreLoop::Render(long frametime)
{
	gctxt->Draw(3, 0);
	Context->Present();
}
