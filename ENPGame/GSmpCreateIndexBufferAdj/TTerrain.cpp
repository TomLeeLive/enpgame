#include "TTerrain.h"

bool TTerrain::CreateIndexData()
{
	GMap::CreateIndexData();
	/////////////////////////////////////////////////////////////////
	// 인덱스 리스트 ( 이웃 정점 추가 )
	/////////////////////////////////////////////////////////////////
	if (!m_bAdjacency)
	{
		return true;
	}
	m_IndexListAdj.resize(m_iNumFace * 3 * 2);

	D3DXVECTOR3 vFaceNormal;
	int iCurIndex = 0;

	//m_rep.GenerateAdjacency(m_VertexList, m_IndexList);	
	//for (int iFace = 0; iFace < m_rep.m_tFaceList.size(); iFace++)
	//{
	//	m_IndexListAdj[iCurIndex + 0] = m_rep.m_tFaceList[iFace].m_iVertexID[0];
	//	m_IndexListAdj[iCurIndex + 2] = m_rep.m_tFaceList[iFace].m_iVertexID[1];
	//	m_IndexListAdj[iCurIndex + 4] = m_rep.m_tFaceList[iFace].m_iVertexID[2];

	//	m_IndexListAdj[iCurIndex + 1] = m_rep.m_tFaceList[iFace].m_iIndexAdj[0];
	//	m_IndexListAdj[iCurIndex + 3] = m_rep.m_tFaceList[iFace].m_iIndexAdj[1];
	//	m_IndexListAdj[iCurIndex + 5] = m_rep.m_tFaceList[iFace].m_iIndexAdj[2];
	//	iCurIndex += 6;
	//}
	//iCurIndex = 0;
	
	for (int iRow = 0; iRow < m_iNumSellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumSellCols; iCol++)
		{
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;			
			m_IndexListAdj[iCurIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexListAdj[iCurIndex + 2] = m_IndexListAdj[iCurIndex + 0] + 1;
			m_IndexListAdj[iCurIndex + 4] = m_IndexListAdj[iCurIndex + 0] + m_iNumCols;
			m_IndexListAdj[iCurIndex + 6] = m_IndexListAdj[iCurIndex + 4];
			m_IndexListAdj[iCurIndex + 8] = m_IndexListAdj[iCurIndex + 2];
			m_IndexListAdj[iCurIndex + 10] = m_IndexListAdj[iCurIndex + 4] + 1;

			m_IndexListAdj[iCurIndex + 1] = m_IndexListAdj[iCurIndex + 2] - m_iNumCols;
			m_IndexListAdj[iCurIndex + 3] = m_IndexListAdj[iCurIndex + 10];
			m_IndexListAdj[iCurIndex + 5] = m_IndexListAdj[iCurIndex + 4] - 1;
			m_IndexListAdj[iCurIndex + 7] = m_IndexListAdj[iCurIndex + 0];
			m_IndexListAdj[iCurIndex + 9] = m_IndexListAdj[iCurIndex + 2] + 1;
			m_IndexListAdj[iCurIndex + 11] = m_IndexListAdj[iCurIndex + 4] + m_iNumCols;

			if (iRow == 0)
			{
				m_IndexListAdj[iCurIndex + 1] = m_IndexListAdj[iCurIndex + 0];
			}
			if (iCol == 0)
			{
				m_IndexListAdj[iCurIndex + 5] = m_IndexListAdj[iCurIndex + 0];
			}
			if (iCol + 1 == m_iNumSellCols)
			{
				m_IndexListAdj[iCurIndex + 9] = m_IndexListAdj[iCurIndex + 2];
			}
			if (iRow + 1 == m_iNumSellRows)
			{
				m_IndexListAdj[iCurIndex + 11] = m_IndexListAdj[iCurIndex + 4];
			}			
			iCurIndex += 12;			
		}
	}	

	m_dxobj.m_iNumIndex = m_IndexListAdj.size();
	m_dxobj.m_iIndexSize = sizeof(DWORD);

	m_pIndexBufferAdj.Attach(DX::CreateIndexBuffer(m_pd3dDevice,
		&m_IndexListAdj.at(0),
		m_dxobj.m_iNumIndex,
		m_dxobj.m_iIndexSize));
	return true;
}

//bool TTerrain::Render(ID3D11DeviceContext*  pContext)
//{
//	PreRender(pContext);
//
//	if (m_bAdjacency)
//	{
//		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
//		pContext->IASetIndexBuffer(m_pIndexBufferAdj.Get(), DXGI_FORMAT_R32_UINT, 0);
//		pContext->GSSetConstantBuffers(0, 1, m_dxobj.g_pConstantBuffer.GetAddressOf());
//	}
//	else {
//		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//		pContext->GSSetShader(NULL, NULL, 0);
//	}
//
//	UpdateConstantBuffer(pContext);
//
//	if (m_bAdjacency)
//		pContext->DrawIndexed(m_iNumFace * 3 * 2, 0, 0);
//	else
//		pContext->DrawIndexed(m_iNumFace * 3, 0, 0);
//	return true;
//}
TTerrain::TTerrain()
{
	m_bAdjacency = true;
}


TTerrain::~TTerrain()
{
}
