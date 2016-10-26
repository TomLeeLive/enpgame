#include "_stdafx.h"

#ifdef G_MACRO_CHAR_ADD
bool GProjMain::LoadFileDlg(TCHAR* szExt, TCHAR* szTitle)
{
	OPENFILENAME    ofn;
	TCHAR           szFile[MAX_PATH] = { 0, };
	TCHAR			szFileTitle[MAX_PATH] = { 0, };
	static TCHAR    *szFilter;

	TCHAR lpCurBuffer[256] = { 0, };
	GetCurrentDirectory(256, lpCurBuffer);

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	_tcscpy_s(szFile, _T("*."));
	_tcscat_s(szFile, szExt);
	_tcscat_s(szFile, _T("\0"));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0L;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = _T("../../data/Character/");
	ofn.lpstrTitle = szTitle;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = szExt;

	if (!GetOpenFileName(&ofn))
	{
		return false;
	}
	TCHAR* load = _tcstok(szFile, _T("\n"));
	T_STR dir = szFile;
	load = &load[_tcslen(load) + 1];
	if (*load == 0)
	{
		m_LoadFiles.push_back(dir);
	}

	while (*load != 0)
	{
		T_STR dir = szFile;
		load = _tcstok(load, _T("\n"));
		dir += _T("\\");
		dir += load;
		m_LoadFiles.push_back(dir);
		load = &load[_tcslen(load) + 1];
	}
	SetCurrentDirectory(lpCurBuffer);
	return true;
}
#endif

#ifdef G_MACRO_CHAR_ADD

