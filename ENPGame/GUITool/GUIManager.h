#pragma once

enum G_UI_TYPE {
	G_UI_BUTTON = 0,
	G_UI_IMAGE,
	G_UI_GUAGE,
	G_UI_CNT
};

class GUIManager
{
	std::vector<GControlUI*>	m_pUIList;
	GControlUI*					m_pSelectPlane;
	GSceneUI					m_Scene;
public:
	bool		Init();
	bool		Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	bool		Render();
	bool		Release();
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	HRESULT		DeleteResource();
public:
	GControlUI* AddRect(G_UI_TYPE type, TCHAR* strImage, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	GControlUI* AddRect(G_UI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	GControlUI* SelectRect();
public:
	GUIManager();
	virtual ~GUIManager();
};

