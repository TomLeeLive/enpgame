#include "_ai_std.h"




bool GAIZombieMgr::Load()
{

	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}

	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

		shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
		pObjA->setState(G_AI_IDLE);

		pObjA->m_matZombWld._41 = (rand() * 3) % 303;
		pObjA->m_matZombWld._43 = (rand() * 3) % 303;

		//pObjA->m_vZombPos.x = pObjA->m_matZombWld._41;
		//pObjA->m_vZombPos.y = 0.0f;
		//pObjA->m_vZombPos.z = pObjA->m_matZombWld._43;

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);
		m_Zomb.push_back(pObjA);
	}

	return true;
}
bool		GAIZombieMgr::Init() { 
	srand((unsigned)time(NULL));

	I_CharMgr.Init();
	Load();

	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->Init();
		for (int j = 0; j < G_AI_CNT; j++)
		{
			m_Zomb[i]->m_GameSeq[j]->Init(m_Zomb[i].get());
		}

	}
	
	return true; };
bool		GAIZombieMgr::Frame(D3DXMATRIX matHeroWorld) {
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->Frame(m_Zomb[i].get(), matHeroWorld);
	}


	return true; };
bool		GAIZombieMgr::Render(GCamera* camera) {
	if (m_Zomb[0]->m_State == G_AI_MOVE)
	{
		int i;
	}
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->SetMatrix(&m_Zomb[i]->m_matZombWld, &camera->m_matView, &camera->m_matProj);
		m_Zomb[i]->Render();
	}

	return true; };
bool		GAIZombieMgr::Release() { 
	I_CharMgr.Release();
	return true; };
int		GAIZombieMgr::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return true; };


//----------------------------------------------------
// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
//----------------------------------------------------
HRESULT		GAIZombieMgr::CreateResource() {
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->CreateResource();
	}

	return S_OK; };
HRESULT		GAIZombieMgr::DeleteResource() { return S_OK; };



GAIZombieMgr::GAIZombieMgr()
{
}


GAIZombieMgr::~GAIZombieMgr()
{
}