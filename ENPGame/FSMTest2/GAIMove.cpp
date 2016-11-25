#include "_stdafx.h"


GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init()
{
	for (int i = 0;i < G_DEFINE_MAX_AI_ZOMBIE;i++)
	{
		Trans[i] = g_pMain->m_Zomb[i]->m_ZombieWorld;
	}
	return true;
}
bool GAIMove::ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	Rotation[i]._11 = Right.x;			Rotation[i]._12 = Right.y;			Rotation[i]._13 = Right.z; // 임의 행렬에 x,y,z 기입
	Rotation[i]._21 = Up.x;				Rotation[i]._22 = Up.y;				Rotation[i]._23 = Up.z;
	Rotation[i]._31 = look.x;			Rotation[i]._32 = look.y;			Rotation[i]._33 = look.z;

	
	Trans[i]._41 -= look.x * g_fSecPerFrame * SPEED;
	Trans[i]._43 -= look.z * g_fSecPerFrame * SPEED;

	
	g_pMain->m_Zomb[i]->vZombiePosition.x = g_pMain->m_Zomb[i]->m_ZombieWorld._41;
	g_pMain->m_Zomb[i]->vZombiePosition.z = g_pMain->m_Zomb[i]->m_ZombieWorld._43;
	
	g_pMain->m_Rotation[i] = Rotation[i];
	g_pMain->m_Trans[i] = Trans[i];

	//g_pMain->m_Zomb[i]->m_ZombieWorld += Rotation[i] * Trans[i];
	//g_pMain->m_Zomb[i]->m_ZombieWorld._41 += look.x * g_fSecPerFrame * SPEED;
	//g_pMain->m_Zomb[i]->m_ZombieWorld._43 += look.x * g_fSecPerFrame * SPEED;

	//회전행렬, 이동행렬 반환하기

	return true;
}
bool GAIMove::Frame()
{
	for (int i = 0;i < G_DEFINE_MAX_AI_ZOMBIE;i++)
	{
		//G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
		//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

		D3DXVECTOR3 Temp = g_pMain->m_Zomb[i]->vBoxPosition - g_pMain->m_Zomb[i]->vZombiePosition;
		float a = D3DXVec3Length(&Temp);
		g_pMain->m_Zomb[i]->vDistance = a;


		if (g_pMain->m_Zomb[i]->vDistance > 70.0f)
		{
				ZombieMgr->RandomMove(i, g_pMain->m_Zomb[i]->vZombiePosition);
				ZombieMove(i, g_pMain->m_Zomb[i]->vLook, g_pMain->m_Zomb[i]->vZRight, g_pMain->m_Zomb[i]->vZUp);
		}
		else if(g_pMain->m_Zomb[i]->vDistance < 70.0f)
		{
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_FOLLOW];
		}
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
	m_pMainCamera = nullptr;
	ZombieMgr = new GNewZombieMgr;
	pInstance_ = 0;
	for (int i = 0; i < ZombieNum; i++)
	{
	D3DXMatrixIdentity(&Trans[i]);
	D3DXMatrixIdentity(&Rotation[i]);
	}
}


GAIMove::~GAIMove()
{
}