bool GProjMain::Load()
{
	//if (!LoadFileDlg(_T("gci"), _T("GCI Viewer")))
	//{
	//	return false;
	//}



	//int iLoad = m_LoadFiles.size() - 1;
	//if (!m_tObject.Load(GetDevice(), m_LoadFiles[iLoad].c_str(), L"MatrixViewer.hlsl"))
	//{
	//	return false;
	//}



	//int iLoad = m_LoadFiles.size() - 1;



	//if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, m_LoadFiles[iLoad].c_str()/*_T("CharTable.gci")*/))
	//{
	//	return false;
	//}

	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharTable3.gci") /*_T("CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"TESTCHAR6");
	//GCharacter* pChar1 = I_CharMgr.GetPtr(L"TEST_CHAR1");
	//GCharacter* pChar2 = I_CharMgr.GetPtr(L"TEST_CHAR2");
	//GCharacter* pChar3 = I_CharMgr.GetPtr(L"TEST_CHAR3");

	shared_ptr<GHeroObj> pObjA = make_shared<GHeroObj>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);
	/*
	shared_ptr<GHeroObj> pObjB = make_shared<GHeroObj>();
	pObjB->Set(pChar1,
	pChar1->m_pBoneObject,
	pChar1->m_pBoneObject->m_Scene.iFirstFrame,
	60);
	m_HeroObj.push_back(pObjB);


	shared_ptr<GHeroObj> pObjC = make_shared<GHeroObj>();
	pObjC->Set(pChar1,
	pChar1->m_pBoneObject,
	61,
	90);
	m_HeroObj.push_back(pObjC);

	shared_ptr<GHeroObj> pObjD = make_shared<GHeroObj>();
	pObjD->Set(pChar1,
	pChar1->m_pBoneObject,
	62,
	116);
	m_HeroObj.push_back(pObjD);


	shared_ptr<GHeroObj> pObjE = make_shared<GHeroObj>();
	pObjE->Set(	pChar2,
	pChar2->m_pBoneObject,
	pChar2->m_pBoneObject->m_Scene.iFirstFrame,
	pChar2->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjE);

	shared_ptr<GHeroObj> pObjF = make_shared<GHeroObj>();
	pObjF->Set( pChar3,
	pChar3->m_pBoneObject,
	pChar3->m_pBoneObject->m_Scene.iFirstFrame,
	pChar3->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjF);*/
	return true;
}
#endif 
bool GProjMain::Init()
{
	


#ifdef G_MACRO_CHAR_ADD
	I_CharMgr.Init();

	Load();
#endif

#ifdef G_MACRO_EFFECT_ADD
	m_pPS.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/Blend.hlsl", "PS_MATERIAL"));
	//--------------------------------------------------------------------------------------
	// 배경 부분
	//--------------------------------------------------------------------------------------
	m_pScreen = make_shared<GPlaneShape>();
	if (m_pScreen->Create(GetDevice(), L"data/shader/plane.hlsl") == false)
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
	m_pSprite.get()->Create(GetDevice(), L"data/shader/plane.hlsl", L"data/effect/ds1.dds");
	// 애니메이션 관련, 가로4x4
	m_pSprite.get()->SetRectAnimation(1.0f, 4, 128, 4, 128);
#endif

#ifdef G_MACRO_MAP_ADD
	m_iDrawDepth = 0;
	m_bDebugRender = false;

	//--------------------------------------------------------------------------------------
	// 디버그 라인 생성
	//--------------------------------------------------------------------------------------
	if (FAILED(m_DrawLine.Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_DrawLine 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
#endif

	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(10.0f, 10.0f, -10.0f), D3DXVECTOR3(-10.0f, 10.0f, 50.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);	


#ifdef G_MACRO_MAP_ADD
	//--------------------------------------------------------------------------------------
	// 카메라 프로스텀 랜더링용 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_pMainCamera->CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/box.hlsl", "PS_Color"));

	//--------------------------------------------------------------------------------------
	// 노이즈 맵 생성
	//--------------------------------------------------------------------------------------
	m_NoiseMap.Init(GetDevice(), m_pImmediateContext);
	TMapDesc MapDesc = { pow(2.0f,5.0f) + 1, pow(2.0f,5.0f) + 1, 50.0f, 1.0f, L"data/sand.jpg", L"data/shader/box.hlsl" };
	//TMapDesc MapDesc = { pow(2.0f,3.0f) + 1, pow(2.0f,3.0f) + 1, 10.0f, 1.0f, L"data/sand.jpg", L"data/shader/box.hlsl" };
	if (!m_NoiseMap.Load(MapDesc))
	{
		return false;
	}
	m_QuadTree.SetMinDivideSize(10);
	m_QuadTree.SetMaxDepthLimit(7);
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	m_QuadTree.Build(&m_NoiseMap, m_NoiseMap.m_iNumCols, m_NoiseMap.m_iNumRows); //가져오기
#endif

	return true;
}

#ifdef G_MACRO_MAP_ADD
void GProjMain::DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	//for (int iObj = 0; iObj < m_QuadTree.m_DrawObjList.size(); iObj++)
	//{
	//	GMapObject* pBox = dynamic_cast<GMapObject*>(m_QuadTree.m_DrawObjList[iObj]);
	//	m_pBoxs->SetAmbientColor(pBox->m_vColor.x, pBox->m_vColor.y, pBox->m_vColor.z, pBox->m_vColor.w);
	//	m_pBoxs->SetMatrix(&pBox->m_matWorld, pView, pProj);
	//	m_pBoxs->Render(m_pImmediateContext);
	//}
}

bool GProjMain::DrawQuadLine(GNode* pNode)
{
	if (pNode == NULL) return true;
	if (m_QuadTree.m_iRenderDepth == pNode->m_iDepth ||
		(pNode->m_isLeaf &&  m_QuadTree.m_iRenderDepth < 0))
	{
		m_DrawLine.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

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

		m_DrawLine.Draw(m_pImmediateContext, vPoint[0], vPoint[1], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[1], vPoint[2], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[2], vPoint[3], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[3], vPoint[0], vColor);

		m_DrawLine.Draw(m_pImmediateContext, vPoint[4], vPoint[5], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[5], vPoint[6], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[6], vPoint[7], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[7], vPoint[0], vColor);

		m_DrawLine.Draw(m_pImmediateContext, vPoint[0], vPoint[4], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[1], vPoint[5], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[2], vPoint[6], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[3], vPoint[7], vColor);
	}
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		DrawQuadLine(pNode->m_ChildList[iNode]);
	}
	return true;
}
#endif

