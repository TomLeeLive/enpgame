#include "_stdafx.h"

GAIAttack * GAIAttack::pInstance_ = 0;

bool GAIAttack::Init()
{
	return true;
}
bool GAIAttack::ZombieAttack(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up)
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
bool GAIAttack::Frame()
{
	for (int i = 0;i < g_pMain->m_CharNZomb.size();i++)
	{
		if (g_pMain->m_Zomb[i]->vDistance[i] < 30.0f)
		{
			ZombieMgr->FollowMove(i, g_pMain->m_Zomb[i]->vBoxPosition[i], g_pMain->m_Zomb[i]->vZombiePosition[i]);
			ZombieAttack(i, g_pMain->m_Zomb[i]->vLook[i], g_pMain->m_Zomb[i]->vZRight[i], g_pMain->m_Zomb[i]->vZUp[i]);
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

