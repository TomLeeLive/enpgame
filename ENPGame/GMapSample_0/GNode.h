#pragma once
#include "GBaseObj.h"
#include "GCamera.h"

struct NodeMtrlInfo
{
	int iMtrl;
	int iNumFaces;
	int iNumVertex;
};

struct GPolygon
{
	int iNumVertides;
	int iNumIndices;
	int iTexIndex;
	bool bBeenUsedAsSplitter;
	D3DXVECTOR3 vNormal;
	PNCT_VERTEX* pVertexList;
	TCHAR strTexName[30];
	DWORD *pIndices;
	GPolygon *pNext;
	virtual ~GPolygon()
	{
		SAFE_DEL(pIndices);
		SAFE_DEL(pVertexList);
	}
};


class GNode
{
public:
	DWORD m_dwDepth;
	BOOL m_isLeaf;
	BOOL m_isTile;
	DWORD m_dwLodLevel;
	DWORD m_dwLodType;

	G_BOX m_gBox;
	vector<DWORD> m_CornerIndex;

	vector<D3DXVECTOR3> m_CornerList;
	vector<GNode*> m_ChildList;
	vector<GNode*> m_NeighborList;
	vector<GBaseObj*> m_ObjectList;

	DWORD m_dwPositionIndex[2];

	D3D11_BOX m_BoxVB;
	D3D11_BOX m_BoxIB;
	UINT m_iBeginVB;
	UINT m_iBeginIB;
	vector<DWORD> m_IndexList;
	vector<PNCT_VERTEX> m_VertexLsit;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D10Buffer> m_pIndexBuffer;

	DWORD m_dwIndex;
	vector<ComPtr<ID3D11Buffer>> m_pVBList;
	vector<ComPtr<ID3D11Buffer>> m_pIBList;
	int iNumPolygon;
	int iNumMtrl;
	vector<NodeMtrlInfo> m_MtrlList;
	GPolygon *m_pSplitter;
	
public:
	GNode();
	virtual ~GNode();
};

