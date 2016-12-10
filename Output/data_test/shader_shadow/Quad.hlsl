//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);
cbuffer cb0
{
	float4x4	g_matWorld	: packoffset(c0);
	float4x4	g_matView	: packoffset(c4);
	float4x4	g_matProj	: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.p = input.p;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	return float4(0.2f,0.2f,0.2f,0.5f);
}
