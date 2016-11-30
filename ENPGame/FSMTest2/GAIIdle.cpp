#include "_stdafx.h"

//GAIIdle * GAIIdle::pInstance_ = 0;

bool GAIIdle::Init(int iMyIndex)
{
	
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

	//GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

	//g_pMain->m_CharNZomb[0]->Set(pChar0,
	//	pChar0->m_pBoneObject,
	//	pChar0->m_pBoneObject->m_Scene.iFirstFrame,
	//	pChar0->m_pBoneObject->m_Scene.iLastFrame);
	return true;
}
bool GAIIdle::Frame(int iMyIndex)
{

	//처음 셋팅된 시간을 저장
	float fTime = 0.0f;

	//경과시간
	//float fElapseTime = 0.0f;

	//7초 후를 체크하기 위한 변수
	float fCoolTime = 3.0f;

	//bool bTime = false;


	if (!m_bTime) {
		fTime = g_fDurationTime;
		m_bTime = true;
	}


	//현재시간에서 - 처음셋팅된 시간 > 쿨타임보다 크면...
	if (g_fDurationTime - fTime > fCoolTime && !m_bDebug) {
		g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_MOVE];
		g_pMain->ChangeZombState(iMyIndex, G_AI_MOVE);

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

