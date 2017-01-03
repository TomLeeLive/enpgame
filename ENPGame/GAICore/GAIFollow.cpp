#include "_ai_std.h"

bool GAIFollow::Init(GNewZombie* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

	return true;
}


bool GAIFollow::Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);
	D3DXVECTOR3 vHeroPos2 = D3DXVECTOR3(matHeroWorld2._41, matHeroWorld2._42, matHeroWorld2._43);

	D3DXVECTOR3 vPos = D3DXVECTOR3(iMyIndex->m_matZombWld._41,
		iMyIndex->m_matZombWld._42, iMyIndex->m_matZombWld._43); 

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	D3DXVECTOR3 Temp2 = vHeroPos2 - vPos;

	float fDistance = D3DXVec3Length(&Temp);
	float fDistance2 = D3DXVec3Length(&Temp2);

	if ((fDistance >= G_DEFINE_AI_ATTACK_CHECK && fDistance <= G_DEFINE_AI_FOLLOW_CHECK) || (fDistance2 >= G_DEFINE_AI_ATTACK_CHECK && fDistance2 <= G_DEFINE_AI_FOLLOW_CHECK))
	{
		if (fDistance >= fDistance2)
		{
			iMyIndex->RotationAndTrans(vHeroPos2);
		}
		else
		{
			iMyIndex->RotationAndTrans(vHeroPos);
		}
	}

	if (fDistance > G_DEFINE_AI_FOLLOW_CHECK && fDistance2 > G_DEFINE_AI_FOLLOW_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_MOVE);
	}


	if (fDistance < G_DEFINE_AI_ATTACK_CHECK || fDistance2 < G_DEFINE_AI_ATTACK_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_ATTACK);
	}

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
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

