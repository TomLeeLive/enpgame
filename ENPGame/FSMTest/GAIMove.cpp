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



	// �̵��� ���� ������ ������ ���� 
	srand(time(NULL));
	if ((rand() * 3) % 2 == 0)
	{
		RandomPoint.x = -((rand() * 3) % 800);
	}
	else
	{
		RandomPoint.x = (rand() * 3) % 800;
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
		RandomPoint.z = -((rand() * 3) % 800);
	}
	else
	{
		RandomPoint.z = (rand() * 3) % 800;
	}


	// ���� ������
	RandomDestination.x = RandomPoint.x;
	/*Destination.y = RandomPoint.y;*/
	RandomDestination.z = RandomPoint.z;

	//�̵��� �������� ȸ�� -1
	// �� �ڽ��� �������� ���ͷ� ������ �����¹���(���ΰ�) - vPos �Ͽ� ������ ���� ����
	D3DXVECTOR3 vPos = D3DXVECTOR3(g_pMain->m_matWorld1._41, 0.0f, g_pMain->m_matWorld1._43);
	D3DXVECTOR3 vDestLook = RandomDestination - vPos; // ������ ����
	D3DXVec3Normalize(&vDestLook, &vDestLook);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vDestLook);
	D3DXVec3Cross(&vUp, &vDestLook, &vRight);

	//�̵��� �������� ȸ�� -2
	 //������ ������ ���ͷ� ������ ȸ��
	D3DXMatrixIdentity(&g_pMain->m_Rotation);
	g_pMain->m_Rotation._11 = vRight.x;	    g_pMain->m_Rotation._12 = vRight.y;		g_pMain->m_Rotation._13 = vRight.z; // ���� ��Ŀ� x,y,z ����
	g_pMain->m_Rotation._21 = vUp.x;		g_pMain->m_Rotation._22 = vUp.y;		g_pMain->m_Rotation._23 = vUp.z;
	g_pMain->m_Rotation._31 = vDestLook.x;  g_pMain->m_Rotation._32 = vDestLook.y;	g_pMain->m_Rotation._33 = vDestLook.z;

	// ���ΰ��� ��ġ
	D3DXVECTOR3 BoxPosition;
	BoxPosition.x = g_pMain->m_matWorld._41;
	BoxPosition.z = g_pMain->m_matWorld._43;
	
	//���� ��ġ
	D3DXVECTOR3 EnemyBoxPosition;
	EnemyBoxPosition.x = g_pMain->m_matWorld1._41;
	EnemyBoxPosition.z = g_pMain->m_matWorld1._43;
	
	//����ġ�� ���� ������ ���� �� �Ÿ����
	D3DXVECTOR3 ResultLenth = BoxPosition - EnemyBoxPosition;
	float Lenth = D3DXVec3Length(&ResultLenth);

	
	// ���ιڽ����� �Ÿ��� 5���� Ŭ��� RandomPoint �� Rotation �� �̵�, 5���� ������� ���� �ڽ��� ���� �̵�
	if (Lenth > 10)
	{
		if (RandomDestination.x > 0)
		{
			g_pMain->m_matWorld1._41 += 1.0f * g_fSecPerFrame;
		}
		else
		{
			g_pMain->m_matWorld1._41 -= 1.0f * g_fSecPerFrame;
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
			g_pMain->m_matWorld1._43 -= 1.0f * g_fSecPerFrame;
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





	if (m_fSecondPerFrmae > fTime)
	{
		g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_IDLE];
		m_fSecondPerFrmae = 0.0f;
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
