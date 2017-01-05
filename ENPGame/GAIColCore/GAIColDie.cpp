#include "_ai_col_std.h"

//GAIColDie * GAIColDie::pInstance_ = 0;

bool GAIColDie::Init(GAICol* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"HERO2_DIE");
	return true;
}
bool GAIColDie::Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	//iMyIndex->ChangeZombState(iMyIndex, G_AI_COL_DIE);
	
	return true;
}
bool GAIColDie::Render()
{

	return true;
}
bool GAIColDie::Release()
{
	return true;
}
HRESULT GAIColDie::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIColDie::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIColDie::GAIColDie()
{
	//pInstance_ = 0;
	GAIColSeq::InitGSeq();
}


GAIColDie::~GAIColDie()
{
}
int GAIColDie::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

