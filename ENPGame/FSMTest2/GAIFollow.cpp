#include "_stdafx.h"

GAIFollow * GAIFollow::pInstance_ = 0;

bool GAIFollow::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");


	Trans = g_pMain->m_Zomb[iMyIndex]->m_ZombieWorld;
	
	return true;
}

bool GAIFollow::ZombieFollow(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
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
bool GAIFollow::Frame(int iMyIndex)
{

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
			g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_ATTACK];
		}
		else
		{
			g_pMain->m_Zomb[iMyIndex]->FollowMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vBoxPosition, g_pMain->m_Zomb[iMyIndex]->vZombiePosition);
			ZombieFollow(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vLook, g_pMain->m_Zomb[iMyIndex]->m_vZRight, g_pMain->m_Zomb[iMyIndex]->m_vZUp);
		}
			
	}
	
	return true;
}
bool GAIFollow::Render()
{
	return true;
}
bool GAIFollow::Release()
{
	return true;
}
HRESULT GAIFollow::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIFollow::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIFollow::GAIFollow()
{
	//ZombieMgr = new GNewZombieMgr;
	pInstance_ = 0;

	D3DXMatrixIdentity(&Trans);
	D3DXMatrixIdentity(&Rotation);
	
}


GAIFollow::~GAIFollow()
{
}
int GAIFollow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

