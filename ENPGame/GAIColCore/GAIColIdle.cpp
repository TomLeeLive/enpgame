#include "_ai_col_std.h"

bool GAIColIdle::Init(GAICol* iMyIndex)
{
	
	pChar0 = I_CharMgr.GetPtr(L"HERO2_IDLE");
	return true;
}
bool GAIColIdle::Frame(GAICol* iMyIndex,D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);

	D3DXVECTOR3 vPos = D3DXVECTOR3(iMyIndex->m_matWorld._41,
		iMyIndex->m_matWorld._42, iMyIndex->m_matWorld._43);

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	float fDistance = D3DXVec3Length(&Temp);

	if (fDistance <= G_DEFINE_AI_COL_IDLE_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_COL_MOVE);
	}

	return true;
}
bool GAIColIdle::Render()
{

	return true;
}
bool GAIColIdle::Release()
{
	return true;
}
HRESULT GAIColIdle::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColIdle::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColIdle::GAIColIdle()
{
	//pInstance_ = 0;
	GAIColSeq::InitGSeq();

}


GAIColIdle::~GAIColIdle()
{
}
int GAIColIdle::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

