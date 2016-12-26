#include "_ai_std.h"

//GAIDie * GAIDie::pInstance_ = 0;

bool GAIDie::Init(GNewZombie* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_DIE");
	return true;
}
bool GAIDie::Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	//iMyIndex->ChangeZombState(iMyIndex, G_AI_DIE);
	
	return true;
}
bool GAIDie::Render()
{

	return true;
}
bool GAIDie::Release()
{
	return true;
}
HRESULT GAIDie::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIDie::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIDie::GAIDie()
{
	//pInstance_ = 0;
	GAISeq::InitGSeq();
}


GAIDie::~GAIDie()
{
}
int GAIDie::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

