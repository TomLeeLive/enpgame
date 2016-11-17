#include "_stdafx.h"


GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init()
{
	m_Zombie = new GNewZombie;
	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");
	g_pMain->m_HeroObj[0]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	return true;
}
void GAIMove::RendomMove() {


	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//									랜덤 목적지 만들기
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		srand(time(NULL));
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint[i].x = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint[i].x = (rand() * 3) % 50;
		}
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint[i].z = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint[i].z = (rand() * 3) % 50;
		}

		// 랜덤 목적지
		m_RandomDestination[i].x = m_RandomPoint[i].x;
		m_RandomDestination[i].y = 0.0f;
		m_RandomDestination[i].z = m_RandomPoint[i].z;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 랜덤 목적지 방향으로 회전 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		vZombiePosition[i] = D3DXVECTOR3(g_pMain->m_HeroObj[i]->m_worldMat._41, 0.0f, g_pMain->m_HeroObj[i]->m_worldMat._43);
		vBoxPosition[i] = D3DXVECTOR3(g_pMain->m_matBoxWorld._41, 0.0f, g_pMain->m_matBoxWorld._43);
		vRDestLook1[i] = m_RandomDestination[i] - vZombiePosition[i]; // 정규화 안한 랜덤 목적지 방향 벡터
		vRDestLook[i] = m_RandomDestination[i] - vZombiePosition[i]; // 랜덤 목적지 방향 벡터
		D3DXVec3Normalize(&vRDestLook[i], &vRDestLook[i]);
		vZRight[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vZUp[i]= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vZRight[i], &vZUp[i], &vRDestLook[i]);
		D3DXVec3Cross(&vZUp[i], &vRDestLook[i], &vZRight[i]);



		D3DXMatrixIdentity(&m_RandomRotation[i]);
		m_RandomRotation[i]._11 = vZRight[i].x;			m_RandomRotation[i]._12 = vZRight[i].y;			m_RandomRotation[i]._13 = vZRight[i].z; // 임의 행렬에 x,y,z 기입
		m_RandomRotation[i]._21 = vZUp[i].x;				m_RandomRotation[i]._22 = vZUp[i].y;		m_RandomRotation[i]._23 = vZUp[i].z;
		m_RandomRotation[i]._31 = vRDestLook[i].x;		m_RandomRotation[i]._32 = vRDestLook[i].y;		m_RandomRotation[i]._33 = vRDestLook[i].z;

		vDistance[i] = vBoxPosition[i] - vZombiePosition[i];
		ZombieDistance[i] = D3DXVec3Length(&vDistance[i]);
	}
}
bool GAIMove::Frame()
{
	 RendomMove();

	 for (int i = 0;i < 5;i++)
	 {
		 hp = 100;  m_Z_Look[i] = vRDestLook1[i];
		 D3DXMatrixIdentity(&m_Z_Trans[i]);

		 if (ZombieDistance[i] > 70.0f) {
			 m_Zombie->ZombieMove(hp, m_Z_Look[i], m_Z_Trans[i], m_RandomRotation[i]);
		 }
		 else if (ZombieDistance[i] < 70.0f) {
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
	return S_OK;
}


GAIMove::GAIMove()
{
	m_pMainCamera = nullptr;
	pInstance_ = 0;

}


GAIMove::~GAIMove()
{
}
