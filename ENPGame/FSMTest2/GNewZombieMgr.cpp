#include "_stdafx.h"
inline void DXUT_SetDebugName(ID3D11DeviceChild* pObj, const CHAR* pstrName)
{
	if (pObj)
		pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
}



HRESULT GNewZombieMgr::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = sizeof(CBConstBoneWorld);
	V_RETURN(g_pd3dDevice->CreateBuffer(&Desc, NULL, m_pCBConstBoneWorld.GetAddressOf()));
	DXUT_SetDebugName(m_pCBConstBoneWorld.Get(), "CBConstBoneWorld");

	//////////////////////////   //////////////////
	D3D11_BUFFER_DESC vbdesc =
	{
		MAX_BONE_MATRICES * sizeof(D3DXMATRIX),
		D3D11_USAGE_DYNAMIC,
		D3D11_BIND_SHADER_RESOURCE,
		D3D11_CPU_ACCESS_WRITE,
		0
	};
	g_pd3dDevice->CreateBuffer(&vbdesc, NULL, &m_pBoneBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	// Again, we need a resource view to use it in the shader
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	SRVDesc.Buffer.ElementOffset = 0;
	SRVDesc.Buffer.ElementWidth = MAX_BONE_MATRICES * 4;
	g_pd3dDevice->CreateShaderResourceView(
		m_pBoneBuffer.Get(), &SRVDesc, m_pBoneBufferRV.GetAddressOf());

	return hr;
}
void GNewZombieMgr::SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex, int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}
}
void GNewZombieMgr::SetBoneMatrices(vector<D3DXMATRIX>* pList)
{
	for (UINT i = 0; i < pList->size(); i++)
	{
		D3DXMatrixTranspose(&m_cbBoneData.g_mConstBoneWorld[i], &((*pList)[i] * m_pMatrix[i]));
	}
}
bool		GNewZombieMgr::Init()
{

	return true;
}
bool	GNewZombieMgr::Set(GCharacter* pChar, GBoneObj* pBone,
	float fStart, float fEnd)
{
	HRESULT hr = S_OK;
	m_pBoneObject = pBone;
	m_pChar = pChar;
	m_Scene = m_pBoneObject->m_Scene;

	SetActionFrame(fStart, fEnd);

	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	return true;
}
bool GNewZombieMgr::Frame()
{
	m_fFrame += (g_fSecPerFrame * m_fSpeed * m_pBoneObject->m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fFrame;
	// 1프레임 사이 간격
	m_fLerpTime = m_fFrame - m_iCurrentFrame;

	if (m_pChar->m_iAniLoop != 0 || m_fFrame < m_iLastFrame - 1)
	{
		if (m_pBoneObject->AniFrame(m_fFrame,
			m_fLerpTime,
			m_iStartFrame,
			m_iLastFrame,
			m_pMatrix))
		{
			m_iCurrentFrame = m_iStartFrame;
			m_fFrame = (float)m_iStartFrame + m_fLerpTime;
		}
	}


	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
	{
		GSkinObj* pModel = (GSkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
		_ASSERT(pModel);

		if (m_bConstantBufferType)
		{
			SetBoneMatrices(pModel->GetMatrix());
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			g_pImmediateContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
			memcpy(MappedResource.pData, &m_cbBoneData, sizeof(CBConstBoneWorld));
			g_pImmediateContext->Unmap(m_pCBConstBoneWorld.Get(), 0);
			g_pImmediateContext->VSSetConstantBuffers(1, 1, m_pCBConstBoneWorld.GetAddressOf());
		}
		else
		{
			m_pBoneObject->SetBoneMatrices(
				g_pImmediateContext,
				m_pBoneBuffer.Get(),
				m_pMatrix,
				pModel->GetMatrix());
		}
	}
 return true;
}
bool GNewZombieMgr::Render(ID3D11DeviceContext*    pContext)
{
	// 메쉬 랜더링
	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
	{
		GSkinObj* pModel = (GSkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
		_ASSERT(pModel);
		pModel->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		ID3D11ShaderResourceView* aRViews[1] = { m_pBoneBufferRV.Get() };
		g_pImmediateContext->VSSetShaderResources(1, 1, aRViews);
		
		pModel->Render(pContext);
	}
	// 본 오브젝트 랜더링
	if (m_bBoneRender)
	{
		memcpy(m_pBoneObject->m_pMatrix, m_pMatrix, m_pBoneObject->m_Scene.iNumMesh*sizeof(D3DXMATRIX));
		m_pBoneObject->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		m_pBoneObject->Render(pContext);
	}
	return true;
}
void GNewZombieMgr::RandomMove(int i, D3DXVECTOR3 vZombiePosition)
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//									랜덤 목적지 만들기
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		srand(time(NULL));
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint.x = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint.x = (rand() * 3) % 50;
			
		}
		if ((rand() * 3) % 2 == 0)
		{
			m_RandomPoint.z = -((rand() * 3) % 50);
		}
		else
		{
			m_RandomPoint.z = (rand() * 3) % 50;
		}

		// 랜덤 목적지
		m_RandomDestination.x = m_RandomPoint.x;
		m_RandomDestination.y = 0.0f;
		m_RandomDestination.z = m_RandomPoint.z;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 랜덤 목적지 방향으로 회전하기 위한 벡터 구현
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		vRDestLook = m_RandomDestination - vZombiePosition; // 랜덤 목적지 방향 벡터
		D3DXVec3Normalize(&vRDestLook, &vRDestLook);
		vZRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vZRight, &vZUp, &vRDestLook);
		D3DXVec3Cross(&vZUp, &vRDestLook, &vZRight);

		g_pMain->m_Zomb[i]->vLook[i] = vRDestLook;
		g_pMain->m_Zomb[i]->vZRight[i] = vZRight;
		g_pMain->m_Zomb[i]->vZUp[i] = vZUp;

}
void GNewZombieMgr::FollowMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition)
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	vBDestLook = vZombiePosition - vBoxPosition; //- vZombiePosition; // 정규화 할 박스로의 목적지 벡터
	D3DXVec3Normalize(&vBDestLook, &vBDestLook);
	vBRight= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vBUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&vBRight, &vBUp, &vBDestLook);
	D3DXVec3Cross(&vBUp, &vBDestLook, &vBRight);


	g_pMain->m_Zomb[i]->vLook[i] = vBDestLook;
	g_pMain->m_Zomb[i]->vZRight[i] = vBRight;
	g_pMain->m_Zomb[i]->vZUp[i] = vBUp;

}

void GNewZombieMgr::AttackMove(int i, D3DXVECTOR3 vBoxPosition, D3DXVECTOR3 vZombiePosition) 
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
		vADestLook = vZombiePosition - vBoxPosition; // 정규화 할 박스로의 목적지 벡터
		D3DXVec3Normalize(&vADestLook, &vADestLook);
		vARight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vAUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vARight, &vAUp, &vADestLook);
		D3DXVec3Cross(&vAUp, &vADestLook, &vARight);

		g_pMain->m_Zomb[i]->vLook[i] = vADestLook;
		g_pMain->m_Zomb[i]->vZRight[i] = vARight;
		g_pMain->m_Zomb[i]->vZUp[i] = vAUp;

}

GNewZombieMgr::GNewZombieMgr()
{
	m_State = G_ZOMB_ST_WALK;

	m_pChar = NULL;
	m_bDead = false;
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_fSpeed = 1.0f;
	m_fFrame = 0.0f;
	m_fLerpTime = 0.0f;
	m_iStartFrame = 0;
	m_iLastFrame = 0;
	m_bConstantBufferType = false;
	m_bBoneRender = false;
	m_RandomPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


GNewZombieMgr::~GNewZombieMgr()
{
}
