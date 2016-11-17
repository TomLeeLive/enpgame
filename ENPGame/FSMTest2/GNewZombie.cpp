#include "_stdafx.h"
inline void DXUT_SetDebugName(ID3D11DeviceChild* pObj, const CHAR* pstrName)
{
	if (pObj)
		pObj->SetPrivateData(WKPDID_D3DDebugObjectName, lstrlenA(pstrName), pstrName);
}

HRESULT GNewZombie::CreateConstantBuffer()
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
void GNewZombie::SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex, int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}
	//if (iModelMatrixIndex >= 0)
	//{
	//	SeGModelMaterixID(iModelMatrixIndex);
	//}
}
void GNewZombie::SetBoneMatrices(vector<D3DXMATRIX>* pList)
{
	for (UINT i = 0; i < pList->size(); i++)
	{
		D3DXMatrixTranspose(&m_cbBoneData.g_mConstBoneWorld[i], &((*pList)[i] * m_pMatrix[i]));
	}
}
bool		GNewZombie::Init()
{

	return true;
}
bool	GNewZombie::Set(GCharacter* pChar, GBoneObj* pBone,
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
bool GNewZombie::Frame()
{


	//m_fLerpTime *= 0.1f;
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
	//#ifdef _DEBUG
	//	TCHAR  strMessage[MAX_PATH] = { 0, };
	//	_stprintf_s(strMessage, _T("<===== %d [%10.4f] %d====>\n "), m_iCurrentFrame,m_fLerpTime,  m_iCurrentFrame+1);
	//	OutputDebugString(strMessage);
	//#endif





	//////////////////////////  보간 없이 투박하게////////////////////////////
	//if(m_iCurrentFrame >= m_iLastFrame- m_iStartFrame)
	//{
	//	m_iCurrentFrame = 0;
	//	m_fFrame = 0.0f;
	//}
	/*for (int i = 0; i < m_pBoneObject->m_Scene.iNumMesh; i++)
	{
	m_pMatrix[i] = m_pBoneObject->m_ppAniMatrix[i][m_iCurrentFrame];
	}*/

	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
	{
		GSkinObj* pModel = (GSkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
		_ASSERT(pModel);
		//pModel->SetMatrix(&m_matWorld, &m_matView, &m_matProj);

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
			/*SetBoneMatrices(
			g_pImmediateContext,
			m_pMatrix,
			pModel->GetMatrix());*/
		}
	}
 return true;
}
bool GNewZombie::Render(ID3D11DeviceContext*    pContext)
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
bool GNewZombie::ZombieMove(int hp, D3DXVECTOR3 look,D3DXMATRIX Trans, D3DXMATRIX Rotation)
{

	if (hp = 0)
	{
		//Die
	}
	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		Trans._41 += look.x * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._41 += Trans._41;
		Trans._43 += look.z * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._43 += Trans._43;
		g_pMain->m_RandomRotation[i] = Rotation;
	}
	return true;
}
bool GNewZombie::Zombiefollow(int hp, D3DXVECTOR3 look, D3DXMATRIX Trans, D3DXMATRIX Rotation)
{

	if (hp = 0)
	{
		//Die
	}
	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		Trans._41 += look.x * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._41 += Trans._41;
		Trans._43 += look.z * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._43 += Trans._43;
		g_pMain->m_RandomRotation[i] = Rotation;
	}

	return true;
}
bool GNewZombie::ZombieAttack(int hp, D3DXVECTOR3 look, D3DXMATRIX Trans, D3DXMATRIX Rotation)
{

	if (hp = 0)
	{
		//Die
	}
	for (int i = 0;i < g_pMain->m_HeroObj.size();i++) {
		Trans._41 += look.x * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._41 += Trans._41;
		Trans._43 += look.z * g_fSecPerFrame;
		g_pMain->m_HeroObj[i]->m_worldMat._43 += Trans._43;
		g_pMain->m_RandomRotation[i] = Rotation;
	}

	return true;
}

GNewZombie::GNewZombie()
{
	m_State = G_ZOMBIE_AI_ST_WALK;

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
}


GNewZombie::~GNewZombie()
{
}
