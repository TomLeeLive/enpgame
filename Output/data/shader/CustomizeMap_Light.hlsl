//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);
cbuffer cb0
{
	row_major float4x4	g_matWorld	: packoffset(c0);
	row_major float4x4	g_matView		: packoffset(c4);
	row_major float4x4	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
//Lighting Variables
//--------------------------------------------------------------------------------------
cbuffer cb1: register(b1)
{
	matrix				g_matWorldInverse: packoffset(c0);
	float4				g_AmbientMaterial: packoffset(c4);
	float4				g_DiffuseMaterial: packoffset(c5);
	float4				g_cSpecularMaterial: packoffset(c6);
	float4				g_cEmissionMaterial: packoffset(c7);

	float4				g_AmbientLightColor : packoffset(c8);
	float4				g_DiffuseLightColor: packoffset(c9);
	float4				g_cSpecularLightColor: packoffset(c10);
	float3				g_vLightDir : packoffset(c11);
	float			    g_fDamping : packoffset(c11.w);
	float3				g_vLightPos : packoffset(c12);
	float			    g_fRadius : packoffset(c12.w);
	float3				g_vEyeDir : packoffset(c13);
	float			    g_fIntensity : packoffset(c13.w);
	float3				g_vEyePos : packoffset(c14);
	float			    g_fEyeRadius : packoffset(c14.w);
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
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float4 d : TEXCOORD1;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(g_matWorld, vIn.p);
	output.p = mul(g_matView,output.p );
	output.p = mul(g_matProj,output.p );
	output.n = normalize(mul(vIn.n, (float3x3)g_matWorldInverse));
	output.c = vIn.c * g_MeshColor;//vIn.c;// *g_MeshColor;
	output.t = vIn.t;// *10;
	//output.n = vIn.n;
	//output.t = vIn.t;
	//output.c = vIn.c * g_MeshColor;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 Diffuse(float3 vNormal)
{
	float Attenuation = 0.5f;
	float fIntensity = max(0, dot(vNormal, normalize(-g_vLightDir)));
	float4 diffuse = g_AmbientMaterial * g_AmbientLightColor +
		(g_DiffuseMaterial * g_DiffuseLightColor * fIntensity)*Attenuation;
	return diffuse;
}


float4 PS(VS_OUTPUT vIn) : SV_Target
{
	//return g_txDiffuse.Sample(samLinear, vIn.t) * vIn.c;
	float4 vTexColor = g_txDiffuse.Sample(samLinear, vIn.t);
	float4 vFinalColor = vTexColor *Diffuse(vIn.n) * vIn.c;
	vFinalColor.a = 1.0f;
	return vFinalColor;
}
float4 PS_Color(VS_OUTPUT vIn) : SV_Target
{
	return vIn.c;
}
