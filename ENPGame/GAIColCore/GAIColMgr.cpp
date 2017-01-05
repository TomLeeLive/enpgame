#include "_ai_col_std.h"




bool GAIColMgr::Load(int iNum, D3DXVECTOR3 position)
{

	if (!I_CharMgr.Load(g_pd3dDevice, g_pImmediateContext, _T("data/CharHero2.gci")))
	{
		return false;
	}

	for (int i = 0; i < iNum; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"HERO2_IDLE");

		shared_ptr<GAICol> pObjA = make_shared<GAICol>();
		pObjA->setState(G_AI_COL_IDLE);

		pObjA->m_matWorld._41 = position.x +((rand() * 3) % 303);
		pObjA->m_matWorld._42 = 40.0f;
		pObjA->m_matWorld._43 = position.z + ((rand() * 3) % 303);

		TCHAR buf[256];
		_stprintf_s(buf, _countof(buf), _T("x:%f, z:%f\n"), pObjA->m_matWorld._41, pObjA->m_matWorld._43);
		OutputDebugString(buf);

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);

		pObjA->m_HeroType = G_HERO_JAKE;
		pObjA->Init();
		for (int j = 0; j < G_AI_COL_CNT; j++)
		{
			pObjA->m_GameSeq[j]->Init(pObjA.get());
		}
	
		//OBB �ڽ� Init.
		pObjA->m_OBB.Init(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);

		m_Zomb.push_back(pObjA);
	}

	return true;
}
bool		GAIColMgr::Init(int iNum) {

	//D3DXVECTOR3 StartPosition(500.0f, 40.0f, 500.0f);
	//D3DXVECTOR3 StartPosition2(-500.0f, 40.0f, -500.0f);
	//srand((unsigned)time(NULL));
	//Load(iNum, StartPosition);
	//Load(iNum, StartPosition2);

	
	
	return true; };

bool		GAIColMgr::Frame(D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2) {



	list<shared_ptr<GAICol>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GAICol>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->Frame((*_F).get(), matHeroWorld, matHeroWorld2);
	}

	return true; };
bool		GAIColMgr::Render(D3DXMATRIX matView, D3DXMATRIX matProj) {
	list<shared_ptr<GAICol>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GAICol>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->SetMatrix(&(*_F)->m_matWorld, &matView, &matProj);
		(*_F)->Render();
	}



	return true;
}
bool		GAIColMgr::Render(GCamera* camera) {
	
	list<shared_ptr<GAICol>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GAICol>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		//D3DXMATRIX matWorld;
		//D3DXMatrixIdentity(&matWorld);
		//matWorld._42 = 40.0f;
		(*_F)->SetMatrix(&(*_F)->m_matWorld, &camera->m_matView, &camera->m_matProj);
		(*_F)->Render();
	}



	return true; };
bool		GAIColMgr::Release() { 
	I_CharMgr.Release();
	return true; };
int		GAIColMgr::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return true; };


//----------------------------------------------------
// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
//----------------------------------------------------
HRESULT		GAIColMgr::CreateResource() {

	list<shared_ptr<GAICol>>::iterator _F = m_Zomb.begin();
	list<shared_ptr<GAICol>>::iterator _L = m_Zomb.end();
	for (; _F != _L; ++_F)
	{
		(*_F)->CreateResource();
	}




	return S_OK; };
HRESULT		GAIColMgr::DeleteResource() { return S_OK; };



GAIColMgr::GAIColMgr()
{
}


GAIColMgr::~GAIColMgr()
{
}
