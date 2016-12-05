#include "_stdafx.h"
GProjMain* g_pMain;


void		GProjMain::ChangeZombState(int iNum, G_AI state) {

	g_pMain->m_Zomb[iNum]->setState(state);

	
	GCharacter* pChar0 = NULL;

	switch (state) {
		case 	G_ZOMB_ST_WALK: {
			pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_WLK);
		}
		break;
		case 	G_ZOMB_ST_IDLE: {
			pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_IDL);
		}
		break;
		case 	G_ZOMB_ST_ATTACK: {
			pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_ATT);
		}
		break;
		case 	G_ZOMB_ST_DEAD: {
			pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_DIE);
		}
		break;
		case 	G_ZOMB_ST_FOLLOW: {
			pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_FLW);
		}
		break;
	}

	g_pMain->m_Zomb[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}
void		GProjMain::ChangeZombState(int iNum, TCHAR* str) {

	//GCharacter* pChar0 = I_CharMgr.GetPtr(str);
	auto pChar0 = I_CharMgr.GetPtr(str);

	 m_Zomb[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

	if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_DIE)) {
		 m_Zomb[iNum]->setState(G_AI_DIE);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_ATT)) {
		 m_Zomb[iNum]->setState(G_AI_ATTACK);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_WLK)) {
		 m_Zomb[iNum]->setState(G_AI_MOVE);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_IDL)) {
		 m_Zomb[iNum]->setState(G_AI_IDLE);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_FLW)) {
		m_Zomb[iNum]->setState(G_AI_FOLLOW);
	}
	else {
		 m_Zomb[iNum]->setState(G_AI_IDLE);
	}
}

bool GProjMain::Load()
{

	srand(time(NULL));


	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}

	for (int i = 0;i < G_DEFINE_MAX_AI_ZOMBIE; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

		shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
		pObjA->setState(G_AI_IDLE);

		pObjA->m_matZombWld._41 = (rand() * 3) % 303;
		pObjA->m_matZombWld._43 = (rand() * 3) % 303;

		pObjA->m_vZombPos.x = pObjA->m_matZombWld._41;
		pObjA->m_vZombPos.y = 0.0f;
		pObjA->m_vZombPos.z = pObjA->m_matZombWld._43;

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);
		m_Zomb.push_back(pObjA);
	}

	return true;
}

bool GProjMain::Init()
{
	I_CharMgr.Init();
	 Load();

	//m_fSecondPerFrmae = g_fSecPerFrame;
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 100000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 200.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");
	D3DXMatrixIdentity(&m_matBoxWorld);
	D3DXMatrixScaling(&m_matBoxWorld, 10.0f, 10.0f, 10.0f);

	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->Init();
		for (int j = 0; j < G_AI_CNT; j++)
		{
			m_Zomb[i]->m_GameSeq[j]->Init(i);
		}

	}
	

	return true;
}
bool GProjMain::Frame()
{

	D3DXMATRIX Logic;
	if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 += 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 -= 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 -= 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}

	if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 += 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->Frame(i);
	}
	

	m_pMainCamera->Frame();


	return true;
}
bool GProjMain::Render()
{
	m_Box->SetMatrix(&m_matBoxWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box->Render(m_pImmediateContext);
	if (m_Zomb[0]->m_State == G_AI_MOVE)
	{
		int i;
	}
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->SetMatrix(&m_Zomb[i]->m_matZombWld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_Zomb[i]->Render();
	}

	//for (int i = 0; i < m_Zomb.size(); i++)
	//{
	//	m_Zomb[i]->Render();
	//}
	
	return true;
}
bool GProjMain::Release()
{
	I_CharMgr.Release();

	return true;
}
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);

	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->CreateResource();
	}

	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{


}

GProjMain::~GProjMain(void)
{

}

int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;

}
GCORE_RUN(FSM TEST);