bool GProjMain::Render()
{	
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);


#ifdef G_MACRO_MAP_ADD
	m_NoiseMap.SetMatrix(0, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	if (m_QuadTree.m_bDynamicUpdateIB == true)
	{
		if (!m_NoiseMap.Render(m_pImmediateContext)) return false;
	}
	else
	{
		if (!m_QuadTree.Render(m_pImmediateContext)) return false;
	}
	//--------------------------------------------------------------------------------------
	// 쿼드트리의 임의의 레벨 선텍 랜더링
	//--------------------------------------------------------------------------------------
	DrawSelectTreeLevel(m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

	if (m_bDebugRender)
	{
		DrawQuadLine(m_QuadTree.m_pRootNode);
	}


#endif


#ifdef G_MACRO_CHAR_ADD 

	D3DXMATRIX matCharWld;
	matCharWld = m_matWorld;
	matCharWld._42 = 20.0f;

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_HeroObj[iChar]->SetMatrix(&matCharWld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_HeroObj[iChar]->Render(m_pImmediateContext);
	}
#endif



#ifdef G_MACRO_EFFECT_ADD
	D3DXVECTOR4 vColor = D3DXVECTOR4(0, 0, 0, 0);
	float fValue = cosf(m_Timer.GetElapsedTime())*0.5f + 0.5f;
	FLOAT fFactor[4] = { 0 , };
	m_vMaterial.x = 1.0f;
	m_vMaterial.y = 1.0f;
	m_vMaterial.z = 1.0f;
	m_vMaterial.w = fValue;
	m_pSprite.get()->m_cbData.Color = m_vMaterial;
	ApplyBS(m_pImmediateContext, GDxState::g_pBSAlphaOne, fFactor, 0xffffffff);

	//if (m_RT.Begin(m_pImmediateContext, vColor))
	//	{
	ApplyRS(GetContext(), GDxState::g_pRSBackCullSolid);
	ApplyDSS(GetContext(), GDxState::g_pDSSDepthEnable);

	D3DXMATRIX matEffectWld;
	matEffectWld = m_matWorld;
	matEffectWld._42 = 10.0f;
	m_pSprite.get()->SetMatrix(&matEffectWld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_pSprite.get()->Render(m_pImmediateContext);
	
	//	m_RT.Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	//	m_RT.End(m_pImmediateContext);
	//	}

	ApplyDSS(GetContext(), GDxState::g_pDSSDepthDisable);
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	m_pScreen->SetMatrix(&matIdentity, &matIdentity, &matIdentity);
	m_pScreen->PreRender(m_pImmediateContext);
	m_pImmediateContext->OMSetBlendState(GDxState::g_pBSAlphaOne, 0, -1);
	//	m_pImmediateContext->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
	m_pImmediateContext->PSSetShader(m_pPS.Get(), NULL, 0);
	m_pImmediateContext->PSSetConstantBuffers(0, 1, m_pSprite.get()->m_dxobj.g_pConstantBuffer.GetAddressOf());
	m_pScreen->PostRender(m_pImmediateContext);




	ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthDisable);
	ApplyBS(m_pImmediateContext, GDxState::g_pBSOneZero);

	ClearD3D11DeviceContext(m_pImmediateContext);
#endif
	return true;
}
bool GProjMain::Release()
{
#ifdef G_MACRO_MAP_ADD
	m_NoiseMap.Release();
	m_QuadTree.Release();
#endif
#ifdef G_MACRO_CHAR_ADD 
	I_CharMgr.Release();
#endif
	return true;
}

bool GProjMain::Frame()
{	
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	//m_pMainCamera->Update(g_fSecPerFrame);
	m_pMainCamera->Frame();


#ifdef G_MACRO_MAP_ADD
	if (I_Input.KeyCheck(DIK_F1) == KEY_UP)
	{
		if (++m_iDrawDepth > 7) m_iDrawDepth = -1;
		m_QuadTree.SetRenderDepth(m_iDrawDepth);
	}
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());

	//--------------------------------------------------------------------------------------
	// 화면 디버그 정보 출력 
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_F2) == KEY_UP)
		m_NoiseMap.SetHurstIndex(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F3) == KEY_UP)
		m_NoiseMap.SetHurstIndex(false); //가져오기
	m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F4) == KEY_UP)m_NoiseMap.SetLacunarity(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F5) == KEY_UP)m_NoiseMap.SetLacunarity(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F6) == KEY_UP)m_NoiseMap.SetOctaves(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F7) == KEY_UP)m_NoiseMap.SetOctaves(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F8) == KEY_UP)m_NoiseMap.SetPersistence(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F9) == KEY_UP)m_NoiseMap.SetPersistence(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);


	if (I_Input.KeyCheck(DIK_U) == KEY_UP)
	{
		m_NoiseMap.SetNoiseType(0);
		m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	}
	if (I_Input.KeyCheck(DIK_I) == KEY_UP)
	{
		m_NoiseMap.SetNoiseType(1);
		m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		m_bDebugRender = !m_bDebugRender;
	}
	if (I_Input.KeyCheck(DIK_GRAVE) == KEY_UP) //문턱값 사용 ~
	{
		m_QuadTree.SetThresHold(!m_QuadTree.m_bThresHoldValue);
	}



	m_QuadTree.Frame();
	if (m_QuadTree.m_bDynamicUpdateIB == true)
	{
		m_NoiseMap.UpdateIndexBuffer(m_pImmediateContext, m_QuadTree.m_IndexList, m_QuadTree.m_iNumFace);
	}
	m_NoiseMap.Frame();
