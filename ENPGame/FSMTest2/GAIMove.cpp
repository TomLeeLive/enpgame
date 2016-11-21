#include "_stdafx.h"


GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init()
{
	return true;
}

bool GAIMove::ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMatrixIdentity(&Rotation);
	
	
	
	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; // 임의 행렬에 x,y,z 기입
	Rotation._21 = Up.x;			Rotation._22 = Up.y;			Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	Trans[i]._41 += look.x * g_fSecPerFrame* SPEED;
	Trans[i]._43 += look.z * g_fSecPerFrame* SPEED;
	
	g_pMain->m_Zomb[i]->m_ZombieWorld[i] = Rotation * Trans[i];

	//회전행렬, 이동행렬 반환하기

	return true;
}
bool GAIMove::Frame()
{
	for (int i = 0;i < g_pMain->m_CharNZomb.size();i++)
	{
		if (g_pMain->m_Zomb[i]->vDistance[i] > 70.0f)
		{
			ZombieMgr->RandomMove(i, g_pMain->m_Zomb[i]->vZombiePosition[i]);
			ZombieMove(i, g_pMain->m_Zomb[i]->vLook[i], g_pMain->m_Zomb[i]->vZRight[i], g_pMain->m_Zomb[i]->vZUp[i]);
		}

		G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
		G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;
		
		if (beforeState != G_ZOMB_ST_WALK)
		{
			afterState = G_ZOMB_ST_WALK;
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_FOLLOW];
			if (beforeState != afterState)
			{
				g_pMain->ChangeZombState(i, G_DEFINE_ANI_ZOMB_WLK);
			}
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
	return S_OK;
}


GAIMove::GAIMove()
{
	m_pMainCamera = nullptr;
	ZombieMgr = new GNewZombieMgr;
	pInstance_ = 0;
	for (int i=0; i < ZombieNum; i++)
	D3DXMatrixIdentity(&Trans[i]);

}


GAIMove::~GAIMove()
{
}
