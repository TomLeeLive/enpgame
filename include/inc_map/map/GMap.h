#pragma once
#include "GShape.h"
using namespace DX;

#define RANDOM(n)	(rand()%(n))
#define RANDOMSCOPE(s,e)	(rand()%(e-s))+s;
#define RANDOMIZE() srand((unsigned)time(NULL))

struct GMapDesc
{
	int iNumCols;
	int iNumRows;
	float fSellDistance;
	float fScaleHeight;
	T_STR strTextureFile;
	T_STR strShaderFile;

};

class GMap : public GModel
{
public:
	GMapDesc m_MapDesc;
	vector<PNCT_VERTEX> m_VertexList;
	DWORD m_dwShaderIndex;
	int m_iNumVertices;
	int m_iNumFace;
	int m_iDiffuseTex;
	int m_iNumCols;
	int m_iNumRows;
	int m_iNumSellCols;
	int m_iNumSellRows;
	float m_fSellDistance;
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXMATRIX m_matNormal;
	D3DXVECTOR3 m_vLightDir;
	int* m_pNormalLookupTable;
	D3DXVECTOR3* m_pFaceNormals;
	bool m_bStaticLight;
public:
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	bool CreateVertexData();
	bool CreateIndexData();
	bool UpdateBuffer();
	HRESULT SetInputLayout();
public:
	DXGI_FORMAT MAKE_TYPELESS(DXGI_FORMAT format);
	DXGI_FORMAT MAKE_SRGB(DXGI_FORMAT format);
public:
	virtual bool ReLoadVBuffer();
	virtual bool ReLoadIBuffer();
	virtual void UpdateIndexBuffer(ID3D11DeviceContext* pContext, DWORD* pdwIndexArray, int iFaceCount);
	virtual void CalcVertexColor(D3DXVECTOR3 vLightDir);
	virtual bool CreateMap(GMapDesc& MapDesc);
	virtual bool Init(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmdiateConttext);
	virtual bool Load(GMapDesc& MapDesc);
	
	virtual void InitFaceNormals();
	virtual void CalcFaceNormals();
	virtual D3DXVECTOR3 ComputeFaceNormal(DWORD dwIndex0, DWORD dwIndex1, DWORD dwIndex2);

	virtual void GetNormalLookupTalbe();
	virtual void CalcPerVertexNormalsFastLookup();
	virtual float GetHeightmap(int row, int col);
	virtual float GetHeightOfVertex(UINT Index);
	virtual D3DXVECTOR3 GetNormalOfVertex(UINT Index);
	virtual D3DXVECTOR4 GetColorOfVertex(UINT Index);
	virtual D3DXVECTOR2 GetTextureOfVertex(float fOffsetX, float fOffsetY);
	virtual float GetHeight(float fPosX, float fPosZ);
	virtual float Lerp(float fStart, float fEnd, float fTangent);
public:
	GMap();
	virtual ~GMap();
};

