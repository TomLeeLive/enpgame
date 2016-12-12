#pragma once
#include "GObjStd.h"
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
typedef vector<INT>				INT_List;
typedef vector<INT>::iterator	INT_itor;
struct TVertex
{
	INT_List 		m_iFaceList;
	INT_List 		m_iEdgeList;
	PNCT_VERTEX		m_Format;
};
struct TEdge
{
	UINT			m_iIndex;
	UINT			m_iVertexID[2];
	float			m_fDistance;
	D3DXVECTOR3		m_vCenter;
	INT_List 		m_tFaceList;
};
struct TFace
{
	UINT			m_iVertexID[3];
	UINT 			m_iEdge[3];
	UINT			m_NeightborFaceID[3];
	UINT			m_iIndexAdj[3];
	D3DXVECTOR3		m_vNormal;
};

typedef vector<TVertex>				tVertexList;
typedef vector<TVertex>::iterator	tVertexitor;
typedef vector<TEdge>				tEdgeList;
typedef vector<TEdge>::iterator		tEdgeitor;
typedef map<T_STR, int>				tEdgeMap;
typedef map<T_STR, int>::iterator	tEdgeMapitor;
typedef vector<TFace>				tFaceList;
typedef vector<TFace>::iterator		tFaceitor;

//임시 데이터를 갖고 주변 정점을 얻는다.(Adjacency To Representative)
struct TAdjacencyRep
{
	tVertexList		m_tVertexList;
	tEdgeList		m_tEdgeList;
	tEdgeMap		m_tEdgeMap;
	tFaceList		m_tFaceList;
	void	AddVertex(PNCT_VERTEX Format);
	int		AddEdge(UINT v0, UINT v1, UINT iFace);
	void	AddFace(UINT v0, UINT v1, UINT v2, UINT e0, UINT e1, UINT e2);
	DWORD	CreateNewVertex(TFace& Face);
	DWORD	CreateNewVertex(TEdge Edge);
	void	GenerateAdjacency(vector<PNCT_VERTEX>& vertexlist, vector<DWORD>& IndexList);
	int		CheckEdge(UINT v0, UINT v1);
	int		CheckEdge(T_STR v0, T_STR v1);
	void	Clear();
};
