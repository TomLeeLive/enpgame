#pragma once

#include "GMapGroup.h"
#include "GInput.h"

#define MAP_OBJ_INFO_LINES 8
#define MAP_TEX_INFO_LINES 2

class GMapGroup;

class GObjData;

class GMapMgr
{
public:
	TCHAR		m_strTex[MAX_PATH];
	TCHAR		m_strHeight[MAX_PATH];


	GObjData*	m_pObjSelected;
	int			m_iMapSelected;

	vector<shared_ptr<GMapGroup>>	m_vecMapGroup;

	//vector<GGbsObj*>	m_vecObj;

	//GTileMap		m_HeightMap;
	void	GetStringFileName(VOID* pOutStr, VOID* pInStr);
	void	GetStringFileNameWithPath(VOID* pOutStr, VOID* pInStr);
	bool	LoadMap(T_STR* strFile, GCamera* pCamera);


public:


	//--------------------------------------------------------------------------------------
	// Åø
	//--------------------------------------------------------------------------------------
	//GCreateMapDlg GCreateDlg;
	//GSaveMapDlg GSaveDlg;




	bool			m_bDebugRender;




	bool			Init();
	bool			Frame(GCamera* pCamera, GInput* pInput = NULL);
	bool			Render(GCamera* pCamera);
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();



	GMapMgr();
	virtual ~GMapMgr();
};

