Texture2D g_txDiffuse: register (t0);
SamplerState g_samLinear: register (s0);
cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
struct PNCT2_VS_INPUT
{
    float3 p		: POSITION;
    float3 n		: NORMAL;
    float4 c	    : COLOR0;
    float2 t		: TEXCOORD0;
};
struct PCT_VS_OUTPUT
{
    float4 p		: SV_POSITION;
	float3 n		: NORMAL;
    float4 c		: COLOR0;
    float2 t		: TEXCOORD;
};

struct GSShadowIn
{
	float3 pos          : POS;
	float3 norm         : TEXTURE0;
};

struct PSShadowIn
{
	float4 pos			: SV_Position;
};

struct PSQuadIn
{
	float4 pos			: SV_Position;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PCT_VS_OUTPUT VS(PNCT2_VS_INPUT input)
{
    PCT_VS_OUTPUT output;	
    output.p = float4(input.p, 1.0f);
	output.p = mul(output.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
    output.n = input.n;    
	output.c = input.c;  
	output.t = input.t;  
    return output;
}
GSShadowIn VS_VolumeShadow(PNCT2_VS_INPUT input)
{
	GSShadowIn output = (GSShadowIn)0.0;

	//output our position in world space
	float4 pos = mul(float4(input.p, 1), g_matWorld);
	output.pos = pos.xyz;

	//world space normal
	output.norm = mul(input.n, (float3x3)g_matWorld);

	return output;
}

void DetectAndProcessSilhouette(float3 N,         // Un-normalized triangle normal
	GSShadowIn v1,    // Shared vertex
	GSShadowIn v2,    // Shared vertex
	GSShadowIn vAdj,  // Adjacent triangle vertex
	inout TriangleStream<PSShadowIn> ShadowTriangleStream // triangle stream
	)
{
	float		g_fExtrudeAmt = 1000.0f;
	float		g_fExtrudeBias = 0.0f;

	float3 NAdj = cross(v2.pos - vAdj.pos, v1.pos - vAdj.pos);

	float3 outpos[4];
	float3 extrude1 = normalize(v1.pos - g_MeshColor.xyz);
	float3 extrude2 = normalize(v2.pos - g_MeshColor.xyz);

	outpos[0] = v1.pos + g_fExtrudeBias*extrude1;
	outpos[1] = v1.pos + g_fExtrudeAmt*extrude1;
	outpos[2] = v2.pos + g_fExtrudeBias*extrude2;
	outpos[3] = v2.pos + g_fExtrudeAmt*extrude2;

	// Extrude silhouette to create two new triangles
	PSShadowIn Out;
	for (int v = 0; v<4; v++)
	{
		Out.pos = mul(float4(outpos[v], 1), g_matView);
		Out.pos = mul(Out.pos, g_matProj);
		ShadowTriangleStream.Append(Out);
	}
	ShadowTriangleStream.RestartStrip();
}
[maxvertexcount(18)]
void GS_VolumeShadow(triangleadj GSShadowIn In[6], inout TriangleStream<PSShadowIn> ShadowTriangleStream)
{
	float		g_fExtrudeAmt = 1000.0f;
	float		g_fExtrudeBias = 0.0f;
	// Compute un-normalized triangle normal
	float3 N = cross(In[2].pos - In[0].pos, In[4].pos - In[0].pos);

	// Compute direction from this triangle to the light
	float3 lightDir = g_MeshColor.xyz - In[0].pos;

	//if we're facing the light
	if (dot(N, lightDir) > 0.0f)
	{
		// For each edge of the triangle, determine if it is a silhouette edge
		DetectAndProcessSilhouette(lightDir, In[0], In[2], In[1], ShadowTriangleStream);
		DetectAndProcessSilhouette(lightDir, In[2], In[4], In[3], ShadowTriangleStream);
		DetectAndProcessSilhouette(lightDir, In[4], In[0], In[5], ShadowTriangleStream);

		//near cap
		PSShadowIn Out;
		for (int v = 0; v<6; v += 2)
		{
			float3 extrude = normalize(In[v].pos - g_MeshColor.xyz);

			float3 pos = In[v].pos + g_fExtrudeBias*extrude;
			Out.pos = mul(float4(pos, 1), g_matView);
			Out.pos = mul(Out.pos, g_matProj);

			ShadowTriangleStream.Append(Out);
		}
		ShadowTriangleStream.RestartStrip();

		//far cap (reverse the order)
		for (int t = 4; t >= 0; t -= 2)
		{
			float3 extrude = normalize(In[t].pos - g_MeshColor.xyz);

			float3 pos = In[t].pos + g_fExtrudeAmt*extrude;
			Out.pos = mul(float4(pos,1.0f), g_matView);
			Out.pos = mul(Out.pos, g_matProj);
			ShadowTriangleStream.Append(Out);
		}
		ShadowTriangleStream.RestartStrip();
	}
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PCT_VS_OUTPUT input) : SV_Target
{
	return g_txDiffuse.Sample(g_samLinear, input.t) * input.c;
}
float4 PS_VolumeShadow(PSShadowIn input) : SV_Target
{
	return float4(g_MeshColor.xyz, 0.1f);
}