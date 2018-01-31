#pragma once

#include "Common.h"

#include "Texture2D.h"
#include "Context.h"

#include <memory>

namespace RougePP::Graphics {
	class RTV
	{
	private:
		struct RTVState;
		std::unique_ptr<RTVState> d_ptr;
		RTV();

	public:
		GRAPH_DllVisible ~RTV();

		friend class GraphicsObjectContext;
	};
}

