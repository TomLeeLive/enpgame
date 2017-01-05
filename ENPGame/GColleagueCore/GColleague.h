#pragma once

//enum G_AI;
class GAISeq;

class GColleague 
{
public:
	bool RotationAndTrans(D3DXVECTOR3 pos);

public:
	G_AI m_State;
public:

	int m_iNum;
	G_AI getState() { return m_State; }
	void setState(G_AI state) { m_State = state; }
	
	void ChangeZombState(GColleague* iNum, G_AI state);

	GAISeq * m_GameSeq[G_AI_CNT];
	GAISeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_matZombWld;
	bool		Init();
	bool		Frame(GColleague* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
	bool		Render();
	bool		Release();
	
public:
	GColleague();
	GColleague(int iNum);
	~GColleague();
};

