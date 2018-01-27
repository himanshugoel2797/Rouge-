#include "stdafx.h"
#include "Vector4.h"

using namespace RougePP::Math;

Vector4::Vector4()
{
}

RougePP::Math::Vector4::Vector4(float x, float y, float z, float w)
{
	Values[0] = x;
	Values[1] = y;
	Values[2] = z;
	Values[3] = w;
}


RougePP::Math::Vector4::Vector4(float a[len])
{
	for (int i = 0; i < len; i++)
		Values[i] = a[i];
}

Vector4::~Vector4()
{
}

void RougePP::Math::Vector4::ToFloatArray(float (&vals)[len])
{
	for (int i = 0; i < len; i++)
		vals[i] = Values[i];
}
