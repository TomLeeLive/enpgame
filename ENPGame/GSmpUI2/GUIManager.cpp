#include "_stdafx.h"

bool		GUIManager::Init() {

	/*
	GImageCtl* pImageCtl = new GImageCtl();
	pImageCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pImageCtl->Create(GetDevice(), nullptr, L"data/ui/hud.dds");
	pImageCtl->Scale(400 - 1.0f, 300 - 1.0f, 1.0f - 1.0f);
	pImageCtl->Move(0, 0, 100);
	m_pUIList.push_back(pImageCtl);

	GButtonCtl* pBoxCtl = new GButtonCtl();
	pBoxCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pBoxCtl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
	pBoxCtl->Scale(100 - 1.0f, 50 - 1.0f, 1 - 1.0f);
	pBoxCtl->Move(0, 0, 0);
	m_pUIList.push_back(pBoxCtl);
	*/
	return true;
};
bool		GUIManager::Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {

	
	if (I_Input.KeyCheck(DIK_P) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_BUTTON, SwapChainDesc);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_EDIT, SwapChainDesc);
	}


	GControlUI* pSelect = SelectRect();

	if (pSelect != NULL && m_pSelectPlane != pSelect)
	{
		m_pSelectPlane = pSelect;
	}

	if (m_pSelectPlane)
	{
		D3DXVECTOR3 vPos(0, 0, 0);
		D3DXVECTOR3 vScale(0, 0, 0);
		if (g_InputData.bQKey)
		{
			vScale.x += 50 * g_fSecPerFrame;
		}
		if (g_InputData.bEKey)
		{
			vScale.x += -50 * g_fSecPerFrame;
		}
		if (g_InputData.bZKey)
		{
			vScale.y += 50 * g_fSecPerFrame;
		}
		if (g_InputData.bCKey)
		{
			vScale.y += -50 * g_fSecPerFrame;
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

	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Update();
	}
	return true;

};
bool		GUIManager::Render() {
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Render(g_pImmediateContext);
	}
	return true;
};
bool		GUIManager::Release() {
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Release();
		delete pRect;
	}
	return true;
};
//bool		PlaneRender(D3DXMATRIX 
//---------------------------------
// 변경된 클라이언트 영역를 재설정을
//---------------------------------
HRESULT		GUIManager::CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {
	HRESULT hr;
	// 투영행렬도 윈도우 사이즈가 변경되면 반드시 업테이트 해야 한다.


	int iRectWidth = SwapChainDesc->BufferDesc.Width;
	int iRectHeight = SwapChainDesc->BufferDesc.Height;
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		if (pRect) pRect->CreateResource(iRectWidth, iRectHeight);
	}
	return S_OK;
};
HRESULT		GUIManager::DeleteResource() {
	HRESULT hr;
	return S_OK;
};

GControlUI* GUIManager::AddRect(GUI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {
	GControlUI* pUIControl = NULL;
	switch (type)
	{
	case GUI_TYPE_BUTTON: {
		pUIControl = new GButtonCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	case GUI_TYPE_EDIT: {
		pUIControl = new GEditCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	}
	pUIControl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
	m_pUIList.push_back(pUIControl);
	return pUIControl;
};
GControlUI* GUIManager::SelectRect() {
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	for (int iRect = 0; iRect < m_pUIList.size(); iRect++)
	{
		GControlUI* pRect = m_pUIList[iRect];
		if (I_Input.m_MouseState[0] == KEY_HOLD)
		{
			RECT rt = pRect->m_rt;
			// 뒤집어 진 경우
			if (pRect->m_rt.left > pRect->m_rt.right)
			{
				rt.left = pRect->m_rt.right;
				rt.right = pRect->m_rt.left;
			}
			if (pRect->m_rt.top > pRect->m_rt.bottom)
			{
				rt.top = pRect->m_rt.bottom;
				rt.bottom = pRect->m_rt.top;
			}
			if (rt.left <= mouse.x && rt.right >= mouse.x)
			{
				if (rt.top <= mouse.y && rt.bottom >= mouse.y)
				{
					return pRect;
				}
			}
		}
	}
	return NULL;
};

GUIManager::GUIManager()
{
	m_pSelectPlane = NULL;
}


GUIManager::~GUIManager()
{
}
