#include "_stdafx.h"
GProjMain* g_pMain;

bool GProjMain:: FollowTom(D3DXVECTOR3 vHeroTom, D3DXVECTOR3 vHeroJake)
{
	D3DXVECTOR3 vLook_toTom, vTRans_toTom;
	D3DXMATRIX matRot, matTrans;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);

	vLook_toTom = vHeroJake - vHeroTom;

	D3DXVec3Normalize(&vLook_toTom, &vLook_toTom);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vLook_toTom);
	D3DXVec3Cross(&vUp, &vLook_toTom, &vRight);

	matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
	matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
	matRot._31 = vLook_toTom.x;		matRot._32 = vLook_toTom.y;		matRot._33 = vLook_toTom.z;

	
	vTRans_toTom = vHeroJake - G_DEFINE_AI_MOVE_SPEED* g_fSecPerFrame *vLook_toTom;
	D3DXMatrixTranslation(&matTrans, vTRans_toTom.x, vTRans_toTom.y, vTRans_toTom.z);

	m_matBoxWorld2 = matRot * matTrans;
	m_matBoxWorld2._42 = G_DEFINE_CHAR_Y_POS;
	return true;
}
bool GProjMain::Init()
{

	m_GAIZombMgr.Init(G_DEFINE_MAX_AI_ZOMBIE);
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 100000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 200.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data_test/flagstone.bmp");
	D3DXMatrixIdentity(&m_matBoxWorld);
	D3DXMatrixScaling(&m_matBoxWorld, 10.0f, 10.0f, 10.0f);
	m_matBoxWorld._42 = 40.0f;

	SAFE_NEW(m_Box2, GBoxShape);
	m_Box2->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data_test/flagstone.bmp");
	D3DXMatrixIdentity(&m_matBoxWorld2);
	D3DXMatrixScaling(&m_matBoxWorld2, 10.0f, 10.0f, 10.0f);
	m_matBoxWorld2._42 = 40.0f;





	return true;
}
bool GProjMain::Frame()
{
	D3DXVECTOR3 vHeroTom = D3DXVECTOR3(m_matBoxWorld._41, m_matBoxWorld._42, m_matBoxWorld._43);
	D3DXVECTOR3 vHeroJake = D3DXVECTOR3(m_matBoxWorld2._41, m_matBoxWorld2._42, m_matBoxWorld2._43);

	D3DXVECTOR3 Temp = vHeroTom - vHeroJake;
	
	float fDistance = D3DXVec3Length(&Temp);

	if ( fDistance > 60.0f)
	{
		FollowTom(vHeroTom, vHeroJake);
	}
	if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 += G_DEFINE_AI_TEST_HERO_SPEED * g_fSecPerFrame;
	}

	if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 -= G_DEFINE_AI_TEST_HERO_SPEED * g_fSecPerFrame;
	}

	if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 -= G_DEFINE_AI_TEST_HERO_SPEED * g_fSecPerFrame;
	}

	if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 += G_DEFINE_AI_TEST_HERO_SPEED * g_fSecPerFrame;
	}
	


	m_pMainCamera->Frame();


	m_GAIZombMgr.Frame(m_matBoxWorld, m_matBoxWorld2);

	return true;
}
bool GProjMain::Render()
{
	m_Box->SetMatrix(&m_matBoxWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box->Render(m_pImmediateContext);

	m_Box2->SetMatrix(&m_matBoxWorld2, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box2->Render(m_pImmediateContext);

	m_GAIZombMgr.Render(m_pMainCamera.get());
	return true;
}
bool GProjMain::Release()
{
	m_GAIZombMgr.Release();
	return true;
}
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);

	m_GAIZombMgr.CreateResource();

	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
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
GCORE_RUN(FSM TEST);
