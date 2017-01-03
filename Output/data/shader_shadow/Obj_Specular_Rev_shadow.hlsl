#define SMAP_SIZE 1024
#define SHADOW_EPSILON 0.0007f

#define WIDEN(x) g_##x
#define HALF_VECTOR
//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
Texture2D g_txDepthMap: register (t1);

SamplerState g_samLinear: register (s0);
SamplerState g_samShadowMap: register (s1);
SamplerComparisonState g_samComShadowMap: register (s2);

cbuffer cb0: register(b0)
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
//Lighting Variables
//--------------------------------------------------------------------------------------
cbuffer cb1: register(b1)
{
	matrix				g_matWorldInverse: packoffset(c0);
	float4				g_cAmbientMaterial: packoffset(c4);
	float4				g_cDiffuseMaterial: packoffset(c5);
	float4				g_cSpecularMaterial: packoffset(c6);
	float4				g_cEmissionMaterial: packoffset(c7);

	float4				g_cAmbientLightColor : packoffset(c8);
	float4				g_cDiffuseLightColor: packoffset(c9);
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
cbuffer cb2: register (b2)
{
	float4x4		g_matShadow: packoffset(c0);
	float			g_iObjectID : packoffset(c4.x);
	float			g_iNumKernel : packoffset(c4.y);
}

//--------------------------------------------------------------------------------------
//struct PNCT_INPUT
//{
//	float3 p : POSITION;
//	float3 n : NORMAL;
//	float4 c : COLOR;
//	float2 t : TEXCOORD;
//};

struct VS_INPUT
{
	float4 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p			: SV_POSITION;
	float3 n			: NORMAL;
	float4 c			: COLOR0;
	float2 t			: TEXCOORD0;
	float4 v			: TEXCOORD1;
	float4 TexShadow	: TEXCOORD2;
};
struct PCT_VS_OUTPUT_SHADOW
{
	float4 p		: SV_POSITION;
	float2 d		: TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	float4 vWorld = mul(vIn.p, WIDEN(matWorld));
	vOut.p = mul(vWorld, WIDEN(matView));
	vOut.p = mul(vOut.p, WIDEN(matProj));
	vOut.n = normalize(mul(vIn.n, (float3x3)g_matWorldInverse));
	vOut.t = vIn.t;// *10;
	vOut.c = vIn.c * g_MeshColor;
	vOut.v = vWorld;
	// 텍스처좌표
	vOut.TexShadow = mul(vIn.p, g_matShadow);
	return vOut;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 Diffuse(float3 vNormal)
{
	float fIntensity = max(0, dot(vNormal, normalize(g_vLightDir)));
	float4 diffuse = g_cAmbientMaterial * g_cAmbientLightColor +
		(g_cDiffuseMaterial * g_cDiffuseLightColor * fIntensity);
	return diffuse;
}
float4 Specular(float3 vNormal)
{
	// Specular Lighting
	float  fPower = 0.0f;
#ifndef HALF_VECTOR
	float3 R = reflect(g_vLightDir, vNormal);
	fPower = pow(saturate(dot(R, -g_vEyeDir)), g_fIntensity);
#else
	float3 vHalf = normalize(-g_vLightDir + -g_vEyeDir);
	fPower = pow(saturate(dot(vNormal, vHalf)), g_fIntensity);
#endif
	float4 specular = g_cSpecularMaterial * g_cSpecularLightColor * fPower;
	return specular;
}
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	//	float4 vTexColor = g_txDiffuse.Sample(g_samLinear, vIn.t);
	//	float4 vFinalColor = vTexColor * (Diffuse(vIn.n) + Specular(vIn.n)) * vIn.c;
	//	vFinalColor.a = 1.0f;
	//	return vTexColor *(Diffuse(vIn.n) + Specular(vIn.n));

	float4 vDiffuseColor = g_txDiffuse.Sample(g_samLinear, vIn.t);
	float fLightAmount = 0.0f;
	float3 ShadowTexColor = vIn.TexShadow.xyz / vIn.TexShadow.w;

	const float fdelta = 1.0f / SMAP_SIZE;
	int iHalf = (g_iNumKernel - 1) / 2;
	for (int v = -iHalf; v <= iHalf; v++)
	{
		for (int u = -iHalf; u <= iHalf; u++)
		{
			float2 vOffset = float2(u*fdelta, v*fdelta);
			fLightAmount += g_txDepthMap.SampleCmpLevelZero(g_samComShadowMap,
				ShadowTexColor.xy + vOffset, ShadowTexColor.z).r;
		}
	}
	fLightAmount /= g_iNumKernel*g_iNumKernel;
	float fColor = fLightAmount;
	float4 vFinalColor = vDiffuseColor*(Diffuse(vIn.n) + Specular(vIn.n))*max(0.5f, fLightAmount);
	vFinalColor.a = 1.0f;
	return  vFinalColor;
}
float4 PS_Texture(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(g_samLinear, vIn.t);
}
float4 PS_Color(VS_OUTPUT vIn) : SV_Target
{
	float4 vColor = Specular(vIn.n);
	vColor.a = 1.0f;
	return vColor;
}
float4 Rim(VS_OUTPUT vIn)
{
	float fRimLightcolor = smoothstep(1.0f - vIn.v.w, 1.0f, 1.0f - max(0, dot(vIn.n, vIn.v.xyz)));
	float4 vFinalColor = float4(fRimLightcolor, fRimLightcolor, fRimLightcolor, 1.0f);
	return vFinalColor;
}
float Geom(VS_OUTPUT vIn)
{
	float3 vReflect = normalize(-g_vLightDir + -g_vEyeDir);
	float fDot = pow(saturate(dot(vIn.n, vReflect)), 1);

	float NdotL = saturate(dot(vIn.n, -g_vLightDir));
	float NdotH = saturate(dot(vIn.n, vReflect));
	float NdotV = saturate(dot(vIn.n, -g_vEyeDir));
	float VdotH = saturate(dot(-g_vEyeDir, vReflect));

	float Geom = min(min(2 * (NdotH*NdotV / VdotH), 2 * (NdotH*NdotL / VdotH)), 1.0f) / max(0.1f, NdotV);
	return Geom;
}

float4 PS_NO_CMP(VS_OUTPUT input) : SV_Target
{
	//const float	g_iNumKernel = 3;
	//float4 shadow  = g_txDepthMap.Sample( g_samShadowMap, input.TexShadow.xy / input.TexShadow.w ); 
	float4 FinalColor = g_txDiffuse.Sample(g_samLinear, input.t);

	float LightAmount = 0.0f;
	float4 vPosLight = input.TexShadow;

	for (int iLight = 0; iLight < 1; iLight++)
	{
		//transform from RT space to texture space.
		float2 ShadowTexC = vPosLight.xy / vPosLight.w;
		// ShadowTexC.y = 1.0f - ShadowTexC.y;
		// transform to texel space
		float2 texelpos = SMAP_SIZE * ShadowTexC;
		// Determine the lerp amounts           
		float2 lerps = frac(texelpos);
		//read in bilerp stamp, doing the shadow checks
		float sourcevals[4];
		sourcevals[0] = (g_txDepthMap.Sample(g_samShadowMap, ShadowTexC)
			+ SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
		sourcevals[1] = (g_txDepthMap.Sample(g_samShadowMap, ShadowTexC
			+ float2(1.0 / SMAP_SIZE, 0)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
		sourcevals[2] = (g_txDepthMap.Sample(g_samShadowMap, ShadowTexC
			+ float2(0, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
		sourcevals[3] = (g_txDepthMap.Sample(g_samShadowMap, ShadowTexC
			+ float2(1.0 / SMAP_SIZE, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
		// lerp between the shadow values to calculate our light amount
		LightAmount = lerp(lerp(sourcevals[0], sourcevals[1], lerps.x),
			lerp(sourcevals[2], sourcevals[3], lerps.x),
			lerps.y);
	}
	return  FinalColor * max(0.5f, LightAmount);
}
float4 AmbientColor(VS_OUTPUT input) : SV_Target
{
	return float4(g_iObjectID, g_iObjectID, g_iObjectID, 1.0f);
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PCT_VS_OUTPUT_SHADOW SHADOW_VS(VS_INPUT input)
{
	PCT_VS_OUTPUT_SHADOW output = (PCT_VS_OUTPUT_SHADOW)0;
	output.p = mul(input.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.d = output.p.zw;
	return output;
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 SHADOW_PS(PCT_VS_OUTPUT_SHADOW input) : SV_Target
{
	float shadow = input.d.x / input.d.y;
return  float4(shadow, shadow, shadow, 1.0f);
}