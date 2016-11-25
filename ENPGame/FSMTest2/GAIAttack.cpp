#include "_stdafx.h"

GAIAttack * GAIAttack::pInstance_ = 0;

bool GAIAttack::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

	return true;
}
bool GAIAttack::ZombieAttack(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; // 임의 행렬에 x,y,z 기입
	Rotation._21 = Up.x;				Rotation._22 = Up.y;				Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	Trans._41 -= look.x * g_fSecPerFrame * SPEED;
	Trans._43 -= look.z * g_fSecPerFrame * SPEED;

	g_pMain->m_Zomb[i]->vZombiePosition.x = g_pMain->m_Zomb[i]->m_ZombieWorld._41;
	g_pMain->m_Zomb[i]->vZombiePosition.z = g_pMain->m_Zomb[i]->m_ZombieWorld._43;

	g_pMain->m_Zomb[i]->m_Rotation = Rotation;
	g_pMain->m_Zomb[i]->m_Trans = Trans;

	return true;
}
bool GAIAttack::Frame(int iMyIndex)
{

			//G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
			//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

			D3DXVECTOR3 Temp = g_pMain->m_Zomb[iMyIndex]->vBoxPosition - g_pMain->m_Zomb[iMyIndex]->vZombiePosition;
			float a = D3DXVec3Length(&Temp);
			g_pMain->m_Zomb[iMyIndex]->vDistance = a;

			if (g_pMain->m_Zomb[iMyIndex]->vDistance > 70.0f)
			{
				g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_MOVE];
			}

			else if (g_pMain->m_Zomb[iMyIndex]->vDistance < 70.0f)
			{
				if (g_pMain->m_Zomb[iMyIndex]->vDistance < 30.0f)
				{
					g_pMain->ChangeZombState(iMyIndex, G_DEFINE_ANI_ZOMB_ATT);
					g_pMain->m_Zomb[iMyIndex]->AttackMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vBoxPosition, g_pMain->m_Zomb[iMyIndex]->vZombiePosition);
					ZombieAttack(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vLook, g_pMain->m_Zomb[iMyIndex]->m_vZRight, g_pMain->m_Zomb[iMyIndex]->m_vZUp);
				
				}
				else
				{
					g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_FOLLOW];
				}

			}
	

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
	m_pMainCamera = nullptr;
	//ZombieMgr = new GNewZombieMgr;
	pInstance_ = 0;

		D3DXMatrixIdentity(&Trans);
		D3DXMatrixIdentity(&Rotation);

}


GAIAttack::~GAIAttack()
{
}
int GAIAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

