#include "_ai_col_std.h"

bool GAIColAttack::Init(GAICol* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"HERO2_ATTACK");

	return true;
}

bool GAIColAttack::Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2, GHero* pHero)
{
	D3DXVECTOR3 vTomPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);
	D3DXVECTOR3 vJakePos = D3DXVECTOR3(iMyIndex->m_matWorld._41, iMyIndex->m_matWorld._42, iMyIndex->m_matWorld._43);
	int BasicHp = 1;
	
	D3DXVECTOR3 Temp = vTomPos - vJakePos;
	float fDistance = D3DXVec3Length(&Temp);
	
	if (pHero->m_iHP <= 50)
	{
		pHero->m_bHealing = true;

		if (fDistance < G_DEFINE_AI_COL_ATTACK_CHECK)
		{
			float Time = g_fSecPerFrame;
			if (pHero->m_iHP < 100)
			{
				pHero->m_iHP += (BasicHp + Time);
			}
		}
		else
		{
			iMyIndex->RotationAndTrans(vTomPos);
			float Time = 0.0f;
		}
	}
	else
	{
		pHero->m_bHealing = false;

		if(fDistance > G_DEFINE_AI_COL_ATTACK_CHECK)
		iMyIndex->ChangeZombState(iMyIndex, G_AI_COL_FOLLOW);
	}
	return true;
}
bool GAIColAttack::Render()
{

	return true;
}
bool GAIColAttack::Release()
{
	return true;
}
HRESULT GAIColAttack::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColAttack::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColAttack::GAIColAttack()
{
	//m_pMainCamera = nullptr;
	//ZombieMgr = new GNewZombieMgr;
	//pInstance_ = 0;

	GAIColSeq::InitGSeq();


}


GAIColAttack::~GAIColAttack()
{
}
int GAIColAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

