#include "_stdafx.h"


//GAIMove * GAIMove::pInstance_ = 0;


bool GAIMove::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

	//Trans = g_pMain->m_Zomb[iMyIndex]->m_ZombieWorld;

	return true;
}

void GAIMove::RandomMove(int i, D3DXVECTOR3 vZombiePosition)
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

		m_vRDestLook = m_RandomDestination - vZombiePosition;  // 랜덤 목적지 방향 벡터
		D3DXVec3Normalize(&m_vRDestLook, &m_vRDestLook);
		m_vZRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&m_vZRight, &m_vZUp, &m_vRDestLook);
		D3DXVec3Cross(&m_vZUp, &m_vRDestLook, &m_vZRight);

		m_vLook = m_vRDestLook;
		m_vZRight = m_vZRight;
		m_vZUp = m_vZUp;

		
}


bool GAIMove::ZombieMove(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&Rotation);
	D3DXMatrixIdentity(&Trans);


	Rotation = g_pMain->m_Zomb[i]->m_matRot;
	Trans = g_pMain->m_Zomb[i]->m_matTrans;

	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; 
	Rotation._21 = Up.x;			Rotation._22 = Up.y;			Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	
	Trans._41 += look.x * g_fSecPerFrame * SPEED;
	Trans._43 += look.z * g_fSecPerFrame * SPEED;

	
	g_pMain->m_Zomb[i]->m_vZombPos.x = Trans._41;
	g_pMain->m_Zomb[i]->m_vZombPos.z = Trans._43;
	
	g_pMain->m_Zomb[i]->m_matRot = Rotation;
	g_pMain->m_Zomb[i]->m_matTrans = Trans;

	//g_pMain->m_Zomb[i]->m_matZombWld = Rotation*Trans;

	//회전행렬, 이동행렬 반환하기

	return true;
}
bool GAIMove::Frame(int iMyIndex)
{

		//G_ZOMB_ST beforeState = g_pMain->m_Zomb[iMyIndex].get()->m_State;
		//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

	
		D3DXVECTOR3 Temp = g_pMain->m_Zomb[iMyIndex]->m_vBoxPos - g_pMain->m_Zomb[iMyIndex]->m_vZombPos;
		float Range = D3DXVec3Length(&Temp);
		m_fDistance = Range;
		
		fTime += g_fSecPerFrame;
		//bool bTime = false;


		
		if (m_fDistance > 70.0f)
		{
			if (fTime> 5.0f)
			{
				RandomMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->m_vZombPos);
				fTime = 0.0f;
			}
			ZombieMove(iMyIndex, m_vLook, m_vZRight, m_vZUp);

		}
		else if(m_fDistance < 70.0f)
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
	GAISeq::InitGSeq();
	m_RandomPoint.x = 0.0f;
	m_RandomDestination.x= 0.0f;
	fTime = 10.0f;

}


GAIMove::~GAIMove()
{
}
