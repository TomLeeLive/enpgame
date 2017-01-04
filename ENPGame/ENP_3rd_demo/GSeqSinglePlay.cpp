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
#ifdef G_MACRO_AI_ADD
//bool GSeqSinglePlay::JakeAI()
//{
//	D3DXVECTOR3 vPosTom,vPosJake,vLook_toTom, vTRans_toTom;
//
//	vPosTom = D3DXVECTOR3(m_CharHero[0]->m_matWorld._41, m_CharHero[0]->m_matWorld._42, m_CharHero[0]->m_matWorld._43);
//	vPosJake = D3DXVECTOR3(m_CharHero[1]->m_matWorld._41, m_CharHero[1]->m_matWorld._42, m_CharHero[1]->m_matWorld._43);
//
//	D3DXMATRIX matRot, matTrans;
//	D3DXMatrixIdentity(&matRot);
//	//D3DXMatrixIdentity(&matTrans);
//
//	vLook_toTom = vPosJake - vPosTom;
//
//	D3DXVec3Normalize(&vLook_toTom, &vLook_toTom);
//	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	D3DXVec3Cross(&vRight, &vUp, &vLook_toTom);
//	D3DXVec3Cross(&vUp, &vLook_toTom, &vRight);
//
//	matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
//	matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
//	matRot._31 = vLook_toTom.x;		matRot._32 = vLook_toTom.y;		matRot._33 = vLook_toTom.z;
//
//
//	vTRans_toTom = vPosJake - vLook_toTom *1000.0f * g_fSecPerFrame;	
//	D3DXMatrixTranslation(&matTrans, vTRans_toTom.x, vTRans_toTom.y, vTRans_toTom.z);
//
//	m_CharHero[1]->m_matWorld = matRot * matTrans;
//	return true;
//}
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

	I_GameEvent.init();

	m_ObjGun.Init();

	m_ObjGun.m_bAniLoop = false;


	if (!m_ObjGun.Load(g_pd3dDevice, G_OBJ_LOC_FPS_SHOTGUN, G_SHA_OBJ_SPECULAR, G_LIGHT_TYPE_SPECULAR))
	{
		return false;
	}

	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	//디버그 카메라.
	m_pDebugCamera = make_shared<GCamera>();
	m_pDebugCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pDebugCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);
	//이벤트용 카메라.
	m_pEventCamera = make_shared<GCamera>();
	m_pEventCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pEventCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);



	for (int i = 0; i < G_HERO_CNT; i++) {
		auto FPSCamera = make_shared<GFPSCamera>();
		fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
		FPSCamera.get()->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
		FPSCamera.get()->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);
		m_pFPSCamera.push_back(FPSCamera);
	}


	



	InitChar();
	InitGame();
	InitEffect();
	InitMap();
	InitObj();

	return true;
}

