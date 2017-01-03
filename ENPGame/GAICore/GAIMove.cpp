#include "_ai_std.h"

bool GAIMove::Init(GNewZombie* iMyIndex)
{
	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");
	
	return true;
}

D3DXVECTOR3 GAIMove::RandomMove( )
{
	D3DXVECTOR3 RandomPoint;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//									랜덤 목적지 만들기
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	RandomPoint.x = rand() % 1000 - 500;
	RandomPoint.y = 40.0f;
	RandomPoint.z = rand() % 1000 - 500;
	return RandomPoint;
}

bool GAIMove::Frame(GNewZombie* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2)
{
	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(matHeroWorld._41, matHeroWorld._42, matHeroWorld._43);
	D3DXVECTOR3 vHeroPos2 = D3DXVECTOR3(matHeroWorld2._41, matHeroWorld2._42, matHeroWorld2._43);

	D3DXVECTOR3 vPos = D3DXVECTOR3(iMyIndex->m_matZombWld._41,
		iMyIndex->m_matZombWld._42, iMyIndex->m_matZombWld._43);

	D3DXVECTOR3 Temp = vHeroPos - vPos;
	D3DXVECTOR3 Temp2 = vHeroPos2 - vPos;

	float fDistance = D3DXVec3Length(&Temp);
	float fDistance2 = D3DXVec3Length(&Temp2);

	//3초 후를 체크하기 위한 변수
	float fCoolTime = G_DEFINE_AI_MOVE_COOLTIME;


	if (!m_bTime)
	{
		fTime = g_fDurationTime;
		m_vPos = RandomMove();
		m_bTime = true;

	}

	if (fDistance > G_DEFINE_AI_IDLE_CHECK && fDistance2 > G_DEFINE_AI_IDLE_CHECK)
	{
		iMyIndex->ChangeZombState(iMyIndex, G_AI_IDLE);
	}

	else
	{
		if (fDistance < G_DEFINE_AI_FOLLOW_CHECK|| fDistance2 < G_DEFINE_AI_FOLLOW_CHECK) {
			iMyIndex->ChangeZombState(iMyIndex, G_AI_FOLLOW);
		}
		if (g_fDurationTime - fTime > fCoolTime) {
			m_bTime = false;
		}
		else
		{
			if (iMyIndex->RotationAndTrans(m_vPos) == false)
			{
				m_vPos = RandomMove();
				m_bTime = true;
			}
		}
	}

	return true;
}
bool GAIMove::Render()
{


	return true;
}
bool GAIMove::Release()
{

	return true;
}
HRESULT GAIMove::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIMove::DeleteResource()
{
	HRESULT hr;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}


GAIMove::GAIMove()
{
	GAISeq::InitGSeq();
	m_fTime = 0.0f;

}


GAIMove::~GAIMove()
{
}
