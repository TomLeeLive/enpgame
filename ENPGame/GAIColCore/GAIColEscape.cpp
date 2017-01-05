#include "_ai_col_std.h"

//GAIColDie * GAIColDie::pInstance_ = 0;

bool GAIColEscape::Init(GAICol* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"HERO2_DIE");
	return true;
}
bool GAIColEscape::Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2, GHero* pHero)
{
	//iMyIndex->ChangeZombState(iMyIndex, G_AI_COL_ESCAPE);
	
	return true;
}
bool GAIColEscape::Render()
{

	return true;
}
bool GAIColEscape::Release()
{
	return true;
}
HRESULT GAIColEscape::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColEscape::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColEscape::GAIColEscape()
{
	//pInstance_ = 0;
	GAIColSeq::InitGSeq();
}


GAIColEscape::~GAIColEscape()
{
}
int GAIColEscape::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

