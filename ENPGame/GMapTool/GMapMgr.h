#pragma once

#include "GMapGroup.h"
#include "GInput.h"

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





public:


	//--------------------------------------------------------------------------------------
	// Åø
	//--------------------------------------------------------------------------------------
	//GCreateMapDlg GCreateDlg;
	//GSaveMapDlg GSaveDlg;




	bool			m_bDebugRender;




	bool			Init();
	bool			Frame(GInput* pInput = NULL,GCamera* pCamera = NULL);
	bool			Render(GCamera* pCamera);
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();



	GMapMgr();
	virtual ~GMapMgr();
};

