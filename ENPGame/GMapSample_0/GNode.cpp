#include "GNode.h"



GNode::GNode()
{
	m_dwLodType = 0;
	m_dwDepth = 0;
	m_isLeaf = FALSE;
	m_gBox.vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_gBox.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_gBox.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_gBox.vAxis[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_gBox.vAxis[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_gBox.vAxis[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_gBox.fExtent[0] = 1;
	m_gBox.fExtent[1] = 1;
	m_gBox.fExtent[2] = 1;


	iNumPolygon = 0;
	iNumMtrl = 0;
	m_pSplitter = NULL;
}


GNode::~GNode()
{
	if(!m_CornerList.empty()) m_CornerList.clear();
	if (!m_CornerList.empty()) m_CornerIndex.clear();

	for (int i = 0; i < m_ChildList.size(); i++)
	{
		SAFE_DEL(m_ChildList[i]);
	}

	if (!m_pVBList.empty())	m_pVBList.clear();
	if (!m_pIBList.empty()) m_pIBList.clear();
	if (!m_MtrlList.empty())	m_MtrlList.clear();
}
