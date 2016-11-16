#include "_stdafx.h"

GSeqSinglePlay * GSeqSinglePlay::pInstance_ = 0;


bool GSeqSinglePlay::ChkOBBToRay(GBBox* pBox, G_RAY* pRay)
{
	if (pRay == NULL) pRay = &m_Ray;
	float t_min = -999999.0f;
	float t_max = 999999.0f;
	float  f[3], fa[3], s[3], sa[3];

	D3DXVECTOR3 vR = pRay->vOrigin - pBox->center;

	for (int v = 0; v < 3; v++)
	{
		f[v] = D3DXVec3Dot(&pBox->axis[v], &pRay->vDirection);
		s[v] = D3DXVec3Dot(&pBox->axis[v], &vR);
		fa[v] = fabs(f[v]);
		sa[v] = fabs(s[v]);

		if (sa[v] > pBox->extent[v] && s[v] * f[v] >= 0.0f)
			return false;

		float t1 = (-s[v] - pBox->extent[v]) / f[v];
		float t2 = (-s[v] + pBox->extent[v]) / f[v];
		if (t1 > t2)
		{
			swap(t1, t2);
		}
		t_min = max(t_min, t1);
		t_max = min(t_max, t2);
		if (t_min > t_max)
			return false;
	}

	float  fCross[3], fRhs;
	D3DXVECTOR3 vDxR;
	D3DXVec3Cross(&vDxR, &pRay->vDirection, &vR);
	// D X pBox->vAxis[0]  분리축
	fCross[0] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[0]));
	float fAxis2 = pBox->extent[1] * fa[2];
	float fAxis1 = pBox->extent[2] * fa[1];
	fRhs = fAxis2 + fAxis1;
	if (fCross[0] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}
	// D x pBox->vAxis[1]  분리축
	fCross[1] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[1]));
	fRhs = pBox->extent[0] * fa[2] + pBox->extent[2] * fa[0];
	if (fCross[1] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}
	// D x pBox->vAxis[2]  분리축
	fCross[2] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[2]));
	fRhs = pBox->extent[0] * fa[1] + pBox->extent[1] * fa[0];
	if (fCross[2] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}

	m_Select.m_vIntersection = pRay->vOrigin + pRay->vDirection* t_min;
	return true;
}

bool GSeqSinglePlay::Init()
{
	InitGame();
	InitChar();
	InitEffect();
	InitMap();
	InitObj();
	return true;
}
bool GSeqSinglePlay::Frame()
{
	FrameGame();
	FrameMap();
	FrameObj();
	FrameEffect();
	FrameChar();

	//총 발사 애니메이션 처리
	if (g_InputData.bLeftClick) {
		m_ObjGun.ResetAni();

		D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		m_Ray.vOrigin = m_pCamera->m_vCameraPos;
		m_Ray.vDirection = m_pCamera->m_vLookVector;
		m_Ray.fExtent = 50.0f;

		//D3DXMATRIX matCharWld;
		//matCharWld = m_matWorld;
		//matCharWld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;
		
		//for (int i = 0; i < 8;i++){
		//D3DXVec3TransformCoord(&m_CharZombie[0].get()->m_OBB.m_vPoint[i],&m_CharZombie[0].get()->m_OBB.m_vPoint[i],&matCharWld);
		//}

		if (ChkOBBToRay(&m_CharZombie[0].get()->m_OBB, &m_Ray))
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_DIE");

			m_CharZombie[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}

		//if (GBBOXFUNC::RaytoBox(&temp, &m_CharZombie[0].get()->m_OBB, &ray))
		//	int a = 10;

	}
	//총 위치 업데이트
	UpdateGunPosition();
	m_ObjGun.Frame();

	return true;
}

bool GSeqSinglePlay::Render()
{
	//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	//g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);

	RenderMap();
	RenderObj();
	RenderChar();
	RenderGame();
	RenderEffect();

	return true;
}
bool GSeqSinglePlay::Release()
{
	ReleaseGame();
	ReleaseMap();
	ReleaseObj();
	ReleaseChar();
	ReleaseEffect();

	return true;
}

