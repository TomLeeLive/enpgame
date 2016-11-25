#pragma once
class GNewZombie
{
public:
	D3DXMATRIX  m_ZombieWorld;
	D3DXVECTOR3 vZombiePosition;
	D3DXVECTOR3 vBoxPosition;
	D3DXVECTOR3 Distance;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vZRight;
	D3DXVECTOR3 vZUp;
	D3DXVECTOR3 m_Trans;

	float vDistance;
	int hp;
public:
	GNewZombie();
	~GNewZombie();
};

