#include "_ai_std.h"

bool GAIIdle::Init(GNewZombie* iMyIndex)
{
	
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE2");
	return true;
}
bool GAIIdle::Frame(GNewZombie* iMyIndex,D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);

	D3DXVECTOR3 vPos = D3DXVECTOR3(iMyIndex->m_matZombWld._41,
		iMyIndex->m_matZombWld._42, iMyIndex->m_matZombWld._43);

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	float fDistance = D3DXVec3Length(&Temp);

	if (fDistance <= G_DEFINE_AI_IDLE_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_MOVE);
	}

	return true;
}
bool GAIIdle::Render()
{

	return true;
}
bool GAIIdle::Release()
{
	return true;
}
HRESULT GAIIdle::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIIdle::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIIdle::GAIIdle()
{
	//pInstance_ = 0;
	GAISeq::InitGSeq();

}


GAIIdle::~GAIIdle()
{
}
int GAIIdle::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

