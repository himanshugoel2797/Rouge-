#pragma once

#include <memory>

namespace RougePP::Graphics {
	class Buffer
	{
	private:
		struct BufferState;
		std::unique_ptr<BufferState> d_ptr;
		Buffer();

	public:

		~Buffer();

		friend class GraphicsObjectContext;
	};
}
