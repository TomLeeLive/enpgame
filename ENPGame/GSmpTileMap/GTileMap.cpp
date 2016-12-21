#include "GTileMap.h"

bool GTileMap::CreateVertexData()
{
	m_VertexList.resize(m_iNumVertices);

	int iHalfCols = m_iNumCols / 2;
	int iHalfRows = m_iNumRows / 2;
	float ftxOffsetU = 1.0f / (m_iNumCols - 1);
	float ftxOffsetV = 1.0f / (m_iNumRows - 1);

	
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int  iVertexIndex = iRow * m_iNumCols + iCol;
			m_VertexList[iVertexIndex].p.x = (iCol - iHalfCols)		* m_fSellDistance;
			m_VertexList[iVertexIndex].p.z = -((iRow - iHalfRows)	* m_fSellDistance);
			m_VertexList[iVertexIndex].p.y = GetHeightOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].n = GetNormalOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].c = GetColorOfVertex(iVertexIndex);
			m_VertexList[iVertexIndex].t.x = ((iCol % UVNum) != 0) ? ((iCol% UVNum) / (1.0f*UVNum)) : 1.0f;//ftxOffsetU *iCol;
			m_VertexList[iVertexIndex].t.y = ((iRow % UVNum) != 0) ? ((iRow % UVNum) / (1.0f*UVNum)) : 1.0f;// ftxOffsetV *iRow;

		}
	}
	return true;
}

GTileMap::GTileMap()
{
}


GTileMap::~GTileMap()
{
}
