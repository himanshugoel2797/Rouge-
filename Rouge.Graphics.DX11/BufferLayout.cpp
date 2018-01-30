#include "stdafx.h"
#include "BufferLayout.h"

#include "State\BufferLayoutState.h"

#include <memory>

using namespace RougePP::Graphics;

BufferLayout::BufferLayout() : d_ptr(new BufferLayoutState())
{
	d_ptr->inputLayout = NULL;
}

void BufferLayout::AddLayout(std::string semantic, unsigned int semantic_idx, Format fmt, unsigned int input_slot, unsigned int byte_off, InputType inputType, unsigned int step_rate) 
{
	D3D11_INPUT_ELEMENT_DESC layout;
	memset(&layout, 0, sizeof(layout));

	layout.SemanticName = semantic.c_str();
	layout.SemanticIndex = semantic_idx;
	layout.Format = (DXGI_FORMAT)fmt;
	layout.InputSlot = input_slot;
	layout.AlignedByteOffset = byte_off;
	layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)inputType;
	layout.InstanceDataStepRate = step_rate;

	d_ptr->layouts.push_back(layout);
}


BufferLayout::~BufferLayout()
{
	d_ptr->layouts.clear();

	if (d_ptr->inputLayout != NULL)
		d_ptr->inputLayout->Release();
}
