#include "stdafx.h"
#include "BufferLayout.h"

#include "State\BufferLayoutState.h"

#include <memory>

using namespace RougePP::Graphics;

BufferLayout::BufferLayout() : d_ptr(new BufferLayoutState())
{
	d_ptr->inputLayout = NULL;
}

void BufferLayout::AddLayout(const char *semantic, unsigned int semantic_idx, Format fmt, unsigned int input_slot, unsigned int byte_off, InputType inputType, unsigned int step_rate) 
{
	d_ptr->layouts.push_back({
		semantic,
		semantic_idx,
		(DXGI_FORMAT)fmt,
		input_slot,
		byte_off,
		(D3D11_INPUT_CLASSIFICATION)inputType,
		step_rate
		});
}


BufferLayout::~BufferLayout()
{
	d_ptr->layouts.clear();

	if (d_ptr->inputLayout != NULL)
		d_ptr->inputLayout->Release();
}