void GSeqSinglePlay::CheckHeroDead(int iChar){

	if (m_CharHero[iChar].get()->m_iHP <= 0 && false == m_CharHero[iChar].get()->m_bDead ){

		m_CharHero[iChar].get()->m_bDead = true;

		if (iChar == 1)
			g_pMain->m_pSound.Play(SND_DEAD_PLAYER_1, true, false);
		else
			g_pMain->m_pSound.Play(SND_DEAD_PLAYER_2, true, false);

		if (iChar == G_HERO_TOM /*&& m_CharHero[iChar].get()->m_bDead == true*/)
		{
			GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO1_DIE");

			m_CharHero[iChar]->Set(pChar1,
				pChar1->m_pBoneObject,
				pChar1->m_pBoneObject->m_Scene.iFirstFrame,
				pChar1->m_pBoneObject->m_Scene.iLastFrame);
		}
		else if (iChar == G_HERO_JAKE /*&& m_CharHero[iChar].get()->m_bDead == true*/)
		{
			GCharacter* pChar1 = I_CharMgr.GetPtr(L"HERO2_DIE");

			m_CharHero[iChar]->Set(pChar1,
				pChar1->m_pBoneObject,
				pChar1->m_pBoneObject->m_Scene.iFirstFrame,
				pChar1->m_pBoneObject->m_Scene.iLastFrame);
		}
	}
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

#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
		UpdateGunEffectPosition();
#endif
#endif

		if(m_bDebugMode == false)
			m_CharHero[m_CurrentHero].get()->m_iBullet -= 1;

		m_Ray.vOrigin = m_pCamera->m_vCameraPos;
		m_Ray.vDirection = m_pCamera->m_vLookVector;
		m_Ray.fExtent = 50.0f;

#ifdef G_MACRO_AI_ADD
		list<shared_ptr<GNewZombie>>::iterator _F = m_GAIZombMgr.m_Zomb.begin();
		list<shared_ptr<GNewZombie>>::iterator _L = m_GAIZombMgr.m_Zomb.end();
		for (; _F != _L; ++_F)
		{

			if ((*_F)->m_bDead == false) {
				if (ChkOBBToRay(&(*_F)->m_OBB, &m_Ray))
				{
					m_iScore += G_DEFINE_SCORE_BASIC;

					//To-Do 아래 변수를 이용해서 이펙트를 터뜨려야함.
					//m_Select.m_vIntersection
					g_pMain->m_pSound.Play(SND_DEAD_ZOMBIE, true, false);
					(*_F)->ChangeZombState((*_F).get(), G_DEFINE_ANI_ZOMB_DIE);
				}
			}	
		}
#else
		for (int i = 0; i < m_CharZombie.size();i++) {
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
#endif


		for (int i = 0; i < m_CharHero.size(); i++) {

			if (i == m_CurrentHero)
				continue;

			if (m_CharHero[i].get()->m_bDead == true)
				continue;

			if (ChkOBBToRay(&m_CharHero[i].get()->m_OBB, &m_Ray))
			{
				m_CharHero[i].get()->m_iHP -= G_DEFINE_DAMAGE_SHOTGUN_TO_PLAYER;
				//hero dead 체크.
				CheckHeroDead(i);
			}
		}
	}
	return true;
}
bool GSeqSinglePlay::Frame()
{


	m_pCamera->Frame();

	if (!m_bGameOver) {
		FrameGun();
	}

	FrameGame();
	FrameChar();
	FrameMap();
	FrameObj();
	FrameEffect();
	

#ifdef G_MACRO_AI_ADD
	//JakeAI();
	int  iZombieAliveCnt = 0;

	list<shared_ptr<GNewZombie>>::iterator _F = m_GAIZombMgr.m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_GAIZombMgr.m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		if ((*_F)->m_bDead == false)
			iZombieAliveCnt++;
	}

	if (iZombieAliveCnt< G_DEFINE_MAX_BASIC_ZOMBIE)
		AddZomb(G_DEFINE_MAX_BASIC_ZOMBIE);


	_F = m_GAIZombMgr.m_Zomb.begin();
	_L = m_GAIZombMgr.m_Zomb.end();

	for (int i = 0; i < m_CharHero.size(); i++) {

		for (; _F != _L; ++_F)
		{
			if (GBBOXFUNC::ColCheck(&m_CharHero[i].get()->m_OBB, &(*_F)->m_OBB) && (*_F)->m_pChar->m_bAttack == true) {

				m_CharHero[i].get()->m_iHP -= G_DEFINE_DAMAGE_SHOTGUN_TO_PLAYER;

				g_pMain->m_pSound.Play(SND_HIT_BY_ZOMBIE, true, false);

				//좀비 애니메이션 리셋
				{
					(*_F)->m_pChar->m_iCurrentFrame = (*_F)->m_pChar->m_iStartFrame;
					(*_F)->m_pChar->m_fFrame = (float)(*_F)->m_pChar->m_iStartFrame + (*_F)->m_pChar->m_fLerpTime;
				}

				//hero dead 체크.
				CheckHeroDead(i);
			}
			else {
			}
		}

	}
