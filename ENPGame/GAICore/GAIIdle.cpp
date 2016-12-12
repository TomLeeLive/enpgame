#include "_ai_std.h"

bool GAIIdle::Init(GNewZombie* iMyIndex)
{
	
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");
	return true;
}
bool GAIIdle::Frame(GNewZombie* iMyIndex,D3DXMATRIX matHeroWorld)
{
	//ó�� ���õ� �ð��� ����
	float fTime = 0.0f;

	//7�� �ĸ� üũ�ϱ� ���� ����
	float fCoolTime = 3.0f;

	if (!m_bTime) 
	{
		fTime = g_fDurationTime;
		m_bTime = true;
	}
	//����ð����� - ó�����õ� �ð� > ��Ÿ�Ӻ��� ũ��...
	if (g_fDurationTime - fTime > fCoolTime && !m_bDebug)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_MOVE);
		//iMyIndex->m_pCurrentSeq = iMyIndex->m_GameSeq[G_AI_MOVE];
		//iMyIndex->m_State = G_AI_MOVE;
		m_bDebug = true;
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
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

