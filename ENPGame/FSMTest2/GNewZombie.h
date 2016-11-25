#pragma once
class GNewZombie : public GZombie
{
public:
	//D3DXMATRIX  m_RandomRotation ;
	D3DXMATRIX  m_BoxRotation ;
	D3DXMATRIX  m_RandomRotResult ;
	D3DXMATRIX  m_BoxRotResult ;
	D3DXMATRIX  m_TransRotation ;
	D3DXMATRIX  m_Rotation ;
	D3DXMATRIX  m_Trans ;

	void  RandomMove(int i, D3DXVECTOR3 vZombiePosition);
	void  FollowMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition);
	void  AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition);
	//move
	D3DXVECTOR3 m_RandomPoint;
	D3DXVECTOR3 m_RandomDestination;


	D3DXVECTOR3 m_vRDestLook;
	D3DXVECTOR3 m_vZRight;
	D3DXVECTOR3 m_vZUp;


	//follow
	D3DXVECTOR3 m_vBDestLook;
	D3DXVECTOR3 m_vBRight;
	D3DXVECTOR3 m_vBUp;

	//attack
	D3DXVECTOR3 m_vADestLook;
	D3DXVECTOR3 m_vARight;
	D3DXVECTOR3 m_vAUp;

	//rotation
	D3DXMATRIX  m_RandomRotation;


private:
	G_AI m_State;
public:
	G_AI getState() { return m_State; }
	void setState(G_AI state) { m_State = state; }
	
	GAISeq * m_GameSeq[G_AI_CNT];
	GAISeq * m_pCurrentSeq;
	
	D3DXMATRIX  m_ZombieWorld;
	D3DXVECTOR3 vZombiePosition;
	D3DXVECTOR3 vBoxPosition;
	D3DXVECTOR3 Distance;
	D3DXVECTOR3 vLook;

	float vDistance;
	int hp;
	
	
	bool		Init();
	bool		Frame(int iMyIndex);
	bool		Render();
	bool		Release();
	
	
	
	
public:
	GNewZombie();
	~GNewZombie();
};

