#include "_stdafx.h"

GProjMain* g_pMain;

void GProjMain::ClipMouse(bool bClip) {
	if (bClip) {
		//마우스커서 가두기
		RECT Clip;
		GetClientRect(g_hWnd, &Clip);
		ClientToScreen(g_hWnd, (LPPOINT)&Clip);
		ClientToScreen(g_hWnd, (LPPOINT)(&Clip.right));
		ClipCursor(&Clip);
	}
	else {
		//마우스 영역해제
		ClipCursor(NULL);
	}

}
bool GProjMain::SoundLoad() {


	int iIndex = 0;

	iIndex = m_pSound.Load("data/sound/bgm/bgm1.mp3",true);				
	iIndex = m_pSound.Load("data/sound/bgm/theme.mp3", true);
	iIndex = m_pSound.Load("data/sound/intro/intro_the_hell.wav");	
	iIndex = m_pSound.Load("data/sound/player/boots1.wav");			
	iIndex = m_pSound.Load("data/sound/player/boots2.wav");			
	iIndex = m_pSound.Load("data/sound/player/boots3.wav");			
	iIndex = m_pSound.Load("data/sound/player/boots4.wav");			
	iIndex = m_pSound.Load("data/sound/weapon/shot1.wav");			
	iIndex = m_pSound.Load("data/sound/weapon/shot2.wav");
	iIndex = m_pSound.Load("data/sound/radio_static.wav"); //라디오 무전 소리
	iIndex = m_pSound.Load("data/sound/player/pain6.wav"); //좀비에게 맞을때 나는 소리
	iIndex = m_pSound.Load("data/sound/zombie/zo_attack1.wav"); //좀비 죽을때 나는 소리

	return true;
}

bool GProjMain::Init()
{	
	ClipMouse(true);

	m_pGameSeq[G_SEQ_LOADING]->Init();
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
		m_pGameSeq[i]->m_UIManager.Release();

	m_pSound.Release();

	for (int i = 0; i < G_SEQ_CNT; i++)
		m_pGameSeq[i]->Release();

	return true;
}

bool GProjMain::Frame()
{	
	m_pCurrentSeq->Frame();

	m_pSound.Frame();
	return true;
}
G_SEQ GProjMain::GetCurSeq() {
	return m_CurSeq;
}
bool GProjMain::ChangeSeq(G_SEQ seq) {
	m_pCurrentSeq = m_pGameSeq[seq];
	m_CurSeq = seq;

	return true;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	m_pCurrentSeq->CreateResource();

	for (int i = 0; i < G_SEQ_CNT; i++)
		m_pCurrentSeq->m_UIManager.CreateResource(&m_SwapChainDesc);
	
	ClipMouse(true);
	
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

	m_pGameSeq[G_SEQ_LOADING] = GSeqLoading::CreateInstance();

	ChangeSeq(G_SEQ_LOADING);
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



