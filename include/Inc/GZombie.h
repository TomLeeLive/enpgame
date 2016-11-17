#pragma once
#include "GCharMgr.h"
#include "GBBox.h"

#define MAX_BONE_MATRICES 255


class GZombie : public GModel
{
	struct CBConstBoneWorld
	{
		D3DXMATRIX    g_mConstBoneWorld[MAX_BONE_MATRICES];
	};

public:
	GBBox			m_OBB;
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
	D3DXMATRIX		m_pMatrix[255];
	CBConstBoneWorld m_cbBoneData;
	ComPtr<ID3D11Buffer>    m_pCBConstBoneWorld;
	int						m_iMatrixIndex;
	bool					m_bBoneRender;

	ComPtr<ID3D11Buffer>             m_pBoneBuffer;
	ComPtr<ID3D11ShaderResourceView> m_pBoneBufferRV;
public:
	virtual bool		Init();
	virtual bool		Set(GCharacter* pChar, GBoneObj* pBone,
						float fStart, float fEnd);
	virtual void		SetBoneMatrices(vector<D3DXMATRIX>* pList);
	virtual bool		Frame();
	virtual bool		Render(ID3D11DeviceContext*    pContext);
	virtual void		SetActionFrame(int iStart, int iEnd,int iCharacterMatrixIndex = -1,	int iModelMatrixIndex = -1);
	virtual HRESULT		CreateConstantBuffer();
public:
	GZombie();
	virtual~GZombie();
};

