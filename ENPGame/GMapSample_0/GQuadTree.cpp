#include "GQuadTree.h"

bool GQuadTree::Build(float fWidth, float fHeight)
{
	m_fWidth = fWidth, m_fHeight = fHeight;
	m_pRootNode = CreateNode(NULL, -fWidth / 2, fWidth / 2, -fHeight / 2, fHeight / 2);
	if (BuildTree(m_pRootNode))
	{
		return true;
	}
	return false;
}
bool GQuadTree::BuildTree(GNode* pNode)
{
	if (SubDivide(pNode))
	{
		for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
		{
			if (m_bUsedIndexList)
			{
				DWORD dwIndex = pNode->m_ChildList[iNode]->m_dwPositionIndex[1]
					* pow(2.0f, (float)pNode->m_ChildList[iNode]->m_dwDepth)
					+ pNode->m_ChildList[iNode]->m_dwPositionIndex[0];
				m_LevelList[pNode->m_ChildList[iNode]->m_dwDepth][dwIndex] = pNode->m_ChildList[iNode];
			}
			BuildTree(pNode->m_ChildList[iNode]);
		}
	}
	return true;
}
bool GQuadTree::SubDivide(GNode* pNode)
{
	if (pNode ==NULL)
	{
		return false;
	}
	if (m_iMaxDepthLimit <= pNode->m_dwDepth)
	{
		pNode->m_isLeaf = TRUE;
		return false;
	}

	float fWidthSplit = (pNode->m_CornerList[tTR].x - pNode->m_CornerList[tTL].x) / 2;
	float fHeightSplit = (pNode->m_CornerList[tTL].z - pNode->m_CornerList[tBL].z) / 2;

	if (fWidthSplit < m_fMinDivideSize || fHeightSplit < m_fMinDivideSize)
	{
		pNode->m_isLeaf = TRUE;
		return false;
	}
	pNode->m_ChildList.push_back(
		CreateNode(pNode, 
			pNode->m_CornerList[tTL].x,
			pNode->m_CornerList[tTL].x + fWidthSplit,
			pNode->m_CornerList[tTL].z - fHeightSplit,
			pNode->m_CornerList[tTL].z));

	pNode->m_ChildList.push_back(
		CreateNode(pNode,
			pNode->m_CornerList[tTL].x + fWidthSplit,
			pNode->m_CornerList[tTR].x,
			pNode->m_CornerList[tTL].z - fHeightSplit,
			pNode->m_CornerList[tTL].z));
	pNode->m_ChildList.push_back(
		CreateNode(pNode,
			pNode->m_CornerList[tTL].x,
			pNode->m_CornerList[tTL].x + fWidthSplit,
			pNode->m_CornerList[tBL].z,
			pNode->m_CornerList[tTL].z - fHeightSplit));
	pNode->m_ChildList.push_back(
		CreateNode(pNode,
			pNode->m_CornerList[tTL].x + fWidthSplit,
			pNode->m_CornerList[tTR].x,
			pNode->m_CornerList[tBR].x,
			pNode->m_CornerList[tTL].z - fHeightSplit));
	return true;

}
bool GQuadTree::Release()
{
	SAFE_DEL(m_pRootNode);
	return true;
}
bool GQuadTree::PreFrame()
{
	m_DrawObjList.clear();
	m_DrawNodeList.clear();
	if (!m_pCamera)
	{
		return false;		
	}
	return true;
}
bool GQuadTree::Frame()
{
	if (!PreFrame())
	{
		return false;
	}
	DrawFindNode(m_pRootNode);
	return true;
}
GNode* GQuadTree::CreateNode(GNode* pParentNode, float fTopLeft, 
	float fTopRight, float fBottomLeft, float fBottomRight)
{ 
	GNode* pNode = 0;
	SAFE_NEW(pNode, GNode);
	assert(pNode);
	pNode->m_ChildList.reserve(4);
	pNode->m_CornerList.reserve(4);

	pNode->m_gBox.vMin = D3DXVECTOR3(fTopLeft, 0.0f, fBottomLeft);
	pNode->m_gBox.vMax = D3DXVECTOR3(fTopRight, 0.0f, fBottomRight);
	pNode->m_gBox.vCenter = (pNode->m_gBox.vMax + pNode->m_gBox.vMin) / 2.0f;
	pNode->m_gBox.fExtent[0] = pNode->m_gBox.vMax.x - pNode->m_gBox.vCenter.x;
	pNode->m_gBox.fExtent[1] = pNode->m_gBox.vMax.y - pNode->m_gBox.vCenter.y;
	pNode->m_gBox.fExtent[2] = pNode->m_gBox.vMax.z - pNode->m_gBox.vCenter.z;

	pNode->m_CornerList.push_back(D3DXVECTOR3(pNode->m_gBox.vMin.x, 0.0f, pNode->m_gBox.vMax.z));
	pNode->m_CornerList.push_back(pNode->m_gBox.vMax);
	pNode->m_CornerList.push_back(pNode->m_gBox.vMin);
	pNode->m_CornerList.push_back(D3DXVECTOR3(pNode->m_gBox.vMax.x, 0.0f, pNode->m_gBox.vMin.z));

	if (pParentNode)
	{
		pNode->m_dwDepth = pParentNode->m_dwDepth + 1;
		if (m_iMaxDepth < pNode->m_dwDepth)
		{
			m_iMaxDepth = pNode->m_dwDepth;
		}
	}
	return pNode;

}

