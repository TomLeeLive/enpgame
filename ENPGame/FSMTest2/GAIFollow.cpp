#include "_stdafx.h"

//GAIFollow * GAIFollow::pInstance_ = 0;

void GAIFollow::FollowMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_vBDestLook = vBoxPosition - vZombiePosition;//- vZombiePosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&m_vBDestLook, &m_vBDestLook);
	m_vBRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vBUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_vBRight, &m_vBUp, &m_vBDestLook);
	D3DXVec3Cross(&m_vBUp, &m_vBDestLook, &m_vBRight);


	//m_vLook = m_vBDestLook;
	//m_vZRight = m_vBRight;
	//m_vZUp = m_vBUp;

}

bool GAIFollow::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");


	//Trans = g_pMain->m_Zomb[iMyIndex]->m_ZombieWorld;
	
	return true;
}

bool GAIFollow::ZombieFollow(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&Rotation);
	D3DXMatrixIdentity(&Trans);

	/*
	Rotation = g_pMain->m_Zomb[i]->m_matRot;
	Trans = g_pMain->m_Zomb[i]->m_matZombWld;

	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; 
	Rotation._21 = Up.x;			Rotation._22 = Up.y;			Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	Trans._41 += look.x * g_fSecPerFrame * SPEED;
	Trans._43 += look.z * g_fSecPerFrame * SPEED;

	g_pMain->m_Zomb[i]->m_vZombPos.x = g_pMain->m_Zomb[i]->m_matZombWld._41;
	g_pMain->m_Zomb[i]->m_vZombPos.z = g_pMain->m_Zomb[i]->m_matZombWld._43;

	g_pMain->m_Zomb[i]->m_matRot = Rotation;
	g_pMain->m_Zomb[i]->m_matTrans = Trans;
	*/
	return true;
}
bool GAIFollow::Frame(int iMyIndex)
{
	/*
	D3DXVECTOR3 Temp = g_pMain->m_Zomb[iMyIndex]->m_vBoxPos - g_pMain->m_Zomb[iMyIndex]->m_vZombPos;
	float a = D3DXVec3Length(&Temp);
	m_fDistance = a;


	if (m_fDistance > 70.0f)
	{
		g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_MOVE];
	}

	else if (m_fDistance < 70.0f)
	{
		if (m_fDistance < 30.0f)
		{
			g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_ATTACK];
		}
		else
		{
			FollowMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->m_vBoxPos,g_pMain->m_Zomb[iMyIndex]->m_vZombPos);
			ZombieFollow(iMyIndex,m_vLook, m_vZRight, m_vZUp);
		}
			
	}
	*/
	return true;
}
bool GAIFollow::Render()
{
	return true;
}
bool GAIFollow::Release()
{
	return true;
}
HRESULT GAIFollow::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIFollow::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIFollow::GAIFollow()
{
	//ZombieMgr = new GNewZombieMgr;
	//pInstance_ = 0;

	GAISeq::InitGSeq();
	
}


GAIFollow::~GAIFollow()
{
}
int GAIFollow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