bool        GSeqSinglePlay::InitGame() {
#ifdef G_MACRO_GAME_ADD


	D3DXMatrixIdentity(&m_matWorld);

	m_ObjGun.Init();

	m_ObjGun.m_bAniLoop = false;

	if (!m_ObjGun.Load(g_pd3dDevice, _T("data/object/fps_shotgun/shotgun3.GBS"), L"data/shader/box.hlsl"))
	{
		return false;
	}


	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pDebugCamera = make_shared<GCamera>();
	m_pDebugCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 2500.0f, -2500.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pDebugCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pDebugCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);


	for (int i = 0; i < G_HERO_CNT; i++) {
		auto FPSCamera = make_shared<GFPSCamera>();

		FPSCamera.get()->SetViewMatrix(D3DXVECTOR3(120.0f + i*20.0f, 60.0f, -1400.0f), D3DXVECTOR3(-10.0f, 10.0f, 50.0f));

		fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
		FPSCamera.get()->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
		FPSCamera.get()->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

		m_pFPSCamera.push_back(FPSCamera);
	}



	if (!m_bDebugCamera) {
		m_pCamera = m_pFPSCamera[m_CurrentHero].get();
		g_pMain->m_bDebugInfoPrint = false;
		g_pMain->m_bDebugFpsPrint = false;
	}

	else {
		m_pCamera = m_pDebugCamera.get();
		g_pMain->m_bDebugInfoPrint = true;
		g_pMain->m_bDebugFpsPrint = true;
	}

#endif
	return true;
};
bool        GSeqSinglePlay::InitMap() {
#ifdef G_MACRO_MAP_ADD


	m_iDrawDepth = 0;
	m_bDebugRender = false;

	//--------------------------------------------------------------------------------------
	// 디버그 라인 생성
	//--------------------------------------------------------------------------------------
	if (FAILED(m_DrawLine.Create(g_pd3dDevice, G_SHA_LINE)))
	{
		MessageBox(0, _T("m_DrawLine 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}



	//--------------------------------------------------------------------------------------
	// 스카이 박스
	//--------------------------------------------------------------------------------------
	m_pSkyBoxObj = make_shared<GN2Skybox>();
	if (m_pSkyBoxObj->Create(g_pd3dDevice, L"data/shader/SkyBox.hlsl") == false)
	{
		MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	m_pSkyBoxObj->CreateTextureArray(g_pd3dDevice, g_pImmediateContext);

	//--------------------------------------------------------------------------------------
	// 카메라 프로스텀 랜더링용 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_pCamera->CreateRenderBox(g_pd3dDevice, g_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(g_pd3dDevice, G_SHA_BOX, "PS_Color"));

	//--------------------------------------------------------------------------------------
	// 커스텀맵 생성
	//--------------------------------------------------------------------------------------
	TMapDesc MapDesc = { 50, 50, 500.0f, 0.0f,L"data/sand.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_CustomMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(m_CustomMap.Load(MapDesc)))
	{
		return false;
	}
	

	//--------------------------------------------------------------------------------------
	//  쿼드 트리
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(MapDesc.iNumCols, MapDesc.iNumRows);

	m_QuadTree.Update(g_pd3dDevice, m_pCamera);

	//m_QuadTree.AddObject(&m_tbsobj[iBox]);
#endif

	return true;
};
bool		GSeqSinglePlay::InitChar() {
#ifdef G_MACRO_CHAR_ADD
	I_CharMgr.Init();

	Load();

	for (int i = 0; i < m_CharZombie.size(); i++) {
		m_CharZombie[i].get()->m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	}
	for (int i = 0; i < m_CharHero.size(); i++) {
		m_CharHero[i].get()->m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	}
#endif
	return true;
};
bool		GSeqSinglePlay::InitObj() {
#ifdef G_MACRO_MAP_ADD

	for (int i = 0; i < G_OBJ_CNT; i++) {
		D3DXMatrixIdentity(&m_matObjWld[i]);
		D3DXMatrixIdentity(&m_matObjScl[i]);
		D3DXMatrixIdentity(&m_matObjRot[i]);
		D3DXMatrixIdentity(&m_matObjTrans[i]);
		D3DXMatrixIdentity(&m_matObjOBB[i]);
	}

	//--------------------------------------------------------------------------------------
	// 오브젝트 생성
	//--------------------------------------------------------------------------------------
	for (int i = 0; i < G_OBJ_CNT; i++) {
		m_Obj[i].Init();
	}


	//연구소 로드
	m_Obj[G_OBJ_LAB].Load(g_pd3dDevice, G_OBJ_LOC_LAB, G_SHA_BOX);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB], 2, 2, 2);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB], 1000.0f, 0.0f, 1000.0f);
	m_matObjWld[G_OBJ_LAB] = m_matObjScl[G_OBJ_LAB] * m_matObjRot[G_OBJ_LAB] * m_matObjTrans[G_OBJ_LAB];
	//연구소 OBB 사이즈
	m_Obj[G_OBJ_LAB].m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));

	//드롭십 로드
	m_Obj[G_OBJ_DROPSHIP].Load(g_pd3dDevice, G_OBJ_LOC_DROPSHIP_LAND, G_SHA_BOX);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_DROPSHIP], 2.f, 2.f, 2.f);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_DROPSHIP], D3DXToRadian(45.0f + 180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_DROPSHIP], -1000.0f, 0.0f, -1000.0f);
	m_matObjWld[G_OBJ_DROPSHIP] = m_matObjScl[G_OBJ_DROPSHIP] * m_matObjRot[G_OBJ_DROPSHIP] * m_matObjTrans[G_OBJ_DROPSHIP];
	//드롭십 OBB 사이즈
	m_Obj[G_OBJ_DROPSHIP].m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));

	//차량1 로드
	m_Obj[G_OBJ_CAR1].Load(g_pd3dDevice, G_OBJ_LOC_CAR, G_SHA_BOX);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR1], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR1], 500.0f, 0.0f, -700.0f);
	m_matObjWld[G_OBJ_CAR1] = m_matObjScl[G_OBJ_CAR1] * m_matObjRot[G_OBJ_CAR1] * m_matObjTrans[G_OBJ_CAR1];
	//드롭십 차량1 OBB 사이즈
	m_Obj[G_OBJ_CAR1].m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));

	//차량2 로드
	m_Obj[G_OBJ_CAR2].Load(g_pd3dDevice, G_OBJ_LOC_CAR, G_SHA_BOX);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR2], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR2], -900.0f, 0.0f, 700.0f);
	m_matObjWld[G_OBJ_CAR2] = m_matObjScl[G_OBJ_CAR2] * m_matObjRot[G_OBJ_CAR2] * m_matObjTrans[G_OBJ_CAR2];
	//드롭십 차량2 OBB 사이즈
	m_Obj[G_OBJ_CAR2].m_OBB.Init(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));


	for (int i = 0; i < G_OBJ_CNT; i++) {

		m_matObjOBB[i] = m_matObjRot[i] * m_matObjTrans[i];
	}

