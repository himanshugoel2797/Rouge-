#pragma once

#include "Common.h"
#include "Format.h"

#include <memory>
#include <string>

namespace RougePP::Graphics {
	class BufferLayout
	{
	private:
		struct BufferLayoutState;
		struct BufferUnitLayout;
		std::unique_ptr<BufferLayoutState> d_ptr;
	public:
		enum class InputType {
			PerVertex = 0,
			PerInstance = 1,
		};

		static constexpr auto NORMAL = "NORMAL";
		static constexpr auto POSITION = "POSITION";
		static constexpr auto PSIZE = "PSIZE";
		static constexpr auto TEXCOORD = "TEXCOORD";

		GRAPH_DllVisible BufferLayout();
		GRAPH_DllVisible ~BufferLayout();
		GRAPH_DllVisible void AddLayout(const std::string &semantic, unsigned int semantic_idx, Format fmt, unsigned int input_slot, unsigned int byte_off, InputType inputType, unsigned int step_rate);

		friend class GraphicsObjectContext;
	};
}

