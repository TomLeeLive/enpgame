#include "_stdafx.h"

GSeqMenu * GSeqMenu::pInstance_ = 0;

bool GSeqMenu::Frame() { 
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc,&g_pMain->m_Timer);
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
			g_pMain->ChangeSeq(G_SEQ_SINGLE);
		}
		break;
		case 2:
		{

		}
		break;
		case 3:
		{

		}
		break;
		case 4:
		{

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
