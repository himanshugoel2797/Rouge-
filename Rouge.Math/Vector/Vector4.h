#pragma once
#include "../Common.h"

namespace RougePP::Math {
	class RMATH_DllVisible Vector4
	{
	private:
		static constexpr int len = 4;
	public:
		float Values[len];

		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(float a[len]);
		~Vector4();

		void ToFloatArray(float (&vals)[len]);
	};
}
