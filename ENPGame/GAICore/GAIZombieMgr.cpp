#include "_ai_std.h"




bool GAIZombieMgr::Load(int iNum, D3DXVECTOR3 position)
{

	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharZombie.gci")))
	{
		return false;
	}

	for (int i = 0; i < iNum; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

		shared_ptr<GNewZombie> pObjA = make_shared<GNewZombie>();
		pObjA->setState(G_AI_IDLE);

		pObjA->m_matZombWld._41 = position.x +((rand() * 3) % 303);
		pObjA->m_matZombWld._42 = 40.0f;
		pObjA->m_matZombWld._43 = position.z + ((rand() * 3) % 303);

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

	D3DXVECTOR3 StartPosition(500.0f, 0.0f, 500.0f);
	srand((unsigned)time(NULL));
	Load(iNum, StartPosition);

	
	
	return true; };

bool		GAIZombieMgr::Frame(D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2) {



	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->Frame((*_F).get(), matHeroWorld, matHeroWorld2);
	}

	return true; };

bool		GAIZombieMgr::Render(GCamera* camera) {
	
	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->SetMatrix(&(*_F)->m_matZombWld, &camera->m_matView, &camera->m_matProj);
		(*_F)->Render();
	}



	return true; };
bool		GAIZombieMgr::Release() { 
	I_CharMgr.Release();
	return true; };
int		GAIZombieMgr::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return true; };


//----------------------------------------------------
// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
//----------------------------------------------------
HRESULT		GAIZombieMgr::CreateResource() {

	list<shared_ptr<GNewZombie>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GNewZombie>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->CreateResource();
	}




	return S_OK; };
HRESULT		GAIZombieMgr::DeleteResource() { return S_OK; };



GAIZombieMgr::GAIZombieMgr()
{
}


GAIZombieMgr::~GAIZombieMgr()
{
}
