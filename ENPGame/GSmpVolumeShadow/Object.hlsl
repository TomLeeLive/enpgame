//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);
cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//cbuffer cb1
//{
//	float4		g_vLightVector;
//	float4		g_vLightPosition;
//	float4		g_vEye;
//	float4		g_vEyeDir;
//};
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

struct GS_INPUT_VolumeShadow
{
	float3 p         : POS;
	float3 n         : TEXTURE0;
};
struct PS_INPUT_VolumeShadow
{
	float4 p : SV_POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.n = vIn.n;
	output.t = vIn.t;
	output.c = vIn.c *g_MeshColor;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(samLinear, vIn.t) * vIn.c;
}

GS_INPUT_VolumeShadow VS_VolumeShadow(VS_INPUT input)
{
	GS_INPUT_VolumeShadow output;
	output.p = mul(float4(input.p, 1), g_matWorld);
	output.p = output.p.xyz;
	output.n = mul(input.n, (float3x3)g_matWorld);
	return output;
}
void GenShadowVolume(GS_INPUT_VolumeShadow v1, GS_INPUT_VolumeShadow v2, inout TriangleStream<PS_INPUT_VolumeShadow> ShadowTriangleStream)
{
	const float		g_fExtrudeAmt = 100.0f;
	const float		g_fExtrudeBias = 0.0f;
	float3 outpos[4];
	float3 extrude1 = normalize(v1.p - g_MeshColor.xyz);
	float3 extrude2 = normalize(v2.p - g_MeshColor.xyz);

	outpos[0] = v1.p + g_fExtrudeBias*extrude1;
	outpos[1] = v1.p + g_fExtrudeAmt*extrude1;
	outpos[2] = v2.p + g_fExtrudeBias*extrude2;
	outpos[3] = v2.p + g_fExtrudeAmt*extrude2;

	PS_INPUT_VolumeShadow output;
	for (int v = 0; v<4; v++)
	{
		output.p = mul(mul(float4(outpos[v], 1), g_matView), g_matProj);
		ShadowTriangleStream.Append(output);
	}
	ShadowTriangleStream.RestartStrip();
}

[maxvertexcount(12)]
void GS_VolumeShadow(triangle GS_INPUT_VolumeShadow In[3],
	inout TriangleStream<PS_INPUT_VolumeShadow> ShadowTriangleStream)
{
	float3 vFaceNormal = cross(In[1].p - In[0].p, In[2].p - In[0].p);
	float3 vLightDir = g_MeshColor.xyz - In[0].p;

	if (dot(vFaceNormal, vLightDir) >= 0.0f)
	{
		GenShadowVolume(In[0], In[1], ShadowTriangleStream);
		GenShadowVolume(In[1], In[2], ShadowTriangleStream);
		GenShadowVolume(In[2], In[0], ShadowTriangleStream);
	}
}

float4 PS_VolumeShadow() : SV_TARGET
{
	return float4(1,0,0,1);
}
