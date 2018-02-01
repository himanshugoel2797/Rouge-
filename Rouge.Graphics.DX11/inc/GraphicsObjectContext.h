#pragma once

#include "Common.h"

#include "Enums.h"
#include "Context.h"
#include "DeferredContext.h"
#include "RTV.h"
#include "Texture2D.h"
#include "ShaderObject.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "Vector\Vector4.h"

#include <string>
#include <memory>

namespace RougePP::Graphics {
	class GraphicsObjectContext
	{
	private:
		struct GraphicsObjectContextState;
		std::unique_ptr<GraphicsObjectContextState> d_ptr;
		GraphicsObjectContext();

	public:
		GRAPH_DllVisible GraphicsObjectContext(Context *ctxt);
		GRAPH_DllVisible GraphicsObjectContext(Context *ctxt, DeferredContext *dctxt);

		GRAPH_DllVisible ~GraphicsObjectContext();
		
		GRAPH_DllVisible Texture2D* LoadTexture2D(std::wstring file);
		GRAPH_DllVisible Texture2D* CreateTexture2D(int w, int h, int mips, Format fmt, Binding binding, Usage use, AccessType access);

		GRAPH_DllVisible RTV* CreateRTV(Texture2D *tex);
		GRAPH_DllVisible void ClearRTV(RTV *rtv, RougePP::Math::Vector4 col);

		GRAPH_DllVisible ShaderObject* CreateShader(std::wstring filename, ShaderObject::ShaderType sType, std::string fname);
		GRAPH_DllVisible void SetShader(ShaderObject *sObj);

		GRAPH_DllVisible Buffer* CreateBuffer(Usage usage, Binding binding, AccessType access, unsigned int size);
		GRAPH_DllVisible void* MapBuffer(Buffer *buf, MapType mapType, bool async);
		GRAPH_DllVisible void UnmapBuffer(Buffer *buf, void *ptr);
		GRAPH_DllVisible void SetVertexBuffer(unsigned int slot, Buffer * buf, unsigned int *offset, unsigned int *stride);

		GRAPH_DllVisible void CompileBufferLayout(BufferLayout *bufLayout, ShaderObject *vshader);
		GRAPH_DllVisible void SetBufferLayout(BufferLayout *bufLayout);

		GRAPH_DllVisible void SetRenderTargets(int num, RTV **rtvs);
		GRAPH_DllVisible void SetViewports(int num, RougePP::Math::Vector4 *vp);

		GRAPH_DllVisible void Draw(int count, int start);
	};
}
