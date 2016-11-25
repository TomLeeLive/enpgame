#include "_stdafx.h"



GNewZombie::GNewZombie()
{
	D3DXMatrixIdentity(&m_ZombieWorld);
	vBoxPosition.x = g_pMain->m_matBoxWorld._41;
	vBoxPosition.y = g_pMain->m_matBoxWorld._42;
	vBoxPosition.z = g_pMain->m_matBoxWorld._43;
	
	hp = 100;
}


GNewZombie::~GNewZombie()
{
}
