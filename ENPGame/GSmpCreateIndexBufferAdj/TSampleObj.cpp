#include "TSampleObj.h"

bool TSampleObj::CreateIndexData()
{
	/////////////////////////////////////////////////////////////////
	// 인덱스 리스트 ( 이웃 정점 추가 )
	/////////////////////////////////////////////////////////////////
	if (!m_bAdjacency)
	{
		return true;
	}
	size_t dstibOffset = 0;
	size_t ibOffset = 0;

	int iCurIndex = 0;
	m_IndexListAdj.resize(m_iMaxIndex * 2);

	m_pMeshAdj.resize(m_pMesh.size());

	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	{
		auto pData = m_pData[dwObject].get();
		auto ptMesh = m_pMesh[dwObject].get();

		if (pData->m_pSubMesh.size() > 0)
		{
			m_pMeshAdj[dwObject].m_pSubMesh.resize(pData->m_pSubMesh.size());
			for (DWORD dwSub = 0; dwSub < pData->m_pSubMesh.size(); dwSub++)
			{
				m_rep.Clear();
				auto pSubData = pData->m_pSubMesh[dwSub].get();
				auto ptSubMesh = ptMesh->m_pSubMesh[dwSub].get();
				if (pSubData->m_VertexArray.size() < 3) continue;

				m_rep.GenerateAdjacency(pSubData->m_VertexArray, pSubData->m_IndexArray);

				for (int iFace = 0; iFace < m_rep.m_tFaceList.size(); iFace++)
				{
					m_IndexListAdj[iCurIndex + 0] = m_rep.m_tFaceList[iFace].m_iVertexID[0];
					m_IndexListAdj[iCurIndex + 2] = m_rep.m_tFaceList[iFace].m_iVertexID[1];
					m_IndexListAdj[iCurIndex + 4] = m_rep.m_tFaceList[iFace].m_iVertexID[2];

					m_IndexListAdj[iCurIndex + 1] = m_rep.m_tFaceList[iFace].m_iIndexAdj[0];
					m_IndexListAdj[iCurIndex + 3] = m_rep.m_tFaceList[iFace].m_iIndexAdj[1];
					m_IndexListAdj[iCurIndex + 5] = m_rep.m_tFaceList[iFace].m_iIndexAdj[2];
					iCurIndex += 6;
				}

				m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iNumIndex = m_rep.m_tFaceList.size()*3*2;
			/*	m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.left = dstibOffset;
				m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.right = dstibOffset + m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iNumIndex*sizeof(DWORD);
				m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.top = 0;	m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.bottom = 1;
				m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.front = 0;	m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.back = 1;*/

				m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iBeginIB = ibOffset;

				ibOffset += m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iNumIndex;
				//dstibOffset = m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_BoxIB.right;
			}
		}
		else
		{
			m_rep.Clear();
			m_rep.GenerateAdjacency(pData->m_VertexArray, pData->m_IndexArray);

			for (int iFace = 0; iFace < m_rep.m_tFaceList.size(); iFace++)
			{
				m_IndexListAdj[iCurIndex + 0] = m_rep.m_tFaceList[iFace].m_iVertexID[0];
				m_IndexListAdj[iCurIndex + 2] = m_rep.m_tFaceList[iFace].m_iVertexID[1];
				m_IndexListAdj[iCurIndex + 4] = m_rep.m_tFaceList[iFace].m_iVertexID[2];

				m_IndexListAdj[iCurIndex + 1] = m_rep.m_tFaceList[iFace].m_iIndexAdj[0];
				m_IndexListAdj[iCurIndex + 3] = m_rep.m_tFaceList[iFace].m_iIndexAdj[1];
				m_IndexListAdj[iCurIndex + 5] = m_rep.m_tFaceList[iFace].m_iIndexAdj[2];
				iCurIndex += 6;
			}
			m_pMeshAdj[dwObject].m_iNumIndex = m_rep.m_tFaceList.size() * 3 * 2;;
		/*	m_pMeshAdj[dwObject].m_BoxIB.left = dstibOffset;
			m_pMeshAdj[dwObject].m_BoxIB.right = dstibOffset + m_pMeshAdj[dwObject].m_iNumIndex*sizeof(DWORD);
			m_pMeshAdj[dwObject].m_BoxIB.top = 0; m_pMeshAdj[dwObject].m_BoxIB.bottom = 1;
			m_pMeshAdj[dwObject].m_BoxIB.front = 0; m_pMeshAdj[dwObject].m_BoxIB.back = 1;*/
	
			m_pMeshAdj[dwObject].m_iBeginIB = ibOffset;
			ibOffset += m_pMeshAdj[dwObject].m_iNumIndex;
			//dstibOffset = m_pMeshAdj[dwObject].m_BoxIB.right;
		}
	}

	m_pIndexBufferAdj.Attach(DX::CreateIndexBuffer(m_pd3dDevice,&m_IndexListAdj.at(0), m_IndexListAdj.size(),sizeof(DWORD)));
	return true;
}

bool TSampleObj::ShadowDraw(ID3D11DeviceContext*    pContext, GModel* pParent)
{
	if (m_bAdjacency)
	{
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
		pContext->IASetIndexBuffer(m_pIndexBufferAdj.Get(), DXGI_FORMAT_R32_UINT, 0);
		//m_pImmediateContext->GSSetConstantBuffers(0, 1, m_HeightMap.m_dxobj.g_pConstantBuffer.GetAddressOf());
	}
	else {
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pContext->GSSetShader(NULL, NULL, 0);
	}

	for (DWORD dwObject = 0; dwObject < m_pData.size(); dwObject++)
	{
		auto pMesh = m_pMesh[dwObject].get();
		D3DXMATRIX matWorld = pMesh->m_matCalculation * pParent->m_matWorld;
		D3DXMatrixTranspose(&m_cbData.matWorld, &matWorld);
		UpdateConstantBuffer(pContext, pParent);

		if (pMesh->m_pSubMesh.size() > 0)
		{
			for (DWORD dwSub = 0; dwSub < pMesh->m_pSubMesh.size(); dwSub++)
			{
				auto pSubMesh = pMesh->m_pSubMesh[dwSub].get();
				if (pSubMesh->m_iNumFace < 1) continue;
				pContext->PSSetShaderResources(0, 1, pSubMesh->m_dxobj.g_pTextureSRV.GetAddressOf());
				pContext->DrawIndexed(m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iNumIndex,
					m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iBeginIB,
					m_pMeshAdj[dwObject].m_pSubMesh[dwSub].m_iBeginVB);
			}
		}
		else
		{
			if (pMesh->m_iNumFace < 1) continue;
			pContext->PSSetShaderResources(0, 1, pMesh->m_dxobj.g_pTextureSRV.GetAddressOf());
			pContext->DrawIndexed(m_pMeshAdj[dwObject].m_iNumIndex,
				m_pMeshAdj[dwObject].m_iBeginIB,
				m_pMeshAdj[dwObject].m_iBeginVB);
		}
	}
	//stopwatch.Output(L"\nTTbsObj::Draw");
	return true;
}

TSampleObj::TSampleObj()
{
	m_bAdjacency = true;
}


TSampleObj::~TSampleObj()
{
}
