#include "TAdjRep.h"

void TAdjacencyRep::Clear()
{
	m_tVertexList.clear();
	m_tEdgeList.clear();
	m_tFaceList.clear();
	m_tEdgeMap.clear();
}
void TAdjacencyRep::AddVertex(PNCT_VERTEX Format)
{
	TVertex Vertex;
	Vertex.m_Format = Format;
	m_tVertexList.push_back(Vertex);
}
int TAdjacencyRep::CheckEdge(UINT v0, UINT v1)
{
	for (int iEdge = 0; iEdge < m_tEdgeList.size(); iEdge++)
	{
		if ((m_tEdgeList[iEdge].m_iVertexID[0] == v0 &&
			m_tEdgeList[iEdge].m_iVertexID[1] == v1) ||
			(m_tEdgeList[iEdge].m_iVertexID[1] == v0 &&
				m_tEdgeList[iEdge].m_iVertexID[0] == v1))
		{
			return iEdge;
		}
	}
	return -1;
}
int TAdjacencyRep::CheckEdge(T_STR v0, T_STR v1)
{
	tEdgeMapitor itor = m_tEdgeMap.find(v0);
	if (itor == m_tEdgeMap.end())
	{
		tEdgeMapitor itor = m_tEdgeMap.find(v1);
		if (itor == m_tEdgeMap.end())
		{
			return -1;
		}
		return (*itor).second;
	}
	return (*itor).second;
}
int TAdjacencyRep::AddEdge(UINT v0, UINT v1, UINT iFace)
{
	TCHAR nameA[256] = { 0, };
	TCHAR nameB[256] = { 0, };
	_stprintf(nameA, L"%d%d", v0, v1);
	_stprintf(nameB, L"%d%d", v1, v0);

	int iEdgeID = CheckEdge(nameA, nameB);
	if (iEdgeID < 0)
	{
		TEdge Edge;
		iEdgeID = m_tEdgeList.size();
		Edge.m_iIndex = iEdgeID;
		Edge.m_iVertexID[0] = v0;
		Edge.m_iVertexID[1] = v1;
		Edge.m_fDistance = D3DXVec3Length(&(m_tVertexList[v0].m_Format.p - m_tVertexList[v1].m_Format.p));
		Edge.m_vCenter = (m_tVertexList[v0].m_Format.p + m_tVertexList[v1].m_Format.p) * 0.5;
		Edge.m_tFaceList.push_back(iFace);
		m_tEdgeList.push_back(Edge);
		m_tEdgeMap[nameA] = iEdgeID;
	}
	else
	{
		m_tEdgeList[iEdgeID].m_tFaceList.push_back(iFace);
	}
	m_tVertexList[v0].m_iEdgeList.push_back(iEdgeID);
	m_tVertexList[v1].m_iEdgeList.push_back(iEdgeID);
	return iEdgeID;
}
void TAdjacencyRep::AddFace(UINT v0, UINT v1, UINT v2, UINT e0, UINT e1, UINT e2)
{
	TFace Face;
	Face.m_iVertexID[0] = v0;
	Face.m_iVertexID[1] = v1;
	Face.m_iVertexID[2] = v2;
	Face.m_iEdge[0] = e0;
	Face.m_iEdge[1] = e1;
	Face.m_iEdge[2] = e2;

	D3DXVECTOR3 vEdge0, vEdge1;
	vEdge0 = m_tVertexList[v1].m_Format.p - m_tVertexList[v0].m_Format.p;
	vEdge1 = m_tVertexList[v2].m_Format.p - m_tVertexList[v0].m_Format.p;

	D3DXVec3Cross(&Face.m_vNormal, &vEdge0, &vEdge1);
	D3DXVec3Normalize(&Face.m_vNormal, &Face.m_vNormal);
	m_tFaceList.push_back(Face);
}
DWORD TAdjacencyRep::CreateNewVertex(TEdge Edge)
{
	TVertex NewVertex;
	// 최대 크기의 에지에서 중점에 해당하는 정점을 생성한다.
	NewVertex.m_Format.p = Edge.m_vCenter;

	D3DXVec3Lerp(&NewVertex.m_Format.n, &m_tVertexList[Edge.m_iVertexID[0]].m_Format.n,
		&m_tVertexList[Edge.m_iVertexID[1]].m_Format.n,
		0.5f);
	D3DXVec4Lerp(&NewVertex.m_Format.c, &m_tVertexList[Edge.m_iVertexID[0]].m_Format.c,
		&m_tVertexList[Edge.m_iVertexID[1]].m_Format.c,
		0.5f);
	D3DXVec2Lerp(&NewVertex.m_Format.t, &m_tVertexList[Edge.m_iVertexID[0]].m_Format.t,
		&m_tVertexList[Edge.m_iVertexID[1]].m_Format.t,
		0.5f);

	// 신규 정점을 리스트에 추가한다.
	AddVertex(NewVertex.m_Format);
	return m_tVertexList.size() - 1;
}
DWORD TAdjacencyRep::CreateNewVertex(TFace& Face)
{
	TVertex NewVertex;
	// 중점을 계산한다.
	DWORD dwIndex[3];
	dwIndex[0] = Face.m_iVertexID[0];
	dwIndex[1] = Face.m_iVertexID[1];
	dwIndex[2] = Face.m_iVertexID[2];

	D3DXVECTOR3 vCenter = (m_tVertexList[dwIndex[0]].m_Format.p + m_tVertexList[dwIndex[1]].m_Format.p +
		m_tVertexList[dwIndex[2]].m_Format.p) / 3;

	D3DXVECTOR3 vNormal = (m_tVertexList[dwIndex[0]].m_Format.n + m_tVertexList[dwIndex[1]].m_Format.n +
		m_tVertexList[dwIndex[2]].m_Format.n) / 3;

	D3DXVECTOR4 vColor = (m_tVertexList[dwIndex[0]].m_Format.c + m_tVertexList[dwIndex[1]].m_Format.c +
		m_tVertexList[dwIndex[2]].m_Format.c) / 3;

	D3DXVECTOR2 vTexCoord = (m_tVertexList[dwIndex[0]].m_Format.t + m_tVertexList[dwIndex[1]].m_Format.t +
		m_tVertexList[dwIndex[2]].m_Format.t) / 3;

	NewVertex.m_Format.p = vCenter;
	NewVertex.m_Format.n = vNormal;
	NewVertex.m_Format.c = vColor;
	NewVertex.m_Format.t = vTexCoord;

	// 신규 정점을 리스트에 추가한다.
	AddVertex(NewVertex.m_Format);
	return m_tVertexList.size() - 1;
}
void TAdjacencyRep::GenerateAdjacency(vector<PNCT_VERTEX>& vertexlist, vector<DWORD>& IndexList)
{
	for (int iVertex = 0; iVertex < vertexlist.size(); iVertex++)
	{
		AddVertex(vertexlist[iVertex]);
	}

	m_tEdgeList.clear();
	m_tFaceList.clear();

	for (int iVetex = 0; iVetex < m_tVertexList.size(); iVetex++)
	{
		m_tVertexList[iVetex].m_iEdgeList.clear();
		m_tVertexList[iVetex].m_iFaceList.clear();
	}
	int iEdge0, iEdge1, iEdge2;
	for (int iFace = 0; iFace < IndexList.size() / 3; iFace++)
	{
		DWORD dwIndex[3];
		dwIndex[0] = IndexList[iFace * 3 + 0];
		dwIndex[1] = IndexList[iFace * 3 + 1];
		dwIndex[2] = IndexList[iFace * 3 + 2];

		iEdge0 = AddEdge(dwIndex[0], dwIndex[1], iFace);
		iEdge1 = AddEdge(dwIndex[1], dwIndex[2], iFace);
		iEdge2 = AddEdge(dwIndex[2], dwIndex[0], iFace);
		//AddFace(dwIndex[0], dwIndex[1], dwIndex[2], iFace * 3 + 0, iFace * 3 + 1, iFace * 3 + 2);
		AddFace(dwIndex[0], dwIndex[1], dwIndex[2], iEdge0, iEdge1, iEdge2);
	}

	// 주변 정점 저장
	for (int iFace = 0; iFace < m_tFaceList.size(); iFace++)
	{
		// 주변 페이스가 없을 경우는 -1을 사용한다.
		m_tFaceList[iFace].m_NeightborFaceID[0] = -1;
		m_tFaceList[iFace].m_NeightborFaceID[1] = -1;
		m_tFaceList[iFace].m_NeightborFaceID[1] = -1;
		// 이웃 페이스 저장( 2 개가 최대값이 된다. )
		for (int iEdge = 0; iEdge < 3; iEdge++)
		{
			int iFaceToEdge = m_tFaceList[iFace].m_iEdge[iEdge];
			// 주변 정점이 없을 경우는 에지의 첫번째 정점을 사용한다.
			int iVertexAdj = m_tEdgeList[iFaceToEdge].m_iVertexID[0];
			for (int iNeightborFace = 0; iNeightborFace < m_tEdgeList[iFaceToEdge].m_tFaceList.size(); iNeightborFace++)
			{
				if (m_tEdgeList[iFaceToEdge].m_tFaceList[iNeightborFace] != iFace)
				{
					int iNeightbor = m_tEdgeList[iFaceToEdge].m_tFaceList[iNeightborFace];
					m_tFaceList[iFace].m_NeightborFaceID[iEdge] = iNeightbor;

					// 이웃 페이스 정점 저장					
					for (int iVer = 0; iVer < 3; iVer++)
					{
						if (m_tFaceList[iNeightbor].m_iVertexID[iVer] != m_tEdgeList[iFaceToEdge].m_iVertexID[0] &&
							m_tFaceList[iNeightbor].m_iVertexID[iVer] != m_tEdgeList[iFaceToEdge].m_iVertexID[1])
						{
							iVertexAdj = m_tFaceList[iNeightbor].m_iVertexID[iVer];
						}
					}
					break;
				}
			}
			m_tFaceList[iFace].m_iIndexAdj[iEdge] = iVertexAdj;
		}
	}
}