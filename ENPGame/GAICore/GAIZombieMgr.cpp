#include "_ai_std.h"




bool GAIZombieMgr::Load(int iNum)
{

	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie.gci")))
	{
		return false;
	}

	for (int i = 0; i < iNum; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

		shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
		pObjA->setState(G_AI_IDLE);

		pObjA->m_matZombWld._41 = (rand() * 3) % 303;
		pObjA->m_matZombWld._42 = 40.0f;
		pObjA->m_matZombWld._43 = (rand() * 3) % 303;

		TCHAR buf[256];
		_stprintf_s(buf, _countof(buf), _T("x:%f, z:%f\n"), pObjA->m_matZombWld._41, pObjA->m_matZombWld._43);
		OutputDebugString(buf);

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);

		pObjA->Init();
		for (int j = 0; j < G_AI_CNT; j++)
		{
			pObjA->m_GameSeq[j]->Init(pObjA.get());
		}
	
		//OBB 박스 Init.
		pObjA->m_OBB.Init(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);

		m_Zomb.push_back(pObjA);
	}

	return true;
}
bool		GAIZombieMgr::Init(int iNum) { 

	srand((unsigned)time(NULL));

//	I_CharMgr.Init();
	Load(iNum);

#ifdef G_MACRO_TESTCODE_ADD

	/*for (int i = 0; i < iNum; i++)
	{
		auto pZomb = make_shared<GNewZombie>(i);
		m_Zomb.push_back(pZomb);

	}
	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();

	for (; _F != _L; ++_F)
	{
		(*_F)->Init();
		for (int j = 0; j < G_AI_CNT; j++)
		{
			(*_F)->m_GameSeq[j]->Init((*_F).get());
		}
	}*/
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


	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->Frame((*_F).get(), matHeroWorld);
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
	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->SetMatrix(&(*_F)->m_matZombWld, &camera->m_matView, &camera->m_matProj);
		(*_F)->Render();
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

	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->CreateResource();
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
