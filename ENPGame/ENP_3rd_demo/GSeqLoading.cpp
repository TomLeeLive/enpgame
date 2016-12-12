#include "_stdafx.h"

GSeqLoading * GSeqLoading::pInstance_ = 0;

unsigned int __stdcall LoadingThread(void* arg) {
	//int xxx = (int)arg;
	GProjMain* g_pMain = (GProjMain*)arg;



	g_pMain->m_bRenderManually = true;

	float fLoading = 0.0f;

	int result = 0;

	//for (int x = 0; x < 100; ++x) {
	//	result += xxx++;
	//}

	//로딩 [Start]

	//각 게임 시퀀스 클래스 객체 생성.
	fLoading = 0.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(&fLoading,L"Loading GameSeq");
	g_pMain->m_pGameSeq[G_SEQ_END] = GSeqGameEnd::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_OVER] = GSeqGameOver::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_HOWTO] = GSeqHowTo::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_INTRO] = GSeqIntro::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_MENU] = GSeqMenu::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_SINGLE] = GSeqSinglePlay::CreateInstance();
	g_pMain->m_pGameSeq[G_SEQ_SURVIVAL] = GSeqSurvivalMode::CreateInstance();


	/*
	G_SEQ_END = 0,
	G_SEQ_OVER,// = 1,
	G_SEQ_HOWTO,// =2,
	G_SEQ_INTRO,// =3,
	G_SEQ_MENU,// = 4,
	G_SEQ_SINGLE,// = 5,
	G_SEQ_SURVIVAL,// = 6,
	G_SEQ_LOADING,// =7,
	*/
	T_STR_VECTOR vecStr;
	vecStr.push_back(L"Loading G_SEQ_END");
	vecStr.push_back(L"Loading G_SEQ_OVER");
	vecStr.push_back(L"Loading G_SEQ_HOWTO");
	vecStr.push_back(L"Loading G_SEQ_INTRO");
	vecStr.push_back(L"Loading G_SEQ_MENU");
	vecStr.push_back(L"Loading G_SEQ_SINGLE");
	vecStr.push_back(L"Loading G_SEQ_SURVIVAL");
	vecStr.push_back(L"Loading G_SEQ_LOADING");

	//Init.
	for (int i = 0; i < G_SEQ_CNT; i++) {
		if (i == G_SEQ_LOADING)
			continue;

		fLoading += 10.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(&fLoading, (void*)vecStr[i].c_str());

		g_pMain->m_pGameSeq[i]->Init();
	}



	//Sound Init
	fLoading = 20.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(&fLoading, L"Loading Sound");
	g_pMain->m_pSound.Init();
	g_pMain->SoundLoad();
	g_pMain->m_pSound.Play(SND_BGM_1, true, false);

	

	fLoading = 20.0f; g_pMain->m_pGameSeq[G_SEQ_LOADING]->RenderManually(&fLoading, L"Loading End");
	//로딩 [End]
	g_pMain->ChangeSeq(G_SEQ_MENU);

	g_pMain->m_bRenderManually = false;

	_endthreadex(result);
	return 0;
}

bool GSeqLoading::Init() {

	T_STR strFile;
	m_UIManager.Init();
	strFile = L"data/ui_loading.gui";
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

bool GSeqLoading::RenderManually(void* arg1, void* arg2) {

	float* fValue = (float*)arg1;
	TCHAR* pStr = (TCHAR*)arg2;


	//Preframe
	g_pMain->GCoreLibV2::PreFrame();
	//frame
	m_UIManager.Frame(&g_pMain->m_SwapChainDesc, &g_pMain->m_Timer);
	((GButtonHalfCtl*)m_UIManager.m_pUIList[1])->SetXSize(*fValue);
	//Postframe
	g_pMain->GCoreLibV2::PostFrame();

	//PreRender
	g_pMain->GCoreLibV2::PreRender();
	//render
	m_UIManager.Render();


	TCHAR pInfoBuffer[256];		//정보 출력
	memset(pInfoBuffer, 0, sizeof(TCHAR) * 256);

	RECT rc;
	
	rc.top = g_pMain->m_DefaultRT.m_vp.Height / 3 * 2;
	rc.bottom = g_pMain->m_DefaultRT.m_vp.Height;
	rc.left = 0;
	rc.right = g_pMain->m_DefaultRT.m_vp.Width;
	
	//rc.top = g_pMain->m_DefaultRT.m_vp.Height - 60;
	//rc.bottom = g_pMain->m_DefaultRT.m_vp.Height;
	//rc.left = 0;
	//rc.right = g_pMain->m_DefaultRT.m_vp.Width;

	if(pStr!=NULL)
		g_pMain->DrawDebugRect(&rc, pStr, DWRITE_TEXT_ALIGNMENT_CENTER,D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

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
