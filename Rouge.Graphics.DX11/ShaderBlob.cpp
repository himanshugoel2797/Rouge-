#include "stdafx.h"
#include "ShaderBlob.h"

#include <fstream>

ShaderBlob::ShaderBlob(std::wstring obj)
{
	this->blob = NULL;

	std::ifstream file;
	file.open(obj, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		auto size = file.tellg();

		this->data = new char[size];
		this->len = size;

		file.seekg(0, std::ios::beg);
		file.read(data, size);
		file.close();
	}
	else {
		//TODO: Error
	}
}

ShaderBlob::ShaderBlob(ID3DBlob *blob) {
	this->blob = blob;
	data = NULL;
	len = 0;
}

void* ShaderBlob::GetBufferPointer(void)
{
	if (this->blob != NULL)return this->blob->GetBufferPointer();
	return this->data;
}

size_t ShaderBlob::GetBufferSize(void) {
	if (this->blob != NULL)return this->blob->GetBufferSize();
	return this->len;
}

ShaderBlob::~ShaderBlob()
{
	if (this->blob != NULL) this->blob->Release();
	else
		delete[] this->data;
}
