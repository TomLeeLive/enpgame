#include "_ai_std.h"




bool GAIZombieMgr::Load()
{

	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie.gci")))
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

#ifdef G_MACRO_TESTCODE_ADD
	auto a = m_Zomb.begin();

	std::advance(a, 1);
	(*a)->Init();
	//(*a)->

	for (auto a = m_Zomb.begin();a != m_Zomb.end;std::advance(a, 1))
	{
		(*a)->Init();
		for (int j = 0; j < G_AI_CNT; j++)
		{
			(*a)->m_GameSeq[j]->Init((*a).get());
		}
	}
#else
	for (int i = 0; i < m_Zomb.size(); i++)
	{
	m_Zomb[i]->Init();
	for (int j = 0; j < G_AI_CNT; j++)
	{
	m_Zomb[i]->m_GameSeq[j]->Init(m_Zomb[i].get());
	}

	}
#endif
	
	

	
	return true; };
bool		GAIZombieMgr::Frame(D3DXMATRIX matHeroWorld) {

#ifdef G_MACRO_TESTCODE_ADD
	for (auto a = m_Zomb.begin();a != m_Zomb.end;std::advance(a, 1))
	{
		(*a)->Frame((*a).get(), matHeroWorld);
	}
#else
	for (int i = 0; i < m_Zomb.size(); i++)
	{
	m_Zomb[i]->Frame(m_Zomb[i].get(), matHeroWorld);
	}
#endif

	



	return true; };
bool		GAIZombieMgr::Render(GCamera* camera) {
	
#ifdef G_MACRO_TESTCODE_ADD
	for (auto a = m_Zomb.begin();a != m_Zomb.end;std::advance(a, 1))
	{
		(*a)->SetMatrix(&(*a)->m_matZombWld, &camera->m_matView, &camera->m_matProj);
	}
#else
	for (int i = 0; i < m_Zomb.size(); i++)
	{
	m_Zomb[i]->SetMatrix(&m_Zomb[i]->m_matZombWld, &camera->m_matView, &camera->m_matProj);
	m_Zomb[i]->Render();
	}
#endif





	return true; };
bool		GAIZombieMgr::Release() { 
	I_CharMgr.Release();
	return true; };
int		GAIZombieMgr::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return true; };


//----------------------------------------------------
// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
//----------------------------------------------------
HRESULT		GAIZombieMgr::CreateResource() {
	

#ifdef G_MACRO_TESTCODE_ADD
	for (auto a = m_Zomb.begin();a != m_Zomb.end;std::advance(a, 1))
	{
		(*a)->CreateResource();
	}
#else
	for (int i = 0; i < m_Zomb.size(); i++)
	{
		m_Zomb[i]->CreateResource();
	}
#endif




	return S_OK; };
HRESULT		GAIZombieMgr::DeleteResource() { return S_OK; };



GAIZombieMgr::GAIZombieMgr()
{
}


GAIZombieMgr::~GAIZombieMgr()
{
}
