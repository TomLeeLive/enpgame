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


	// 메인 카메라 뷰 행렬 세팅
	SAFE_NEW(m_pMainCamera, GCamera);
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);



	m_pBBox.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));


#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));

#endif

	m_vPosBefore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vPosCurrent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//m_matWorld = *m_pMainCamera->GetWorldMatrix(); // 주인공 박스
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

	SAFE_DEL(m_pMainCamera);
	return true;
}

bool GProjMain::Frame()
{	




	//--------------------------------------------------------------------------------------
	// 엔진에 있는 뷰 및 투영 행렬 갱신
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	if (I_Input.KeyCheck(DIK_RIGHT)) {

		m_matWorld._41 += 2.0f*g_fSecPerFrame;
	}
	if (I_Input.KeyCheck(DIK_LEFT)) {

		m_matWorld._41 -= 2.0f*g_fSecPerFrame;
	}
	if (I_Input.KeyCheck(DIK_UP)) {

		m_matWorld._43 += 2.0f*g_fSecPerFrame;
	}
	if (I_Input.KeyCheck(DIK_DOWN)) {

		m_matWorld._43 -= 2.0f*g_fSecPerFrame;
	}
		

	m_vPosCurrent.x = m_matWorld._41;
	m_vPosCurrent.y = m_matWorld._42;
	m_vPosCurrent.z = m_matWorld._43;

	D3DXVECTOR3 vDir = m_vPosBefore - m_vPosCurrent;
	D3DXVec3Normalize(&vDir, &vDir);


#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Frame(&m_matWorldEnemy);

	int nRet = GBBOXFUNC::ColCheck(&m_pBBoxEnemy, &m_pBBox);

	if (nRet == 1) {
		// 충돌시 처리할 코드 add
		int a = 10;

		D3DXVECTOR3 vTemp = m_vPosCurrent + 0.1f* vDir;

		D3DXMATRIX matTemp;
		D3DXMatrixIdentity(&matTemp);
		D3DXMatrixTranslation(&matTemp, vTemp.x, vTemp.y, vTemp.z);
		m_matWorld *= matTemp;


	}
	else {
		int a = 10;
	}

#endif

	
	m_vPosBefore.x = m_vPosCurrent.x;
	m_vPosBefore.y = m_vPosCurrent.y;
	m_vPosBefore.z = m_vPosCurrent.y;

	m_pBBox.Frame(&m_matWorld);


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


	m_pDirectionLine.SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_pDirectionLine.SetMatrix(&m_World[0], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);
	return GCoreLibV2::DrawDebug();
}


GCORE_RUN(ENP Test);