#endif

	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;



#ifdef G_MACRO_EFFECT_ADD
	//--------------------------------------------------------------------------------------
	// 빌보드 행렬
	//-----------------------------------------------------------------------------------
	FLOAT fDeterminant;
	D3DXMATRIX matBillboard;
	D3DXMatrixInverse(&matBillboard, &fDeterminant, m_pMainCamera->GetViewMatrix());
	matBillboard._41 = 0.0f;
	matBillboard._42 = 0.0f;
	matBillboard._43 = 0.0f;
	matBillboard._44 = 1.0f;


	m_pSprite.get()->SetMatrix(&matBillboard, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_pSprite.get()->Frame(m_pImmediateContext, m_Timer.GetElapsedTime(), g_fSecPerFrame);
#endif


#ifdef G_MACRO_CHAR_ADD 
	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		if (I_Input.KeyCheck(DIK_ADD))
		{
			m_HeroObj[iChar]->m_fSpeed += g_fSecPerFrame;			
		}
		if (I_Input.KeyCheck(DIK_SUBTRACT))
		{
			m_HeroObj[iChar]->m_fSpeed -= g_fSecPerFrame;
			if (m_HeroObj[iChar]->m_fSpeed < 0.0f) m_HeroObj[iChar]->m_fSpeed = 0.01f;
		}
		m_HeroObj[iChar]->Frame();
	}
	if(I_Input.KeyCheck( DIK_F10 ) == KEY_UP && m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame( 120, 205 );//jump		
	}
	if(I_Input.KeyCheck(DIK_F11) == KEY_UP&& m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame( 205, 289 );//attack		
	}

	if (I_Input.KeyCheck(DIK_F12) == KEY_UP)
	{
		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
		}
	}

	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		Load();
	}
#endif
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
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
#ifdef G_MACRO_EFFECT_ADD
	m_pSprite = nullptr;
#endif
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
GBASIS_RUN(ENP Game);



