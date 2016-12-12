#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::DrawDebug() {
	/*
	if (I_Input.KeyCheck(DIK_N))
	{
		// 정점노말 표시
		m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		D3DXMATRIX invWorld;
		D3DXMatrixIdentity(&invWorld);
		D3DXMatrixInverse(&invWorld, 0, m_pMainCamera->GetWorldMatrix());
		D3DXMatrixTranspose(&invWorld, &invWorld);
		D3DXVECTOR3 vStart, vEnd, vDir, vEye;
		vEye = *m_pMainCamera->GetLookVector();

		for (int i = 0; i < m_stModel.m_vGeomObj.size(); i++) {
			for (int j = 0; j < m_stModel.m_vGeomObj[i]->m_vObj.size(); j++) {
				for (int k = 0; k < m_stModel.m_vGeomObj[i]->m_vObj[j]->m_vPnctVertex.size(); k++) {
					
					
					D3DXVec3TransformCoord(&vStart, &m_stModel.m_vGeomObj[i]->m_vObj[j]->m_vPnctVertex[k].p, m_pMainCamera->GetWorldMatrix());
					D3DXVec3TransformNormal(&vDir, &m_stModel.m_vGeomObj[i]->m_vObj[j]->m_vPnctVertex[k].n, &invWorld);
					D3DXVec3Normalize(&vDir, &vDir);
					vEnd = vStart + vDir * 2.0f;
					float fDot = D3DXVec3Dot(&vEye, &vDir);
					if (fDot < 0)
					{
						vDir.x = vDir.x * 0.5f + 0.5f;
						vDir.y = vDir.y * 0.5f + 0.5f;
						vDir.z = vDir.z * 0.5f + 0.5f;
						m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(vDir.x, vDir.y, vDir.z, 1.0f));
					}

				}
			}
		}
	}
	*/
	if (!GCoreLibV2::DrawDebug()) return false;
	return true;
}
bool GProjMain::Init()
{
	// 메인 카메라 뷰 행렬 세팅
	SAFE_NEW(m_pMainCamera, GCamera);
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);


	D3DXMatrixIdentity(&m_matObjWld);
	D3DXMatrixIdentity(&m_matObjScl);
	D3DXMatrixIdentity(&m_matObjRot);
	D3DXMatrixIdentity(&m_matObjTrans);
	D3DXMatrixIdentity(&m_matObjOBB);

	int iIndex = -1;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_DROPSHIP_LAND, G_SHA_OBJ_DIFFUSE);				if (iIndex < 0) return false;

	//연구소 로드
	m_Obj = I_ObjMgr.GetPtr(G_OBJ_NAME_DROPSHIP_LAND);
	D3DXMatrixScaling(&m_matObjScl, 2, 2, 2);
	D3DXMatrixTranslation(&m_matObjTrans, 0.0f, 0.0f, 0.0f);
	m_matObjWld = m_matObjScl * m_matObjRot * m_matObjTrans;

	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj)->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	return true;
}

bool GProjMain::Render()
{	
	m_Obj->SetMatrix(&m_matObjWld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_Obj->Render(g_pImmediateContext);
	return true;
}
bool GProjMain::Release()
{
	SAFE_DEL(m_pMainCamera);

	I_ObjMgr.Release();


	return true;
}

bool GProjMain::Frame()
{	
	//--------------------------------------------------------------------------------------
	// 엔진에 있는 뷰 및 투영 행렬 갱신
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	m_Obj->SetMatrix(&m_matObjWld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_Obj->Frame();

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	if (m_pMainCamera)
	{
		// Setup the camera's projection parameters
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetWindow(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	}

	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;

	return S_OK;
}
GProjMain::GProjMain(void)
{

}

GProjMain::~GProjMain(void)
{

}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}
GCORE_RUN(ENP Test);



