#include "_stdafx.h"

GAIAttack * GAIAttack::pInstance_ = 0;

bool GAIAttack::Init()
{
	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");
	g_pMain->m_HeroObj[0]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_ATTACK];
	return true;
}
void GAIAttack::AttackMove() {

	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		vZombiePosition[i] = D3DXVECTOR3(g_pMain->m_HeroObj[i]->m_worldMat._41, 0.0f, g_pMain->m_HeroObj[i]->m_worldMat._43);
		vBoxPosition[i] = D3DXVECTOR3(g_pMain->m_matBoxWorld._41, 0.0f, g_pMain->m_matBoxWorld._43);
		vADestLook1[i] = vBoxPosition[i] - vZombiePosition[i]; // 정규화 안한 박스로의 목적지 벡터
		vADestLook[i] = vZombiePosition[i] - vBoxPosition[i]; // 정규화 할 박스로의 목적지 벡터
		D3DXVec3Normalize(&vADestLook[i], &vADestLook[i]);
		vARight[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vAUp[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vARight[i], &vAUp[i], &vADestLook[i]);
		D3DXVec3Cross(&vAUp[i], &vADestLook[i], &vARight[i]);


		D3DXMatrixIdentity(&m_ABoxRotation);
		//D3DXMatrixIdentity(&g_pMain->m_RandomRotation);
		m_ABoxRotation._11 = vARight[i].x;			m_ABoxRotation._12 = vARight[i].y;			m_ABoxRotation._13 = vARight[i].z; // 임의 행렬에 x,y,z 기입
		m_ABoxRotation._21 = vAUp[i].x;				m_ABoxRotation._22 = vAUp[i].y;				m_ABoxRotation._23 = vAUp[i].z;
		m_ABoxRotation._31 = vADestLook[i].x;		m_ABoxRotation._32 = vADestLook[i].y;		m_ABoxRotation._33 = vADestLook[i].z;


		vDistance[i]= vBoxPosition[i] - vZombiePosition[i];
		ZombieDistance[i] = D3DXVec3Length(&vDistance[i]);
	}
}
bool GAIAttack::Frame()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 주인공 목적지 방향으로 회전 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	AttackMove();
	for (int i = 0;i < 5;i++)
	{
		hp = 100;  A_Look = vADestLook1[i];
		D3DXMatrixIdentity(&A_Trans[i]);


		if (ZombieDistance[i] > 70.0f) {
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_MOVE];
		}
		else if (ZombieDistance[i] < 70.0f) {
			Zombie->Zombiefollow(hp, A_Look, A_Trans[i], m_ABoxRotation);
			if (ZombieDistance[i] < 30.0f)
			{
				g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_ATTACK];
			}
		}
	}
	return true;
}
bool GAIAttack::Render()
{

	return true;
}
bool GAIAttack::Release()
{
	return true;
}
HRESULT GAIAttack::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIAttack::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIAttack::GAIAttack()
{
	pInstance_ = 0;
}


GAIAttack::~GAIAttack()
{
}
int GAIAttack::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

