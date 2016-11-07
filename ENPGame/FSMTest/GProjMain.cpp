#include "GProjMain.h"

bool GProjMain::Init()
{
	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");

	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 50.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 10000.0f);

	return true;
}
bool GProjMain::Frame()
{
	m_pMainCamera->Frame();
	D3DXMatrixIdentity(&m_matWorld);
	m_Box->SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	return true;
}
bool GProjMain::Render()
{
	m_Box->Render(m_pImmediateContext);
	return true;
}
bool GProjMain::Release()
{
	return true;
}
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	return true;
}

GProjMain::GProjMain(void)
{
#ifdef G_MACRO_EFFECT_ADD
	m_pSprite = nullptr;
#endif
}

GProjMain::~GProjMain(void)
{

}

int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;

	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_RIGHT:
				{
					m_fAngleY += m_Timer.GetSPF() * 180.0f;
				}break;
				case VK_LEFT:
				{
					m_fAngleY += m_Timer.GetSPF() * 180.0f;
				}break;
				case VK_UP:
				{
					m_fAngleY += m_Timer.GetSPF() * 180.0f;
				}break;
				case VK_DOWN:
				{
					m_fAngleY += m_Timer.GetSPF() * 180.0f;
				}break;
			}
			break;
		}
	}
	return -1;
}
GCORE_RUN(FSM TEST);