#else
	int  iZombieAliveCnt = 0;
	for (int i = 0; i < m_CharZombie.size(); i++) {
		if (m_CharZombie[i].get()->m_bDead == false)
			iZombieAliveCnt++;
	}

	if (iZombieAliveCnt< G_DEFINE_MAX_BASIC_ZOMBIE)
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
#endif

	m_UIManager.Frame(&g_pMain->m_SwapChainDesc);

	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_HEALTH])->SetXSize(m_CharHero[0].get()->m_iHP);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_HEALTH])->SetXSize(m_CharHero[1].get()->m_iHP);

	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_BULLET])->SetXSize(m_CharHero[0].get()->m_iBullet);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_BULLET])->SetXSize(m_CharHero[1].get()->m_iBullet);

	m_UIManager.m_pUIList[G_DEFINE_UI_CROSSHAIR]->m_bRender = !m_bGameOver;
	m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER]->m_bRender = m_bGameOver;

	m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING]->m_bRender = m_bChatting;
	m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_SPACE]->m_bRender = m_bChatting;



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


	if (m_bChatting) {
		//글자 출력한다.
		RECT rc;
		rc.top = g_pMain->m_DefaultRT.m_vp.Height / 3 * 2;
		rc.bottom = g_pMain->m_DefaultRT.m_vp.Height;
		rc.left = 0;
		rc.right = g_pMain->m_DefaultRT.m_vp.Width;


		_stprintf_s(m_pTextOutBuffer, L"%s", I_GameEvent.m_vecEvent[m_iEventNum]->m_vecScript[m_iScriptNum]->m_Str.c_str());
		g_pMain->DrawDebugRect(&rc, m_pTextOutBuffer, DWRITE_TEXT_ALIGNMENT_CENTER, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	}


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

	for (int iEvent = 0; iEvent < I_GameEvent.m_vecEvent.size(); iEvent++)
		I_GameEvent.m_vecEvent[iEvent]->m_bDone = false;

	((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_IMG])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_IMG])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

	m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
	m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
	m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_YELLOW_BTN]->m_bRender = false;
	m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_SPACE]->m_bRender = false;
	m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_TO_MENU_TEXT]->m_bRender = false;

	D3DXMatrixIdentity(&m_matWorld);

	m_pDebugCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 2500.0f, -2500.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	m_pEventCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 2500.0f, -2500.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	
	for (int i = 0; i < m_pFPSCamera.size(); i++) {

		m_pFPSCamera[i].get()->SetViewMatrix(D3DXVECTOR3(G_DEFINE_HERO_1_POS_X + i*100.0f, G_DEFINE_HERO_1_POS_Y, G_DEFINE_HERO_1_POS_Z)
			, D3DXVECTOR3(-10.0f, 10.0f, 50.0f));
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

	GCharacter* pChar[2];
	pChar[0] = I_CharMgr.GetPtr(L"HERO1_IDLE");
	pChar[1] = I_CharMgr.GetPtr(L"HERO2_IDLE");

	for (int i = 0; i < m_CharHero.size(); i++) {
		m_CharHero[i]->Set(pChar[i], 
			pChar[i]->m_pBoneObject,
			pChar[i]->m_pBoneObject->m_Scene.iFirstFrame,
			pChar[i]->m_pBoneObject->m_Scene.iLastFrame);
		
		m_CharHero[i]->m_pChar->Init();

		m_CharHero[i].get()->m_bDead = false;
		m_CharHero[i].get()->m_iBullet = 100;
		m_CharHero[i].get()->m_iHP = 100;
		m_CharHero[i].get()->m_OBB.Init(m_CharHero[i].get()->m_pChar->m_vMin, m_CharHero[i].get()->m_pChar->m_vMax);
	}





	//좀비 로드
	m_GAIZombMgr.m_Zomb.clear();

	AddZomb(G_DEFINE_MAX_BASIC_ZOMBIE);


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
	if (FAILED(m_HeightMap.CreateHeightMap(L"data/map/HeightTest.bmp")))
	{
		return false;
	}

	m_HeightMap.m_bStaticLight = true;

#ifdef G_DEFINE_SHADOW
	TMapDesc MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//5,5,
		30.0f, 1.0f,
		L"data/map/Sand.jpg",
		L"data/shader/CustomizeMap_shadow.hlsl" };
