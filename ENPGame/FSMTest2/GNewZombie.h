#pragma once
class GNewZombie : public GZombie
{
public:
	D3DXMATRIX	 m_matWorld;
	D3DXMATRIX	 m_matTrans;
	D3DXMATRIX	 m_matRot;

	//D3DXMATRIX  m_RandomRotation ;
	//D3DXMATRIX  m_BoxRotation ;
	//D3DXMATRIX  m_RandomRotResult ;
	//D3DXMATRIX  m_BoxRotResult ;
	//D3DXMATRIX  m_TransRotation ;
	//D3DXMATRIX  m_Rotation ;
	//D3DXMATRIX  m_Trans ;

	//rotation
	//D3DXMATRIX  m_RandomRotation;


private:
	G_AI m_State;
public:
	G_AI getState() { return m_State; }
	void setState(G_AI state) { m_State = state; }
	
	GAISeq * m_GameSeq[G_AI_CNT];
	GAISeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_matZombWld;
	D3DXVECTOR3 m_vZombPos;
	D3DXVECTOR3 m_vBoxPos;
	D3DXVECTOR3 m_vLook;
	//D3DXVECTOR3 Distance;

	bool		Init();
	bool		Frame(int iMyIndex);
	bool		Render();
	bool		Release();
	
public:
	GNewZombie();
	~GNewZombie();
};

