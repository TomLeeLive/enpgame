#include "GProjMain.h"
#include "GObjMgr.h"

GProjMain* g_pMain;

bool GProjMain::Load()
{
	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}


	vector<TCHAR*> vecStr;
	vecStr.push_back(L"ZOMBIE_IDLE");
	vecStr.push_back(L"ZOMBIE_ATTACK");
	vecStr.push_back(L"ZOMBIE_WALK");
	vecStr.push_back(L"ZOMBIE_DIE");
	
	for (int i = 0; i < G_ZOMB_CNT; i++) {
		pChar0[i] = I_CharMgr.GetPtr(vecStr[i]);
		memcpy(&m_ZombieAni[i], pChar0[i], sizeof(GCharacter));
	}
	
	shared_ptr<GZombie> pObjA = make_shared<GZombie>();
	pObjA->Set(&m_ZombieAni[G_ZOMB_IDLE],
		m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject,
		m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject->m_Scene.iFirstFrame,
		m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);


	vecStr.clear();
	return true;
}

bool GProjMain::Init()
{
	
	//_CrtSetBreakAlloc(3069);
	I_CharMgr.Init();

	Load();

	
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	

#ifdef G_MACRO_MODELVIEW
	m_pMainCamera = make_shared<GModelViewCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
#else
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 10.0f, 100.0f));
#endif
	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);

	return true;
}
bool GProjMain::Render()
{	
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_HeroObj[iChar]->SetMatrix(&m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_HeroObj[iChar]->Render(m_pImmediateContext);
	}
	return true;
}
bool GProjMain::Release()
{

	for (int i = 0; i < G_ZOMB_CNT; i++) {
		m_ZombieAni[i].m_pBoneObject->Release();
		m_ZombieAni[i].Release();
		I_CharMgr.Delete(pChar0[i]);
	}
	I_CharMgr.Release();
	return true;
}

bool GProjMain::Frame()
{	
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	
#ifdef G_MACRO_MODELVIEW
	m_pMainCamera->Update(g_fSecPerFrame);
#else
	m_pMainCamera->Frame();
#endif

	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->Frame();
	}


	if (I_Input.KeyCheck(DIK_F5) == KEY_UP)
	{
		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
		}
	}



	static int iChange = 0;



	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
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
			m_HeroObj[0]->Set(&m_ZombieAni[G_ZOMB_DIE],
				m_ZombieAni[G_ZOMB_DIE].m_pBoneObject,
				m_ZombieAni[G_ZOMB_DIE].m_pBoneObject->m_Scene.iFirstFrame,
				m_ZombieAni[G_ZOMB_DIE].m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_ATTACK:
		{
			m_HeroObj[0]->Set(&m_ZombieAni[G_ZOMB_ATTACK],
				m_ZombieAni[G_ZOMB_ATTACK].m_pBoneObject,
				m_ZombieAni[G_ZOMB_ATTACK].m_pBoneObject->m_Scene.iFirstFrame,
				m_ZombieAni[G_ZOMB_ATTACK].m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_WALK:
		{
			m_HeroObj[0]->Set(&m_ZombieAni[G_ZOMB_WALK],
				m_ZombieAni[G_ZOMB_WALK].m_pBoneObject,
				m_ZombieAni[G_ZOMB_WALK].m_pBoneObject->m_Scene.iFirstFrame,
				m_ZombieAni[G_ZOMB_WALK].m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_IDLE:
		{
			m_HeroObj[0]->Set(&m_ZombieAni[G_ZOMB_IDLE],
				m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject,
				m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject->m_Scene.iFirstFrame,
				m_ZombieAni[G_ZOMB_IDLE].m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		}


	}
	

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

}

GProjMain::~GProjMain(void)
{
	//_CrtDumpMemoryLeaks();
}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}
GCORE_RUN(GCI Animation Viewer);



