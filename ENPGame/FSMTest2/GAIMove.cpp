#include "_stdafx.h"


//GAIMove * GAIMove::pInstance_ = 0;


void GAIMove::RandomMove(int i, D3DXVECTOR3 vZombiePosition)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//									���� ������ �����
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

	// ���� ������
	m_RandomDestination.x = m_RandomPoint.x;
	m_RandomDestination.y = 0.0f;
	m_RandomDestination.z = m_RandomPoint.z;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���� ������ �������� ȸ���ϱ� ���� ���� ����
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_vRDestLook = vZombiePosition - m_RandomDestination;  // ���� ������ ���� ����
	D3DXVec3Normalize(&m_vRDestLook, &m_vRDestLook);
	m_vZRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_vZRight, &m_vZUp, &m_vRDestLook);
	D3DXVec3Cross(&m_vZUp, &m_vRDestLook, &m_vZRight);

	g_pMain->m_Zomb[i]->m_vLook = m_vRDestLook;
	m_vZRight = m_vZRight;
	m_vZUp = m_vZUp;

}


bool GAIMove::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

	//Trans = g_pMain->m_Zomb[iMyIndex]->m_ZombieWorld;
	
	return true;
}
bool GAIMove::ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&Rotation);
	D3DXMatrixIdentity(&Trans);

	Rotation = g_pMain->m_Zomb[i]->m_matRot;
	Trans = g_pMain->m_Zomb[i]->m_matTrans;

	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; // ���� ��Ŀ�
	Rotation._21 = Up.x;				Rotation._22 = Up.y;				Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	
	Trans._41 -= look.x * g_fSecPerFrame * SPEED;
	Trans._43 -= look.z * g_fSecPerFrame * SPEED;

	
	g_pMain->m_Zomb[i]->m_vZombPos.x = g_pMain->m_Zomb[i]->m_matZombWld._41;
	g_pMain->m_Zomb[i]->m_vZombPos.z = g_pMain->m_Zomb[i]->m_matZombWld._43;
	


	g_pMain->m_Zomb[i]->m_matRot = Rotation;
	g_pMain->m_Zomb[i]->m_matTrans = Trans;

	//ȸ�����, �̵���� ��ȯ�ϱ�

	return true;
}
bool GAIMove::Frame(int iMyIndex)
{

		//G_ZOMB_ST beforeState = g_pMain->m_Zomb[iMyIndex].get()->m_State;
		//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

	
		D3DXVECTOR3 Temp = g_pMain->m_Zomb[iMyIndex]->m_vBoxPos - g_pMain->m_Zomb[iMyIndex]->m_vZombPos;
		float a = D3DXVec3Length(&Temp);

		m_fDistance = a;


		if (m_fDistance > 50.0f)
		{
				RandomMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->m_vZombPos);
				ZombieMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->m_vLook, m_vZRight, m_vZUp);
		}
		else if(m_fDistance < 50.0f)
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
	//pInstance_ = 0;
	GAISeq::InitGSeq();


}


GAIMove::~GAIMove()
{
}
