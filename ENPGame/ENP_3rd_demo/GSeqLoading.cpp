#include "_stdafx.h"

GSeqLoading * GSeqLoading::pInstance_ = 0;

unsigned int __stdcall LoadingThread(void* arg) {
	//int xxx = (int)arg;
	GProjMain* g_pMain = (GProjMain*)arg;

	g_pMain->m_bRenderManually = true;

	float fLoading = 0.0f;

	g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(fLoading);

	int result = 0;

	//for (int x = 0; x < 100; ++x) {
	//	result += xxx++;
	//}

	//로딩 [Start]
	g_pMain->m_pGameSeq[G_SEQ_END] = GSeqGameEnd::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_OVER] = GSeqGameOver::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_HOWTO] = GSeqHowTo::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_INTRO] = GSeqIntro::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_MENU] = GSeqMenu::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_SINGLE] = GSeqSinglePlay::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_SURVIVAL] = GSeqSurvivalMode::CreateInstance();

	fLoading = 10.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(fLoading);

	g_pMain->m_pSound.Init();

	g_pMain->SoundLoad();

	fLoading = 28.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(fLoading);

	g_pMain->m_pSound.Play(SND_BGM_1, true, false);


	for (int i = 0; i < G_SEQ_CNT; i++) {
		if (i == G_SEQ_LOADING)
			continue;

		g_pMain->m_pGameSeq[i]->Init();

		fLoading += i * 12.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(fLoading);
	}
	//로딩 [End]
	g_pMain->ChangeSeq(G_SEQ_MENU);

	g_pMain->m_bRenderManually = false;

	_endthreadex(result);
	return 0;
}

bool GSeqLoading::Init() {

	T_STR strFile;
	m_UIManager.Init();
	strFile = L"ui_loading.gui";
	m_UIManager.UILoad(&strFile, &g_pMain->m_SwapChainDesc, g_pMain->m_DefaultRT.m_vp.Width, g_pMain->m_DefaultRT.m_vp.Height);



	unsigned int id;
	HANDLE hand;
	//int xxx = 120;

	hand = (HANDLE)_beginthreadex(NULL, 0, LoadingThread, g_pMain, 0, &id);
	//hand2 = (HANDLE)_beginthreadex(NULL, 0, INfinityThread, (void *)xxx, 0, &id);

	//WaitForSingleObject(hand, INFINITE);

	//DWORD test = 0;
	//GetExitCodeThread(hand, &test);
	//CloseHandle(hand);

	//TerminateThread(hand2, 0);






	return true; 
}

bool GSeqLoading::RenderManually(float fValue) { 
	//Preframe
	g_pMain->GCoreLibV2::PreFrame();
	//frame
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc, &g_pMain->m_Timer);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[1])->SetXSize(fValue);
	//Postframe
	g_pMain->GCoreLibV2::PostFrame();

	//PreRender
	g_pMain->GCoreLibV2::PreRender();
	//render
	m_UIManager.Render();
	//PostRender
	g_pMain->GCoreLibV2::PostRender();

	return true; 
};
bool GSeqLoading::Frame() {
	/*
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc, &g_pMain->m_Timer);

	EnterCriticalSection(&CSfLoading);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[1])->SetXSize(m_fLoading);
	LeaveCriticalSection(&CSfLoading);
	*/
	return true;
};
bool GSeqLoading::Render() {
	/*
	EnterCriticalSection(&CSfLoading);
	float fLoading = m_fLoading;
	LeaveCriticalSection(&CSfLoading);

	if (fLoading <= 100.0f) {
		m_UIManager.Render();
	}
	*/	
	return true;
};
//GSeqLoading::GSeqLoading()
//{
//}
//
//
//GSeqLoading::~GSeqLoading()
//{
//}
