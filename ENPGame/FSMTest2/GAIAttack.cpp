#include "_stdafx.h"

//GAIAttack * GAIAttack::pInstance_ = 0;

void GAIAttack::AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_vADestLook = vZombiePosition - vBoxPosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&m_vADestLook, &m_vADestLook);
	m_vARight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vAUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&m_vARight, &m_vAUp, &m_vADestLook);
	D3DXVec3Cross(&m_vAUp, &m_vADestLook, &m_vARight);

	//m_vLook = m_vADestLook;
	//m_vZRight = m_vARight;
	//m_vZUp = m_vAUp;

}

bool GAIAttack::Init(int iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");

	return true;
}
bool GAIAttack::ZombieAttack(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&Rotation);
	D3DXMatrixIdentity(&Trans);

	/*
	Rotation = g_pMain->m_Zomb[i]->m_matRot;
	Trans = g_pMain->m_Zomb[i]->m_matTrans;

	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; // 임의 행렬에 x,y,z 기입
	Rotation._21 = Up.x;				Rotation._22 = Up.y;				Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	Trans._41 -= look.x * g_fSecPerFrame * SPEED;
	Trans._43 -= look.z * g_fSecPerFrame * SPEED;

	g_pMain->m_Zomb[i]->m_vZombPos.x = g_pMain->m_Zomb[i]->m_matZombWld._41;
	g_pMain->m_Zomb[i]->m_vZombPos.z = g_pMain->m_Zomb[i]->m_matZombWld._43;

	g_pMain->m_Zomb[i]->m_matRot = Rotation;
	g_pMain->m_Zomb[i]->m_matTrans = Trans;
	*/
	return true;
}
bool GAIAttack::Frame(int iMyIndex)
{
	/*
			//G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
			//G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;

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
					g_pMain->ChangeZombState(iMyIndex, G_DEFINE_ANI_ZOMB_ATT);
					AttackMove(iMyIndex, g_pMain->m_Zomb[iMyIndex]->m_vBoxPos, g_pMain->m_Zomb[iMyIndex]->m_vZombPos);
					ZombieAttack(iMyIndex,m_vLook,m_vZRight, m_vZUp);
				
				}
				else
				{
					g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_FOLLOW];
				}

			}
	
	*/
	return true;
}
bool GAIAttack::Render()
{

	return true;
}
bool GAIAttack::Release()
{
	return true;
}
HRESULT GAIAttack::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIAttack::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIAttack::GAIAttack()
{
	//m_pMainCamera = nullptr;
	//ZombieMgr = new GNewZombieMgr;
	//pInstance_ = 0;

	GAISeq::InitGSeq();


}


GAIAttack::~GAIAttack()
{
}
int GAIAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (m_pMainCamera != nullptr)
	//{
	//	m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	//}
	return -1;
}

