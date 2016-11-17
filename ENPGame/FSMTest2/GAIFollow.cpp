#include "_stdafx.h"

GAIFollow * GAIFollow::pInstance_ = 0;

bool GAIFollow::Init()
{
	return true;
}
void GAIFollow::FollowMove() {

	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 주인공 목적지 방향으로 회전 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
	    vZombiePosition[i] = D3DXVECTOR3(g_pMain->m_HeroObj[i]->m_worldMat._41, 0.0f, g_pMain->m_HeroObj[i]->m_worldMat._43);
		vBoxPosition[i] = D3DXVECTOR3(g_pMain->m_matBoxWorld._41, 0.0f, g_pMain->m_matBoxWorld._43);
		vBDestLook1[i] = vBoxPosition[i] - vZombiePosition[i]; // 정규화 안한 박스로의 목적지 벡터
		vBDestLook[i] = vZombiePosition[i] - vBoxPosition[i]; //- vZombiePosition; // 정규화 할 박스로의 목적지 벡터
		D3DXVec3Normalize(&vBDestLook[i], &vBDestLook[i]);
		vBRight[i]= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vBUp[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vBRight[i], &vBUp[i], &vBDestLook[i]);
		D3DXVec3Cross(&vBUp[i], &vBDestLook[i], &vBRight[i]);


		D3DXMatrixIdentity(&m_BoxRotation[i]);
		//D3DXMatrixIdentity(&g_pMain->m_RandomRotation);
		m_BoxRotation[i]._11 = vBRight[i].x;			m_BoxRotation[i]._12 = vBRight[i].y;			m_BoxRotation[i]._13 = vBRight[i].z; // 임의 행렬에 x,y,z 기입
		m_BoxRotation[i]._21 = vBUp[i].x;				m_BoxRotation[i]._22 = vBUp[i].y;				m_BoxRotation[i]._23 = vBUp[i].z;
		m_BoxRotation[i]._31 = vBDestLook[i].x;		m_BoxRotation[i]._32 = vBDestLook[i].y;				m_BoxRotation[i]._33 = vBDestLook[i].z;


		vDistance[i] = vBoxPosition[i] - vZombiePosition[i];
	    float a = D3DXVec3Length(&vDistance[i]);
		ZombieDistance[i] = a;
	}

}
bool GAIFollow::Frame()
{
	FollowMove();

	for (int i = 0;i < 5;i++)
	{
		hp = 100;  B_Look[i] = vBDestLook1[i]; 
		D3DXMatrixIdentity(&B_Trans[i]);

		if (ZombieDistance[i] > 70.0f) {
			g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_MOVE];
		}
		else if (ZombieDistance[i] < 70.0f) {
			Zombie->Zombiefollow(hp, B_Look[i], B_Trans[i], m_BoxRotation[i]);

			if (ZombieDistance[i] < 30.0f)
			{
				GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_ATTACK");
				g_pMain->m_HeroObj[i]->Set(pChar0,
					pChar0->m_pBoneObject,
					pChar0->m_pBoneObject->m_Scene.iFirstFrame,
					pChar0->m_pBoneObject->m_Scene.iLastFrame);
				g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_AI_ATTACK];
			}
		}
	}
	return true;
}
bool GAIFollow::Render()
{
	return true;
}
bool GAIFollow::Release()
{
	return true;
}
HRESULT GAIFollow::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIFollow::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIFollow::GAIFollow()
{
	pInstance_ = 0;
}


GAIFollow::~GAIFollow()
{
}
int GAIFollow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

