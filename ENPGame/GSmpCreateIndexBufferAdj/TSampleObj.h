#pragma once
#include "GObject.h"
#include "TAdjRep.h"
struct TAdjData
{
	UINT					m_iNumVertex;
	UINT					m_iNumIndex;
	UINT					m_iVertexSize;
	UINT					m_iIndexSize;
	D3D11_BOX				m_BoxVB;
	D3D11_BOX				m_BoxIB;
	UINT					m_iBeginVB;
	UINT					m_iBeginIB;
	vector<TAdjData>		m_pSubMesh;
};
class TSampleObj : public GGbsObj
{
public:
	bool					m_bAdjacency;
	TAdjacencyRep			m_rep;
	vector<DWORD>			m_IndexListAdj;
	ComPtr<ID3D11Buffer>	m_pIndexBufferAdj;
	vector<TAdjData>		m_pMeshAdj;
public:
	bool ShadowDraw(ID3D11DeviceContext*    pContext, GModel* pParent);
	bool CreateIndexData();
public:
	TSampleObj();
	virtual ~TSampleObj();
};