#else
	TMapDesc MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//5,5,
		20.0f, 1.0f,
		L"data/map/Sand.jpg",
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


	//---------------------------------------------------------------------------
	// Map Boudery
	//---------------------------------------------------------------------------
	//앞
	m_Wall[G_BB_WALL1].Init(D3DXVECTOR3(-4500.0f, 0.0f, -4500.0f), D3DXVECTOR3(4500.0f, 1000.0f, -4500.0f));
	//뒤
	m_Wall[G_BB_WALL2].Init(D3DXVECTOR3(-4500.0f, 0.0f, 4500.0f), D3DXVECTOR3(4500.0f, 1000.0f, 4500.0f));
	//좌
	m_Wall[G_BB_WALL3].Init(D3DXVECTOR3(-4500.0f, 0.0f, -4500.0f), D3DXVECTOR3(-4500.0f, 1000.0f, 4500.0f));
	//우
	m_Wall[G_BB_WALL4].Init(D3DXVECTOR3(4500.0f, 0.0f, -4500.0f), D3DXVECTOR3(4500.0f, 1000.0f, 4500.0f));
	for (int i = 0; i < G_BB_CNT; i++)
	{
		D3DXMatrixIdentity(&m_matWallBB[i]);
	}

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
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB], -4000.0f, 0.0f, -4000.0f);
	m_matObjWld[G_OBJ_LAB] = m_matObjScl[G_OBJ_LAB] * m_matObjRot[G_OBJ_LAB] * m_matObjTrans[G_OBJ_LAB];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB])->m_OBB.Init(G_DEFINE_OBB_LAB);

	//드롭십 로드
	m_Obj[G_OBJ_DROPSHIP] = I_ObjMgr.GetPtr(G_OBJ_NAME_DROPSHIP_LAND);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_DROPSHIP],3.f, 3.f, 3.f);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_DROPSHIP], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_DROPSHIP], 4000.0f, 0.0f, 4000.0f);
	m_matObjWld[G_OBJ_DROPSHIP] = m_matObjScl[G_OBJ_DROPSHIP] * m_matObjRot[G_OBJ_DROPSHIP] * m_matObjTrans[G_OBJ_DROPSHIP];
	//드롭십 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_DROPSHIP])->m_OBB.Init(G_DEFINE_OBB_DROPSHIP_LAND);

	//차량1 로드
	m_Obj[G_OBJ_CAR1] = I_ObjMgr.GetPtr(G_OBJ_NAME_CAR);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR1], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR1], 500.0f, 0.0f, -700.0f);
	m_matObjWld[G_OBJ_CAR1] = m_matObjScl[G_OBJ_CAR1] * m_matObjRot[G_OBJ_CAR1] * m_matObjTrans[G_OBJ_CAR1];
	//드롭십 차량1 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_CAR1])->m_OBB.Init(G_DEFINE_OBB_CAR);

	//차량2 로드
	m_Obj[G_OBJ_CAR2] = I_ObjMgr.GetPtr(G_OBJ_NAME_CAR);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_CAR2], 0.3, 0.3, 0.3);
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_CAR2], -900.0f, 0.0f, 700.0f);
	m_matObjWld[G_OBJ_CAR2] = m_matObjScl[G_OBJ_CAR2] * m_matObjRot[G_OBJ_CAR2] * m_matObjTrans[G_OBJ_CAR2];
	//드롭십 차량2 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_CAR2])->m_OBB.Init(G_DEFINE_OBB_CAR);

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
	((GGbsObj*)m_Obj[G_OBJ_LAB1])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 2
	m_Obj[G_OBJ_LAB2] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB2], 4, 1.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB2], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB2], 2000.0f, 0.0f, 2100.0f);
	m_matObjWld[G_OBJ_LAB2] = m_matObjScl[G_OBJ_LAB2] * m_matObjRot[G_OBJ_LAB2] * m_matObjTrans[G_OBJ_LAB2];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB2])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 3
	m_Obj[G_OBJ_LAB3] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB3], 3.5, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB3], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB3], 2000.0f, 0.0f, 2800.0f);
	m_matObjWld[G_OBJ_LAB3] = m_matObjScl[G_OBJ_LAB3] * m_matObjRot[G_OBJ_LAB3] * m_matObjTrans[G_OBJ_LAB3];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB3])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 4 
	m_Obj[G_OBJ_LAB4] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB4], 10, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB4], D3DXToRadian(270.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB4], 2000.0f, 0.0f, 4000.0f);
	m_matObjWld[G_OBJ_LAB4] = m_matObjScl[G_OBJ_LAB4] * m_matObjRot[G_OBJ_LAB4] * m_matObjTrans[G_OBJ_LAB4];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB4])->m_OBB.Init(G_DEFINE_OBB_LAB);

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
	((GGbsObj*)m_Obj[G_OBJ_LAB5])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 6  
	m_Obj[G_OBJ_LAB6] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB6], 2, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB6], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB6], 750.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB6] = m_matObjScl[G_OBJ_LAB6] * m_matObjRot[G_OBJ_LAB6] * m_matObjTrans[G_OBJ_LAB6];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB6])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 7 
	m_Obj[G_OBJ_LAB7] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB7], 4, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB7], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB7], 200.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB7] = m_matObjScl[G_OBJ_LAB7] * m_matObjRot[G_OBJ_LAB7] * m_matObjTrans[G_OBJ_LAB7];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB7])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 8
	m_Obj[G_OBJ_LAB8] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB8], 4, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB8], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB8], -550.0f, 0.0f, 1250.0f);
	m_matObjWld[G_OBJ_LAB8] = m_matObjScl[G_OBJ_LAB8] * m_matObjRot[G_OBJ_LAB8] * m_matObjTrans[G_OBJ_LAB8];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB8])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 9
	m_Obj[G_OBJ_LAB9] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB9], 3, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB9], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB9], -1200.0f, 0.0f, 1200.0f);
	m_matObjWld[G_OBJ_LAB9] = m_matObjScl[G_OBJ_LAB9] * m_matObjRot[G_OBJ_LAB9] * m_matObjTrans[G_OBJ_LAB9];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB9])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 10
	m_Obj[G_OBJ_LAB10] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB10], 2.7, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB10], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB10], -1700.0f, 0.0f, 1100.0f);
	m_matObjWld[G_OBJ_LAB10] = m_matObjScl[G_OBJ_LAB10] * m_matObjRot[G_OBJ_LAB10] * m_matObjTrans[G_OBJ_LAB10];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB10])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 11
	m_Obj[G_OBJ_LAB11] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB11], 4, 2.3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB11], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB11], -2300.0f, 0.0f, 1000.0f);
	m_matObjWld[G_OBJ_LAB11] = m_matObjScl[G_OBJ_LAB11] * m_matObjRot[G_OBJ_LAB11] * m_matObjTrans[G_OBJ_LAB11];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB11])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 12
	m_Obj[G_OBJ_LAB12] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB12], 3, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB12], D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB12], -2950.0f, 0.0f, 900.0f);
	m_matObjWld[G_OBJ_LAB12] = m_matObjScl[G_OBJ_LAB12] * m_matObjRot[G_OBJ_LAB12] * m_matObjTrans[G_OBJ_LAB12];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB12])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 13
	m_Obj[G_OBJ_LAB13] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB13], 4, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB13], D3DXToRadian(315.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB13], -3600.0f, 0.0f, 550.0f);
	m_matObjWld[G_OBJ_LAB13] = m_matObjScl[G_OBJ_LAB13] * m_matObjRot[G_OBJ_LAB13] * m_matObjTrans[G_OBJ_LAB13];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB13])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 14
	m_Obj[G_OBJ_LAB14] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB14], 6, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB14], D3DXToRadian(315.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB14], -4250.0f, 0.0f, -100.0f);
	m_matObjWld[G_OBJ_LAB14] = m_matObjScl[G_OBJ_LAB14] * m_matObjRot[G_OBJ_LAB14] * m_matObjTrans[G_OBJ_LAB14];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB14])->m_OBB.Init(G_DEFINE_OBB_LAB);
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
	((GGbsObj*)m_Obj[G_OBJ_LAB16])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 17 
	m_Obj[G_OBJ_LAB17] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB17], 2, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB17], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB17], 2250.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB17] = m_matObjScl[G_OBJ_LAB17] * m_matObjRot[G_OBJ_LAB17] * m_matObjTrans[G_OBJ_LAB17];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB17])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 18 
	m_Obj[G_OBJ_LAB18] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB18], 4, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB18], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB18], 1700.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB18] = m_matObjScl[G_OBJ_LAB18] * m_matObjRot[G_OBJ_LAB18] * m_matObjTrans[G_OBJ_LAB18];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB18])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 19
	m_Obj[G_OBJ_LAB19] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB19], 4, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB19], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB19], 950.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB19] = m_matObjScl[G_OBJ_LAB19] * m_matObjRot[G_OBJ_LAB19] * m_matObjTrans[G_OBJ_LAB19];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB19])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 20
	m_Obj[G_OBJ_LAB20] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB20], 3, 2.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB20], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB20], 300.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB20] = m_matObjScl[G_OBJ_LAB20] * m_matObjRot[G_OBJ_LAB20] * m_matObjTrans[G_OBJ_LAB20];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB20])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 21
	m_Obj[G_OBJ_LAB21] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB21], 2.7, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB21], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB21], -200.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB21] = m_matObjScl[G_OBJ_LAB21] * m_matObjRot[G_OBJ_LAB21] * m_matObjTrans[G_OBJ_LAB21];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB21])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 22
	m_Obj[G_OBJ_LAB22] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB22], 4, 2.3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB22], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB22], -800.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB22] = m_matObjScl[G_OBJ_LAB22] * m_matObjRot[G_OBJ_LAB22] * m_matObjTrans[G_OBJ_LAB22];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB22])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 23
	m_Obj[G_OBJ_LAB23] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB23], 3, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB23], D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB23], -1450.0f, 0.0f, -1250.0f);
	m_matObjWld[G_OBJ_LAB23] = m_matObjScl[G_OBJ_LAB23] * m_matObjRot[G_OBJ_LAB23] * m_matObjTrans[G_OBJ_LAB23];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB23])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 24
	m_Obj[G_OBJ_LAB24] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB24], 4, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB24], D3DXToRadian(135.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB24], 3480.0f, 0.0f, -250.0f);
	m_matObjWld[G_OBJ_LAB24] = m_matObjScl[G_OBJ_LAB24] * m_matObjRot[G_OBJ_LAB24] * m_matObjTrans[G_OBJ_LAB24];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB24])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 25
	m_Obj[G_OBJ_LAB25] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB25], 7, 3, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB25], D3DXToRadian(135.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB25], 4250.0f, 0.0f, 450.0f);
	m_matObjWld[G_OBJ_LAB25] = m_matObjScl[G_OBJ_LAB25] * m_matObjRot[G_OBJ_LAB25] * m_matObjTrans[G_OBJ_LAB25];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB25])->m_OBB.Init(G_DEFINE_OBB_LAB);

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
	((GGbsObj*)m_Obj[G_OBJ_LAB15])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 26
	m_Obj[G_OBJ_LAB26] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB26], 3.5, 2, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB26], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB26], -1900.0f, 0.0f, -2050.0f);
	m_matObjWld[G_OBJ_LAB26] = m_matObjScl[G_OBJ_LAB26] * m_matObjRot[G_OBJ_LAB26] * m_matObjTrans[G_OBJ_LAB26];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB26])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 27
	m_Obj[G_OBJ_LAB27] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB27], 4, 1.5, 2);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB27], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB27], -1900.0f, 0.0f, -2750.0f);
	m_matObjWld[G_OBJ_LAB27] = m_matObjScl[G_OBJ_LAB27] * m_matObjRot[G_OBJ_LAB27] * m_matObjTrans[G_OBJ_LAB27];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB27])->m_OBB.Init(G_DEFINE_OBB_LAB);

	// 28
	m_Obj[G_OBJ_LAB28] = I_ObjMgr.GetPtr(G_OBJ_NAME_LAB);
	D3DXMatrixScaling(&m_matObjScl[G_OBJ_LAB28], 10, 2, 3);
	D3DXMatrixRotationY(&m_matObjRot[G_OBJ_LAB28], D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&m_matObjTrans[G_OBJ_LAB28], -1800.0f, 0.0f, -4000.0f);
	m_matObjWld[G_OBJ_LAB28] = m_matObjScl[G_OBJ_LAB28] * m_matObjRot[G_OBJ_LAB28] * m_matObjTrans[G_OBJ_LAB28];
	//연구소 OBB 사이즈
	((GGbsObj*)m_Obj[G_OBJ_LAB28])->m_OBB.Init(G_DEFINE_OBB_LAB);


	for (int i = 0; i < G_OBJ_CNT; i++) {

		m_matObjOBB[i] = m_matObjScl[i] * m_matObjRot[i] * m_matObjTrans[i];
	}