#endif
	return true;
};
bool		GSeqSinglePlay::InitEffect() {
#ifdef G_MACRO_EFFECT_ADD
	m_pPS.Attach(DX::LoadPixelShaderFile(g_pd3dDevice,
		L"data/shader/Blend.hlsl", "PS_MATERIAL"));
	//--------------------------------------------------------------------------------------
	// 배경 부분
	//--------------------------------------------------------------------------------------
	m_pScreen = make_shared<GPlaneShape>();
	if (m_pScreen->Create(g_pd3dDevice, G_SHA_PLANE) == false)
	{
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//SAFE_NEW(m_pSprite, GSprite);
	m_pSprite = make_shared<GSprite>();
	//--------------------------------------------------------------------------------------
	// 월드  행렬
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matRotation, matScale;
	D3DXMatrixScaling(&matScale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationX(&matRotation, D3DX_PI*0.5f);
	D3DXMatrixMultiply(&m_mPlanWorld, &matScale, &matRotation);
	D3DXMatrixIdentity(&m_matPlaneWorld);


	//play 버튼시 init() 부분
	m_pSprite.get()->Create(g_pd3dDevice, G_SHA_PLANE, L"data/effect/ds1.dds");
	// 애니메이션 관련, 가로4x4
	m_pSprite.get()->SetRectAnimation(1.0f, 4, 128, 4, 128);
#endif
	return true;
};

bool        GSeqSinglePlay::FrameGame() {
#ifdef G_MACRO_GAME_ADD
	if (!m_bDebugCamera)
		ShowCursor(false); // 커서를 화면에서 감추기
	else {
		ShowCursor(true);
	}

	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_UP) {

		if (m_bDebugCamera) {
			m_bDebugCamera = false;
			m_pCamera = m_pFPSCamera[m_CurrentHero].get();
			g_pMain->m_bDebugInfoPrint = false;
			g_pMain->m_bDebugFpsPrint = false;
		}
		else {
			m_bDebugCamera = true;
			m_pCamera = m_pDebugCamera.get();
			g_pMain->m_bDebugInfoPrint = true;
			g_pMain->m_bDebugFpsPrint = true;
		}
	}

	if (I_Input.KeyCheck(DIK_TAB) == KEY_PUSH) {

		if (G_HERO_TOM == m_CurrentHero) {
			m_CurrentHero = G_HERO_JAKE;
			m_pCamera = m_pFPSCamera[m_CurrentHero].get();
		}
		else {
			m_CurrentHero = G_HERO_TOM;
			m_pCamera = m_pFPSCamera[m_CurrentHero].get();
		}
		m_bDebugCamera = false;
		g_pMain->m_bDebugInfoPrint = false;
		g_pMain->m_bDebugFpsPrint = false;
	}

	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = g_pMain->m_Timer.GetElapsedTime() * D3DX_PI;

	m_pCamera->Frame();

	//for (int i = 0; i < m_pFPSCamera.size(); i++) {
	//	
	//	m_pFPSCamera[i].get()->Frame();
	//}


#endif
	return true;
};

bool        GSeqSinglePlay::FrameMap() {
#ifdef G_MACRO_MAP_ADD

	if (I_Input.KeyCheck(DIK_F1) == KEY_UP)
	{
		if (++m_iDrawDepth > 7) m_iDrawDepth = -1;
		m_QuadTree.SetRenderDepth(m_iDrawDepth);
	}
	m_QuadTree.Update(g_pd3dDevice, m_pCamera);


	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		m_bDebugRender = !m_bDebugRender;
	}
	if (I_Input.KeyCheck(DIK_GRAVE) == KEY_UP) //문턱값 사용 ~
	{
		m_QuadTree.SetThresHold(!m_QuadTree.m_bThresHoldValue);
	}

	m_QuadTree.Frame();

#endif
	return true;
};
bool		GSeqSinglePlay::FrameChar() {
#ifdef G_MACRO_CHAR_ADD

	for (int iChar = 0; iChar < m_CharHero.size(); iChar++)
	{
		m_CharHero[iChar]->Frame();
	}

	for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
	{
		/*
		if (I_Input.KeyCheck(DIK_ADD))
		{
		m_HeroObj[iChar]->m_fSpeed += g_fSecPerFrame;
		}
		if (I_Input.KeyCheck(DIK_SUBTRACT))
		{
		m_HeroObj[iChar]->m_fSpeed -= g_fSecPerFrame;
		if (m_HeroObj[iChar]->m_fSpeed < 0.0f) m_HeroObj[iChar]->m_fSpeed = 0.01f;
		}
		*/
		m_CharZombie[iChar]->Frame();
	}


	enum G_ZOMBIE_STATE {
		G_ZOMB_IDLE = 0,
		G_ZOMB_ATTACK,
		G_ZOMB_WALK,
		G_ZOMB_DIE,
		G_ZOMB_CNT
	};
	static int iChange = 0;



	if (I_Input.KeyCheck(DIK_F11) == KEY_UP)
	{
		if (iChange != G_ZOMB_DIE) {
			iChange++;
		}
		else {
			iChange = 0;
		}

		switch (iChange) {
		case G_ZOMB_DIE:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_DIE");

			m_CharZombie[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_ATTACK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

			m_CharZombie[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_WALK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

			m_CharZombie[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_IDLE:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

			m_CharZombie[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		}


	}

	if (I_Input.KeyCheck(DIK_F12) == KEY_UP)
	{
		for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
		{
			m_CharZombie[iChar]->m_bBoneRender = !m_CharZombie[iChar]->m_bBoneRender;
		}
	}

	if (I_Input.KeyCheck(DIK_F9) == KEY_UP)
	{
		Load();
	}
#endif
	return true;
};
bool		GSeqSinglePlay::FrameObj() {
#ifdef G_MACRO_MAP_ADD
	for (int i = 0; i < G_OBJ_CNT; i++) {
		m_Obj[i].Frame();
	}
#endif
	return true;
};
bool		GSeqSinglePlay::FrameEffect() {
#ifdef G_MACRO_EFFECT_ADD
	//--------------------------------------------------------------------------------------
	// 빌보드 행렬
	//-----------------------------------------------------------------------------------
	FLOAT fDeterminant;
	D3DXMATRIX matBillboard;
	D3DXMatrixInverse(&matBillboard, &fDeterminant, m_pCamera->GetViewMatrix());
	matBillboard._41 = 0.0f;
	matBillboard._42 = 0.0f;
	matBillboard._43 = 0.0f;
	matBillboard._44 = 1.0f;


	m_pSprite.get()->SetMatrix(&matBillboard, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_pSprite.get()->Frame(g_pImmediateContext, g_pMain->m_Timer.GetElapsedTime(), g_fSecPerFrame);
#endif
	return true;
};

bool        GSeqSinglePlay::RenderGame() {
#ifdef G_MACRO_GAME_ADD
	m_ObjGun.SetMatrix(NULL, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());

	//if(!m_bDebugCamera)
	m_ObjGun.Render(g_pImmediateContext);
#endif
	return true;
};

bool        GSeqSinglePlay::RenderMap() {
#ifdef G_MACRO_MAP_ADD
	//--------------------------------------------------------------------------------------
	// 스카이 박스
	//--------------------------------------------------------------------------------------
	//DX::ApplyRS(g_pImmediateContext, DX::GDxState::g_pRSNoneCullSolid);
	//DX::ApplyDSS(g_pImmediateContext, DX::GDxState::g_pDSSDepthDisable);
	//DX::ApplyBS(g_pImmediateContext, DX::GDxState::g_pAlphaBlend);

	//g_pImmediateContext->PSSetSamplers(0, 1, &DX::GDxState::g_pSSWrapLinear);
	m_pSkyBoxObj->SetMatrix(0, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_pSkyBoxObj->Render(g_pImmediateContext);
	//--------------------------------------------------------------------------------------
	// 커스텀 맵
	//--------------------------------------------------------------------------------------
	m_CustomMap.SetMatrix(m_pCamera->GetWorldMatrix(), m_pCamera->GetViewMatrix(),
		m_pCamera->GetProjMatrix());
	m_CustomMap.Render(g_pImmediateContext);

	DrawSelectTreeLevel(m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	if (m_bDebugRender)
	{
		DrawQuadLine(m_QuadTree.m_pRootNode);
	}



#endif
	return true;
};

bool		GSeqSinglePlay::RenderChar() {
#ifdef G_MACRO_CHAR_ADD
	D3DXMATRIX matCharWld;
	matCharWld = m_matWorld;
	matCharWld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;

	D3DXMATRIX matHeroWld[G_HERO_CNT];
	D3DXMATRIX matHeroScl[G_HERO_CNT];
	D3DXMATRIX matHeroRot[G_HERO_CNT];
	D3DXMATRIX matHeroTrans[G_HERO_CNT];

	for (int i = 0; i < G_HERO_CNT; i++){
		D3DXMatrixIdentity(&matHeroWld[i]);
		D3DXMatrixIdentity(&matHeroScl[i]);

		D3DXMatrixIdentity(&matHeroTrans[i]);
		D3DXMatrixTranslation(&matHeroTrans[i], m_pFPSCamera[i].get()->m_vCameraPos.x, G_DEFINE_CHAR_Y_POS_OFFSET, m_pFPSCamera[i].get()->m_vCameraPos.z);
		matHeroRot[i] = m_pFPSCamera[i].get()->GetRotMatY();

		matHeroWld[i] = matHeroScl[i] * matHeroRot[i] * matHeroTrans[i];
	}

	for (int iChar = 0; iChar < m_CharHero.size(); iChar++)
	{
		if (iChar == m_CurrentHero && m_bDebugCamera==false)
			continue;
		m_CharHero[iChar].get()->SetMatrix(&matHeroWld[iChar], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharHero[iChar].get()->Render(g_pImmediateContext);
	}

	for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_CharZombie[iChar]->SetMatrix(&matCharWld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharZombie[iChar]->Render(g_pImmediateContext);
	}

	if(m_bDebugCamera){
		for (int iChar = 0; iChar < m_CharZombie.size(); iChar++) {
			m_CharZombie[iChar].get()->m_OBB.Render(&matCharWld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
		for (int iChar = 0; iChar < m_CharHero.size(); iChar++) {
			m_CharHero[iChar].get()->m_OBB.Render(&matHeroWld[iChar], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
	}

#endif
	return true;
};
bool		GSeqSinglePlay::RenderObj() {
#ifdef G_MACRO_MAP_ADD
	for (int i = 0; i < G_OBJ_CNT; i++) {
		m_Obj[i].SetMatrix(&m_matObjWld[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_Obj[i].Render(g_pImmediateContext);

		if(m_bDebugCamera)
			m_Obj[i].m_OBB.Render(&m_matObjOBB[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	}
#endif
	return true;
};
bool		GSeqSinglePlay::RenderEffect() {
#ifdef G_MACRO_EFFECT_ADD
	D3DXVECTOR4 vColor = D3DXVECTOR4(0, 0, 0, 0);
	float fValue = cosf(g_pMain->m_Timer.GetElapsedTime())*0.5f + 0.5f;
	FLOAT fFactor[4] = { 0 , };
	m_vMaterial.x = 1.0f;
	m_vMaterial.y = 1.0f;
	m_vMaterial.z = 1.0f;
	m_vMaterial.w = fValue;
	m_pSprite.get()->m_cbData.Color = m_vMaterial;
	ApplyBS(g_pImmediateContext, GDxState::g_pBSAlphaOne, fFactor, 0xffffffff);

	//if (m_RT.Begin(g_pImmediateContext, vColor))
	//	{
	ApplyRS(g_pMain->GetContext(), GDxState::g_pRSBackCullSolid);
	ApplyDSS(g_pMain->GetContext(), GDxState::g_pDSSDepthEnable);

	D3DXMATRIX matEffectWld;
	matEffectWld = m_matWorld;
	matEffectWld._42 = 10.0f;
	m_pSprite.get()->SetMatrix(&matEffectWld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_pSprite.get()->Render(g_pImmediateContext);

	//	m_RT.Apply(g_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	//	m_RT.End(g_pImmediateContext);
	//	}

	ApplyDSS(g_pMain->GetContext(), GDxState::g_pDSSDepthDisable);
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	m_pScreen->SetMatrix(&matIdentity, &matIdentity, &matIdentity);
	m_pScreen->PreRender(g_pImmediateContext);
	g_pImmediateContext->OMSetBlendState(GDxState::g_pBSAlphaOne, 0, -1);
	//	g_pImmediateContext->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
	g_pImmediateContext->PSSetShader(m_pPS.Get(), NULL, 0);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, m_pSprite.get()->m_dxobj.g_pConstantBuffer.GetAddressOf());
	m_pScreen->PostRender(g_pImmediateContext);




	ApplyDSS(g_pImmediateContext, GDxState::g_pDSSDepthDisable);
	ApplyBS(g_pImmediateContext, GDxState::g_pBSOneZero);

	ClearD3D11DeviceContext(g_pImmediateContext);
#endif
	return true;
};

bool        GSeqSinglePlay::ReleaseGame() {
#ifdef G_MACRO_GAME_ADD
	m_ObjGun.Release();
#endif
	return true;
};

bool        GSeqSinglePlay::ReleaseMap() {
#ifdef G_MACRO_MAP_ADD
	m_CustomMap.Release();
	m_QuadTree.Release();
#endif
	return true;
};
bool		GSeqSinglePlay::ReleaseChar() {
#ifdef G_MACRO_CHAR_ADD

	I_CharMgr.Release();

#endif
	return true;
};
bool		GSeqSinglePlay::ReleaseObj() {
#ifdef G_MACRO_MAP_ADD
	for (int i = 0; i < G_OBJ_CNT; i++) {
		m_Obj[i].Release();
	}
#endif
	return true;
};
bool		GSeqSinglePlay::ReleaseEffect() {
#ifdef G_MACRO_EFFECT_ADD

#endif
	return true;
};




bool GSeqSinglePlay::UpdateGunPosition() {

	if (!m_pCamera)
		return false;

	D3DXMATRIX matWorld, matScl, matRot, matTrans, matViewInv;

	D3DXVECTOR3 vScl, vTrans;
	D3DXQUATERNION qRot;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matViewInv);

	D3DXMatrixInverse(&matViewInv, NULL, m_pCamera->GetViewMatrix());


	D3DXMatrixTranslation(&matTrans, 5.0f, -5.0f, 10.0f);

	D3DXMatrixRotationY(&matRot, D3DXToRadian(180.0f));

	m_ObjGun.m_matWorld = matScl * matRot * matTrans * matViewInv;// *matTrans;

	return true;
}


#ifdef G_MACRO_CHAR_ADD

bool GSeqSinglePlay::Load()
{
	//좀비 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("CharZombie.gci") /*_T("CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");


	shared_ptr<GZombie> pObjA = make_shared<GZombie>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_CharZombie.push_back(pObjA);

	//주인공1 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("CharHero1.gci") /*_T("CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO1_IDLE");


	shared_ptr<GHero> pObjB = make_shared<GHero>();
	pObjB->Set(pChar1,
		pChar1->m_pBoneObject,
		pChar1->m_pBoneObject->m_Scene.iFirstFrame,
		pChar1->m_pBoneObject->m_Scene.iLastFrame);
	m_CharHero.push_back(pObjB);

	//주인공2 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("CharHero2.gci") /*_T("CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar2 = I_CharMgr.GetPtr(L"HERO2_IDLE");


	shared_ptr<GHero> pObjC = make_shared<GHero>();
	pObjC->Set(pChar2,
		pChar2->m_pBoneObject,
		pChar2->m_pBoneObject->m_Scene.iFirstFrame,
		pChar2->m_pBoneObject->m_Scene.iLastFrame);
	m_CharHero.push_back(pObjC);

	return true;
}
#endif 

#ifdef G_MACRO_MAP_ADD
void GSeqSinglePlay::DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	//for (int iObj = 0; iObj < m_QuadTree.m_DrawObjList.size(); iObj++)
	//{
	//	GMapObject* pBox = dynamic_cast<GMapObject*>(m_QuadTree.m_DrawObjList[iObj]);
	//	m_pBoxs->SetAmbientColor(pBox->m_vColor.x, pBox->m_vColor.y, pBox->m_vColor.z, pBox->m_vColor.w);
	//	m_pBoxs->SetMatrix(&pBox->m_matWorld, pView, pProj);
	//	m_pBoxs->Render(g_pImmediateContext);
	//}
}

bool GSeqSinglePlay::DrawQuadLine(GNode* pNode)
{
	if (pNode == NULL) return true;
	if (m_QuadTree.m_iRenderDepth == pNode->m_iDepth ||
		(pNode->m_isLeaf &&  m_QuadTree.m_iRenderDepth < 0))
	{
		m_DrawLine.SetMatrix(m_pCamera->GetWorldMatrix(), m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());

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
		DrawQuadLine(pNode->m_ChildList[iNode]);
	}
	return true;
}
#endif



//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GSeqSinglePlay::CreateResource()
{
	HRESULT hr;
	if (m_pCamera)
	{
		float fAspectRatio = g_pMain->m_SwapChainDesc.BufferDesc.Width /
			(float)g_pMain->m_SwapChainDesc.BufferDesc.Height;
		m_pCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GSeqSinglePlay::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GSeqSinglePlay::GSeqSinglePlay(void)
{
	m_CurrentHero = G_HERO_TOM;
	m_bDebugCamera = false;
	m_pCamera = nullptr;
#ifdef G_MACRO_EFFECT_ADD
	m_pSprite = nullptr;
#endif
}

GSeqSinglePlay::~GSeqSinglePlay(void)
{
}
int GSeqSinglePlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera != nullptr)
	{
		m_pCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}





