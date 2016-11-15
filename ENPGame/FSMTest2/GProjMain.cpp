#include "_stdafx.h"
#include "GObjMgr.h"
GProjMain* g_pMain;


bool GProjMain::Load()
{
	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");


	shared_ptr<GZombie> pObjA = make_shared<GZombie>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);

	return true;
}

bool GProjMain::Init()
{
	m_fSecondPerFrmae = g_fSecPerFrame;
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 100000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 20.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = 10.0f;
	m_matWorld._43 = 10.0f;

	SAFE_NEW(m_Box1, GBoxShape);
	m_Box1->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/cncr21S.bmp");
	D3DXMatrixIdentity(&m_matWorld1);
	m_pCurrentSeq->Init();

	I_CharMgr.Init();
	
	return true;
}
bool GProjMain::Frame()
{
	
	D3DXMATRIX Logic;
	if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
	{
		g_pMain->m_matWorld._43 += 10.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matWorld._43;
	}

	if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
	{
		g_pMain->m_matWorld._43 -= 10.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matWorld._43;
	}

	if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
	{
		g_pMain->m_matWorld._41 -= 10.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matWorld._41;
	}

	if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
	{
		g_pMain->m_matWorld._41 += 10.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matWorld._41;
	}

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->Frame();
	}

	//if (I_Input.KeyCheck(DIK_F5) == KEY_UP)
	//{
	//	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	//	{
	//		m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
	//	}
	//}

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
		}


	}

	m_pMainCamera->Frame();
	m_pCurrentSeq->Frame();

	m_Result = m_Rotation * m_matWorld1;

	
	return true;
}
bool GProjMain::Render()
{
	m_Box->SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box1->SetMatrix(&m_Result, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	m_Box->Render(m_pImmediateContext);
	m_Box1->Render(m_pImmediateContext);
	
	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_HeroObj[iChar]->SetMatrix(&m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
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
