#pragma once
#include "Common.h"
#include "Context.h"

#include <memory>

namespace RougePP::Graphics {
	class Texture2D
	{
	private:
		struct Texture2DState;
		std::unique_ptr<Texture2DState> d_ptr;
		Texture2D();

	public:
		GRAPH_DllVisible static Texture2D* BackBuffer(Context *ctxt);
		GRAPH_DllVisible ~Texture2D();

		friend class GraphicsObjectContext;
	};
}
