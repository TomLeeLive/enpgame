#include "_stdafx.h"

bool GAIFollow::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");


	
	return true;
}


bool GAIFollow::Frame(int iMyIndex)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(g_pMain->m_Box->m_matWorld._41, g_pMain->m_Box->m_matWorld._42, g_pMain->m_Box->m_matWorld._43);
	
	D3DXVECTOR3 vPos = D3DXVECTOR3(g_pMain->m_Zomb[iMyIndex]->m_matZombWld._41,
		g_pMain->m_Zomb[iMyIndex]->m_matZombWld._42, g_pMain->m_Zomb[iMyIndex]->m_matZombWld._43);

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	float fDistance = D3DXVec3Length(&Temp);

	if (fDistance < G_DEFINE_AI_ATTACK_CHECK) 
	{
		g_pMain->ChangeZombState(iMyIndex, G_AI_ATTACK);
	}
	
	g_pMain->m_Zomb[iMyIndex]->RotationAndTrans(vHeroPos);


	return true;
}
bool GAIFollow::Render()
{
	return true;
}
bool GAIFollow::Release()
{
	return true;
}
HRESULT GAIFollow::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIFollow::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIFollow::GAIFollow()
{
	//ZombieMgr = new GNewZombieMgr;
	//pInstance_ = 0;

	GAISeq::InitGSeq();
	
}


GAIFollow::~GAIFollow()
{
}
int GAIFollow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

