#pragma once


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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	HRESULT		DeleteResource();
public:
	GControlUI* AddRect(GUI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	GControlUI* SelectRect();
public:
	GUIManager();
	virtual ~GUIManager();
};

