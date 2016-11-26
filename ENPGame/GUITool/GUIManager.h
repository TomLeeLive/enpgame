#pragma once

//enum G_TOOL_IMG_EXT {
//	G_TOOL_IMG_EXT_BMP,
//	G_TOOL_IMG_EXT_PNG,
//	G_TOOL_IMG_EXT_JPG,
//	G_TOOL_IMG_EXT_CNT
//};
//enum G_UI_TYPE {
//	G_UI_BUTTON = 0,
//	G_UI_IMAGE,
//	G_UI_GUAGE,
//	G_UI_CNT
//};

class GUIManager
{
public:
	std::vector<GControlUI*>	m_pUIList;
	T_STR_VECTOR				m_ImageList;
	GControlUI*					m_pSelectPlane;
	//GSceneUI					m_Scene;
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
	void	UILoad(T_STR* strFile);
	void	UICreate(GUI_TYPE type, T_STR_VECTOR* strFile, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
#if defined(_DEBUG) || defined(DEBUG)
	GControlUI* AddRect(GUI_TYPE type, TCHAR* strImage, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	GControlUI* AddRect(GUI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	GControlUI* SelectRect();
#endif
public:
	GUIManager();
	virtual ~GUIManager();
};

