#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	for (int i = 0; i < G_SEQ_CNT; i++)
		m_pGameSeq[i]->Init();
	
	return true;
}

bool GProjMain::Render()
{	
	m_pCurrentSeq->Render();
	return true;
}
bool GProjMain::Release()
{
	for (int i = 0; i < G_SEQ_CNT; i++)
		m_pGameSeq[i]->Release();

	return true;
}

bool GProjMain::Frame()
{	
	m_pCurrentSeq->Frame();
	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	m_pCurrentSeq->CreateResource();
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	m_pCurrentSeq->DeleteResource();
	return S_OK;
}
GProjMain::GProjMain(void)
{
	m_pGameSeq[G_SEQ_END] = GSeqGameEnd::CreateInstance();
	m_pGameSeq[G_SEQ_OVER] = GSeqGameOver::CreateInstance();
	m_pGameSeq[G_SEQ_HOWTO] = GSeqHowTo::CreateInstance();
	m_pGameSeq[G_SEQ_INTRO] = GSeqIntro::CreateInstance();
	m_pGameSeq[G_SEQ_MENU] = GSeqMenu::CreateInstance();
	m_pGameSeq[G_SEQ_SINGLE] = GSeqSinglePlay::CreateInstance();
	m_pGameSeq[G_SEQ_SURVIVAL] = GSeqSurvivalMode::CreateInstance();

	m_pCurrentSeq = m_pGameSeq[G_SEQ_SINGLE];
}

GProjMain::~GProjMain(void)
{
	for (int i = 0; i < G_SEQ_CNT; i++)
		delete m_pGameSeq[i];
}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_pCurrentSeq->WndProc(hWnd, msg, wParam, lParam);

	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}
GCORE_RUN(ENP Game);



