#include "_stdafx.h"

GSeqSinglePlay * GSeqSinglePlay::pInstance_ = 0;

//그림자 [Start]
#ifdef G_DEFINE_SHADOW
const float g_fMaxSize = 1024;
void GSeqSinglePlay::RenderObject(D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	D3DXMATRIX matInvView;
	ApplySS(g_pMain->GetContext(), GDxState::g_pSSClampLinear, 1);
	ApplySS(g_pMain->GetContext(), GDxState::g_pSSShadowMap, 2);
	ApplyRS(g_pMain->GetContext(), GDxState::g_pRSBackCullSolid);

	/*
	m_pBoxShape->PreRender(g_pMain->GetContext());
	for (int iObj = 0; iObj < MAX_OBJECT_CNT; iObj++)
	{
		D3DXMatrixInverse(&matInvView, 0, matView);
		D3DXMATRIX matWVPT1 = m_matWorld[iObj] * m_matShadowView * m_matShadowProj * m_matTexture;
		D3DXMatrixTranspose(&m_cbShadow.g_matShadow, &matWVPT1);
		m_cbShadow.g_ShadowID = m_fObjID[iObj];
		m_cbShadow.g_iNumKernel = 3;
		g_pMain->GetContext()->UpdateSubresource(m_pShadowConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
		g_pMain->GetContext()->VSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());
		g_pMain->GetContext()->PSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());
		g_pMain->GetContext()->PSSetShaderResources(1, 1, m_RT.m_pDsvSRV.GetAddressOf());

		m_pBoxShape->SetMatrix(&m_matWorld[iObj], matView, matProj);
		m_pBoxShape->PostRender(g_pMain->GetContext());
	}
	*/
	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		D3DXMatrixInverse(&matInvView, 0, matView);
		D3DXMATRIX matWVPT1 = m_matObjWld[i] * m_matShadowView * m_matShadowProj * m_matTexture;
		D3DXMatrixTranspose(&m_cbShadow.g_matShadow, &matWVPT1);
		m_cbShadow.g_ShadowID = m_fObjID[i];
		m_cbShadow.g_iNumKernel = 3;
		g_pMain->GetContext()->UpdateSubresource(m_pShadowConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
		g_pMain->GetContext()->VSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());
		g_pMain->GetContext()->PSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());
		g_pMain->GetContext()->PSSetShaderResources(1, 1, m_RT.m_pDsvSRV.GetAddressOf());

		m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_Obj[i]->PostRender(g_pImmediateContext);
	}
}
void GSeqSinglePlay::RenderShadow(D3DXMATRIX* matShadow,
	D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	ApplyDSS(g_pMain->GetContext(), GDxState::g_pDSSDepthEnable);
	//ApplyRS(GetContext(), TDxState::g_pRSBackCullSolid);
	ApplyBS(g_pMain->GetContext(), GDxState::g_pAlphaBlend);
	ApplyRS(g_pMain->GetContext(), GDxState::g_pRSSlopeScaledDepthBias);

	m_CustomMap.SetMatrix(NULL, matView, matProj);
	m_CustomMap.PreRender(g_pMain->GetContext());
	g_pMain->GetContext()->VSSetShader(m_pShadowVS.Get(), NULL, 0);
	//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
	// 깊이스텐실 버퍼를 리소스로 전달하면 되기 때문에 픽쉘쉐이더를 사용하지 않아도 된다.
	// 하지만, 화면에 쿼드로 깊이맵 결과를 확인하고자 위 문장에서 픽쉘쉐이더를 활성화 하였다.
	g_pMain->GetContext()->PSSetShader(NULL, NULL, 0);
	m_CustomMap.PostRender(g_pMain->GetContext());

	/*
	for (int iObj = 0; iObj < MAX_OBJECT_CNT; iObj++)
	{
		m_pBoxShape->SetMatrix(&m_matWorld[iObj], matView, matProj);
		m_pBoxShape->PreRender(g_pMain->GetContext());
		g_pMain->GetContext()->VSSetShader(m_pShadowVS.Get(), NULL, 0);
		//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
		// 깊이스텐실 버퍼를 리소스로 전달하면 되기 때문에 픽쉘쉐이더를 사용하지 않아도 된다.
		// 하지만, 화면에 쿼드로 깊이맵 결과를 확인하고자 위 문장에서 픽쉘쉐이더를 활성화 하였다.
		g_pMain->GetContext()->PSSetShader(NULL, NULL, 0);
		m_pBoxShape->PostRender(g_pMain->GetContext());
	}
	*/
	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		m_Obj[i]->SetMatrix(&m_matObjWld[i], matView, matProj);
		m_Obj[i]->PreRender(g_pMain->GetContext());
		g_pMain->GetContext()->VSSetShader(m_pShadowVS.Get(), NULL, 0);
		//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
		// 깊이스텐실 버퍼를 리소스로 전달하면 되기 때문에 픽쉘쉐이더를 사용하지 않아도 된다.
		// 하지만, 화면에 쿼드로 깊이맵 결과를 확인하고자 위 문장에서 픽쉘쉐이더를 활성화 하였다.
		g_pMain->GetContext()->PSSetShader(NULL, NULL, 0);
		m_Obj[i]->PostRender(g_pMain->GetContext());
	}
}
//그림자 [End]
#endif

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
#ifdef G_DEFINE_SHADOW
	//그림자 [Start]
	SAFE_NEW(m_pQuad, GPlaneShape);
	m_pQuad->SetScreenVertex(15, 15, 300, 300,
		D3DXVECTOR2(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight));
	if (FAILED(m_pQuad->Create(g_pd3dDevice, L"data/shader/plane.hlsl", L"data/castle.jpg")))
	{
		MessageBox(0, _T("m_pLIne 실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	ComPtr<ID3DBlob> pVSBlob;
	m_pShadowVS.Attach(DX::LoadVertexShaderFile(g_pd3dDevice, L"data/shader_shadow/CustomizeMap_shadow.hlsl", pVSBlob.GetAddressOf(), "SHADOW_VS"));
	m_pShadowPS.Attach(DX::LoadPixelShaderFile(g_pd3dDevice, L"data/shader_shadow/CustomizeMap_shadow.hlsl", "SHADOW_PS"));

	// Create Source and Dest textures
	m_RT.m_DSFormat = DXGI_FORMAT_R32_TYPELESS;
	m_RT.Create(g_pd3dDevice, g_fMaxSize, g_fMaxSize);// m_bColorTexRender );

													  //m_ShaderEditer.Create( L"CustomizeMap.fx", m_hWnd );
	m_matTexture = D3DXMATRIX(0.5f, 0.0f, 0.0f, 0.0f
		, 0.0f, -0.5f, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, 0.5f, 0.5f, 0.0f, 1.0f);
	m_pShadowConstantBuffer.Attach(DX::CreateConstantBuffer(g_pd3dDevice, &m_cbShadow, 1, sizeof(SHADOW_CONSTANT_BUFFER)));


	m_vLightPos = D3DXVECTOR3(15, 40, -35);

	float fWidthLength = m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumCols*
		m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumCols;
	float fHeightLength = m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumRows*
		m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumRows;

	// 지형의 대각선의 길이, 텍스처에 적합하게 배치하려고 작업한다.
	float fMaxViewDistance = sqrt(fWidthLength + fHeightLength);
	//D3DXMatrixPerspectiveFovLH( &m_matShadowProj, D3DX_PI*0.25f, 1.0f, 20.0f, 200.0f );
	//D3DXMatrixOrthoLH( &m_matShadowProj, fMaxViewDistance, fMaxViewDistance, 0.0f, 100.0f );
	D3DXMatrixOrthoOffCenterLH(&m_matShadowProj,
		-fMaxViewDistance / 2, fMaxViewDistance / 2, -fMaxViewDistance / 2, fMaxViewDistance / 2, 0.0f, 100.0f);
	//그림자 [End]
#endif


	T_STR strFile;
	m_UIManager.Init();
	strFile = L"data/ui_singleplay.gui";
	m_UIManager.UILoad(&strFile, &g_pMain->m_SwapChainDesc, g_pMain->m_DefaultRT.m_vp.Width, g_pMain->m_DefaultRT.m_vp.Height);

	InitGame();
	InitChar();
	InitEffect();
	InitMap();
	InitObj();

	return true;
}
bool GSeqSinglePlay::FrameGun() {

	//총 위치 업데이트
	UpdateGunPosition();
	m_ObjGun.Frame();

	//총 발사 애니메이션 처리
	if (g_InputData.bLeftClick) {

		if (m_CharHero[m_CurrentHero].get()->m_iBullet <= 0&& m_bDebugMode==false)
			return false;

		m_ObjGun.ResetAni();

		g_pMain->m_pSound.Play(SND_SHOT1, true, true);

		//To-Do 총구 이펙트가 나와야함..아래 변수 이용하면 될듯?
		//m_ObjGun.m_matWorld._41, m_ObjGun.m_matWorld._42, m_ObjGun.m_matWorld._43

		if(m_bDebugMode == false)
			m_CharHero[m_CurrentHero].get()->m_iBullet -= 1;

		m_Ray.vOrigin = m_pCamera->m_vCameraPos;
		m_Ray.vDirection = m_pCamera->m_vLookVector;
		m_Ray.fExtent = 50.0f;

		for (int i = 0; i < m_CharZombie.size();i++){
			if (m_CharZombie[i].get()->m_bDead == false) {
				if (ChkOBBToRay(&m_CharZombie[i].get()->m_OBB, &m_Ray))
				{
					m_iScore += G_DEFINE_SCORE_BASIC;

					//To-Do 아래 변수를 이용해서 이펙트를 터뜨려야함.
					//m_Select.m_vIntersection

					ChangeZombState(i, G_DEFINE_ANI_ZOMB_DIE);
				}
			}
		}

		for (int i = 0; i < m_CharHero.size(); i++) {

			if (i == m_CurrentHero)
				continue;

			if (m_CharHero[i].get()->m_bDead == true)
				continue;

			if (ChkOBBToRay(&m_CharHero[i].get()->m_OBB, &m_Ray))
			{
				m_CharHero[i].get()->m_iHP -= G_DEFINE_DAMAGE_SHOTGUN_TO_PLAYER;

				if (m_CharHero[i].get()->m_iHP <= 0)
					m_CharHero[i].get()->m_bDead = true;

				if (i == G_HERO_TOM && m_CharHero[i].get()->m_bDead == true)
				{
					GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO1_DIE");

					m_CharHero[i]->Set(pChar1,
						pChar1->m_pBoneObject,
						pChar1->m_pBoneObject->m_Scene.iFirstFrame,
						pChar1->m_pBoneObject->m_Scene.iLastFrame);
				}
				else if (i == G_HERO_JAKE && m_CharHero[i].get()->m_bDead == true)
				{
					GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO2_DIE");

					m_CharHero[i]->Set(pChar1,
						pChar1->m_pBoneObject,
						pChar1->m_pBoneObject->m_Scene.iFirstFrame,
						pChar1->m_pBoneObject->m_Scene.iLastFrame);
				}
			}
		}
	}
	return true;
}
bool GSeqSinglePlay::Frame()
{
	int  iZombieAliveCnt = 0;
	for (int i = 0; i < m_CharZombie.size(); i++) {
		if (m_CharZombie[i].get()->m_bDead == false)
			iZombieAliveCnt++;
	}

	if(iZombieAliveCnt< G_DEFINE_MAX_BASIC_ZOMBIE)
		AddZomb(G_DEFINE_MAX_BASIC_ZOMBIE);



	for (int i = 0; i < m_CharHero.size(); i++) {
		for (int j = 0; j < m_CharZombie.size(); j++) {

			//if (m_CharZombie[j].get()->getState() == G_ZOMB_ST_ATTACK) {
			//	D3DXVECTOR3 vHeroPos, vZombPos;
			//	vHeroPos= D3DXVECTOR3(m_CharHero[i].get()->m_matWorld._41, m_CharHero[i].get()->m_matWorld._42, m_CharHero[i].get()->m_matWorld._43);
			//	vZombPos= D3DXVECTOR3(m_CharZombie[j].get()->m_matWorld._41, m_CharZombie[j].get()->m_matWorld._42, m_CharZombie[j].get()->m_matWorld._43);
			//	if (GBBOXFUNC::CalcDistance(&vHeroPos, &vZombPos) > 100.0f) {
			//		ChangeZombState(j, G_DEFINE_ANI_ZOMB_WLK);
			//	}
			//}
			
			if (GBBOXFUNC::ColCheck(&m_CharHero[i].get()->m_OBB, &m_CharZombie[j].get()->m_OBB)) {
				//ChangeZombState(j, G_DEFINE_ANI_ZOMB_ATT);

				m_CharHero[i].get()->m_iHP -= 1;
			}
			else {
			}
		}

	}




	FrameGame();
	FrameChar();
	FrameMap();
	FrameObj();
	FrameEffect();


	m_UIManager.Frame(&g_pMain->m_SwapChainDesc);

	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_HEALTH])->SetXSize(m_CharHero[0].get()->m_iHP);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_HEALTH])->SetXSize(m_CharHero[1].get()->m_iHP);

	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_BULLET])->SetXSize(m_CharHero[0].get()->m_iBullet);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_BULLET])->SetXSize(m_CharHero[1].get()->m_iBullet);

	FrameGun();
	return true;
}

