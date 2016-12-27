#pragma once

#include "map/GMap.h"
#include "map/GQuadTree.h"
#include "GMapMgr.h"
#include "GInput.h"
#include "map/GTileMap.h"

#define G_DEFINE_MAP_DIR L"data/map/"
#define G_DEFINE_MAP_SHADER L"data/shader/CustomizeMap.hlsl"

class GMapMgr
{
public:
	GTileMap		m_HeightMap;


	bool			DrawQuadLine(GNode* pNode,GCamera* pCamera);
	bool			DrawDebug(GCamera* pCamera);

public:
	bool			CreateInit(int Width, int Height, float Distance, CString strTex,GCamera* pCamera);

	//--------------------------------------------------------------------------------------
	// Åø
	//--------------------------------------------------------------------------------------
	//GCreateMapDlg GCreateDlg;
	//GSaveMapDlg GSaveDlg;
	//--------------------------------------------------------------------------------------
	// ¸Ê
	//--------------------------------------------------------------------------------------
	//GMap	 m_CustomMap;
	TMapDesc m_MapDesc;
	//--------------------------------------------------------------------------------------
	// ÄõµåÆ®¸®
	//--------------------------------------------------------------------------------------
	GQuadTree m_QuadTree;

	//--------------------------------------------------------------------------------------
	// µð¹ö±ë ¿ëµµ
	//--------------------------------------------------------------------------------------
	GLineShape		m_DrawLine;
	bool			m_bDebugRender;
	int				m_iDrawDepth;



	bool			Init();
	bool			Frame(GInput* pInput = NULL);
	bool			Render(GCamera* pCamera);
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();



	GMapMgr();
	virtual ~GMapMgr();
};

