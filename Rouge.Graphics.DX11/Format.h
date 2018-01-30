#pragma once

namespace RougePP::Graphics {
	enum class Format {
		R32_G32_B32_A32_FLOAT = 2,
		R32_G32_B32_A32_UINT = 3,
		R32_G32_B32_A32_SINT = 4,
		
		R32_G32_B32_FLOAT = 6,
		R32_G32_B32_UINT = 7,
		R32_G32_B32_SINT = 8,

		R16_G16_B16_A16_FLOAT = 10,
		R16_G16_B16_A16_UNORM = 11,
		R16_G16_B16_A16_UINT = 12,
		R16_G16_B16_A16_SNORM = 13,
		R16_G16_B16_A16_SINT = 14,

		R32_G32_FLOAT = 16,
		R32_G32_UINT = 17,
		R32_G32_SINT = 18,

		R10_G10_B10_A2_UNORM = 24,
		R10_G10_B10_A2_UINT = 25,

		R11_G11_B10_FLOAT = 26,

		R8_G8_B8_A8_UNORM = 28,
		R8_G8_B8_A8_UNORM_SRGB = 29,
		R8_G8_B8_A8_UINT = 30,
		R8_G8_B8_A8_SNORM = 31,
		R8_G8_B8_A8_SINT = 32,

		R16_G16_FLOAT = 34,
		R16_G16_UNORM = 35,
		R16_G16_UINT = 36,
		R16_G16_SNORM = 37,
		R16_G16_SINT = 38,

		D32_FLOAT = 40,
		R32_FLOAT = 41,
		R32_UINT = 42,
		R32_SINT = 43,

		R8_G8_UNORM = 49,
		R8_G8_UINT = 50,
		R8_G8_SNORM = 51,
		R8_G8_SINT = 52,

		D16_UNORM = 55,

		BC1_UNORM = 71,
		BC1_UNORM_SRGB = 72,

		BC2_UNORM = 74,
		BC2_UNORM_SRGB = 75,

		BC3_UNORM = 77,
		BC3_UNORM_SRGB = 78,

		BC4_UNORM = 80,
		BC4_SNORM = 81,

		BC5_UNORM = 83,
		BC5_SNORM = 84,

		BC6H_UF16 = 95,
		BC6H_SF16 = 96,

		BC7_UNORM = 98,
		BC7_UNORM_SRGB = 99,
	};
}