bool GSeqSinglePlay::Render()
{
	//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	//g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);

#ifdef G_DEFINE_SHADOW
	//그림자 [Start]
	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	g_pMain->GetContext()->PSSetShaderResources(0, 16, pSRVs);

	D3DXVECTOR4 vClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vLookat = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//-----------------------------------------------------
	// 지형 및 오브젝트의 그림자맵 생성
	//-----------------------------------------------------		
	if (m_RT.Begin(g_pImmediateContext, vClearColor))
	{
		D3DXMatrixLookAtLH(&m_matShadowView, &m_vLightPos, &vLookat, &vUp);
		RenderShadow(NULL, &m_matShadowView, &m_matShadowProj);
		m_RT.End(g_pImmediateContext);
	}
	////-----------------------------------------------------
	//// 오브젝트 + 쉐도우 랜더링
	////-----------------------------------------------------	
	RenderObject(m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	////-----------------------------------------------------
	//// 1패스: 지형 + 쉐도우 랜더링
	////-----------------------------------------------------		
	ApplySS(g_pMain->GetContext(), GDxState::g_pSSClampLinear, 1);
	ApplySS(g_pMain->GetContext(), GDxState::g_pSSShadowMap, 2);
	ApplyRS(g_pMain->GetContext(), GDxState::g_pRSBackCullSolid);

	m_CustomMap.SetMatrix(NULL, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	D3DXMATRIX matWVPT = m_matShadowView * m_matShadowProj * m_matTexture;
	D3DXMatrixTranspose(&m_cbShadow.g_matShadow, &matWVPT);
	m_cbShadow.g_ShadowID = 0;
	m_cbShadow.g_iNumKernel = 3;
	g_pMain->GetContext()->UpdateSubresource(m_pShadowConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
	g_pMain->GetContext()->VSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());
	g_pMain->GetContext()->PSSetConstantBuffers(2, 1, m_pShadowConstantBuffer.GetAddressOf());

	m_CustomMap.PreRender(g_pMain->GetContext());
	g_pMain->GetContext()->PSSetShaderResources(1, 1, m_RT.m_pDsvSRV.GetAddressOf());
	m_CustomMap.PostRender(g_pMain->GetContext());

	/////////////////////////////////////////
	// 디버깅
	/////////////////////////////////////////
	if (m_bColorTexRender)
	{
		m_pQuad->SetMatrix(NULL, NULL, NULL);
		m_pQuad->PreRender(g_pMain->GetContext());
		//GetContext()->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
		g_pMain->GetContext()->PSSetShaderResources(0, 1, m_RT.m_pDsvSRV.GetAddressOf());
		m_pQuad->PostRender(g_pMain->GetContext());
	}
	//그림자 [End]
#else
	RenderMap();
	RenderObj();
	RenderChar();
#endif

	RenderGame();
	
	//render UI
	m_UIManager.Render();

	RenderEffect();

	return true;
}
bool GSeqSinglePlay::Release()
{
#ifdef G_DEFINE_SHADOW
	//그림자 [Start]
	SAFE_DEL(m_pQuad);
	//그림자 [End]
#endif

	ReleaseGame();
	ReleaseMap();
	ReleaseObj();
	ReleaseChar();
	ReleaseEffect();
	return true;
}

bool        GSeqSinglePlay::InitGame() {
#ifdef G_MACRO_GAME_ADD
	//EnterCriticalSection(&g_CSd3dDevice);

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



	if (!m_bDebugMode) {
		m_pCamera = m_pFPSCamera[m_CurrentHero].get();
		g_pMain->m_bDebugInfoPrint = false;
		g_pMain->m_bDebugFpsPrint = false;
	}

	else {
		m_pCamera = m_pDebugCamera.get();
		g_pMain->m_bDebugInfoPrint = true;
		g_pMain->m_bDebugFpsPrint = true;
	}

	//LeaveCriticalSection(&g_CSd3dDevice);
#endif
	return true;
};
bool        GSeqSinglePlay::InitMap() {
#ifdef G_MACRO_MAP_ADD


	m_iDrawDepth = 0;
	m_bMapDebugRender = false;

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
	//HeightMap
	m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(m_HeightMap.CreateHeightMap(L"data/HeightTest.bmp")))
	{
		return false;
	}

	m_HeightMap.m_bStaticLight = true;

#ifdef G_DEFINE_SHADOW
	TMapDesc MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//5,5,
		30.0f, 1.0f,
		L"data/Sand.jpg",
		L"data/shader/CustomizeMap_shadow.hlsl" };
#else
	TMapDesc MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//5,5,
		30.0f, 1.0f,
		L"data/Sand.jpg",
		L"data/shader/CustomizeMap_Light.hlsl" };
