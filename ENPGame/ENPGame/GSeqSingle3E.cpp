#include "_stdafx.h"

GSeqSingle3E * GSeqSingle3E::pInstance_ = 0;
//
//
//GSeqSingle3E::GSeqSingle3E()
//{
//}
//
//
//GSeqSingle3E::~GSeqSingle3E()
//{
//}
bool GSeqSingle3E::Init() {
	T_STR strFile;
	m_UIManager.Init();
	strFile = L"data/ui_stage3e.gui";
	m_UIManager.UILoad(&strFile, &g_pMain->m_SwapChainDesc, g_pMain->m_DefaultRT.m_vp.Width, g_pMain->m_DefaultRT.m_vp.Height);
	return true;

};
bool GSeqSingle3E::Frame() {
	//frame
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc, &g_pMain->m_Timer);

	static float fSpaceKeyShadeTime = 0.0f;
	static bool	 fSpaceKeyShade = false;
	static bool bThisStarted = false;

	if (bThisStarted == false) {
		bThisStarted = true;
		fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();

		//�̱� �÷��� ���� �����͸� �ʱ�ȭ�Ѵ�.
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->InitValues();
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->InitGame();
	}

	//�޴��� ������ ����.//m_iSelected =0 ���� ������
	if (I_Input.KeyCheck(DIK_SPACE) == KEY_PUSH) {
		bThisStarted = false;

		//Ŭ�� ����
		g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);



		//ī�޶� �ٲ۴�.
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera = ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pFPSCamera[G_HERO_TOM].get();


		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.m_iMapSelected = 0;
		g_pMain->ChangeSeq(G_SEQ_MENU);
	}

	//����ð�.
	float fElapsedTime = g_pMain->m_Timer.GetElapsedTime() - fSpaceKeyShadeTime;

	if (fElapsedTime > G_DEFINE_TIME_SPACEKEY_SHADE) {
		fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
		fSpaceKeyShade = !fSpaceKeyShade;
	}

	if (fSpaceKeyShade)
		((GButtonCtl*)m_UIManager.m_pUIList[1])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	else
		((GButtonCtl*)m_UIManager.m_pUIList[1])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	return true;
};
bool GSeqSingle3E::Render() {
	//render
	m_UIManager.Render();
	return true;
};
bool GSeqSingle3E::Release() {
	return true;
};