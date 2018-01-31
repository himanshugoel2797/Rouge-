struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader(float4 position : POSITION)
{
	VOut output;

	output.position = position;
	output.color = float4(1.0f, 0.5f, 0.1f, 1.0f);

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}
