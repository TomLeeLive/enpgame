#pragma once
#ifdef G_MACRO_AI_ADD
#else

class GN2Zombie : public GZombie
{
public:
	G_ZOMB_ST getState() { return m_State; }
	void setState(G_ZOMB_ST state) {m_State = state;}
private:
	G_ZOMB_ST			m_State;
public:
	//D3DXMATRIX m_matZombie;

	//virtual bool		Init();
	//virtual bool		Set(GCharacter* pChar, GBoneObj* pBone,
	//	float fStart, float fEnd);
	//virtual void		SetBoneMatrices(vector<D3DXMATRIX>* pList);
	virtual bool		Frame();
	//virtual bool		Render(ID3D11DeviceContext*    pContext);
	//virtual void		SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex = -1, int iModelMatrixIndex = -1);
	//virtual HRESULT		CreateConstantBuffer();

	GN2Zombie();
	virtual ~GN2Zombie();
};

#endif