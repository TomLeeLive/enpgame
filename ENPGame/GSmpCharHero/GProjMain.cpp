#include "GProjMain.h"
#include "GObjMgr.h"

GProjMain* g_pMain;

bool GProjMain::Load()
{
	//if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharHero1.gci")))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_IDLE");
	//GCharacter* pChar1 = I_CharMgr.GetPtr(L"TEST_CHAR1");
	//GCharacter* pChar2 = I_CharMgr.GetPtr(L"TEST_CHAR2");
	//GCharacter* pChar3 = I_CharMgr.GetPtr(L"TEST_CHAR3");

	shared_ptr<GHero> pObjA = make_shared<GHero>();
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


	enum G_ZOMBIE_STATE {
		G_ZOMB_IDLE = 0,
		G_ZOMB_ATTACK,
		G_ZOMB_WALK,
		G_ZOMB_RUN,
		G_ZOMB_JUMP,
		G_ZOMB_DIE,
		G_ZOMB_CNT
	};
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
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_DIE");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_ATTACK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_ATTACK");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_WALK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_WALK");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_IDLE:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_IDLE");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;

		case G_ZOMB_RUN:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_RUN");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_JUMP:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO_JUMP");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
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



