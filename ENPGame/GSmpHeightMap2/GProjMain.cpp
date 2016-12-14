#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	HRESULT hr;
	//카메라 생성
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(-2000.0f, -0.1f, -4500.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(-3500.0f, 1000.0f, 1000.0f);
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
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB], -4000.0f, 0.0f, -4000.0f);
	m_matObjWld[G_OBJ_LAB] = m_matObjScl[G_OBJ_LAB] * m_matObjRot[G_OBJ_LAB] * m_matObjTrans[G_OBJ_LAB];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	//드롭십 로드
	m_Obj[G_OBJ_DROPSHIP] = I_ObjMgr.GetPtr(G_OBJ_NAME_DROPSHIP_LAND);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_DROPSHIP], 3.f, 3.f, 3.f);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_DROPSHIP], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_DROPSHIP], 5000.0f, 0.0f, 5000.0f);
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


	//-------------------------------------------------------------------------------------------------------------
	//상단 세로길 만들기
	//-------------------------------------------------------------------------------------------------------------
	// 1 
	m_Obj[G_OBJ_LAB1] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB1], 2, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB1], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB1], 2000.0f, 0.0f, 1350.0f);
	m_matObjWld[G_OBJ_LAB1] = m_matObjScl[G_OBJ_LAB1] * m_matObjRot[G_OBJ_LAB1] * m_matObjTrans[G_OBJ_LAB1];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB1])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 2
	m_Obj[G_OBJ_LAB2] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB2], 4, 1.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB2], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB2], 2000.0f, 0.0f, 2100.0f);
	m_matObjWld[G_OBJ_LAB2] = m_matObjScl[G_OBJ_LAB2] * m_matObjRot[G_OBJ_LAB2] * m_matObjTrans[G_OBJ_LAB2];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB2])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 3
	m_Obj[G_OBJ_LAB3] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB3], 3.5, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB3], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB3], 2000.0f, 0.0f,2800.0f);
	m_matObjWld[G_OBJ_LAB3] = m_matObjScl[G_OBJ_LAB3] * m_matObjRot[G_OBJ_LAB3] * m_matObjTrans[G_OBJ_LAB3];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB3])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 4 
	m_Obj[G_OBJ_LAB4] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB4], 10, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB4], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB4], 2000.0f, 0.0f, 4000.0f);
	m_matObjWld[G_OBJ_LAB4] = m_matObjScl[G_OBJ_LAB4] * m_matObjRot[G_OBJ_LAB4] * m_matObjTrans[G_OBJ_LAB4];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB4])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	//-------------------------------------------------------------------------------------------------------------
	//상단 가로 길 만들기
	//-------------------------------------------------------------------------------------------------------------
	// 5 
	m_Obj[G_OBJ_LAB5] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB5], 5, 1.7, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB5], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB5], 1400.0f, 0.0f, 1280.0f);
	m_matObjWld[G_OBJ_LAB5] = m_matObjScl[G_OBJ_LAB5] * m_matObjRot[G_OBJ_LAB5] * m_matObjTrans[G_OBJ_LAB5];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB5])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 6  
	m_Obj[G_OBJ_LAB6] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB6], 2, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB6], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB6], 750.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB6] = m_matObjScl[G_OBJ_LAB6] * m_matObjRot[G_OBJ_LAB6] * m_matObjTrans[G_OBJ_LAB6];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB6])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 7 
	m_Obj[G_OBJ_LAB7] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB7], 4, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB7], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB7], 200.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB7] = m_matObjScl[G_OBJ_LAB7] * m_matObjRot[G_OBJ_LAB7] * m_matObjTrans[G_OBJ_LAB7];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB7])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 8
	m_Obj[G_OBJ_LAB8] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB8], 4, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB8], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB8], -550.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB8] = m_matObjScl[G_OBJ_LAB8] * m_matObjRot[G_OBJ_LAB8] * m_matObjTrans[G_OBJ_LAB8];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB8])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 9
	m_Obj[G_OBJ_LAB9] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB9], 3, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB9], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB9], -1200.0f, 0.0f, 1200.0f);
	m_matObjWld[G_OBJ_LAB9] = m_matObjScl[G_OBJ_LAB9] * m_matObjRot[G_OBJ_LAB9] * m_matObjTrans[G_OBJ_LAB9];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB9])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 10
	m_Obj[G_OBJ_LAB10] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB10], 2.7, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB10], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB10], -1700.0f, 0.0f, 1100.0f);
	m_matObjWld[G_OBJ_LAB10] = m_matObjScl[G_OBJ_LAB10] * m_matObjRot[G_OBJ_LAB10] * m_matObjTrans[G_OBJ_LAB10];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB10])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 11
	m_Obj[G_OBJ_LAB11] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB11], 4, 2.3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB11], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB11], -2300.0f, 0.0f, 1000.0f);
	m_matObjWld[G_OBJ_LAB11] = m_matObjScl[G_OBJ_LAB11] * m_matObjRot[G_OBJ_LAB11] * m_matObjTrans[G_OBJ_LAB11];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB11])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 12
	m_Obj[G_OBJ_LAB12] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB12], 3, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB12], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB12], -2950.0f, 0.0f, 900.0f);
	m_matObjWld[G_OBJ_LAB12] = m_matObjScl[G_OBJ_LAB12] * m_matObjRot[G_OBJ_LAB12] * m_matObjTrans[G_OBJ_LAB12];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB12])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 13
	m_Obj[G_OBJ_LAB13] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB13], 4, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB13], D3DXToRadian(315.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB13], -3600.0f, 0.0f, 550.0f);
	m_matObjWld[G_OBJ_LAB13] = m_matObjScl[G_OBJ_LAB13] * m_matObjRot[G_OBJ_LAB13] * m_matObjTrans[G_OBJ_LAB13];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB13])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 14
	m_Obj[G_OBJ_LAB14] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB14], 6, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB14], D3DXToRadian(315.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB14], -4250.0f, 0.0f, -100.0f);
	m_matObjWld[G_OBJ_LAB14] = m_matObjScl[G_OBJ_LAB14] * m_matObjRot[G_OBJ_LAB14] * m_matObjTrans[G_OBJ_LAB14];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB14])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));
	//-------------------------------------------------------------------------------------------------------------
	//하단 가로 길 만들기
	//-----------------------------------------------------------------------------------------------------------

	// 16
	m_Obj[G_OBJ_LAB16] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB16], 5, 1.7, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB16], D3DXToRadian(135.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB16], 2880.0f, 0.0f, -850.0f);
	m_matObjWld[G_OBJ_LAB16] = m_matObjScl[G_OBJ_LAB16] * m_matObjRot[G_OBJ_LAB16] * m_matObjTrans[G_OBJ_LAB16];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB16])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 17 
	m_Obj[G_OBJ_LAB17] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB17], 2, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB17], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB17], 2250.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB17] = m_matObjScl[G_OBJ_LAB17] * m_matObjRot[G_OBJ_LAB17] * m_matObjTrans[G_OBJ_LAB17];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB17])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 18 
	m_Obj[G_OBJ_LAB18] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB18], 4, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB18], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB18], 1700.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB18] = m_matObjScl[G_OBJ_LAB18] * m_matObjRot[G_OBJ_LAB18] * m_matObjTrans[G_OBJ_LAB18];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB18])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 19
	m_Obj[G_OBJ_LAB19] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB19], 4, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB19], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB19], 950.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB19] = m_matObjScl[G_OBJ_LAB19] * m_matObjRot[G_OBJ_LAB19] * m_matObjTrans[G_OBJ_LAB19];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB19])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 20
	m_Obj[G_OBJ_LAB20] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB20], 3, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB20], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB20], 300.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB20] = m_matObjScl[G_OBJ_LAB20] * m_matObjRot[G_OBJ_LAB20] * m_matObjTrans[G_OBJ_LAB20];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB20])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 21
	m_Obj[G_OBJ_LAB21] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB21], 2.7, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB21], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB21], -200.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB21] = m_matObjScl[G_OBJ_LAB21] * m_matObjRot[G_OBJ_LAB21] * m_matObjTrans[G_OBJ_LAB21];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB21])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 22
	m_Obj[G_OBJ_LAB22] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB22], 4, 2.3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB22], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB22], -800.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB22] = m_matObjScl[G_OBJ_LAB22] * m_matObjRot[G_OBJ_LAB22] * m_matObjTrans[G_OBJ_LAB22];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB22])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 23
	m_Obj[G_OBJ_LAB23] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB23], 3, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB23], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB23], -1450.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB23] = m_matObjScl[G_OBJ_LAB23] * m_matObjRot[G_OBJ_LAB23] * m_matObjTrans[G_OBJ_LAB23];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB23])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 24
	m_Obj[G_OBJ_LAB24] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB24], 4, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB24], D3DXToRadian(135.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB24], 3480.0f, 0.0f, -250.0f);
	m_matObjWld[G_OBJ_LAB24] = m_matObjScl[G_OBJ_LAB24] * m_matObjRot[G_OBJ_LAB24] * m_matObjTrans[G_OBJ_LAB24];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB24])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 25
	m_Obj[G_OBJ_LAB25] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB25], 7, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB25], D3DXToRadian(135.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB25], 4250.0f, 0.0f, 450.0f);
	m_matObjWld[G_OBJ_LAB25] = m_matObjScl[G_OBJ_LAB25] * m_matObjRot[G_OBJ_LAB25] * m_matObjTrans[G_OBJ_LAB25];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB25])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));
	
	//-------------------------------------------------------------------------------------------------------------
	//하단 세로길 만들기
	//-------------------------------------------------------------------------------------------------------------
	// 15
	m_Obj[G_OBJ_LAB15] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB15], 2, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB15], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB15], -1900.0f, 0.0f, -1350.0f);
	m_matObjWld[G_OBJ_LAB15] = m_matObjScl[G_OBJ_LAB15] * m_matObjRot[G_OBJ_LAB15] * m_matObjTrans[G_OBJ_LAB15];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB15])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 26
	m_Obj[G_OBJ_LAB26] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB26], 3.5, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB26], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB26], -1900.0f, 0.0f, -2050.0f);
	m_matObjWld[G_OBJ_LAB26] = m_matObjScl[G_OBJ_LAB26] * m_matObjRot[G_OBJ_LAB26] * m_matObjTrans[G_OBJ_LAB26];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB26])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 27
	m_Obj[G_OBJ_LAB27] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB27], 4, 1.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB27], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB27], -1900.0f, 0.0f, -2750.0f);
	m_matObjWld[G_OBJ_LAB27] = m_matObjScl[G_OBJ_LAB27] * m_matObjRot[G_OBJ_LAB27] * m_matObjTrans[G_OBJ_LAB27];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB27])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));

	// 28
	m_Obj[G_OBJ_LAB28] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB28], 10, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB28], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB28], -1800.0f, 0.0f, -4000.0f);
	m_matObjWld[G_OBJ_LAB28] = m_matObjScl[G_OBJ_LAB28] * m_matObjRot[G_OBJ_LAB28] * m_matObjTrans[G_OBJ_LAB28];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB28])->m_OBB.Init(D3DXVECTOR3(-95.0f, 0.0f, -85.0f), D3DXVECTOR3(93.0f, 100.0f, 125.0f));
	

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

	
	m_Objbit.reset();	


	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_Obj[i]->Frame();

		if (m_pMainCamera->CheckOBBInPlane(&(((GGbsObj*)m_Obj[i])->m_OBB)))
		{
			m_Objbit.set(i);
		}
	}


	return true;
}
bool GProjMain::Render()
{
	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_HeightMap.Render(m_pImmediateContext);


	for (int i = 0; i < G_OBJ_CNT; i++) 
	{
		D3DXMATRIX mat = m_Obj[i]->m_matWorld;

		if (m_Objbit[i])
		{
			m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
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