int GQuadTree::AddObject(GBaseObj* pObj)
{
	if (CheckRect(m_pRootNode, pObj))
	{
		GNode* pNode = FindNode(m_pRootNode, pObj);
		if (pNode)
		{
			pNode->m_ObjectList.push_back(pObj);
		}
		return 1;
	}
	return 0;
}
GNode* GQuadTree::FindNode(GNode* pNode, GBaseObj* pObj)
{
	assert(pNode);
	do
	{
		for (DWORD dwChild = 0; dwChild < pNode->m_ChildList.size(); dwChild++)
		{
			if (pNode->m_ChildList[dwChild] && CheckRect(pNode->m_ChildList[dwChild], pObj))
			{
				m_QuadTreeQueue.push(pNode->m_ChildList[dwChild]);
			}
		}
		if (m_QuadTreeQueue.empty())	break;

		pNode = m_QuadTreeQueue.front();
		m_QuadTreeQueue.pop();
	} while (pNode);
	return pNode;
}
int GQuadTree::CheckRect(GNode* pNode, GBaseObj* pObj)
{
	if(pNode->m_gBox.vMin.x <= pObj->m_tBox.vMin.x && pNode->m_gBox.vMax.x >= pObj->m_tBox.vMax.x)
	{
		if (pNode->m_gBox.vMin.z <= pObj->m_tBox.vMin.z && pNode->m_gBox.vMax.z >= pObj->m_tBox.vMax.z)
		{
			return 1;
		}
	}
	return 0;
}

