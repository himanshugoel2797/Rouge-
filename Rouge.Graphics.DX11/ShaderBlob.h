#pragma once
#include <d3d11.h>
#include <string>
#include <memory>

class ShaderBlob
{
private:
	char* data;
	size_t len;
	ID3DBlob *blob;
public:
	ShaderBlob(std::wstring obj);
	ShaderBlob(ID3DBlob *blob);
	~ShaderBlob();
	void* GetBufferPointer(void);
	size_t GetBufferSize(void);
};

