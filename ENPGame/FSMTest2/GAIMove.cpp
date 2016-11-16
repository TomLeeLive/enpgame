#include "_stdafx.h"
#include <time.h>

GAIMove * GAIMove::pInstance_ = 0;

bool GAIMove::Init()
{
	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");
	g_pMain->m_HeroObj[0]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
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


	//좀비 랜덤쪽으로 회전(Rotation) -1
	// 좀비의 포지션을 vPos벡터로 저장후 랜덤방향 vRandomDest를  RandomDestination- vPos 하여 목적지 벡터 구함
	D3DXVECTOR3 vZombiePosition = D3DXVECTOR3(g_pMain->m_matZombieWorld._41, 0.0f, g_pMain->m_matZombieWorld._43);
	D3DXVECTOR3 vRandomDest = RandomDestination - vZombiePosition;// 정규화 하지 않는 랜덤 목적지 벡터
	D3DXVECTOR3 vRDestLook = RandomDestination - vZombiePosition; // 정규화 할 랜덤 목적지 벡터
	D3DXVec3Normalize(&vRDestLook, &vRDestLook);
	D3DXVECTOR3 vZRight, vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vZRight, &vZUp, &vRDestLook);
	D3DXVec3Cross(&vZUp, &vRDestLook, &vZRight);

	//좀비 랜덤쪽으로 회전(Rotation) -2
	 //구해진 목적지 벡터로 방향을 회전
	D3DXMatrixIdentity(&g_pMain->m_RandomRotation);
	g_pMain->m_RandomRotation._11 = vZRight.x;			 g_pMain->m_RandomRotation._12 = vZRight.y;				g_pMain->m_RandomRotation._13 = vZRight.z; // 임의 행렬에 x,y,z 기입
	g_pMain->m_RandomRotation._21 = vZUp.x;				 g_pMain->m_RandomRotation._22 = vZUp.y;				g_pMain->m_RandomRotation._23 = vZUp.z;
	g_pMain->m_RandomRotation._31 = vRDestLook.x;		 g_pMain->m_RandomRotation._32 = vRDestLook.y;			g_pMain->m_RandomRotation._33 = vRDestLook.z;


	
	////좀비 주인공으로 회전(Rotation) -1
	D3DXVECTOR3 vBoxPosition = D3DXVECTOR3(g_pMain->m_matWorld._41, 0.0f, g_pMain->m_matWorld._43);
	D3DXVECTOR3 vBoxDest = RandomDestination - vBoxPosition;// 정규화 하지 않는 박스로의 목적지 벡터
	D3DXVECTOR3 vBDestLook = RandomDestination - vBoxPosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&vBDestLook, &vBDestLook);
	D3DXVECTOR3 vBRight, vBUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vBRight, &vBUp, &vBDestLook);
	D3DXVec3Cross(&vBUp, &vBDestLook, &vBRight);
	

	//좀비 랜덤쪽으로 회전(Rotation) -2
	//구해진 목적지 벡터로 방향을 회전
	D3DXMatrixIdentity(&g_pMain->m_BoxRotation);
	g_pMain->m_BoxRotation._11 = vBRight.x;			 g_pMain->m_BoxRotation._12 = vBRight.y;			g_pMain->m_BoxRotation._13 = vBRight.z; // 임의 행렬에 x,y,z 기입
	g_pMain->m_BoxRotation._21 = vBUp.x;			 g_pMain->m_BoxRotation._22 = vBUp.y;				g_pMain->m_BoxRotation._23 = vBUp.z;
	g_pMain->m_BoxRotation._31 = vRDestLook.x;		 g_pMain->m_BoxRotation._32 = vRDestLook.y;			g_pMain->m_BoxRotation._33 = vRDestLook.z;
	

	
	//두위치를 빼서 방향을 구한 후 거리계산
	D3DXVECTOR3 ResultLenth = vBoxPosition - vZombiePosition;
	float Lenth = D3DXVec3Length(&ResultLenth);


	// 메인박스와의 거리가 60보다 클경우 RandomPoint 로 Rotation 후 이동
	if (Lenth > 70.0f)
	{
		if (RandomDestination.x > 0)
		{
			g_pMain->m_matZombieWorld._41 += RandomDestination.x * g_fSecPerFrame;
		}
		else
		{
			g_pMain->m_matZombieWorld._41 += RandomDestination.x  * g_fSecPerFrame;
		}
		/*if (g_pMain->m_matZombieWorld._42 <= Destination.y)
		{
		g_pMain->m_matZombieWorld._42 += 1.0f * g_fSecPerFrame;
		}*/
		if (RandomDestination.z > 0)
		{
			g_pMain->m_matZombieWorld._43 += RandomDestination.z * g_fSecPerFrame;
		}
		else
		{
			g_pMain->m_matZombieWorld._43 += RandomDestination.z* g_fSecPerFrame;
		}
	
	}
	// 40보다 작을경우 메인 박스를 향해 이동
	else if(Lenth <70.0f)
	{
		g_pMain->m_matZombieWorld._41 += ResultLenth.x * g_fSecPerFrame *2.0f;
		g_pMain->m_matZombieWorld._43 += ResultLenth.z * g_fSecPerFrame *2.0f;
		//20보다 작을경우 Attack
		if (Lenth < 5.0f)
		{
			GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

			g_pMain->m_HeroObj[0]->Set(pChar0,
				pChar0->m_pBoneObject,
				pChar0->m_pBoneObject->m_Scene.iFirstFrame,
				pChar0->m_pBoneObject->m_Scene.iLastFrame);
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_ATTACK];
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
	pInstance_ = 0;
}


GAIMove::~GAIMove()
{
}
