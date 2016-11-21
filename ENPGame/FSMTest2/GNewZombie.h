#pragma once
class GNewZombie
{
public:
	D3DXMATRIX  m_ZombieWorld[ZombieNum];
	D3DXVECTOR3 vZombiePosition[ZombieNum];
	D3DXVECTOR3 vBoxPosition[ZombieNum];
	D3DXVECTOR3 Distance[ZombieNum];
	D3DXVECTOR3 vLook[ZombieNum];
	D3DXVECTOR3 vZRight[ZombieNum];
	D3DXVECTOR3 vZUp[ZombieNum];
	D3DXVECTOR3 m_Trans;

	float vDistance[ZombieNum];
	int hp;
public:
	GNewZombie();
	~GNewZombie();
};

