#pragma once
#include "GCharMgr.h"
#include "GBBox.h"
#define MAX_BONE_MATRICES 255

//오브젝트 위치
#define G_OBJ_LOC_GUN_SHOTGUN _T("data/object/shotgun/shotgun.GBS")
//오브젝트 매니저 등록 이름
#define G_OBJ_NAME_GUN_SHOTGUN L"shotgun.GBS"

#define G_DEFINE_HERO1_GUN_POS_RIGHT_HAND 25
#define G_DEFINE_HERO2_GUN_POS_RIGHT_HAND 26

enum G_HERO {
	G_HERO_TOM = 0,
	G_HERO_JAKE,
	G_HERO_CNT
};

class GHero : public GModel
{
	struct CBConstBoneWorld
	{
		D3DXMATRIX    g_mConstBoneWorld[MAX_BONE_MATRICES];
	};

public:
	G_HERO			m_HeroType;
	GModel*			m_ObjGun;
	D3DXMATRIX		m_matObjGunWld, m_matObjGunScl, m_matObjGunRot, m_matObjGunTrans;

	GBBox			m_OBB;
	int				m_iScore;
	int				m_iBullet;
	int				m_iHP;

	bool			m_bDead;
	D3DXVECTOR3		m_vLook;
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
	int				m_State;
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
	bool		Release();
	void		SetActionFrame(int iStart, int iEnd,int iCharacterMatrixIndex = -1,	int iModelMatrixIndex = -1);
	HRESULT		CreateConstantBuffer();
public:
	GHero();
	virtual~GHero();
};

