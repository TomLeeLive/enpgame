#include "_stdafx.h"
#include <time.h>

GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init()
{
	return true;
}
bool GAIMove::Frame()
{
	 m_fSecondPerFrmae += g_fSecPerFrame;



	// 이동을 위한 임의의 목적지 조성 
	srand(time(NULL));
	if ((rand() * 3) % 2 == 0)
	{
		RandomPoint.x = -((rand() * 3) % 50);
	}
	else
	{
		RandomPoint.x = (rand() * 3) % 50;
	}
	/*if ((rand() * 3) % 2 == 0)
	{
		RandomPoint.y = -((rand() * 3) % 60);
	}
	else
	{
		RandomPoint.y = (rand() * 3) % 60;
	}*/
	if ((rand() * 3) % 2 == 0)
	{
		RandomPoint.z = -((rand() * 3) % 50);
	}
	else
	{
		RandomPoint.z = (rand() * 3) % 50;
	}


	// 랜덤 목적지
	RandomDestination.x = RandomPoint.x;
	RandomDestination.y = 0.0f;
	RandomDestination.z = RandomPoint.z;

	//이동할 방향으로 회전 -1
	// 적 박스의 포지션을 벡터로 저장후 가려는방향(주인공) - vPos 하여 목적지 벡터 구함
	D3DXVECTOR3 vPos = D3DXVECTOR3(g_pMain->m_matWorld1._41, 0.0f, g_pMain->m_matWorld1._43);
	D3DXVECTOR3 vRandomDest = RandomDestination - vPos;
	D3DXVECTOR3 vDestLook = vPos-RandomDestination; // 랜덤 목적지 벡터
	D3DXVec3Normalize(&vDestLook, &vDestLook);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vDestLook);
	D3DXVec3Cross(&vUp, &vDestLook, &vRight);

	//이동할 방향으로 회전 -2
	 //구해진 목적지 벡터로 방향을 회전
	D3DXMatrixIdentity(&g_pMain->m_Rotation);
	g_pMain->m_Rotation._11 = vRight.x;	    g_pMain->m_Rotation._12 = vRight.y;		g_pMain->m_Rotation._13 = vRight.z; // 임의 행렬에 x,y,z 기입
	g_pMain->m_Rotation._21 = vUp.x;		g_pMain->m_Rotation._22 = vUp.y;		g_pMain->m_Rotation._23 = vUp.z;
	g_pMain->m_Rotation._31 = vDestLook.x;  g_pMain->m_Rotation._32 = vDestLook.y;	g_pMain->m_Rotation._33 = vDestLook.z;


	// 주인공의 위치
	D3DXVECTOR3 vBoxPosition;
	vBoxPosition.x = g_pMain->m_matWorld._41;
	vBoxPosition.z = g_pMain->m_matWorld._43;
	
	//적의 위치
	D3DXVECTOR3 vEnemyBoxPosition;
	vEnemyBoxPosition.x = g_pMain->m_matWorld1._41;
	vEnemyBoxPosition.z = g_pMain->m_matWorld1._43;
	
	//두위치를 빼서 방향을 구한 후 거리계산
	D3DXVECTOR3 ResultLenth = vBoxPosition - vEnemyBoxPosition;
	float Lenth = D3DXVec3Length(&ResultLenth);




	// IDle  로 상태 전이 조건
	if (RandomDestination.x > 0)
	{
		if (m_fSecondPerFrmae > fTime)
		{
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_IDLE];
			m_fSecondPerFrmae = 0.0f;
		}
	}
	

	// 메인박스와의 거리가 5보다 클경우 RandomPoint 로 Rotation 후 이동, 5보다 작을경우 메인 박스를 향해 이동
	if (Lenth > 10)
	{
		if (RandomDestination.x > 0)
		{
			g_pMain->m_matWorld1._41 += 1.0f * g_fSecPerFrame;
		}
		else
		{
			g_pMain->m_matWorld1._41 -= 1.0f  * g_fSecPerFrame;
		}
		/*if (g_pMain->m_matWorld1._42 <= Destination.y)
		{
		g_pMain->m_matWorld1._42 += 1.0f * g_fSecPerFrame;
		}*/
		if (RandomDestination.z > 0)
		{
			g_pMain->m_matWorld1._43 += 1.0f * g_fSecPerFrame;
		}
		else
		{
			g_pMain->m_matWorld1._43 -= 1.0f* g_fSecPerFrame;
		}
	}
	else if(Lenth <5)
	{
		g_pMain->m_matWorld1._41 += ResultLenth.x * g_fSecPerFrame;
		g_pMain->m_matWorld1._43 += ResultLenth.z * g_fSecPerFrame;
	}
	else if(Lenth <1)
	{
		g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_ATTACK];
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
	pInstance_ = 0;
}


GAIMove::~GAIMove()
{
}
