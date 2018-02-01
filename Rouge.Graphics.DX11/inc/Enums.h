#pragma once

enum class Usage {
	Default = 0,
	Immutable = 1,
	Dynamic = 2,
	Staging = 3,
};

enum class Binding {
	VertexBuffer = 1,
	IndexBuffer = 2,
	ConstantBuffer = 4,
	ShaderResource = 8,
	StreamOutput = 16,
	UnorderedAccess = 128,
};

enum class AccessType {
	Write = 0x10000L,
	Read = 0x20000L,
};

enum class MapType {
	Read = 1,
	Write = 2,
	ReadWrite = 3,
	WriteDiscard = 4,
	WriteNoOverwrite = 5
};