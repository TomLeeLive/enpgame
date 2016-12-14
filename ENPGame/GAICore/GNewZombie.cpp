#include "_ai_std.h"
//#include "GAISeq.h"
void		GNewZombie::ChangeZombState(GNewZombie* iNum, G_AI state) {

	iNum->setState(state);


	GCharacter* pChar0 = NULL;

	switch (state) {
	case 	G_ZOMB_AI_ST_WALK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_WLK);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_ZOMB_AI_ST_WALK];
	}
	break;
	case 	G_ZOMB_AI_ST_IDLE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_IDL);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_ZOMB_AI_ST_IDLE];
	}
	break;
	case 	G_ZOMB_AI_ST_ATTACK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_ATT);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_ZOMB_AI_ST_ATTACK];
	}
	break;
	case 	G_ZOMB_AI_ST_DEAD: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_DIE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_ZOMB_AI_ST_DEAD];
	}
	break;
	case 	G_ZOMB_AI_ST_FOLLOW: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_FLW);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_ZOMB_AI_ST_FOLLOW];
	}
	break;
	}

	iNum->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}
void		GNewZombie::ChangeZombState(GNewZombie* iNum, TCHAR* str) {

	//GCharacter* pChar0 = I_CharMgr.GetPtr(str);
	auto pChar0 = I_CharMgr.GetPtr(str);

	iNum->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

	if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_DIE)) {
		iNum->setState(G_AI_DIE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_DIE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_ATT)) {
		iNum->setState(G_AI_ATTACK);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_ATTACK];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_WLK)) {
		iNum->setState(G_AI_MOVE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_MOVE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_IDL)) {
		iNum->setState(G_AI_IDLE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_IDLE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_FLW)) {
		iNum->setState(G_AI_FOLLOW);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_FOLLOW];
	}
	else {
		iNum->setState(G_AI_IDLE);
	}
}

bool GNewZombie::RotationAndTrans(D3DXVECTOR3 pos) {

	D3DXVECTOR3 vLook_toPos;
	D3DXMATRIX matZombie, matRot, matTrans;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);
	
	matZombie = m_matZombWld;


	//반환받은 방향으로 회전을 하기 위해서..
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_matZombWld._41, m_matZombWld._42, m_matZombWld._43);
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
	matRot._31 = vLook_toPos.x;		matRot._32 = vLook_toPos.y;		matRot._33 = vLook_toPos.z;


	D3DXVECTOR3 vMove = D3DXVECTOR3(matZombie._41, matZombie._42, matZombie._43);
	D3DXVECTOR3 vNewPos;
	vNewPos = vMove - G_DEFINE_AI_MOVE_SPEED * g_fSecPerFrame * vLook_toPos;
	D3DXMatrixTranslation(&matTrans, vNewPos.x, vNewPos.y, vNewPos.z);



	matZombie = matRot * matTrans;

	m_matZombWld = matZombie;

	m_matZombWld._42 = G_DEFINE_CHAR_Y_POS;

	return true;
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
bool	GNewZombie::Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld)
{
	GZombie::Frame();

	if (m_State == G_AI_DIE)
		m_bDead = true;
	else
		m_bDead = false;

	//if( true == m_bDead)
	//	iMyIndex->ChangeZombState(iMyIndex, G_AI_DIE);

	m_pCurrentSeq->Frame(iMyIndex, matHeroWorld);

	return true;
};
bool	GNewZombie::Render(){
	m_pCurrentSeq->Render();
	GZombie::Render(g_pImmediateContext);
	return true;
};
bool	GNewZombie::Release()
{
	m_pCurrentSeq->Release();
	return true;
};


	
GNewZombie::GNewZombie(int iNum) {
	m_iNum = iNum;
	D3DXMatrixIdentity(&m_matZombWld);

	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_State = G_AI_MOVE;
	D3DXMatrixIdentity(&m_matZombWld);
}
GNewZombie::GNewZombie()
{
	m_iNum = 0;
	D3DXMatrixIdentity(&m_matZombWld);
	
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_State = G_AI_MOVE;
	D3DXMatrixIdentity(&m_matZombWld);
	
}


GNewZombie::~GNewZombie()
{
}
