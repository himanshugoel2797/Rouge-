#pragma once

#include "Common.h"

#include "Context.h"
#include "DeferredContext.h"
#include "RTV.h"
#include "Texture2D.h"
#include "Vector\Vector4.h"
#include "ShaderObject.h"

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
		
		GRAPH_DllVisible RTV* CreateRTV(Texture2D *tex);
		GRAPH_DllVisible void ClearRTV(RTV *rtv, RougePP::Math::Vector4 col);

		GRAPH_DllVisible ShaderObject* CreateShader(std::wstring filename, ShaderObject::ShaderType sType, std::string fname);
		GRAPH_DllVisible void SetShader(ShaderObject *sObj);

		GRAPH_DllVisible void SetRenderTargets(int num, RTV **rtvs);
		GRAPH_DllVisible void SetViewports(int num, RougePP::Math::Vector4 *vp);
	};
}
