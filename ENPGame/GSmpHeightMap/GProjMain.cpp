#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	HRESULT hr;
	//카메라 생성
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 100.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 10.0f, -50.1f);
	// 메인 카메라 뷰 행렬 세팅
	m_pMainCamera->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);

	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		0.1f, 10000.0f);

	//G_MACRO_MAP_ADD
	//HeightMap
	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	if (FAILED(m_HeightMap.CreateHeightMap(L"data/HeightTest.bmp")))
	{
		return false;
	}

	m_HeightMap.m_bStaticLight = true;
	TMapDesc MapDesc = 
	{
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		20.0f, 1.0f,
		L"data/Sand.jpg",
		L"data/shader/CustomizeMap.hlsl" 
	};

	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}	
	//--------------------------------------------------------------------------------------
	// 오브젝트 Init()
	//--------------------------------------------------------------------------------------
	//m_Objbit.reset();
	//for (int i = 0; i < NUM_OBJECTS; i++)
	//{
	//	m_Objbit.set(i);
	//}	
	for (int i = 0; i < G_OBJ_CNT; i++) {
		D3DXMatrixIdentity(&m_matObjWld[i]);
		D3DXMatrixIdentity(&m_matObjScl[i]);
		D3DXMatrixIdentity(&m_matObjRot[i]);
		D3DXMatrixIdentity(&m_matObjTrans[i]);
		D3DXMatrixIdentity(&m_matObjOBB[i]);
	}

	int iIndex = -1;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_LAB, G_SHA_BOX);				if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_DROPSHIP_LAND, G_SHA_BOX);	if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_CAR, G_SHA_BOX);				if (iIndex < 0) return false;

	//연구소 로드
	m_Obj[G_OBJ_LAB] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB], 2, 2, 2);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB], 1000.0f, 0.0f, 1000.0f);
	m_matObjWld[G_OBJ_LAB] = m_matObjScl[G_OBJ_LAB] * m_matObjRot[G_OBJ_LAB] * m_matObjTrans[G_OBJ_LAB];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	//드롭십 로드
	m_Obj[G_OBJ_DROPSHIP] = I_ObjMgr.GetPtr(G_OBJ_NAME_DROPSHIP_LAND);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_DROPSHIP], 2.f, 2.f, 2.f);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_DROPSHIP], D3DXToRadian(45.0f + 180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_DROPSHIP], -1000.0f, 0.0f, -1000.0f);
	m_matObjWld[G_OBJ_DROPSHIP] = m_matObjScl[G_OBJ_DROPSHIP] * m_matObjRot[G_OBJ_DROPSHIP] * m_matObjTrans[G_OBJ_DROPSHIP];
	//드롭십 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_DROPSHIP])->m_OBB.Init(D3DXVECTOR3(-42.0f, 0.0f, -75.0f), D3DXVECTOR3(42.0f, 60.0f, 115.0f));

	//차량1 로드
	m_Obj[G_OBJ_CAR1] = I_ObjMgr.GetPtr(G_OBJ_NAME_CAR);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR1], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR1], 500.0f, 0.0f, -700.0f);
	m_matObjWld[G_OBJ_CAR1] = m_matObjScl[G_OBJ_CAR1] * m_matObjRot[G_OBJ_CAR1] * m_matObjTrans[G_OBJ_CAR1];
	//드롭십 차량1 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_CAR1])->m_OBB.Init(D3DXVECTOR3(-160.0f, 0.0f, -440.0f), D3DXVECTOR3(160.0f, 300.0f, 440.0f));

	//차량2 로드
	m_Obj[G_OBJ_CAR2] = I_ObjMgr.GetPtr(G_OBJ_NAME_CAR);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR2], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR2], -900.0f, 0.0f, 700.0f);
	m_matObjWld[G_OBJ_CAR2] = m_matObjScl[G_OBJ_CAR2] * m_matObjRot[G_OBJ_CAR2] * m_matObjTrans[G_OBJ_CAR2];
	//드롭십 차량2 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_CAR2])->m_OBB.Init(D3DXVECTOR3(-160.0f, 0.0f, -440.0f), D3DXVECTOR3(160.0f, 300.0f, 440.0f));


	for (int i = 0; i < G_OBJ_CNT; i++) 
	{

		m_matObjOBB[i] = m_matObjScl[i] * m_matObjRot[i] * m_matObjTrans[i];
	}


	return true;
}


bool GProjMain::Frame()
{
	m_pMainCamera->Frame();

	m_HeightMap.Frame();
	g_pImmediateContext->UpdateSubresource(
		m_HeightMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_HeightMap.m_VertexList.at(0), 0, 0);

	

	G_BOX pBox2;
	m_Objbit.reset();	





	return true;
}
bool GProjMain::Render()
{
	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_HeightMap.Render(m_pImmediateContext);

	G_BOX pBox2;

	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_Obj[i]->Frame();

	
		float f2 = ((GGbsObj*)m_Obj[i])->m_OBB.extent[0];
		float f3 = ((GGbsObj*)m_Obj[i])->m_OBB.extent[1];
		float f4 = ((GGbsObj*)m_Obj[i])->m_OBB.extent[2];

		D3DXVECTOR3 v1 = ((GGbsObj*)m_Obj[i])->m_OBB.center;
		D3DXVECTOR3 v2 = ((GGbsObj*)m_Obj[i])->m_OBB.axis[0];
		D3DXVECTOR3 v3 = ((GGbsObj*)m_Obj[i])->m_OBB.axis[1];
		D3DXVECTOR3 v4 = ((GGbsObj*)m_Obj[i])->m_OBB.axis[2];


		pBox2.vCenter = ((GGbsObj*)m_Obj[i])->m_OBB.center;

		pBox2.fExtent[0] = ((GGbsObj*)m_Obj[i])->m_OBB.extent[0];
		pBox2.fExtent[1] = ((GGbsObj*)m_Obj[i])->m_OBB.extent[1];
		pBox2.fExtent[2] = ((GGbsObj*)m_Obj[i])->m_OBB.extent[2];

		pBox2.vAxis[0] = ((GGbsObj*)m_Obj[i])->m_OBB.axis[0];
		pBox2.vAxis[1] = ((GGbsObj*)m_Obj[i])->m_OBB.axis[1];
		pBox2.vAxis[2] = ((GGbsObj*)m_Obj[i])->m_OBB.axis[2];
		if (m_pMainCamera->CheckOBBInPlane(&pBox2))
		{
			m_Objbit.set(i);
		}
	}

	for (int i = 0; i < G_OBJ_CNT; i++) 
	{
		D3DXMATRIX mat = m_Obj[i]->m_matWorld;

		if (m_Objbit[i])
		{
			m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
			m_Obj[i]->Frame();
			m_Obj[i]->Render(g_pImmediateContext);
		}
		

		if (m_Objbit[i])
		{
			((GGbsObj*)m_Obj[i])->m_OBB.Render(&m_matObjOBB[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		}
			
	}

	
	return true;
}
bool GProjMain::Release()
{	
	m_HeightMap.Release();
	
	I_ObjMgr.Release();

	SAFE_ZERO(m_pMainCamera);
	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	
	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{
	m_pMainCamera = NULL;
	m_bDebugMode = true;
}
GProjMain::~GProjMain(void){
	
}



int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GProjMain gProjMain; g_pMain = &gProjMain;
	if (!gProjMain.InitWindow(hInstance, nCmdShow, L"Frustum & ObjCulling", 1024, 768)) { return 0; }
	ShowCursor(TRUE);
	gProjMain.Run();	return 1;
}


