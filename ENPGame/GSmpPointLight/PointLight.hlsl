#define WIDEN(x) g_##x
#define g_iNumLight  3
//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState g_samLinear: register (s0);
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
	float4				g_cAmbientMaterial[g_iNumLight];
	float4				g_cDiffuseMaterial[g_iNumLight];
	float4				g_cSpecularMaterial[g_iNumLight];
	float4				g_cEmissionMaterial[g_iNumLight];

	float4				g_cAmbientLightColor[g_iNumLight];
	float4				g_cDiffuseLightColor[g_iNumLight];
	float4				g_cSpecularLightColor[g_iNumLight];
};
//--------------------------------------------------------------------------------------
//Lighting Variables
//--------------------------------------------------------------------------------------
cbuffer cb2: register(b2)
{
	matrix				g_matWorldInverse[g_iNumLight];
	float4				g_vLightDir[g_iNumLight];	
	float4				g_vLightPos[g_iNumLight];	
	float4				g_vEyeDir[g_iNumLight];	
	float4				g_vEyePos[g_iNumLight];	
};
//--------------------------------------------------------------------------------------
//Lighting Variables
//--------------------------------------------------------------------------------------
cbuffer cb3: register(b3)
{	
	float4		g_vSpotInfo[g_iNumLight];
	//float		g_fTheta[g_iNumLight] : packoffset(c0.x);		// 내부 콘의 각도 범위	
	//float		g_fPhi[g_iNumLight] : packoffset(c0.y);			// 외부 콘의 각도 범위
	//float		g_fFalloff[g_iNumLight] : packoffset(c0.z);		// 내부 콘과 외부 콘의 휘도( Luminance )	
	//float     g_nNumLights[g_iNumLight] : packoffset(c0.w);	// 거리
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
	float4 v : TEXCOORD1;
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
	//vOut.n = normalize(mul(vIn.n, (float3x3)g_matWorldInverse));
	vOut.n = vIn.n;
	vOut.t = vIn.t;
	vOut.c = vIn.c * g_MeshColor;
	vOut.v = vWorld;
	return vOut;
}
float4 ComputePointLight( float3 vVertexPos, float3 vVertexNormal, int nNumLights )
{
	float4 vPointLightColor= float4(0,0,0,1);
	for( int iLight = 0; iLight < nNumLights; iLight++ )
	{		
		float4 vLight;
		vLight.xyz	= normalize( vVertexPos - g_vLightPos[iLight].xyz );
		vLight.w	= distance( vVertexPos, g_vLightPos[iLight].xyz );
		
		float fLuminance = smoothstep( vLight.w-5,  vLight.w, g_vLightPos[iLight].w);
		float fIntensity = saturate( dot( vVertexNormal, -vLight.xyz ) );
		vPointLightColor += float4(g_cDiffuseLightColor[iLight].rgb *  fLuminance , 1.0f);
	}			
	return vPointLightColor;
}

float4 ComputeSpotLight(float3 vVertexPos,	float3 vVertexNormal,	int nNumLights)
{	
	float4 vSpotLightColor = float4(0, 0, 0, 1);
	for (int iLight = 0; iLight < nNumLights; iLight++)
	{		
		float fInner = g_vSpotInfo[iLight].x;
		float fOutner = g_vSpotInfo[iLight].y;
		float fFalloff = g_vSpotInfo[iLight].z;
		float fRange = g_vSpotInfo[iLight].w;
		float4 vLight;
		vLight.xyz = normalize(vVertexPos - g_vLightPos[iLight].xyz);
		vLight.w = distance(vVertexPos, g_vLightPos[iLight].xyz);
		float fDot = dot(vLight.xyz, g_vLightDir[iLight].xyz);
		float fPhi = fInner - fOutner;

		float3 vNormal = normalize(mul(vVertexNormal, (float3x3)g_matWorldInverse[iLight]));
		// 거리에 따라 블랜딩
		float fIntensity = saturate(dot(vVertexNormal, -vLight.xyz));
		// 원 거리의 블랜딩
		float fLuminance = smoothstep(vLight.w - fFalloff, vLight.w, fRange);
		//내부콘
		if (fDot > fInner)
		{			
			vSpotLightColor += float4(g_cDiffuseLightColor[iLight].rgb* fLuminance/**fIntensity*/, 1.0f);
		}
		//외부콘
		else if (fDot > fOutner)
		{
			// 내부에서 외부 각의 블랜닝
			float fLuminanceB = 1.0f - (fInner - fDot) / fPhi;
			fLuminance = min(fLuminance, fLuminanceB);
			vSpotLightColor +=  float4(g_cDiffuseLightColor[iLight].rgb * fLuminance/**fIntensity*/, 1.0f);
		}
	}
	return vSpotLightColor;
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	float4 vTexColor = g_txDiffuse.Sample(g_samLinear, vIn.t);
	float4 vFinalColor = ComputePointLight(vIn.v, vIn.n, g_iNumLight) *vTexColor;
	return vFinalColor;
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_Texture(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(g_samLinear, vIn.t);
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS_Color(VS_OUTPUT vIn) : SV_Target
{
	float4 vFinalColor = ComputePointLight(vIn.v, vIn.n, g_iNumLight);
	return vFinalColor;
}
