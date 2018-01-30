#pragma once

#include "Common.h"
#include "Context.h"

#include <string>
#include <memory>

namespace RougePP::Graphics {
	class ShaderObject
	{
	private:
		struct ShaderObjectState;
		std::unique_ptr<ShaderObjectState> d_ptr;
		ShaderObject();

	public:
		enum class ShaderType {
			Vertex,
			Fragment,
			Domain,
			Hull,
			Geometry,
			Compute
		};
		
		GRAPH_DllVisible ~ShaderObject();
		GRAPH_DllVisible ShaderType Type();

		friend class GraphicsObjectContext;
	};
}
