#include "_stdafx.h"

GSeqSingle3S * GSeqSingle3S::pInstance_ = 0;
//
//
//GSeqSingle3S::GSeqSingle3S()
//{
//}
//
//
//GSeqSingle3S::~GSeqSingle3S()
//{
//}
bool GSeqSingle3S::Init() {
	T_STR strFile;
	m_UIManager.Init();
	strFile = L"data/ui_stage3s.gui";
	m_UIManager.UILoad(&strFile, &g_pMain->m_SwapChainDesc, g_pMain->m_DefaultRT.m_vp.Width, g_pMain->m_DefaultRT.m_vp.Height);
	return true;

};
bool GSeqSingle3S::Frame() {
	//frame
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc, &g_pMain->m_Timer);


	static float fSpaceKeyShadeTime = 0.0f;
	static bool	 fSpaceKeyShade = false;
	static bool bThisStarted = false;

	if (bThisStarted == false) {
		bThisStarted = true;
		fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();

		//싱글 플레이 관련 데이터를 초기화한다.
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->InitValues();
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->InitGame();
	}




	//리셋:스테이지1 주인공 위치, 스테이지1 주인공2 위치 잡을것
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pFPSCamera[G_HERO_TOM].get()->SetViewMatrix(D3DXVECTOR3(
		I_GameEventMgr.m_vecStage[2]->m_vPosStart.x,
		G_DEFINE_HERO_1_POS_Y,
		I_GameEventMgr.m_vecStage[2]->m_vPosStart.z)
		, D3DXVECTOR3(-10.0f, 10.0f, 50.0f));

	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIColMgr.m_Zomb[0]->m_matWorld._41 = I_GameEventMgr.m_vecStage[2]->m_vPosStart.x + 100.0f;
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIColMgr.m_Zomb[0]->m_matWorld._42 = G_DEFINE_HERO_1_POS_Y;
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIColMgr.m_Zomb[0]->m_matWorld._43 = I_GameEventMgr.m_vecStage[2]->m_vPosStart.z;

	//주인공1,2 총알 HP 리셋
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_CharHero[G_HERO_TOM]->m_iHP = 100;
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_CharHero[G_HERO_TOM]->m_iBullet = 100;

	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIColMgr.m_Zomb[0]->m_iHP = 100;
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIColMgr.m_Zomb[0]->m_iBullet = 100;

	//좀비매니저 좀비 초기화
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIZombMgr.m_Zomb.clear();
	//1스테이지 좀비 push back 할것.
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIZombMgr.Init(0);

	for (int i = 0; i < I_GameEventMgr.m_vecStage[2]->m_vecZombiePos.size(); i++) {
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_GAIZombMgr.Load(G_DEFINE_ZOMBIE_ADD_UNIT, I_GameEventMgr.m_vecStage[2]->m_vecZombiePos[i]);
	}



	//싱글 플레이로 스페이스 키 눌렀을 때 시퀀스변경.//m_iSelected =2 으로 돌릴것

	if (I_Input.KeyCheck(DIK_SPACE) == KEY_PUSH) {
		bThisStarted = false;

		//클릭 사운드
		g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);



		//카메라를 바꾼다.
		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera = ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pFPSCamera[G_HERO_TOM].get();

		((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.m_iMapSelected = 2;
		g_pMain->ChangeSeq(G_SEQ_SINGLE);
	}

	//경과시간.
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
bool GSeqSingle3S::Render() {
	//render
	m_UIManager.Render();
	return true;
};
bool GSeqSingle3S::Release() {
	return true;
};