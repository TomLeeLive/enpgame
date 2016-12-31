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
		//Distance, 0.1f,
		20.0f, 1.0f,
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


	//if (m_vecMapGroup.size() == 0)
	//	return false;
	if (m_iMapSelected == -1)
		return false;
	
	//for(int i = 0; i < m_vecMapGroup.size(); i++)
	m_vecMapGroup[m_iMapSelected]->Frame(pInput, pCamera);


	if (m_pObjSelected !=NULL)
	{
		D3DXMATRIX matScl, matRot;
		D3DXMatrixIdentity(&matScl);
		D3DXMatrixIdentity(&matRot);

		if (I_Input.KeyCheck(DIK_Y) == KEY_PUSH)
		{
			m_pObjSelected->m_iScl += 1;
		}
		if (I_Input.KeyCheck(DIK_U) == KEY_PUSH)
		{
			m_pObjSelected->m_iScl -= 1;

			if (m_pObjSelected->m_iScl < 1)
				m_pObjSelected->m_iScl = 1;
		}
		if (I_Input.KeyCheck(DIK_H) == KEY_PUSH)
		{
			m_pObjSelected->m_fRotY += 5;
		}
		if (I_Input.KeyCheck(DIK_J) == KEY_PUSH)
		{
			m_pObjSelected->m_fRotY -= 5;
		}
		if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._43 += 200 * g_fSecPerFrame;
		}
		if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._43 += -200 * g_fSecPerFrame;
		}
		if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._41 += -200 * g_fSecPerFrame;
		}
		if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._41 += 200 * g_fSecPerFrame;
		}
		D3DXMatrixScaling(&matScl, m_pObjSelected->m_iScl, m_pObjSelected->m_iScl, m_pObjSelected->m_iScl);
		D3DXMatrixRotationY(&matRot, D3DXToRadian(m_pObjSelected->m_fRotY));

		m_pObjSelected->m_matObjWld = matScl * matRot * m_pObjSelected->m_matObjTrans;
	}
	return true;
}

bool			GMapMgr::Render(GCamera* pCamera)
{

	//if (m_vecMapGroup.size() == 0)
	//	return false;

	if (m_iMapSelected == -1)
		return false;

	//for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[m_iMapSelected]->Render(pCamera);

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
	m_iMapSelected = -1;
	m_pObjSelected = NULL;
	m_bDebugRender = false;
}


GMapMgr::~GMapMgr()
{
}
