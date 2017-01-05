#include "_ai_col_std.h"
//#include "GAIColSeq.h"
void		GAICol::ChangeZombState(GAICol* iNum, G_AI_COL state) {

	iNum->setState(state);


	GCharacter* pChar0 = NULL;

	switch (state) {
	case 	G_COL_AI_ST_WALK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_COL_WLK);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_COL_AI_ST_WALK];
	}
	break;
	case 	G_COL_AI_ST_IDLE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_COL_IDL);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_COL_AI_ST_IDLE];
	}
	break;
	case 	G_COL_AI_ST_ATTACK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_COL_ATT);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_COL_AI_ST_ATTACK];
	}
	break;
	case 	G_COL_AI_ST_DEAD: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_COL_DIE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_COL_AI_ST_DEAD];
	}
	break;
	case 	G_COL_AI_ST_FOLLOW: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_COL_FLW);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_COL_AI_ST_FOLLOW];
	}
	break;
	}

	iNum->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}
void		GAICol::ChangeZombState(GAICol* iNum, TCHAR* str) {

	//GCharacter* pChar0 = I_CharMgr.GetPtr(str);
	auto pChar0 = I_CharMgr.GetPtr(str);

	iNum->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

	if (0 == _tcscmp(str, G_DEFINE_ANI_COL_DIE)) {
		iNum->setState(G_AI_COL_DIE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_COL_DIE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_COL_ATT)) {
		iNum->setState(G_AI_COL_ATTACK);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_COL_ATTACK];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_COL_WLK)) {
		iNum->setState(G_AI_COL_MOVE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_COL_MOVE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_COL_IDL)) {
		iNum->setState(G_AI_COL_IDLE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_COL_IDLE];
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_COL_FLW)) {
		iNum->setState(G_AI_COL_FOLLOW);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_AI_COL_FOLLOW];
	}
	else {
		iNum->setState(G_AI_COL_IDLE);
	}
}

bool GAICol::RotationAndTrans(D3DXVECTOR3 pos) {

	D3DXVECTOR3 vLook_toPos;
	D3DXMATRIX matZombie, matRot, matTrans ;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);

	matZombie = m_matWorld;


	//반환받은 방향으로 회전을 하기 위해서..
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
	vLook_toPos = vPos - pos;

	D3DXVec3Normalize(&vLook_toPos, &vLook_toPos);
	D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vRight, &vUp, &vLook_toPos);
	D3DXVec3Cross(&vUp, &vLook_toPos, &vRight);

	matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
	matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
	matRot._31 = vLook_toPos.x;		matRot._32 = vLook_toPos.y;		matRot._33 = vLook_toPos.z;


	D3DXVECTOR3 vMove = D3DXVECTOR3(matZombie._41, matZombie._42, matZombie._43);
	D3DXVECTOR3 vNewPos;
	vNewPos = vMove - G_DEFINE_AI_COL_MOVE_SPEED * g_fSecPerFrame * vLook_toPos;
	D3DXMatrixTranslation(&matTrans, vNewPos.x, vNewPos.y, vNewPos.z);


	matZombie = matRot * matTrans;
	m_matWorld = matZombie;

	m_matWorld._42 = G_DEFINE_CHAR_COL_Y_POS;

	return true;
}

bool	GAICol::Init()
{
	GHero::Init();
	
	m_GameSeq[G_AI_COL_IDLE] = new GAIColIdle;//CreateInstance();
	m_GameSeq[G_AI_COL_MOVE] = new GAIColMove;//::CreateInstance();
	m_GameSeq[G_AI_COL_FOLLOW] = new GAIColFollow;//::CreateInstance();
	m_GameSeq[G_AI_COL_ATTACK] = new GAIColAttack;//::CreateInstance();
	m_GameSeq[G_AI_COL_DIE] = new GAIColDie;//::CreateInstance();
	

	
	m_pCurrentSeq = m_GameSeq[G_AI_COL_IDLE];
	
	return true;
};
bool	GAICol::Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	GHero::Frame();

	if (m_State == G_AI_COL_DIE)
		m_bDead = true;
	else
		m_bDead = false;

	m_pCurrentSeq->Frame(iMyIndex, matHeroWorld, matHeroWorld2);

	return true;
};
bool	GAICol::Render(){
	m_pCurrentSeq->Render();
	GHero::Render(g_pImmediateContext);
	return true;
};
bool	GAICol::Release()
{
	m_pCurrentSeq->Release();
	return true;
};


	
GAICol::GAICol(int iNum) {
	m_iNum = iNum;
	D3DXMatrixIdentity(&m_matWorld);

	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_State = G_AI_COL_MOVE;
}
GAICol::GAICol()
{
	m_iNum = 0;
	D3DXMatrixIdentity(&m_matWorld);
	
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_State = G_AI_COL_MOVE;
	
}


GAICol::~GAICol()
{
}
