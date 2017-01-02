#pragma once

#include "map/GMap.h"
#include "map/GQuadTree.h"
#include "GMapMgr.h"
#include "GInput.h"
#include "map/GTileMap.h"
#include "GModel.h"
#include "GGbsObj.h"
#include "GObjMgr.h"

#define G_SHA_OBJ_DIFFUSE L"data/shader/Obj_Diffuse.hlsl"
#define G_SHA_OBJ_DIFFUSE_REVERSE L"data/shader/Obj_Diffuse_Rev.hlsl"

#define G_DEFINE_MAP_DIR L"data/map/"
#define G_DEFINE_MAP_SHADER L"data/shader/CustomizeMap_light.hlsl"

class GObjData {
public:
	TCHAR			m_strName[MAX_PATH];
	GGbsObj*		m_pObj;
	D3DXMATRIX		m_matObjWld;
	//D3DXMATRIX	m_matObjScl;
	//D3DXMATRIX	m_matObjRot;
	D3DXMATRIX		m_matObjTrans;
	int				m_iScl;
	float			m_fRotY;
	bool			m_bLightReverse;
	bool			m_bLightSpecular;

	GObjData() {
		m_bLightReverse = true;
		m_bLightSpecular = false;
		D3DXMatrixIdentity(&m_matObjWld);
		D3DXMatrixIdentity(&m_matObjTrans);
		m_iScl = 1;
		m_fRotY = 0.0f;
	};
	~GObjData() {};
};

class GMapGroup {
public:
	TCHAR			m_strTex[MAX_PATH];
	TCHAR			m_strHeight[MAX_PATH];


	int				m_iDrawDepth;
	//--------------------------------------------------------------------------------------
	// µð¹ö±ë ¿ëµµ
	//--------------------------------------------------------------------------------------
	GLineShape		m_DrawLine;
	//--------------------------------------------------------------------------------------
	// ¸Ê
	//--------------------------------------------------------------------------------------
	//GMap	 m_CustomMap;
	TMapDesc m_MapDesc;
	//--------------------------------------------------------------------------------------
	// ÄõµåÆ®¸®
	//--------------------------------------------------------------------------------------
	GQuadTree m_QuadTree;

	GTileMap		m_HeightMap;
	vector<shared_ptr<GObjData>>	m_vecObj;

	bool			DrawQuadLine(GNode* pNode, GCamera* pCamera);
	bool			DrawDebug(GCamera* pCamera);
	bool			CreateInit(int Width, int Height, float Distance, CString strTex, GCamera* pCamera);


	bool			Init();
	bool			Frame(GCamera* pCamera, GInput* pInput = NULL);
	bool			Render(GCamera* pCamera);
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();

	GMapGroup() {
		m_iDrawDepth = 0;
	};
	~GMapGroup() {};
};
