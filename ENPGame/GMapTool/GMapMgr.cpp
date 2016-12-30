#include "stdafx.h"
//#include "_stdafx.h"
#include "GMapMgr.h"


bool			GMapMgr::Init()
{





	return true; 
}

bool GMapGroup::CreateInit(int Width, int Height, float Distance, CString strTex, GCamera* pCamera)
{
	Init();

	//--------------------------------------------------------------------------------------
	//  맵 생성
	//--------------------------------------------------------------------------------------

	wchar_t szCharPath[MAX_PATH] = G_DEFINE_MAP_DIR;
	wchar_t szChar[MAX_PATH];
	//CString strString;
	//strString = "test";
	_tcscpy_s(szChar, 16, strTex.GetBuffer());
	_tcscat_s(szCharPath, szChar);
	//theApp.m_MapDesc.strTextureFile = m_strCharName;

	//m_MapDesc = { Width, Height, Distance, 0.1f,L"data/sand.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,		
		Distance, 0.1f,
		szCharPath, 
		G_DEFINE_MAP_SHADER };

	if (!m_HeightMap.Load(m_MapDesc))
	{
		return false;
	}
	//m_CustomMap.Init(g_pd3dDevice, g_pImmediateContext);
	//if (FAILED(m_CustomMap.Load(m_MapDesc))) { return false; }
	//--------------------------------------------------------------------------------------
	//  쿼드 트리
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(m_MapDesc.iNumCols, m_MapDesc.iNumRows);
	m_QuadTree.Update(g_pd3dDevice, pCamera);


}
bool			GMapMgr::Frame(GInput* pInput, GCamera* pCamera)
{



	//--------------------------------------------------------------------------------------
	// add
	//--------------------------------------------------------------------------------------
	//2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;


	if (m_vecMapGroup.size() == 0)
		return false;

	
	for(int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[i]->Frame(pInput, pCamera);

	return true;
}

bool			GMapMgr::Render(GCamera* pCamera)
{

	if (m_vecMapGroup.size() == 0)
		return false;

	for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[i]->Render(pCamera);

	return true;
}
bool			GMapMgr::Release()
{
	for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[i]->Release();
	return true;
}
HRESULT			GMapMgr::CreateResource()
{


	return S_OK;
}
HRESULT			GMapMgr::DeleteResource()
{
	return S_OK;
}


GMapMgr::GMapMgr()
{
	m_pObjSelected = NULL;
	m_bDebugRender = false;
}


GMapMgr::~GMapMgr()
{
}
