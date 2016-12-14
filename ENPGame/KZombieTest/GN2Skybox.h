#pragma once
#include "GShape.h"
#define MAX_SKYBOX_TEXTURE	6
class GN2Skybox : public GBoxShape
{
public:
	ComPtr<ID3D11ShaderResourceView>	m_pTexSRV[MAX_SKYBOX_TEXTURE];
	ComPtr<ID3D11PixelShader>			m_pPSTextrueIndex;
	ComPtr<ID3D11PixelShader>			m_pPSTextureArray;
	ComPtr<ID3D11PixelShader>			m_pPSCubeTexture;
	ComPtr<ID3D11Texture2D>				m_pSkyTexture;
	ComPtr<ID3D11ShaderResourceView>    m_pSkyTexRV;
	ComPtr<ID3D11ShaderResourceView>	m_pCubeTexSRV;
	int									m_iRenderType;
public:
	bool				Create(ID3D11Device* pDevice, TCHAR* pLoadShaderFile, TCHAR* pLoadTextureString = 0);
	bool				Render(ID3D11DeviceContext*    pContext);
	HRESULT				LoadTextures(ID3D11Device* pDevice, TCHAR* pLoadTextureString);
	HRESULT				LoadTextureArray(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*    pContext,
		TCHAR** szTextureNames,
		int iNumTextures,
		ID3D11Texture2D** ppTex2D,
		ID3D11ShaderResourceView** ppSRV);
	HRESULT				CreateTextureArray(ID3D11Device* pDevice, ID3D11DeviceContext*    pContext);
public:
	GN2Skybox();
	virtual ~GN2Skybox();
};

