#include "_stdafx.h"

void GNewZombie::RandomMove(int i, D3DXVECTOR3 vZombiePosition)
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//									랜덤 목적지 만들기
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		srand(time(NULL));
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint.x = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint.x = (rand() * 3) % 50;
			
		}
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint.z = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint.z = (rand() * 3) % 50;
		}

		// 랜덤 목적지
		m_RandomDestination.x = m_RandomPoint.x;
		m_RandomDestination.y = 0.0f;
		m_RandomDestination.z = m_RandomPoint.z;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 랜덤 목적지 방향으로 회전하기 위한 벡터 구현
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		m_vRDestLook = vZombiePosition - m_RandomDestination;  // 랜덤 목적지 방향 벡터
		D3DXVec3Normalize(&m_vRDestLook, &m_vRDestLook);
		m_vZRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&m_vZRight, &m_vZUp, &m_vRDestLook);
		D3DXVec3Cross(&m_vZUp, &m_vRDestLook, &m_vZRight);

		g_pMain->m_Zomb[i]->vLook = m_vRDestLook;
		g_pMain->m_Zomb[i]->m_vZRight = m_vZRight;
		g_pMain->m_Zomb[i]->m_vZUp = m_vZUp;

}
void GNewZombie::FollowMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition)
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_vBDestLook = vZombiePosition - vBoxPosition;//- vZombiePosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&m_vBDestLook, &m_vBDestLook);
	m_vBRight= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vBUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_vBRight, &m_vBUp, &m_vBDestLook);
	D3DXVec3Cross(&m_vBUp, &m_vBDestLook, &m_vBRight);


	g_pMain->m_Zomb[i]->vLook = m_vBDestLook;
	g_pMain->m_Zomb[i]->m_vZRight = m_vBRight;
	g_pMain->m_Zomb[i]->m_vZUp = m_vBUp;

}

void GNewZombie::AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition) 
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_vADestLook = vZombiePosition - vBoxPosition; // 정규화 할 박스로의 목적지 벡터
		D3DXVec3Normalize(&m_vADestLook, &m_vADestLook);
		m_vARight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vAUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&m_vARight, &m_vAUp, &m_vADestLook);
		D3DXVec3Cross(&m_vAUp, &m_vADestLook, &m_vARight);

		g_pMain->m_Zomb[i]->vLook = m_vADestLook;
		g_pMain->m_Zomb[i]->m_vZRight = m_vARight;
		g_pMain->m_Zomb[i]->m_vZUp = m_vAUp;

}

bool	GNewZombie::Init()
{
	GZombie::Init();
	
	m_GameSeq[G_AI_IDLE] = GAIIdle::CreateInstance();
	m_GameSeq[G_AI_MOVE] = GAIMove::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = GAIFollow::CreateInstance();
	m_GameSeq[G_AI_ATTACK] = GAIAttack::CreateInstance();
	m_GameSeq[G_AI_DIE] = GAIDie::CreateInstance();
	

	
	m_pCurrentSeq = m_GameSeq[G_AI_MOVE];
	
	return true;
};
bool	GNewZombie::Frame(int iMyIndex)
{
	GZombie::Frame();
	m_pCurrentSeq->Frame(iMyIndex);


	vBoxPosition.x = g_pMain->m_matBoxWorld._41;
	vBoxPosition.y = g_pMain->m_matBoxWorld._42;
	vBoxPosition.z = g_pMain->m_matBoxWorld._43;
	

	

	m_ZombieWorld = m_Rotation * m_Trans;
	


	return true;
};
bool	GNewZombie::Render(){
	m_pCurrentSeq->Render();
	GZombie::Render(g_pMain->GetContext());
	return true;
};
bool	GNewZombie::Release()
{
	m_pCurrentSeq->Release();
	return true;
};


	
	
GNewZombie::GNewZombie()
{

	D3DXMatrixIdentity(&m_Rotation);
	D3DXMatrixIdentity(&m_Trans);


	m_State = G_AI_MOVE;
	D3DXMatrixIdentity(&m_ZombieWorld);
	vBoxPosition.x = g_pMain->m_matBoxWorld._41;
	vBoxPosition.y = g_pMain->m_matBoxWorld._42;
	vBoxPosition.z = g_pMain->m_matBoxWorld._43;
	
	hp = 100;
}


GNewZombie::~GNewZombie()
{
}
