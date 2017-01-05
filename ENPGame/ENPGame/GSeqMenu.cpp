#include "_stdafx.h"

GSeqMenu * GSeqMenu::pInstance_ = 0;

bool GSeqMenu::Init() {
	T_STR strFile;
	m_UIManager.Init();
	strFile = L"data/ui_menu.gui";
	m_UIManager.UILoad(&strFile, &g_pMain->m_SwapChainDesc, g_pMain->m_DefaultRT.m_vp.Width, g_pMain->m_DefaultRT.m_vp.Height);

	return true;
}

bool GSeqMenu::Frame() { 
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc,&g_pMain->m_Timer);

	
	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_HOLD) {

		ShowCursor(true);
	}
	return true; 
};
bool GSeqMenu::Render() { 
	int iClickedButton = -1;
	m_UIManager.Render(&iClickedButton);

	if (iClickedButton == -1)
		return true;

	/*
	1.싱글플레이
	2.서바이벌
	3.하우투페이지
	4.게임종료
	*/

	switch (iClickedButton) {

		case 1: 
		{
			//g_pMain->m_pGameSeq[G_SEQ_SINGLE]->Init();
			//g_pMain->ChangeSeq(G_SEQ_SINGLE);
			g_pMain->ChangeSeq(G_SEQ_SINGLE_1S);
			g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);

		}
		break;
		case 2:
		{
			g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
		}
		break;
		case 3:
		{
			g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
		}
		break;
		case 4:
		{
			g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
		}
		break;
	}


	return true; 
};
//
//GSeqMenu::GSeqMenu()
//{
//}
//
//
//GSeqMenu::~GSeqMenu()
//{
//}
