#include "_stdafx.h"


GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");


	Trans = g_pMain->m_Zomb[iMyIndex]->m_ZombieWorld;
	
	return true;
}
bool GAIMove::ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
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

	//g_pMain->m_Zomb[i]->m_ZombieWorld += Rotation[i] * Trans[i];
	//g_pMain->m_Zomb[i]->m_ZombieWorld._41 += look.x * g_fSecPerFrame * SPEED;
	//g_pMain->m_Zomb[i]->m_ZombieWorld._43 += look.x * g_fSecPerFrame * SPEED;

	//회전행렬, 이동행렬 반환하기

	return true;
}
bool GAIMove::Frame(int iMyIndex)
{

		//G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
		//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

		D3DXVECTOR3 Temp = g_pMain->m_Zomb[iMyIndex]->vBoxPosition - g_pMain->m_Zomb[iMyIndex]->vZombiePosition;
		float a = D3DXVec3Length(&Temp);
		g_pMain->m_Zomb[iMyIndex]->vDistance = a;


		if (g_pMain->m_Zomb[iMyIndex]->vDistance > 70.0f)
		{
				g_pMain->m_Zomb[iMyIndex]->RandomMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vZombiePosition);
				ZombieMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->vLook, g_pMain->m_Zomb[iMyIndex]->m_vZRight, g_pMain->m_Zomb[iMyIndex]->m_vZUp);
		}
		else if(g_pMain->m_Zomb[iMyIndex]->vDistance < 70.0f)
		{
			g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_FOLLOW];
		}
	
	return true;
}
bool GAIMove::Render()
{


	return true;
}
bool GAIMove::Release()
{

	return true;
}
HRESULT GAIMove::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIMove::DeleteResource()
{
	HRESULT hr;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}


GAIMove::GAIMove()
{
//	m_pMainCamera = nullptr;
	//ZombieMgr = new GNewZombieMgr;
	pInstance_ = 0;
	for (int i = 0; i < ZombieNum; i++)
	{
	D3DXMatrixIdentity(&Trans);
	D3DXMatrixIdentity(&Rotation);
	}
}


GAIMove::~GAIMove()
{
}
