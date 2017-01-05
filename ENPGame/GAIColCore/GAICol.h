#pragma once

//enum G_AI_COL;
class GAIColSeq;

class GAICol : public GHero
{
public:
	bool RotationAndTrans(D3DXVECTOR3 pos);

public:
	G_AI_COL m_State;
public:

	int m_iNum;
	G_AI_COL getState() { return m_State; }
	void setState(G_AI_COL state) { m_State = state; }
	
	void ChangeZombState(GAICol* iNum, G_AI_COL state);
	void ChangeZombState(GAICol* iNum, TCHAR* str);

	GAIColSeq * m_GameSeq[G_AI_COL_CNT];
	GAIColSeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_matWorld;
	bool		Init();
	bool		Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
	bool		Render();
	bool		Release();
	
public:
	GAICol();
	GAICol(int iNum);
	~GAICol();
};

