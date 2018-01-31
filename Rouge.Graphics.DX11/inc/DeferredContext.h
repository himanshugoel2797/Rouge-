#pragma once
#include <memory>

#include "Context.h"

namespace RougePP::Graphics {
	class DeferredContext
	{
	private:
		struct DeferredContextState;
		std::unique_ptr<DeferredContextState> d_ptr;
	public:
		GRAPH_DllVisible DeferredContext(Context *ctxt);
		GRAPH_DllVisible ~DeferredContext();

		friend class GraphicsObjectContext;
	};
}