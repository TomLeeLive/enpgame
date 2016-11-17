#include "_stdafx.h"


bool		GN2Zombie::Frame() {
	GZombie::Frame();

	if (g_pMain->GetCurSeq() != G_SEQ_SINGLE || m_bDead == true)
		return false;
	GSeqSinglePlay* seqSinglePlay = (GSeqSinglePlay*)g_pMain->m_pCurrentSeq;

	D3DXVECTOR3 vPlayerPos = seqSinglePlay->m_pFPSCamera[G_HERO_TOM].get()->m_vCameraPos;

	vPlayerPos.y = 0.0f;
	D3DXVECTOR3 vLook_toPlayer;
	D3DXMATRIX matZombie, matScl, matRot, matTrans;
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);


	matZombie = m_matWorld;

	//플레이어 방향으로 회전을 하기 위해서..
	D3DXVECTOR3 vPos = D3DXVECTOR3(matZombie._41, 0.0f, matZombie._43);
	vLook_toPlayer = vPos - vPlayerPos;
	D3DXVec3Normalize(&vLook_toPlayer, &vLook_toPlayer);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vLook_toPlayer);
	D3DXVec3Cross(&vUp, &vLook_toPlayer, &vRight);

	matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
	matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
	matRot._31 = vLook_toPlayer.x;  matRot._32 = vLook_toPlayer.y;  matRot._33 = vLook_toPlayer.z;
	

	D3DXVECTOR3 vMove = D3DXVECTOR3(matZombie._41, matZombie._42, matZombie._43);
	D3DXVECTOR3 vNewPos;
	vNewPos = vMove - 100.0f*g_fSecPerFrame * vLook_toPlayer;
	D3DXMatrixTranslation(&matTrans, vNewPos.x, vNewPos.y, vNewPos.z);
	
	matZombie = matScl * matRot * matTrans;

	m_matWorld = matZombie;

	m_matWorld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;

	return true;
}

GN2Zombie::GN2Zombie()
{
}


GN2Zombie::~GN2Zombie()
{
}