#endif



	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}
	

	//--------------------------------------------------------------------------------------
	//  쿼드 트리
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(MapDesc.iNumCols, MapDesc.iNumRows);
	m_QuadTree.Update(g_pd3dDevice, m_pCamera);

#endif

	return true;
};
bool		GSeqSinglePlay::InitChar() {
#ifdef G_MACRO_CHAR_ADD
	I_CharMgr.Init();

	Load();


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
	//for (int i = 0; i < G_OBJ_CNT; i++) {
	//	m_Obj[i].Init();
	//}

#ifdef G_DEFINE_SHADOW
	int iIndex = -1;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_LAB, G_SHA_OBJ_SHADOW);			if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_DROPSHIP_LAND, G_SHA_OBJ_SHADOW);	if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_CAR, G_SHA_OBJ_SHADOW);				if (iIndex < 0) return false;
#else
	int iIndex = -1;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_LAB, G_SHA_OBJ_DIFFUSE_REVERSE);			if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_DROPSHIP_LAND, G_SHA_OBJ_SPECULAR, G_LIGHT_TYPE_SPECULAR);	if (iIndex < 0) return false;
	iIndex = I_ObjMgr.Load(g_pd3dDevice, G_OBJ_LOC_CAR, G_SHA_OBJ_SPECULAR, G_LIGHT_TYPE_SPECULAR);				if (iIndex < 0) return false;
