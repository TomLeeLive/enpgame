#pragma once
//#define G_MACRO_MAP_ADD		1
#define G_MACRO_MAP_2_ADD		2

#ifdef G_MACRO_MAP_ADD
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif
#endif

#ifdef G_MACRO_MAP_2_ADD
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d_2.lib" )
#else
#pragma comment( lib, "GMapCore32_2.lib" )
#endif
#endif

#include "GCoreLibV2.h"
//#include"GHeightMap.h"
#include "GQuadTree.h"
#include "GCamera.h"

#define NUM_OBJECTS 1000

class G_BoxObject :public GBaseObj
{
public:
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR4 m_vColor;
public:
	G_BoxObject();
};

class GProjMain : public GCoreLibV2
{
public:
	//GHeightMap		m_HeightMap;
	//GMap m_CustomMap;

	GQuadTree m_QuadTree;	
	D3DXMATRIX m_matWorld;

	GShape* m_pBoxShape;
	ID3D11DepthStencilState* m_pDepthStencilStateDepthEnable;
	GShape* m_pLine;
	int m_iDrawDepth;
	ComPtr<ID3D11PixelShader> m_pPixelShader;

	G_BoxObject* m_pObject;
	G_BOX m_GBoxBase;

public:
	shared_ptr<GCamera> m_pMainCamera;
	GLineShape m_LineDraw;

public:
	void DrawObject();
	void DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj);

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool DrawDebug();

	HRESULT CreateResource();
	HRESULT DeleteResource();
public:
	GProjMain();
	virtual ~GProjMain();
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언

