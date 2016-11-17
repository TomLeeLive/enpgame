#include "_stdafx.h"
GProjMain* g_pMain;


bool GProjMain::Load()
{
	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");
	//GCharacter* pChar1 = I_CharMgr.GetPtr(L"TEST_CHAR1");
	//GCharacter* pChar2 = I_CharMgr.GetPtr(L"TEST_CHAR2");
	//GCharacter* pChar3 = I_CharMgr.GetPtr(L"TEST_CHAR3");

	shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);

	return true;
}

bool GProjMain::Init()
{
	I_CharMgr.Init();
	 Load();

	m_fSecondPerFrmae = g_fSecPerFrame;
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 100000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 200.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");
	D3DXMatrixIdentity(&m_matBoxWorld);
	D3DXMatrixScaling(&m_matBoxWorld, 10.0f, 10.0f, 10.0f);

	m_pCurrentSeq->Init();

	srand(time(NULL));

	for (int i = 0;i < 4; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");
		//GCharacter* pChar1 = I_CharMgr.GetPtr(L"TEST_CHAR1");
		//GCharacter* pChar2 = I_CharMgr.GetPtr(L"TEST_CHAR2");
		//GCharacter* pChar3 = I_CharMgr.GetPtr(L"TEST_CHAR3");

		shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);
		m_HeroObj.push_back(pObjA);
	}

	for (int i = 0;i < m_HeroObj.size();i++){
		D3DXMatrixIdentity(&m_HeroObj[i]->m_worldMat);
		m_HeroObj[i]->m_worldMat._41 = (rand() * 3) % 203;
		m_HeroObj[i]->m_worldMat._43 = (rand() * 3) % 203;
	}

	/*D3DXMatrixIdentity(&m_HeroObj[0]->m_worldMat);
	m_HeroObj[0]->m_worldMat._41 = (rand() * 3) % 83;
	m_HeroObj[0]->m_worldMat._43 = (rand() * 3) % 83;

	D3DXMatrixIdentity(&m_HeroObj[1]->m_worldMat);
	m_HeroObj[1]->m_worldMat._41 = (rand() * 3) % 83;
	m_HeroObj[1]->m_worldMat._43 = (rand() * 3) % 83;*/

	return true;
}
bool GProjMain::Frame()
{

	D3DXMATRIX Logic;
	if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 += 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 -= 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 -= 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}

	if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 += 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->Frame();
	}
	
	m_pMainCamera->Frame();
	m_pCurrentSeq->Frame();

	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		m_RandomRotResult[i] = m_RandomRotation[i] * m_HeroObj[i]->m_worldMat;
		m_BoxRotResult[i] = m_BoxRotation[i] * m_HeroObj[i]->m_worldMat;
	}
	return true;
}
bool GProjMain::Render()
{
	m_Box->SetMatrix(&m_matBoxWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box->Render(m_pImmediateContext);
	
	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->SetMatrix(&m_RandomRotResult[iChar], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_HeroObj[iChar]->Render(m_pImmediateContext);
	}

	m_pCurrentSeq->Render();
	return true;
}
bool GProjMain::Release()
{
	m_pCurrentSeq->Release();
	return true;
}
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
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
	m_GameSeq[G_AI_IDLE] = GAIIdle::CreateInstance();
	m_GameSeq[G_AI_MOVE] = GAIMove::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = GAIFollow::CreateInstance();
	m_GameSeq[G_AI_ATTACK] = GAIAttack::CreateInstance();
	m_GameSeq[G_AI_DIE] = GAIDie::CreateInstance();
	m_pCurrentSeq = m_GameSeq[G_AI_MOVE];
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
