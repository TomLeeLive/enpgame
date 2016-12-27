#include "stdafx.h"
//#include "_stdafx.h"
#include "GMapMgr.h"


bool GMapMgr::DrawDebug(GCamera* pCamera)
{
	//-----------------------------------------------------------------------
	// 적용되어 있는 카메라의 방향벡터 표시
	//-----------------------------------------------------------------------
	T_STR	str;
	RECT	rc;
	str.clear();
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Depth Control Key[F4] : Current Depth: %d %d\n"), m_iDrawDepth, g_InputData.iMouseValue[1]);
	str += pBuffer;

	//_stprintf_s(pBuffer, _T("Look:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vLookVector.x,
	//	m_pMainCamera->m_vLookVector.y,
	//	m_pMainCamera->m_vLookVector.z);
	//str += pBuffer;

	//memset(pBuffer, 0, sizeof(TCHAR) * 256);
	//_stprintf_s(pBuffer, _T("Up:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vUpVector.x,
	//	m_pMainCamera->m_vUpVector.y,
	//	m_pMainCamera->m_vUpVector.z);
	//str += pBuffer;

	//memset(pBuffer, 0, sizeof(TCHAR) * 256);
	//_stprintf_s(pBuffer, _T("Right:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vRightVector.x,
	//	m_pMainCamera->m_vRightVector.y,
	//	m_pMainCamera->m_vRightVector.z);
	//str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("p:%10.4f,%10.4f,%10.4f "), pCamera->m_vCameraPos.x,
		pCamera->m_vCameraPos.y,
		pCamera->m_vCameraPos.z);
	str += pBuffer;

	//rc.left = 0;
	//rc.top = 100;
	//rc.right = m_DefaultRT.m_vp.Width;
	//rc.bottom = m_DefaultRT.m_vp.Height;
	//DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	return true;
	//return GCoreLibV2::DrawDebug();
}

bool GMapMgr::DrawQuadLine(GNode* pNode, GCamera* pCamera)
{
	if (pNode == NULL) return true;

	if (m_QuadTree.m_iRenderDepth == pNode->m_iDepth ||
		(pNode->m_isLeaf &&  m_QuadTree.m_iRenderDepth < 0))
	{
		m_DrawLine.SetMatrix(pCamera->GetWorldMatrix(), pCamera->GetViewMatrix(), pCamera->GetProjMatrix());

		D3DXVECTOR4 vColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 1) vColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 2) vColor = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 3) vColor = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 4) vColor = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 5) vColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 6) vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 7) vColor = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 8) vColor = D3DXVECTOR4(1.0f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 9) vColor = D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f);

		D3DXVECTOR3 vPoint[8];
		vPoint[0] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[1] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[2] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMin.z);
		vPoint[3] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMin.z);
		vPoint[4] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[5] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[6] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMax.z);
		vPoint[7] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMax.z);

		m_DrawLine.Draw(g_pImmediateContext, vPoint[0], vPoint[1], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[1], vPoint[2], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[2], vPoint[3], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[3], vPoint[0], vColor);

		m_DrawLine.Draw(g_pImmediateContext, vPoint[4], vPoint[5], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[5], vPoint[6], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[6], vPoint[7], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[7], vPoint[0], vColor);

		m_DrawLine.Draw(g_pImmediateContext, vPoint[0], vPoint[4], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[1], vPoint[5], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[2], vPoint[6], vColor);
		m_DrawLine.Draw(g_pImmediateContext, vPoint[3], vPoint[7], vColor);
	}
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		DrawQuadLine(pNode->m_ChildList[iNode], pCamera);
	}
	return true;
}
bool			GMapMgr::Init()
{

	//--------------------------------------------------------------------------------------
	// 디버그 라인 생성
	//--------------------------------------------------------------------------------------
	if (FAILED(m_DrawLine.Create(g_pd3dDevice, L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_DrawLine 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}




	return true; 
}

bool GMapMgr::CreateInit(int Width, int Height, float Distance, CString strTex, GCamera* pCamera)
{
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
bool			GMapMgr::Frame(GInput* pInput)
{



	//--------------------------------------------------------------------------------------
	// add
	//--------------------------------------------------------------------------------------
	//2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;

	//--------------------------------------------------------------------------------------
	// QuadTree Frame
	//--------------------------------------------------------------------------------------
	if (m_MapDesc.iNumCols > 0 || m_MapDesc.iNumRows > 0)
	{
		//g_pImmediateContext->UpdateSubresource(
		//	m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

		//m_CustomMap.Frame();

		// 쿼드트리
		if (pInput != NULL &&  pInput->KeyCheck(DIK_F4) == KEY_UP)
		{
			if (++m_iDrawDepth > 7)	m_iDrawDepth = -1;
			m_QuadTree.SetRenderDepth(m_iDrawDepth);
		}
		m_QuadTree.Frame();


		m_HeightMap.Frame();
		g_pImmediateContext->UpdateSubresource(
			m_HeightMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_HeightMap.m_VertexList.at(0), 0, 0);
	}

	return true;
}

bool			GMapMgr::Render(GCamera* pCamera)
{
	//--------------------------------------------------------------------------------------
	//  QuadTree Render
	//--------------------------------------------------------------------------------------
	if (m_MapDesc.iNumCols > 0 || m_MapDesc.iNumRows > 0)
	{

		m_HeightMap.SetMatrix(pCamera->GetWorldMatrix(), pCamera->GetViewMatrix(), pCamera->GetProjMatrix());
		m_HeightMap.Render(g_pImmediateContext);

		//m_CustomMap.SetMatrix(pCamera->GetWorldMatrix(), pCamera->GetViewMatrix(),
		//	pCamera->GetProjMatrix());
		//m_CustomMap.Render(g_pImmediateContext);

		//DrawQuadLine(m_QuadTree.m_pRootNode);
	}

	return true;
}
bool			GMapMgr::Release()
{
	m_HeightMap.Release();
	//m_CustomMap.Release();
	m_QuadTree.Release();
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
	m_iDrawDepth = 0;
	m_bDebugRender = false;
}


GMapMgr::~GMapMgr()
{
}
