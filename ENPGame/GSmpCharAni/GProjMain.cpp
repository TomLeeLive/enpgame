#include "GProjMain.h"
#include "GObjMgr.h"

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

	shared_ptr<GZombie> pObjA = make_shared<GZombie>();
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

bool GProjMain::Init()
{
	

	I_CharMgr.Init();

	Load();

	
	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
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
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
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
	if(I_Input.KeyCheck( DIK_F3 ) == KEY_UP && m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame( 120, 205 );//jump		
	}
	if(I_Input.KeyCheck(DIK_F4) == KEY_UP&& m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame( 205, 289 );//attack		
	}

	if (I_Input.KeyCheck(DIK_F5) == KEY_UP)
	{
		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
		}
	}

	//if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	//{
	//	Load();
	//}

	enum G_ZOMBIE_STATE {
		G_ZOMB_IDLE = 0,
		G_ZOMB_ATTACK,
		G_ZOMB_WALK,
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
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_DIE");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		case G_ZOMB_ATTACK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_WALK:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;	
		case G_ZOMB_IDLE:
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

			m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
		}
		break;
		//case G_ZOMB_CNT:
		//{

		//	GCharacter* pChar0 = I_CharMgr.GetPtr(L"G_ZOMB_DIE");

		//	m_HeroObj[0]->Set(pChar0,
		//		pChar0->m_pBoneObject,
		//		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		//		pChar0->m_pBoneObject->m_Scene.iLastFrame);

		//	iChange = 0;
		//}
		//break;
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



