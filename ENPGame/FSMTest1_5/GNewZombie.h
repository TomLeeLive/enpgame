#pragma once
#include "_stdafx.h"
#include "GCharMgr.h"

#define MAX_BONE_MATRICES 255

struct CBConstBoneWorld
{
	D3DXMATRIX    g_mConstBoneWorld[MAX_BONE_MATRICES];
};

class GNewZombie : public GModel
{
public:
	G_ZOMB_ST  m_State;
	G_ZOMB_ST getState() { return m_State; }
	void setState(G_ZOMB_ST state) { m_State = state; }

	bool			m_bDead;
	GSeq*           m_pState;
	int				m_hp;
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
	D3DXVECTOR3 RandomPoint;
	D3DXVECTOR3 RandomDestination;
	D3DXVECTOR3 BoxDestination;
public:
	bool			ZombieMove(int m_hp, D3DXVECTOR3 vLook, D3DXMATRIX Trans, D3DXMATRIX Rotation);
	bool			Zombiefollow(int m_hp, D3DXVECTOR3 vLook, D3DXMATRIX Trans, D3DXMATRIX Rotation);
	bool			ZombieAttack(int m_hp, D3DXVECTOR3 vLook, D3DXMATRIX Trans, D3DXMATRIX Rotation);
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
	GNewZombie();
	virtual~GNewZombie();
};

