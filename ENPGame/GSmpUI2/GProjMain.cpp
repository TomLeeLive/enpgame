#include "GProjMain.h"

GProjMain* g_pMain;

//int		 GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wData,
//	LPARAM lData)
//{
//	return I_Ime.WndProc(hWnd, msg, wData, lData);
//}

/*
GControlUI* GProjMain::AddRect(GUI_TYPE type)
{
	GControlUI* pUIControl = NULL;
	switch (type)
	{
	case G_BUTTON: {
		pUIControl = new GButtonCtl(); 
		pUIControl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	case G_EDIT: {
		pUIControl = new GEditCtl();
		pUIControl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
		}
	}
	pUIControl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);	
	m_pUIList.push_back(pUIControl);
	return pUIControl;
}
*/

GControlUI* GProjMain::SelectRect()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_hWnd, &mouse);
	for (int iRect = 0; iRect < m_pUIList.size(); iRect++)
	{
		GControlUI* pRect = m_pUIList[iRect];
		if (I_Input.m_MouseState[0] == KEY_HOLD)
		{
			RECT rt= pRect->m_rt;
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
}
bool GProjMain::Init()
{
	//I_Ime.ImeUi_Initialize(m_hWnd);

	GImageCtl* pImageCtl = new GImageCtl();
	pImageCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pImageCtl->Create(GetDevice(), nullptr, L"data/ui/hud.dds");
	pImageCtl->Scale(400-1.0f, 300-1.0f, 1.0f-1.0f);
	pImageCtl->Move(0, 0, 100);
	m_pUIList.push_back(pImageCtl);

	GButtonCtl* pBoxCtl = new GButtonCtl();
	pBoxCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pBoxCtl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
	pBoxCtl->Scale(100 - 1.0f, 50 - 1.0f, 1 - 1.0f);
	pBoxCtl->Move(0, 0, 0);
	m_pUIList.push_back(pBoxCtl);
	
#pragma region g_pTextureSRV
	//m_pTextureSRV[0].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/Background.bmp"));
	//m_pTextureSRV[1].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/_connect.bmp"));
	//m_pTextureSRV[2].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/_exit_lg.bmp"));
#pragma endregion
	return true;
}
bool GProjMain::Frame()
{
	/*
	if (I_Input.KeyCheck(DIK_P) == KEY_UP)
	{
		m_pSelectPlane = AddRect(G_BUTTON);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		m_pSelectPlane = AddRect(G_EDIT);
	}
	*/

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
		m_pSelectPlane->Move(vPos.x,vPos.y,	vPos.z);
		m_pSelectPlane->Scale(vScale.x,	vScale.y,vScale.z);
	}

	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Update();
	}
	return true;
}
bool GProjMain::Render()
{
	D3DXMATRIX matTrans, matRotation, matZ;
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

	//D3DXMatrixTranspose(&m_cbData.matProj, &m_Projection[1]);
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Render(m_pImmediateContext);		
	}
	return true;
}
bool GProjMain::Release()
{
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Release();
		delete pRect;
	}
	//I_Ime.Uninitialize();
	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	// 투영행렬도 윈도우 사이즈가 변경되면 반드시 업테이트 해야 한다.
	int iRectWidth = m_SwapChainDesc.BufferDesc.Width;
	int iRectHeight = m_SwapChainDesc.BufferDesc.Height;
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		if( pRect ) pRect->CreateResource(iRectWidth, iRectHeight);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
	m_pSelectPlane = NULL;
}

GProjMain::~GProjMain(void)
{
}
GCORE_RUN(L"GBasisSample UI_0");