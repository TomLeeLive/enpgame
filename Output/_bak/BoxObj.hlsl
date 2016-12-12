//--------------------------------------------------------------------------------------
// 입출력 정점 구조
//--------------------------------------------------------------------------------------	
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t    : TEXCOORD0;
};

struct VS_INPUT
{
	float3 p	: POSITION;
	float4 c	: COLOR0;
	float2 t	: TEXCOORD0;
};

struct PNCT2_VS_INPUT
{
	float4 p		: POSITION;
	float3 n		: NORMAL;
	float4 c		: COLOR0;
	float2 t		: TEXCOORD0;
};
//--------------------------------------------------------------------------------------
// RasterizerState
//--------------------------------------------------------------------------------------
RasterizerState Wireframe
{
	CullMode = BACK;
	FillMode = WIREFRAME;
};

RasterizerState Solid
{
	CullMode = BACK;
	FillMode = SOLID;
};
SamplerState g_samWrap
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
SamplerComparisonState g_samComparison
{
	Filter = COMPARISON_MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
	ComparisonFunc = LESS;
};
SamplerState g_samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};
//--------------------------------------------------------------------------------------
// DepthStates
//--------------------------------------------------------------------------------------
DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS;
};
DepthStencilState DisableDepth
{
	DepthEnable = FALSE;
	DepthWriteMask = 0;
	DepthFunc = LESS;
};
RasterizerState FrontCullSolid
{
	CullMode = FRONT;
	FillMode = SOLID;
};
RasterizerState DisableCulling
{
	CullMode = NONE;
};
BlendState AlphaBlending
{
	AlphaToCoverageEnable = FALSE;
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ONE;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};
//--------------------------------------------------------------------------------------
// 전역 변수 선언
//--------------------------------------------------------------------------------------
matrix			g_matWorld;
matrix			g_matView;
matrix			g_matProj;
float4			g_vAmbientColor = { 1.0f, 1.0f, 1.0f, 1.0f };
//--------------------------------------------------------------------------------------
// 텍스쳐 선언
//--------------------------------------------------------------------------------------
Texture2D				g_txDiffuse		< string name = "../../data/wetsand.bmp"; >;
Texture2D				g_txR32FormatMap< string name = "../../data/sky_top32.dds"; >;

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT Box_VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(input.p, 1), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = input.c;
	output.t = input.t;
	return output;
}
VS_OUTPUT DebugBox_VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(input.p, 1), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = input.c;
	output.t = input.t;
	return output;
}
//--------------------------------------------------------------------------------------
// Sampling Fuction
//--------------------------------------------------------------------------------------
float4 GetLevelSampler(float2 tex)
{
	return g_txDiffuse.SampleLevel(g_samLinear, tex, 3);
}
float GetCmpSampler(float2 vPosition)
{
	//비교 통과하면 1을 반환하고, 그렇지 않으면 0을 반환합니다
	float fShadow = g_txR32FormatMap.SampleCmp(g_samComparison, vPosition, 0.2f);
	return fShadow;
}
//--------------------------------------------------------------------------------------
// 박스 Pixel Shader
//--------------------------------------------------------------------------------------
float4 Box_PS(VS_OUTPUT input) : SV_Target
{
	float4 fFinalColor = GetLevelSampler(input.t) * input.c * g_vAmbientColor;
	float fCmpValue = GetCmpSampler(input.t);
	return fFinalColor + (fFinalColor * fCmpValue);
}
technique11 BoxRender
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, Box_VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Box_PS()));

		SetRasterizerState(FrontCullSolid);
		SetBlendState(AlphaBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(EnableDepth, 0);
	}
	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, Box_VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Box_PS()));

		SetRasterizerState(Solid);
		SetBlendState(AlphaBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(EnableDepth, 0);
	}
}
technique11 DebugBoxRender
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, DebugBox_VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Box_PS()));

		SetRasterizerState(FrontCullSolid);
		SetBlendState(AlphaBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(EnableDepth, 0);
	}
	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, DebugBox_VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Box_PS()));

		SetRasterizerState(Solid);
		SetBlendState(AlphaBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(EnableDepth, 0);
	}
}