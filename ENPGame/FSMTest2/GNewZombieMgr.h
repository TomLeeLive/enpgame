#pragma once
#include "_stdafx.h"
#include "GCharMgr.h"

#define MAX_BONE_MATRICES 255

struct CBConstBoneWorld
{
	D3DXMATRIX    g_mConstBoneWorld[MAX_BONE_MATRICES];
};

class GNewZombieMgr : public GModel
{
public:
	void  RandomMove(int i, D3DXVECTOR3 vZombiePosition);
	void  FollowMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition);
	void  AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition);
	//move
	D3DXVECTOR3 m_RandomPoint;
	D3DXVECTOR3 m_RandomDestination;


	D3DXVECTOR3 vRDestLook;
	D3DXVECTOR3 vZRight;
	D3DXVECTOR3 vZUp;


	//follow
	D3DXVECTOR3 vBDestLook;
	D3DXVECTOR3 vBRight;
	D3DXVECTOR3 vBUp;

	//attack
	D3DXVECTOR3 vADestLook;
	D3DXVECTOR3 vARight;
	D3DXVECTOR3 vAUp;

	//rotation
	D3DXMATRIX  m_RandomRotation;

	G_ZOMB_ST  m_State;
	G_ZOMB_ST getState() { return m_State; }
	void setState(G_ZOMB_ST state) { m_State = state; }
	
	
	GAISeq*           m_pState;


public:
	bool			m_bDead;
	D3DXVECTOR3		m_vLook;
	D3DXMATRIX      m_worldMat;
public:
	int				m_iObjectIndex;
	GCharacter*		m_pChar;
	T_STR			m_szName;
	GBoneObj*		m_pBoneObject;
	bool			m_bConstantBufferType;
	int				m_iStartFrame;
	int				m_iLastFrame;
	int				m_iCurrentFrame;
	float			m_fFrame;
	float			m_fLerpTime;
	float			m_fSpeed;

public:
	D3DXMATRIX		m_pMatrix[255];
	CBConstBoneWorld m_cbBoneData;
	ComPtr<ID3D11Buffer>    m_pCBConstBoneWorld;
	int						m_iMatrixIndex;
	bool					m_bBoneRender;

	ComPtr<ID3D11Buffer>             m_pBoneBuffer;
	ComPtr<ID3D11ShaderResourceView> m_pBoneBufferRV;
public:
	bool		Init();
	bool		Set(GCharacter* pChar, GBoneObj* pBone,
		float fStart, float fEnd);
	void		SetBoneMatrices(vector<D3DXMATRIX>* pList);
	bool		Frame();
	bool		Render(ID3D11DeviceContext*    pContext);
	void		SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex = -1, int iModelMatrixIndex = -1);
	HRESULT		CreateConstantBuffer();


public:
	GNewZombieMgr();
	virtual~GNewZombieMgr();
};

