#include "_ai_std.h"

//GAIAttack * GAIAttack::pInstance_ = 0;

void GAIAttack::AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_vADestLook = vZombiePosition - vBoxPosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&m_vADestLook, &m_vADestLook);
	m_vARight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vAUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_vARight, &m_vAUp, &m_vADestLook);
	D3DXVec3Cross(&m_vAUp, &m_vADestLook, &m_vARight);

	//m_vLook = m_vADestLook;
	//m_vZRight = m_vARight;
	//m_vZUp = m_vAUp;

}

bool GAIAttack::Init(GNewZombie* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

	return true;
}

bool GAIAttack::Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);

	D3DXVECTOR3 vPos = D3DXVECTOR3(iMyIndex->m_matZombWld._41,
		iMyIndex->m_matZombWld._42, iMyIndex->m_matZombWld._43);

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	float fDistance = D3DXVec3Length(&Temp);

	if (fDistance > G_DEFINE_AI_ATTACK_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_FOLLOW);
	}
	

	iMyIndex->RotationAndTrans(vHeroPos);

	return true;
}
bool GAIAttack::Render()
{

	return true;
}
bool GAIAttack::Release()
{
	return true;
}
HRESULT GAIAttack::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIAttack::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIAttack::GAIAttack()
{
	//m_pMainCamera = nullptr;
	//ZombieMgr = new GNewZombieMgr;
	//pInstance_ = 0;

	GAISeq::InitGSeq();


}


GAIAttack::~GAIAttack()
{
}
int GAIAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

