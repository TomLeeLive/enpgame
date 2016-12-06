#include "_stdafx.h"



bool GNewZombie::RotationAndTrans(D3DXVECTOR3 pos) {

	D3DXVECTOR3 vLook_toPos;
	D3DXMATRIX matZombie, matScl, matRot, matTrans;
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);

	matZombie = m_matZombWld;


	//플레이어 방향으로 회전을 하기 위해서..
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_matZombWld._41, 0.0f, m_matZombWld._43);
	vLook_toPos = vPos - pos;

	if (abs(vPos.x - pos.x) < G_DEFINE_AI_ALMOST_ZERO && abs(vPos.z - pos.z) < G_DEFINE_AI_ALMOST_ZERO)
	{
		TCHAR buf[256];
		_stprintf_s(buf, _countof(buf), _T("ALMOST_ZERO\n"));
		OutputDebugString(buf);

		return false;
	}



	D3DXVec3Normalize(&vLook_toPos, &vLook_toPos);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vLook_toPos);
	D3DXVec3Cross(&vUp, &vLook_toPos, &vRight);

	matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
	matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
	matRot._31 = vLook_toPos.x;  matRot._32 = vLook_toPos.y;  matRot._33 = vLook_toPos.z;

	//if (m_State == G_ZOMB_ST_WALK){
	D3DXVECTOR3 vMove = D3DXVECTOR3(matZombie._41, matZombie._42, matZombie._43);
	D3DXVECTOR3 vNewPos;
	vNewPos = vMove - 100.0f*g_fSecPerFrame * vLook_toPos;
	D3DXMatrixTranslation(&matTrans, vNewPos.x, vNewPos.y, vNewPos.z);
	//}
	matZombie = matScl * matRot * matTrans;

	m_matZombWld = matZombie;

	return true;
	//m_matWorld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;
}

bool	GNewZombie::Init()
{
	GZombie::Init();
	
	m_GameSeq[G_AI_IDLE] = new GAIIdle;//CreateInstance();
	m_GameSeq[G_AI_MOVE] = new GAIMove;//::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = new GAIFollow;//::CreateInstance();
	m_GameSeq[G_AI_ATTACK] = new GAIAttack;//::CreateInstance();
	m_GameSeq[G_AI_DIE] = new GAIDie;//::CreateInstance();
	

	
	m_pCurrentSeq = m_GameSeq[G_AI_IDLE];
	
	return true;
};
bool	GNewZombie::Frame(int iMyIndex)
{
	GZombie::Frame();

	//if (g_pMain->m_Zomb[iMyIndex]->m_State != G_AI_IDLE && m_matTrans._41 != 0.0f)
	//{
	//	m_matZombWld = m_matRot * m_matTrans;
	//	//m_vZombPos.x = m_matWorld._41;
	//	//m_vZombPos.z = m_matWorld._43;
	//}
	
	m_pCurrentSeq->Frame(iMyIndex);

	/*
	m_vBoxPos.x = g_pMain->m_matBoxWorld._41;
	m_vBoxPos.y = g_pMain->m_matBoxWorld._42;
	m_vBoxPos.z = g_pMain->m_matBoxWorld._43;

	*/

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
	/*
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);
	*/
	D3DXMatrixIdentity(&m_matZombWld);
	/*
	m_vZombPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vBoxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	*/
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_State = G_AI_MOVE;
	D3DXMatrixIdentity(&m_matZombWld);
	/*
	m_vBoxPos.x = g_pMain->m_matBoxWorld._41;
	m_vBoxPos.y = g_pMain->m_matBoxWorld._42;
	m_vBoxPos.z = g_pMain->m_matBoxWorld._43;
	*/
	
}


GNewZombie::~GNewZombie()
{
}
