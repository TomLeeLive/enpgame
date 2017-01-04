#pragma once

#include "GCoreLibV2.h"
#include "GMapGroup.h"
#include "GInput.h"



#define MAP_OBJ_INFO_LINES 8
#define MAP_TEX_INFO_LINES 2

class GMapGroup;

class GObjData;

class GMapMgr
{
public:
	ID3D11RasterizerState*      m_pRS;

	TCHAR		m_strTex[MAX_PATH];
	TCHAR		m_strHeight[MAX_PATH];


	GObjData*	m_pObjSelected;
	int			m_iMapSelected;

	vector<shared_ptr<GMapGroup>>	m_vecMapGroup;

	//vector<GGbsObj*>	m_vecObj;

	//GTileMap		m_HeightMap;
	void	GetStringFileName(VOID* pOutStr, VOID* pInStr);
	void	GetStringFileNameWithPath(VOID* pOutStr, VOID* pInStr);
	bool	LoadMap(T_STR* strFile, GCamera* pCamera, GCoreLibV2* pMain = NULL);


public:


	//--------------------------------------------------------------------------------------
	// Åø
	//--------------------------------------------------------------------------------------
	//GCreateMapDlg GCreateDlg;
	//GSaveMapDlg GSaveDlg;




	bool			m_bDebugRender;




	bool			Init(GCoreLibV2* pMain);
	bool			Frame(GCamera* pCamera, GInput* pInput = NULL);
	bool			Render(GCamera* pCamera, bool bDebug, GCoreLibV2* pMain = NULL);
#ifdef G_DEFINE_SHADOW_ADD
	bool			RenderShadow(GCoreLibV2* pMain, D3DXMATRIX* matView, D3DXMATRIX* matProj, bool bDebug);
	bool			RenderObject(GCoreLibV2* pMain, GCamera* pCamera, bool bDebug);
#endif
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();



	GMapMgr();
	virtual ~GMapMgr();
};

