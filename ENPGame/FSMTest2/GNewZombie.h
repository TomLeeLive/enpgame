#pragma once
class GNewZombie : public GZombie
{
public:
	D3DXMATRIX	 m_matWorld;
	//D3DXMATRIX	 m_matTrans;
	//D3DXMATRIX	 m_matRot;

	//D3DXMATRIX  m_RandomRotation ;
	//D3DXMATRIX  m_BoxRotation ;
	//D3DXMATRIX  m_RandomRotResult ;
	//D3DXMATRIX  m_BoxRotResult ;
	//D3DXMATRIX  m_TransRotation ;
	//D3DXMATRIX  m_Rotation ;
	//D3DXMATRIX  m_Trans ;

	//rotation
	//D3DXMATRIX  m_RandomRotation;

	void RotationAndTrans( D3DXVECTOR3 pos) {

		D3DXVECTOR3 vLook_toPos;
		D3DXMATRIX matZombie, matScl, matRot, matTrans;
		D3DXMatrixIdentity(&matScl);
		D3DXMatrixIdentity(&matRot);
		D3DXMatrixIdentity(&matTrans);

		matZombie = m_matZombWld;


		//플레이어 방향으로 회전을 하기 위해서..
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_matZombWld._41, 0.0f, m_matZombWld._43);
		vLook_toPos = vPos - pos;
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

		//m_matWorld._42 = G_DEFINE_CHAR_Y_POS_OFFSET;
	}
public:
	G_AI m_State;
public:
	G_AI getState() { return m_State; }
	void setState(G_AI state) { m_State = state; }
	
	GAISeq * m_GameSeq[G_AI_CNT];
	GAISeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_matZombWld;
	//D3DXVECTOR3 m_vZombPos;
	//D3DXVECTOR3 m_vBoxPos;
	//D3DXVECTOR3 m_vLook;
	//D3DXVECTOR3 Distance;

	bool		Init();
	bool		Frame(int iMyIndex);
	bool		Render();
	bool		Release();
	
public:
	GNewZombie();
	~GNewZombie();
};