#endif



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


	for (int i = 0; i < G_OBJ_CNT; i++) {

		m_matObjOBB[i] = m_matObjScl[i] * m_matObjRot[i] * m_matObjTrans[i];
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
	
	m_fPlayTime = (int)g_fDurationTime;

	if (!m_bDebugMode)
		ShowCursor(false); // 커서를 화면에서 감추기
	else {
		ShowCursor(true);
	}

	//디버그 모드 토글
	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_UP) {

		if (m_bDebugMode) {
			m_bDebugMode = false;
			g_pMain->ClipMouse(true);
			m_pCamera = m_pFPSCamera[m_CurrentHero].get();
			g_pMain->m_bDebugInfoPrint = false;
			g_pMain->m_bDebugFpsPrint = false;
		}
		else {
			m_bDebugMode = true;
			g_pMain->ClipMouse(false);
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
		m_bDebugMode = false;
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
		m_bMapDebugRender = !m_bMapDebugRender;
	}
	if (I_Input.KeyCheck(DIK_GRAVE) == KEY_UP) //문턱값 사용 ~
	{
		m_QuadTree.SetThresHold(!m_QuadTree.m_bThresHoldValue);
	}
	
	m_QuadTree.Frame();	

	m_HeightMap.Frame();
	g_pImmediateContext->UpdateSubresource(
		m_HeightMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_HeightMap.m_VertexList.at(0), 0, 0);
#endif
	return true;
};
void		GSeqSinglePlay::ChangeZombState(int iNum, G_ZOMB_ST state) {

	m_CharZombie[iNum]->setState(state);

	int iState = state;
	
	GCharacter* pChar0;

	switch (iState) {
	case 	G_ZOMB_ST_WALK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_IDL);
	}
		break;
	case 	G_ZOMB_ST_IDLE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_WLK);
	}
		break;
	case 	G_ZOMB_ST_ATTACK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_ATT);
	}
		break;
	case 	G_ZOMB_ST_DEAD: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_DIE);
	}
		break;
	}

	m_CharZombie[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}
