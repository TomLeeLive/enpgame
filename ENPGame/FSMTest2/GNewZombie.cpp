#include "_stdafx.h"



GNewZombie::GNewZombie()
{
	for (int i = 0;i < g_pMain->m_CharNZomb.size();i++)
	{
		D3DXMatrixIdentity(&m_ZombieWorld[i]);

		vZombiePosition[i].x = g_pMain->m_CharNZomb[i]->m_worldMat._41;
		vZombiePosition[i].y = g_pMain->m_CharNZomb[i]->m_worldMat._42;
		vZombiePosition[i].z = g_pMain->m_CharNZomb[i]->m_worldMat._43;

		vBoxPosition[i].x = g_pMain->m_matBoxWorld._41;
		vBoxPosition[i].y = g_pMain->m_matBoxWorld._42;
		vBoxPosition[i].z = g_pMain->m_matBoxWorld._43;
		
		Distance[i] = vBoxPosition[i] - vZombiePosition[i];
		vDistance[i] = D3DXVec3Length(&Distance[i]);
		hp = 100;
	}
}


GNewZombie::~GNewZombie()
{
}
