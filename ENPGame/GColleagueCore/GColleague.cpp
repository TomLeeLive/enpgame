#include "_Colleague_std.h"
//#include "GAISeq.h"
void		GColleague::ChangeZombState(GColleague* iNum, G_AI state) {

	iNum->setState(state);


	GCharacter* pChar0 = NULL;

	switch (state) {
	case 	G_JAKE_AI_ST_ESCAPE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_WLK);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_JAKE_AI_ST_ESCAPE];
	}
	break;
	case 	G_JAKE_AI_ST_IDLE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_IDL);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_JAKE_AI_ST_IDLE];
	}
	break;
	case 	G_JAKE_AI_ST_HEAL: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_ATT);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_JAKE_AI_ST_HEAL];
	}
	break;
	case 	G_JAKE_AI_ST_DEAD: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_DIE);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_JAKE_AI_ST_DEAD];
	}
	break;
	case 	G_JAKE_AI_ST_FOLLOW: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_FLW);
		iNum->m_pCurrentSeq = iNum->m_GameSeq[G_JAKE_AI_ST_FOLLOW];
	}
	break;
	}

	iNum->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}

bool GColleague::RotationAndTrans(D3DXVECTOR3 pos) {

	D3DXVECTOR3 vLook_toPos;
	D3DXMATRIX matZombie, matRot, matTrans ;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);

	matZombie = m_matZombWld;


	//반환받은 방향으로 회전을 하기 위해서..
	D3DXVECTOR3 vPos = D3DXVECTOR3(m_matZombWld._41, m_matZombWld._42, m_matZombWld._43);
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
	vNewPos = vMove - G_DEFINE_AI_MOVE_SPEED * g_fSecPerFrame * vLook_toPos;
	D3DXMatrixTranslation(&matTrans, vNewPos.x, vNewPos.y, vNewPos.z);


	matZombie = matRot * matTrans;
	m_matZombWld = matZombie;

	m_matZombWld._42 = G_DEFINE_CHAR_Y_POS;

	return true;
}

bool	GColleague::Init()
{

	m_GameSeq[G_AI_IDLE] = new GAIIdle;//CreateInstance();
	m_GameSeq[G_AI_ESCAPE] = new GAIEscape;//::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = new GAIFollow;//::CreateInstance();
	m_GameSeq[G_AI_HEAL] = new GAIHeal;//::CreateInstance();
	m_GameSeq[G_AI_DIE] = new GAIDie;//::CreateInstance();
	

	
	m_pCurrentSeq = m_GameSeq[G_AI_IDLE];
	
	return true;
};
bool	GColleague::Frame(GColleague* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{

	m_pCurrentSeq->Frame(iMyIndex, matHeroWorld, matHeroWorld2);

	return true;
};
bool	GColleague::Render(){
	m_pCurrentSeq->Render();
	return true;
};
bool	GColleague::Release()
{
	m_pCurrentSeq->Release();
	return true;
};


	
GColleague::GColleague(int iNum) {
	m_iNum = iNum;
	D3DXMatrixIdentity(&m_matZombWld);

	//m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//m_State = G_AI_MOVE;
}
GColleague::GColleague()
{
	m_iNum = 0;
	D3DXMatrixIdentity(&m_matZombWld);
	
	//m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//m_State = G_AI_MOVE;
	
}


GColleague::~GColleague()
{
}
