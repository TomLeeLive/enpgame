#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{

	if (FAILED(m_pDirectionLine.Create(GetDevice(), L"data/shader/Line.hlsl")))
	{
		MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	if (FAILED(m_pPlane.Create(GetDevice(), L"data/shader/Plane.hlsl", L"data/Sand.jpg")))
	{
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(m_pBox.Create(GetDevice(), L"data/shader/Box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_pBox 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

#ifdef G_MACRO_ENEMYBOX
	if (FAILED(m_pBoxEnemy.Create(GetDevice(), L"data/shader/Box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_pBoxEnemy 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	D3DXMatrixIdentity(&m_matWorldEnemy);

	D3DXMatrixTranslation(&m_matWorldEnemy, 10.0f, 0.0f, 10.0f);
#endif

	D3DXMatrixIdentity(&m_World[0]);
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIX matRotX, matScale;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90));
	D3DXMatrixScaling(&matScale, 100.0f, 100.0f, 100.0f);
	D3DXMatrixMultiply(&m_matWorldPlaneBase, &matScale, &matRotX);

	// 4 종류의 카메라 세팅
	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);

	SAFE_NEW(m_pCamera[0], GCamera);
	m_pCamera[0]->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);
	// Front g_matView
	SAFE_NEW(m_pCamera[1], GCamera);
	vCameraPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_pCamera[1]->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);
	// Side g_matView
	SAFE_NEW(m_pCamera[2], GCamera);
	vCameraPosition = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_pCamera[2]->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);
	// User g_matView
	SAFE_NEW(m_pCamera[3], GCamera);
	vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	m_pCamera[3]->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);

	// 뷰포트에 들어 맞게 카메라 조정.
	m_pCamera[0]->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[1]->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[2]->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[3]->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));


	// 메인 카메라 뷰 행렬 세팅
	SAFE_NEW(m_pMainCamera, GBackViewCamera);
	//m_pMainCamera->SetModelCenter( D3DXVECTOR3( 1.0f, -1.0f, -1.0f ) );
	m_pMainCamera->SetModelCenter(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMainCamera->SetViewMatrix(*m_pCamera[m_iCameraType]->GetEyePt(), *m_pCamera[3]->GetLookAtPt(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pMainCamera->m_vCameraDestination = *m_pCamera[m_iCameraType]->GetEyePt();

	// Setup the camera's projection parameters
	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);


	m_pBBox.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));


#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));

#endif

	return true;
}

bool GProjMain::Render()
{	
	HRESULT hr;
	//-----------------------------------------------------------------------
	// 메인 뷰포트
	//-----------------------------------------------------------------------	

	m_pBox.SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pBox.Render(m_pImmediateContext);
	m_pBBox.Render(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

#ifdef G_MACRO_ENEMYBOX
	m_pBoxEnemy.SetMatrix(&m_matWorldEnemy, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pBoxEnemy.Render(m_pImmediateContext);
	m_pBBoxEnemy.Render(&m_matWorldEnemy, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
#endif

	m_pPlane.SetMatrix(&m_matWorldPlaneBase, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pPlane.Render(m_pImmediateContext);



	return true;
}
bool GProjMain::Release()
{
	SAFE_DEL(m_pCamera[1]);
	SAFE_DEL(m_pCamera[2]);
	SAFE_DEL(m_pCamera[3]);
	SAFE_DEL(m_pMainCamera);
	return true;
}

bool GProjMain::Frame()
{	
	//--------------------------------------------------------------------------------------
	// 카메라 타입 선택
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_1) && I_Input.KeyCheck(DIK_LCONTROL))
	{
		m_iCameraType++;
		if (m_iCameraType > 3)m_iCameraType = 0;
		m_fCameraYaw = m_pCamera[m_iCameraType]->GetYawAngle();
		m_fCameraPitch = m_pCamera[m_iCameraType]->GetPitchAngle();
		m_fRadius = m_pMainCamera->GetRadius();
		m_pMainCamera->SetViewMatrix(*m_pCamera[m_iCameraType]->GetEyePt(), *m_pCamera[m_iCameraType]->GetLookAtPt());
		m_pMainCamera->SetRadius(m_fRadius);
		m_pMainCamera->m_vCameraDestination = *m_pCamera[m_iCameraType]->GetEyePt();
	}


	//--------------------------------------------------------------------------------------
	// 엔진에 있는 뷰 및 투영 행렬 갱신
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Update(m_Timer.GetSPF());
	m_matWorld = *m_pMainCamera->GetWorldMatrix();//(const_cast< D3DXMATRIX* > (m_pMainCamera->GetWorldMatrix()));	

	m_pBBox.Frame(&m_matWorld);
#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Frame(&m_matWorldEnemy);

	int nRet = GBBOXFUNC::ColCheck(&m_pBBoxEnemy, &m_pBBox);

	if (nRet == 1) {
		// 충돌시 처리할 코드 add
		int a = 10;
	}
	else {
		int a = 10;
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

	// 아래의 경고는 GetDevice()->ClearState();를 호출하지 않을 때 발생한다.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
	// 추가
	m_iCameraType = 3; // User Camera	
	m_fCameraYaw = 0.0f;
	m_fCameraPitch = 0.0f;
	m_fCameraRoll = 0.0f;
	m_fRadius = 0.0f;
	SAFE_ZERO(m_pCamera[0]);
	SAFE_ZERO(m_pCamera[1]);
	SAFE_ZERO(m_pCamera[2]);
	SAFE_ZERO(m_pCamera[3]);
	SAFE_ZERO(m_pMainCamera);
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



bool GProjMain::DrawDebug()
{
	D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT nViewPorts = 1;
	m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);



	//-----------------------------------------------------------------------
	// 기본 뷰포트 정보로 복원
	//-----------------------------------------------------------------------
	m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);
	//-----------------------------------------------------------------------
	// 기본 뷰포트 정보로 복원
	//-----------------------------------------------------------------------
	m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);

	m_matWorld._41 = m_pMainCamera->GetLookAtPt()->x;
	m_matWorld._42 = m_pMainCamera->GetLookAtPt()->y;
	m_matWorld._43 = m_pMainCamera->GetLookAtPt()->z;

	m_pDirectionLine.SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_pDirectionLine.SetMatrix(&m_World[0], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);
	return GCoreLibV2::DrawDebug();
}


GCORE_RUN(ENP Test);



