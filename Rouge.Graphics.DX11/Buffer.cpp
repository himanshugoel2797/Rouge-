#include "stdafx.h"
#include "Buffer.h"

#include "State\BufferState.h"

using namespace RougePP::Graphics;

Buffer::Buffer() : d_ptr(new BufferState())
{
}


Buffer::~Buffer()
{
	d_ptr->buffer->Release();
}