void		GSeqSinglePlay::ChangeZombState(int iNum, TCHAR* str) {

	//GCharacter* pChar0 = I_CharMgr.GetPtr(str);
	auto pChar0 = I_CharMgr.GetPtr(str);

	m_CharZombie[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

	if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_DIE)) {
		m_CharZombie[iNum]->setState(G_ZOMB_ST_DEAD);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_ATT)) {
		m_CharZombie[iNum]->setState(G_ZOMB_ST_ATTACK);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_WLK)) {
		m_CharZombie[iNum]->setState(G_ZOMB_ST_WALK);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_IDL)) {
		m_CharZombie[iNum]->setState(G_ZOMB_ST_IDLE);
	}
	else {
		m_CharZombie[iNum]->setState(G_ZOMB_ST_IDLE);
	}





}
bool		GSeqSinglePlay::FrameChar() {
#ifdef G_MACRO_CHAR_ADD

	D3DXMATRIX matHeroWld[G_HERO_CNT];
	D3DXMATRIX matHeroScl[G_HERO_CNT];
	D3DXMATRIX matHeroRot[G_HERO_CNT];
	D3DXMATRIX matHeroTrans[G_HERO_CNT];

	for (int iChar = 0; iChar < m_CharHero.size(); iChar++) {
		D3DXMatrixIdentity(&matHeroWld[iChar]);
		D3DXMatrixIdentity(&matHeroScl[iChar]);
		D3DXMatrixIdentity(&matHeroRot[iChar]);
		D3DXMatrixIdentity(&matHeroTrans[iChar]);
		D3DXMatrixTranslation(&matHeroTrans[iChar], m_pFPSCamera[iChar].get()->m_vCameraPos.x, G_DEFINE_CHAR_Y_POS_OFFSET, m_pFPSCamera[iChar].get()->m_vCameraPos.z);
		matHeroRot[iChar] = m_pFPSCamera[iChar].get()->GetRotMatY();

		matHeroWld[iChar] = matHeroScl[iChar] * matHeroRot[iChar] * matHeroTrans[iChar];

		m_CharHero[iChar]->m_matWorld = matHeroWld[iChar];
	}

	for (int iChar = 0; iChar < m_CharHero.size(); iChar++)
	{
		m_CharHero[iChar]->Frame();
	}

	int iChange = 0;

	if (I_Input.KeyCheck(DIK_F11) == KEY_UP)
	{
		for (int i = 0; i < m_CharZombie.size(); i++){
			iChange = m_CharZombie[i]->getState();

			//if (m_CharZombie[i]->m_bDead == true)
			//	m_CharZombie[i]->setState(G_ZOMB_ST_WALK);
			
			if (m_CharZombie[i]->m_bDead == true)
				continue;

			if (iChange != G_ZOMB_ST_DEAD) {
				iChange++;
			}
			else {
				iChange = G_ZOMB_ST_WALK;
			}

			switch (iChange) {
			case G_ZOMB_ST_DEAD:
			{
				ChangeZombState(i, G_DEFINE_ANI_ZOMB_DIE);
			}
			break;
			case G_ZOMB_ST_ATTACK:
			{
				ChangeZombState(i, G_DEFINE_ANI_ZOMB_ATT);
			}
			break;
			case G_ZOMB_ST_WALK:
			{
				ChangeZombState(i, G_DEFINE_ANI_ZOMB_WLK);
			}
			break;
			case G_ZOMB_ST_IDLE:
			{
				ChangeZombState(i, G_DEFINE_ANI_ZOMB_IDL);
			}
			break;
			}
		}
	}


	for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
	{
		m_CharZombie[iChar]->Frame();
	}

	if (I_Input.KeyCheck(DIK_F12) == KEY_UP)
	{
		for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
		{
			m_CharZombie[iChar]->m_bBoneRender = !m_CharZombie[iChar]->m_bBoneRender;
		}
	}

	//if (I_Input.KeyCheck(DIK_F9) == KEY_UP)
	//{
	//	Load();
	//}
#endif
	return true;
};
bool		GSeqSinglePlay::FrameObj() {
#ifdef G_MACRO_MAP_ADD
	m_Objbit.reset();

	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		if(m_Obj[i]->m_LightType == G_LIGHT_TYPE_SPECULAR)
		{
			//스페큘러 값 업데이트를 위해..
			m_Obj[i]->m_cbLight.g_vEyeDir.x = m_pCamera->m_vLookVector.x;
			m_Obj[i]->m_cbLight.g_vEyeDir.y = m_pCamera->m_vLookVector.y;
			m_Obj[i]->m_cbLight.g_vEyeDir.z = m_pCamera->m_vLookVector.z;
		}
		m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_Obj[i]->Frame();

		if (m_pCamera->CheckOBBInPlane(&(((GGbsObj*)m_Obj[i])->m_OBB)))
		{
			m_Objbit.set(i);
		}
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


	if(g_pMain->m_bDebugInfoPrint){
		RECT rc;
		rc.top = g_pMain->m_DefaultRT.m_vp.Height/2;
		rc.bottom = g_pMain->m_DefaultRT.m_vp.Height;
		rc.left = 0;
		rc.right = g_pMain->m_DefaultRT.m_vp.Width;

		_stprintf_s(m_pTextOutBuffer, L"PlayTime : %d", m_fPlayTime);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		rc.top += G_MACRO_DEBUG_STR_INTERVAL;

		_stprintf_s(m_pTextOutBuffer, _T("Score : %d"), m_iScore);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		rc.top += G_MACRO_DEBUG_STR_INTERVAL;

		_stprintf_s(m_pTextOutBuffer, _T("Tom HP : %d"), m_CharHero[G_HERO_TOM].get()->m_iHP);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		rc.top += G_MACRO_DEBUG_STR_INTERVAL;

		_stprintf_s(m_pTextOutBuffer, _T("Tom Bullet : %d"), m_CharHero[G_HERO_TOM].get()->m_iBullet);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		rc.top += G_MACRO_DEBUG_STR_INTERVAL;

		_stprintf_s(m_pTextOutBuffer, _T("Jake HP : %d"), m_CharHero[G_HERO_JAKE].get()->m_iHP);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		rc.top += G_MACRO_DEBUG_STR_INTERVAL;

		_stprintf_s(m_pTextOutBuffer, _T("Jake Bullet : %d"), m_CharHero[G_HERO_JAKE].get()->m_iBullet);
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	}
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

	m_HeightMap.SetMatrix(m_pCamera->GetWorldMatrix(), m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	m_HeightMap.Render(g_pImmediateContext);

	DrawSelectTreeLevel(m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	if (m_bMapDebugRender)
	{
		DrawQuadLine(m_QuadTree.m_pRootNode);
	}



#endif
	return true;
};

bool		GSeqSinglePlay::RenderChar() {
#ifdef G_MACRO_CHAR_ADD
	//D3DXMATRIX matCharWld;
	//matCharWld = m_matWorld;
	//matCharWld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;



	for (int iChar = 0; iChar < m_CharHero.size(); iChar++)
	{
		if (iChar == m_CurrentHero && m_bDebugMode==false)
			continue;

		m_CharHero[iChar].get()->SetMatrix(&m_CharHero[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharHero[iChar].get()->Render(g_pImmediateContext);
	}

	for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_CharZombie[iChar]->SetMatrix(&m_CharZombie[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharZombie[iChar]->Render(g_pImmediateContext);
	}

	if(m_bDebugMode){
		for (int iChar = 0; iChar < m_CharZombie.size(); iChar++) {
			m_CharZombie[iChar].get()->m_OBB.Render(&m_CharZombie[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
		for (int iChar = 0; iChar < m_CharHero.size(); iChar++) {
			m_CharHero[iChar].get()->m_OBB.Render(&m_CharHero[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
	}

#endif
	return true;
};
bool		GSeqSinglePlay::RenderObj() {
#ifdef G_MACRO_MAP_ADD
	for (int i = 0; i < G_OBJ_CNT; i++)
	{
		D3DXMATRIX mat = m_Obj[i]->m_matWorld;

		if (m_Objbit[i])
		{
			m_Obj[i]->SetMatrix(&m_matObjWld[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
			m_Obj[i]->Render(g_pImmediateContext);
		}

		if(m_bDebugMode)
			((GGbsObj*)m_Obj[i])->m_OBB.Render(&m_matObjOBB[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
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


#ifdef G_DEFINE_TOMLEE_TEST
	D3DXMATRIX matEffectWld, matScl,matRot,matTrans,matViewInv;
	D3DXMatrixIdentity(&matEffectWld);
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);

	D3DXMatrixScaling(&matScl, 10.0f, 10.0f, 10.0f);
	D3DXMatrixTranslation(&matTrans, m_pCamera->m_vCameraPos.x, m_pCamera->m_vCameraPos.y+40.0f, m_pCamera->m_vCameraPos.z+50.0f);

	D3DXMatrixInverse(&matViewInv, NULL, m_pCamera->GetViewMatrix());
	matEffectWld = matScl * matRot * matTrans * matViewInv;
#else
	D3DXMATRIX matEffectWld;
	matEffectWld = m_matWorld;
	matEffectWld._42 = 10.0f;
#endif
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
	
	m_HeightMap.Release();
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
	//for (int i = 0; i < G_OBJ_CNT; i++) {
	//	m_Obj[i].Release();
	//}
	I_ObjMgr.Release();
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

void GSeqSinglePlay::AddZomb(int iNum) {
	srand(time(NULL));

	for (int i = 0; i < iNum; i++) {
		auto pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

		shared_ptr<GN2Zombie> pObjA = make_shared<GN2Zombie>();
		pObjA.get()->setState(G_ZOMB_ST_WALK);

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);
	
		int iX = (rand() % 1000) - 100;
		int iZ = (rand() % 1000) - 100;

		if (iX >= 0)
			iX += 300;
		if (iX < 0)
			iX -= 300;

		if (iZ >= 0)
			iZ += 300;
		if (iZ < 0)
			iZ -= 300;

		D3DXMatrixTranslation(&pObjA->m_matWorld, float(iX), 0.0f, float(iZ));
		pObjA->m_OBB.Init(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);

		m_CharZombie.push_back(pObjA);
	}
}
bool GSeqSinglePlay::Load()
{
#ifdef G_DEFINE_SHADOW
	//좀비 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie_shadow.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	AddZomb(G_DEFINE_MAX_BASIC_ZOMBIE);


	//주인공1 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharHero1_shadow.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO1_IDLE");


	shared_ptr<GHero> pObjB = make_shared<GHero>();
	pObjB->Set(pChar1,
		pChar1->m_pBoneObject,
		pChar1->m_pBoneObject->m_Scene.iFirstFrame,
		pChar1->m_pBoneObject->m_Scene.iLastFrame);

	pObjB->Init();

	m_CharHero.push_back(pObjB);

	//주인공2 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharHero2_shadow.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar2 = I_CharMgr.GetPtr(L"HERO2_IDLE");


	shared_ptr<GHero> pObjC = make_shared<GHero>();
	pObjC->Set(pChar2,
		pChar2->m_pBoneObject,
		pChar2->m_pBoneObject->m_Scene.iFirstFrame,
		pChar2->m_pBoneObject->m_Scene.iLastFrame);

	pObjC->Init();

	pObjC.get()->m_HeroType = G_HERO_JAKE;
	m_CharHero.push_back(pObjC);


	for (int i = 0; i < m_CharHero.size(); i++) {
		m_CharHero[i].get()->m_iBullet = 100;
		m_CharHero[i].get()->m_iHP = 100;
		m_CharHero[i].get()->m_OBB.Init(m_CharHero[i].get()->m_pChar->m_vMin, m_CharHero[i].get()->m_pChar->m_vMax);
	}
#else
	//좀비 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	AddZomb(G_DEFINE_MAX_BASIC_ZOMBIE);


	//주인공1 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharHero1.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO1_IDLE");


	shared_ptr<GHero> pObjB = make_shared<GHero>();
	pObjB->Set(pChar1,
		pChar1->m_pBoneObject,
		pChar1->m_pBoneObject->m_Scene.iFirstFrame,
		pChar1->m_pBoneObject->m_Scene.iLastFrame);

	pObjB->Init();

	m_CharHero.push_back(pObjB);

	//주인공2 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharHero2.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar2 = I_CharMgr.GetPtr(L"HERO2_IDLE");


	shared_ptr<GHero> pObjC = make_shared<GHero>();
	pObjC->Set(pChar2,
		pChar2->m_pBoneObject,
		pChar2->m_pBoneObject->m_Scene.iFirstFrame,
		pChar2->m_pBoneObject->m_Scene.iLastFrame);

	pObjC->Init();

	pObjC.get()->m_HeroType = G_HERO_JAKE;
	m_CharHero.push_back(pObjC);


	for (int i = 0; i < m_CharHero.size(); i++) {
		m_CharHero[i].get()->m_iBullet = 100;
		m_CharHero[i].get()->m_iHP = 100;
		m_CharHero[i].get()->m_OBB.Init(m_CharHero[i].get()->m_pChar->m_vMin, m_CharHero[i].get()->m_pChar->m_vMax);
	}
#endif
	
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
#ifdef G_DEFINE_SHADOW
	//그림자 [Start]
	SAFE_ZERO(m_pQuad);
	m_bColorTexRender = true;
	//그림자 [End]
#endif
	memset(m_pTextOutBuffer, 0, sizeof(TCHAR) * 256);

	m_iScore = 0;
	m_fPlayTime = 0.0f;
	m_CurrentHero = G_HERO_TOM;
	m_bDebugMode = false;
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





