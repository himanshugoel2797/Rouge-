#pragma once
#include <d3d11.h>
#include <vector>
#include <string>

#include "Format.h"

struct RougePP::Graphics::BufferLayout::BufferUnitLayout {
	std::string semantic;
	unsigned int semantic_idx;
	Format fmt;
	unsigned int input_slot;
	unsigned int byte_offset;
	InputType inputType;
	unsigned int instance_step_rate;
};

struct RougePP::Graphics::BufferLayout::BufferLayoutState {
	std::vector<D3D11_INPUT_ELEMENT_DESC> layouts;
	ID3D11InputLayout *inputLayout;
};