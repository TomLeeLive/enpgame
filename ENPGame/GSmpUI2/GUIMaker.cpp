//#include "stdafx.h"
#include "_stdafx.h"


bool		GUIMaker::Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {

#if defined(_DEBUG)	|| defined(DEBUG)
	if (I_Input.KeyCheck(DIK_P) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_BUTTON, SwapChainDesc);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_IMAGE, SwapChainDesc);
	}


	//GControlUI* pSelect = SelectRect();
	
	
	GControlUI* pSelect = NULL;
	int iSelected = -1;
	iSelected = SelectRect(&pSelect);
	
	//if (iSelected != -1) {
	//	int a = 10;
	//}
	
	if (pSelect != NULL && m_pSelectPlane != pSelect && iSelected != 0)
	{
		m_pSelectPlane = pSelect;

		//선택된 버튼은 어둡게 처리.
		if (m_pSelectPlane->m_type == GUI_TYPE_BUTTON)
			((GButtonCtl*)m_pSelectPlane)->m_Box.m_bShaded = true;

		//선택되지 않은 버튼은 밝게 처리.
		for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
		{
			if (iPlane == iSelected)
				continue;

			if (m_pUIList[iPlane]->m_type == GUI_TYPE_BUTTON) {
				//((GButtonCtl*)m_pUIList[iPlane])->m_Box.m_bShaded = false;

				GButtonCtl* pRect = (GButtonCtl*)m_pUIList[iPlane];
				pRect->m_Box.m_bShaded = false;
			}

		}
	}


	if (m_pSelectPlane)
	{
		D3DXVECTOR3 vPos(0, 0, 0);
		D3DXVECTOR3 vScale(0, 0, 0);
		if (g_InputData.bQKey)
		{
			vScale.x += 50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.x = m_pSelectPlane->m_vScale.x;

		}
		if (g_InputData.bEKey)
		{
			vScale.x += -50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.x = m_pSelectPlane->m_vScale.x;
		}
		if (g_InputData.bZKey)
		{
			vScale.y += 50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.y = m_pSelectPlane->m_vScale.y;
		}
		if (g_InputData.bCKey)
		{
			vScale.y += -50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.y = m_pSelectPlane->m_vScale.y;
		}
		if (g_InputData.bWKey)
		{
			vPos.y = 50 * g_fSecPerFrame;
		}
		if (g_InputData.bSKey)
		{
			vPos.y = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bAKey)
		{
			vPos.x = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bDKey)
		{
			vPos.x = 50 * g_fSecPerFrame;
		}
		m_pSelectPlane->Move(vPos.x, vPos.y, vPos.z);
		m_pSelectPlane->Scale(vScale.x, vScale.y, vScale.z);
	}
#endif
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Update();
	}
	return true;

};

GUIMaker::GUIMaker()
{
	m_pSelectPlane = NULL;
}


GUIMaker::~GUIMaker()
{
}