void GQuadTree::VisibleNode(GNode* pNode)
{

}
void GQuadTree::VisibleObject(GNode* pNode)
{
	assert(m_pCamera);
	if (pNode->m_dwDepth < m_iRenderDepth)
	{
		return;
	}
	if (m_pCamera->CheckOBBInPlane(&pNode->m_gBox))
	{
		VisibleObject(pNode);
		for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
		{
			VisibleNode(pNode->m_ChildList[iNode]);
		}
	}
}
void GQuadTree::DrawFindNode(GNode* pNode)
{
	assert(pNode);
	G_POSITION g_Pos = m_pCamera->CheckPoitionOBBInPlane(&pNode->m_gBox);
	GetLodSubIndex(pNode);
	if (pNode->m_dwDepth < m_iRenderDepth)
	{
		return;
	}
	if (pNode->m_isLeaf && g_Pos != P_BACK)
	{
		m_DrawNodeList.push_back(pNode);
		VisibleObject(pNode);
		return;
	}

	if (g_Pos ==P_FRONT)
	{
		m_DrawNodeList.push_back(pNode);
		VisibleNode(pNode);
		return;
	}

	if (g_Pos == P_SPANNING)
	{
		VisibleObject(pNode);
	}
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		DrawFindNode(pNode->m_ChildList[iNode]);
	}
}
DWORD GQuadTree::CheckSize(DWORD dwSize)
{
	float fCount = 0;
	DWORD dwChecker = dwSize / 2;
	if (dwChecker <= 0)
	{
		return 0;
	}
	while (dwChecker !=0)
	{
		dwChecker >>= 1;
		fCount += 1.0f;
	}
	float fMinimum = pow(2.0f, fCount - 1.0f);
	float fMaximum = pow(2.0f, fCount);

	float fMin = fabs(fMinimum - fabs(((float)dwSize - fMinimum)));
	float fMax = fabs(fMaximum - fabs(((float)dwSize - fMaximum)));

	if (fMin <= fMax)
	{
		return fMinimum;
	}
	return fMaximum;
}
void GQuadTree::SetRenderDepth(DWORD dwDepth)
{
	if (m_iMaxDepth <= dwDepth) m_iRenderDepth = -1;
	else m_iRenderDepth = dwDepth;
}
void GQuadTree::SetNeighborNode(GNode* pNode)
{
	FindNeighborNode(pNode);
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		SetNeighborNode(pNode->m_ChildList[iNode]);
	}
}
void GQuadTree::FindNeighborNode(GNode* pNode)
{
	pNode->m_NeighborList.resize(4);
	
	DWORD dwNumPatchCount = pow(2.0f, (float)pNode->m_dwDepth);

	DWORD dwNeighborCol, dwNeighborRow;
	if (pNode->m_dwPositionIndex[1] >0)
	{
		dwNeighborCol = pNode->m_dwPositionIndex[0];
		dwNeighborRow = (pNode->m_dwPositionIndex[1] - 1)* dwNumPatchCount;
		pNode->m_NeighborList[0] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
	}
	if (pNode->m_dwPositionIndex[1] < dwNumPatchCount -1)
	{
		dwNeighborCol = pNode->m_dwPositionIndex[0];
		dwNeighborRow = (pNode->m_dwPositionIndex[1] + 1)*dwNumPatchCount;
		pNode->m_NeighborList[1] = m_LevelList[pNode->m_dwDepth][dwNeighborCol + dwNeighborRow];
	}
	if (pNode->m_dwPositionIndex[0] > 0) // аб
	{
		dwNeighborCol = pNode->m_dwPositionIndex[0] - 1;
		dwNeighborRow = pNode->m_dwPositionIndex[1] * dwNumPatchCount;
		pNode->m_NeighborList[2] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
	}
	if (pNode->m_dwPositionIndex[0] < dwNumPatchCount - 1) // ©Л
	{
		dwNeighborCol = pNode->m_dwPositionIndex[0] + 1;
		dwNeighborRow = pNode->m_dwPositionIndex[1] * dwNumPatchCount;
		pNode->m_NeighborList[3] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
	}
}

GQuadTree::GQuadTree()
{
	m_iNumCell = 1;
	m_iPatchLodCount = 0;
	m_iRenderDepth = 0;
	m_iMaxDepth = 0;
	m_iMaxDepth = 0;
	m_iMaxDepthLimit = 4;
	m_fMinDivideSize = 2;
	m_bUsedIndexList = false;
	SAFE_ZERO(m_pd3dDevice);
	SAFE_ZERO(m_pRootNode);
}


GQuadTree::~GQuadTree()
{
	Release();
}
