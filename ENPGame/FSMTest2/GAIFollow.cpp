#include "_stdafx.h"

GAIFollow * GAIFollow::pInstance_ = 0;

bool GAIFollow::Init()
{
	return true;
}

bool GAIFollow::Zombiefollow(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
{
	D3DXMATRIX Rotation;
	D3DXMatrixIdentity(&Rotation);

	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&Trans);

	Rotation._11 = Right.x;			Rotation._12 = Right.y;			Rotation._13 = Right.z; // 임의 행렬에 x,y,z 기입
	Rotation._21 = Up.x;			Rotation._22 = Up.y;			Rotation._23 = Up.z;
	Rotation._31 = look.x;			Rotation._32 = look.y;			Rotation._33 = look.z;

	Trans._41 += look.x * g_fSecPerFrame* SPEED;
	Trans._43 += look.z * g_fSecPerFrame* SPEED;
	
	g_pMain->m_Zomb[i]->m_ZombieWorld[i] = Rotation*Trans;

	return true;
}
bool GAIFollow::Frame()
{
	for (int i = 0;i < g_pMain->m_CharNZomb.size();i++)
	{
		if (g_pMain->m_Zomb[i]->vDistance[i] < 70.0f)
		{
			ZombieMgr->FollowMove(i, g_pMain->m_Zomb[i]->vBoxPosition[i], g_pMain->m_Zomb[i]->vZombiePosition[i]);
			Zombiefollow(i, g_pMain->m_Zomb[i]->vLook[i], g_pMain->m_Zomb[i]->vZRight[i], g_pMain->m_Zomb[i]->vZUp[i]);
			
			G_ZOMB_ST beforeState = g_pMain->m_CharNZomb[i].get()->m_State;
			G_ZOMB_ST afterState = g_pMain->m_CharNZomb[i].get()->m_State;
			
			if (g_pMain->m_Zomb[i]->vDistance[i] < 30.0f)
			{
				if (beforeState != G_ZOMB_ST_ATTACK)
				{
					afterState = G_ZOMB_ST_ATTACK;
					g_pMain->m_pCurrentSeq = g_pMain->m_GameSeq[G_ZOMB_ST_ATTACK];
					if (beforeState != afterState)
					{
						g_pMain->ChangeZombState(i, G_DEFINE_ANI_ZOMB_WLK);
					}
				}
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