#endif
	return true;
};
bool		GSeqSinglePlay::InitEffect() {
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
	T_STR strFile = L"fire.eff";
	I_EffMgr.Load(&strFile, L"data/shader/plane.hlsl");
#else
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
#endif
	return true;
};

void	GSeqSinglePlay::SetEventCamera(G_HERO hero) {
	//말하는 캐릭터 중심으로 카메라 회전 처리.
	m_vEventCamPos.x = 30.f*(FLOAT)cos(0.7f*g_pMain->m_Timer.GetElapsedTime()) + m_CharHero[hero]->m_matWorld._41;
	m_vEventCamPos.z = 30.f*(FLOAT)sin(0.7f*g_pMain->m_Timer.GetElapsedTime()) + m_CharHero[hero]->m_matWorld._43;
	m_vEventCamPos.y = 100.f;
	m_pEventCamera->SetViewMatrix(m_vEventCamPos, D3DXVECTOR3(m_CharHero[hero]->m_matWorld._41, m_CharHero[hero]->m_matWorld._42, m_CharHero[hero]->m_matWorld._43));
}

bool        GSeqSinglePlay::FrameGame() {
#ifdef G_MACRO_GAME_ADD

	//디버그 모드 토글
	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_UP) {

		if (m_bGameOver) {
			if (m_bDebugMode) {
				m_bDebugMode = false;
				g_pMain->ClipMouse(true);
				m_pCamera = m_pEventCamera.get();
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
		else {
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
		
	}

	if (!m_bDebugMode)
		ShowCursor(false); // 커서를 화면에서 감추기
	else {
		ShowCursor(true);
	}

	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(m_CharHero[m_CurrentHero]->m_matWorld._41, m_CharHero[m_CurrentHero]->m_matWorld._42, m_CharHero[m_CurrentHero]->m_matWorld._43 );

	static float fSpaceKeyShadeTime = 0.0f;
	static bool	 fSpaceKeyShade = false;

	//게임 이벤트 처리[Start]
	{

		for (int iEvent = 0; iEvent < I_GameEvent.m_vecEvent.size(); iEvent++) {
	
			if (m_bChatting == true)
				break;

			if (I_GameEvent.m_vecEvent[iEvent]->m_bDone == true)
				continue;

			if (D3DXVec3Length(&(I_GameEvent.m_vecEvent[iEvent]->m_vEventPos - vHeroPos)) < G_DEFINE_LENGTH_EVENT_RADIUS) {
				m_bChatting = true;
				m_iEventNum = iEvent;
				m_iScriptNum = 0;

				fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
				m_pCamera = m_pEventCamera.get();

				break;
			}
		}

		if (m_bChatting) {

			SetEventCamera(I_GameEvent.m_vecEvent[m_iEventNum]->m_vecScript[m_iScriptNum]->m_Hero);

			//채팅 창을 보여준다.
			if (I_GameEvent.m_vecEvent[m_iEventNum]->m_vecScript[m_iScriptNum]->m_Hero == G_HERO_TOM) {
				m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = true;
				m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
			}
			else {
				m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
				m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = true;
			}




			//스페이스 키를 눌렀을때..
			if (I_Input.KeyCheck(DIK_SPACE) == KEY_PUSH) {

				if (m_iScriptNum < I_GameEvent.m_vecEvent[m_iEventNum]->m_vecScript.size()-1) {
					m_iScriptNum++;
				}
				else {
					I_GameEvent.m_vecEvent[m_iEventNum]->m_bDone = true;
					m_iEventNum = -1;
					m_iScriptNum = -1;
					m_bChatting = false;

					fSpaceKeyShadeTime = 0.0f;
					fSpaceKeyShade = false;

					//카메라를 바꾼다.
					m_pCamera = m_pFPSCamera[m_CurrentHero].get();

					//채팅 UI를 안보이게 한다.
					m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
					m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
				}
				//클릭 사운드
				g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
			}

			//경과시간.
			float fElapsedTime = g_pMain->m_Timer.GetElapsedTime() - fSpaceKeyShadeTime;

			if (fElapsedTime > G_DEFINE_TIME_SPACEKEY_SHADE) {
				fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
				fSpaceKeyShade = !fSpaceKeyShade;
			}

			if (fSpaceKeyShade)
				((GButtonCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_SPACE])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
			else
				((GButtonCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_SPACE])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));



			
			
		}
	}
	//게임 이벤트 처리[End]


	//게임 오버 처리 [Start]


	for (int i = 0; i < m_CharHero.size(); i++) {
		if (m_CharHero[i]->m_bDead == true && false == m_bGameOver) {
			fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
			m_bGameOver = true;
			m_pCamera = m_pEventCamera.get();
			m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_YELLOW_BTN]->m_bRender = true;
			m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_SPACE]->m_bRender = true;
			m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_TO_MENU_TEXT]->m_bRender = true;
		}
	}

	
	if (m_bGameOver) {
		//경과시간.
		float fElapsedTime = g_pMain->m_Timer.GetElapsedTime() - fSpaceKeyShadeTime;

		if (fElapsedTime > G_DEFINE_TIME_SPACEKEY_SHADE) {
			fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
 			fSpaceKeyShade = !fSpaceKeyShade;
		}

		if (fSpaceKeyShade)
			((GButtonCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_SPACE])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
		else
			((GButtonCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_GAMEOVER_SPACE])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

		
		//죽은 캐릭터 중심으로 카메라 회전 처리.
		for (int i = 0; i < m_CharHero.size(); i++) {
			if (m_CharHero[i]->m_bDead == true)
			{
				m_vEventCamPos.x = 30.f*(FLOAT)cos(0.7f*g_pMain->m_Timer.GetElapsedTime()) + m_CharHero[i]->m_matWorld._41;
				m_vEventCamPos.z = 30.f*(FLOAT)sin(0.7f*g_pMain->m_Timer.GetElapsedTime()) + m_CharHero[i]->m_matWorld._43;
				m_vEventCamPos.y = 100.f;

				m_pEventCamera->SetViewMatrix(m_vEventCamPos, D3DXVECTOR3(m_CharHero[i]->m_matWorld._41, m_CharHero[i]->m_matWorld._42, m_CharHero[i]->m_matWorld._43));

				break;
			}
		}




		if (I_Input.KeyCheck(DIK_SPACE) == KEY_PUSH) {
			//클릭 사운드
			g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);

			//싱글 플레이 관련 데이터를 초기화한다.
			InitValues();
			InitGame();

			//카메라를 바꾼다.
			m_pCamera = m_pFPSCamera[0].get();

			//마우스를 화면에 보이게 한다.
			ShowCursor(true);

			//메뉴로 돌아간다.
			g_pMain->ChangeSeq(G_SEQ_MENU);
			return true;
		}
	}
	//게임 오버 처리 [End]
	


	m_fPlayTime = (int)g_fDurationTime;



	//1인칭 샷것 스페큘러 값 업데이트를 위해..
	if (m_ObjGun.m_LightType == G_LIGHT_TYPE_SPECULAR) {
		m_ObjGun.m_cbLight.g_vEyeDir.x = m_pCamera->m_vLookVector.x;
		m_ObjGun.m_cbLight.g_vEyeDir.y = m_pCamera->m_vLookVector.y;
		m_ObjGun.m_cbLight.g_vEyeDir.z = m_pCamera->m_vLookVector.z;
	}

	
	if (!m_bGameOver) {
		if (I_Input.KeyCheck(DIK_TAB) == KEY_PUSH) {

			if (G_HERO_TOM == m_CurrentHero) {
				m_CurrentHero = G_HERO_JAKE;
				m_pCamera = m_pFPSCamera[m_CurrentHero].get();

				((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_IMG])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
				((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_IMG])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else {
				m_CurrentHero = G_HERO_TOM;
				m_pCamera = m_pFPSCamera[m_CurrentHero].get();

				((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER1_IMG])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
				((GImageCtl*)m_UIManager.m_pUIList[G_DEFINE_UI_PLAYER2_IMG])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
			}
			m_bDebugMode = false;
			g_pMain->m_bDebugInfoPrint = false;
			g_pMain->m_bDebugFpsPrint = false;
		}
	}
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = g_pMain->m_Timer.GetElapsedTime() * D3DX_PI;



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

#ifdef G_MACRO_AI_ADD
#else
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
#endif
	





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

#ifdef G_MACRO_AI_ADD
	m_GAIZombMgr.Frame(m_CharHero[0]->m_matWorld,m_CharHero[1]->m_matWorld);
#else
	if (I_Input.KeyCheck(DIK_F11) == KEY_UP)
	{
		for (int i = 0; i < m_CharZombie.size(); i++) {
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

#endif
	
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

	for (int i = 0; i < G_BB_CNT; i++)
	{
		m_Wall[i].Frame(&m_matWallBB[i]);
		if (m_pCamera->CheckOBBInPlane(&m_Wall[i]))
		{
			m_Wallbit.set(i);
		}
	}

#endif
	return true;
};
bool		GSeqSinglePlay::FrameEffect() {
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
	I_EffMgr.Frame(m_pCamera, &g_pMain->m_Timer);
#else
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
#endif
	return true;
};

bool        GSeqSinglePlay::RenderGame() {
#ifdef G_MACRO_GAME_ADD
	m_ObjGun.SetMatrix(NULL, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());

	//if(!m_bDebugCamera)
	if (!m_bGameOver && m_bChatting == false) {
		m_ObjGun.Render(g_pImmediateContext);
	}


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
		if (iChar == m_CurrentHero && m_bDebugMode==false 
			&& m_CharHero[iChar]->m_bDead == false && m_bChatting == false)
			continue;

		m_CharHero[iChar].get()->SetMatrix(&m_CharHero[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharHero[iChar].get()->Render(g_pImmediateContext);
	}

#ifdef G_MACRO_AI_ADD
	m_GAIZombMgr.Render(m_pCamera);

	if (m_bDebugMode) {

		list<shared_ptr<GNewZombie>>::iterator _F = m_GAIZombMgr.m_Zomb.begin();
		list<shared_ptr<GNewZombie>>::iterator _L = m_GAIZombMgr.m_Zomb.end();
		for (; _F != _L; ++_F)
		{
			(*_F)->m_OBB.Render(&(*_F)->m_matZombWld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
	}
#else
	for (int iChar = 0; iChar < m_CharZombie.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_CharZombie[iChar]->SetMatrix(&m_CharZombie[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		m_CharZombie[iChar]->Render(g_pImmediateContext);
	}

	if (m_bDebugMode) {
		for (int iChar = 0; iChar < m_CharZombie.size(); iChar++) {
			m_CharZombie[iChar].get()->m_OBB.Render(&m_CharZombie[iChar]->m_matWorld, m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
		}
	}
#endif

	if (m_bDebugMode) {
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

	//BOUD
	for (int i = 0; i < G_BB_CNT; i++)
	{
		if(m_bDebugMode)
		m_Wall[i].Render(&m_matWallBB[i], m_pCamera->GetViewMatrix(), m_pCamera->GetProjMatrix());
	}

#endif
	return true;
};
bool		GSeqSinglePlay::RenderEffect() {
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
	I_EffMgr.Render();
#else
	
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
	m_GAIZombMgr.Release();
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
#ifdef G_MACRO_EFFECT_TEST_ADD
	I_EffMgr.Release();
#endif
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
#ifdef G_MACRO_EFFECT_TEST_ADD
bool GSeqSinglePlay::UpdateGunEffectPosition() {

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


	D3DXMatrixTranslation(&matTrans, 5.0f, -5.0f, 100.0f);

	D3DXMatrixRotationY(&matRot, D3DXToRadian(180.0f));

	matWorld = matScl * matRot * matTrans * matViewInv;// *matTrans;

	KEffect* eff = I_EffMgr.GetPtr(L"fire.eff");
	auto Effect = make_shared<KEffectObj>();
	Effect->Set(eff, 0.0f, 100.0f, D3DXVECTOR3(matWorld._41, matWorld._42, matWorld._43));
	Effect->Init();
	//Effect->m_pEffect->m_pSprite->m_bLoop = false;
	I_EffMgr.m_List.push_back(Effect);

	return true;
}
#endif

#ifdef G_MACRO_CHAR_ADD

void GSeqSinglePlay::AddZomb(int iNum) {
	srand(time(NULL));


#ifdef G_MACRO_AI_ADD
	m_GAIZombMgr.Init(iNum);
#else

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
#endif

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

#ifdef G_MACRO_AI_ADD
#else
	//좀비 로드
	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie.gci") /*_T("data/CharTable.gci")*/))
	{
		return false;
	}
#endif

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
#ifdef G_MACRO_AI_ADD
	m_GAIZombMgr.CreateResource();
#endif
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
	I_EffMgr.CreateResource(&g_pMain->m_SwapChainDesc);
#endif
#endif
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
bool GSeqSinglePlay::InitValues(){
	m_iEventNum = -1;
	m_iScriptNum = -1;

	m_vEventCamPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bGameOver = false;
	m_bChatting = false;
	memset(m_pTextOutBuffer, 0, sizeof(TCHAR) * 256);

	m_iScore = 0;
	m_fPlayTime = 0.0f;
	m_CurrentHero = G_HERO_TOM;
	m_bDebugMode = false;
	return true;
};

GSeqSinglePlay::GSeqSinglePlay(void)
{
#ifdef G_DEFINE_SHADOW
	//그림자 [Start]
	SAFE_ZERO(m_pQuad);
	m_bColorTexRender = true;
	//그림자 [End]
#endif

	InitValues();
	m_pCamera = nullptr;
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
#else
	m_pSprite = nullptr;
#endif
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





