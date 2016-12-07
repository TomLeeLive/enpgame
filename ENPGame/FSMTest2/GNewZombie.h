#pragma once

//enum G_AI;
class GAISeq;

class GNewZombie : public GZombie
{
public:
	bool RotationAndTrans(D3DXVECTOR3 pos);

public:
	G_AI m_State;
public:
	G_AI getState() { return m_State; }
	void setState(G_AI state) { m_State = state; }
	
	void ChangeZombState(GNewZombie* iNum, G_AI state);
	void ChangeZombState(GNewZombie* iNum, TCHAR* str);

	GAISeq * m_GameSeq[G_AI_CNT];
	GAISeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_matZombWld;
	bool		Init();
	bool		Frame(GNewZombie* iMyIndex);
	bool		Render();
	bool		Release();
	
public:
	GNewZombie();
	~GNewZombie();
};

