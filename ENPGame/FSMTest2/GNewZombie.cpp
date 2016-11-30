#include "_stdafx.h"





bool	GNewZombie::Init()
{
	GZombie::Init();
	
	m_GameSeq[G_AI_IDLE] = new GAIIdle;//CreateInstance();
	m_GameSeq[G_AI_MOVE] = new GAIMove;//::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = new GAIFollow;//::CreateInstance();
	m_GameSeq[G_AI_ATTACK] = new GAIAttack;//::CreateInstance();
	m_GameSeq[G_AI_DIE] = new GAIDie;//::CreateInstance();
	

	
	m_pCurrentSeq = m_GameSeq[G_AI_IDLE];
	
	return true;
};
bool	GNewZombie::Frame(int iMyIndex)
{
	GZombie::Frame();


	
	m_pCurrentSeq->Frame(iMyIndex);

	m_vBoxPos.x = g_pMain->m_matBoxWorld._41;
	m_vBoxPos.y = g_pMain->m_matBoxWorld._42;
	m_vBoxPos.z = g_pMain->m_matBoxWorld._43;

	if (g_pMain->m_Zomb[iMyIndex]->m_State != G_AI_IDLE)
	{
		m_matZombWld = m_matRot * m_matTrans;
	}
	return true;
};
bool	GNewZombie::Render(){
	m_pCurrentSeq->Render();
	GZombie::Render(g_pMain->GetContext());
	return true;
};
bool	GNewZombie::Release()
{
	m_pCurrentSeq->Release();
	return true;
};


	
	
GNewZombie::GNewZombie()
{
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);

	D3DXMatrixIdentity(&m_matZombWld);
	m_vZombPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vBoxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_State = G_AI_MOVE;
	D3DXMatrixIdentity(&m_matZombWld);
	m_vBoxPos.x = g_pMain->m_matBoxWorld._41;
	m_vBoxPos.y = g_pMain->m_matBoxWorld._42;
	m_vBoxPos.z = g_pMain->m_matBoxWorld._43;
	
}


GNewZombie::~GNewZombie()
{
}
