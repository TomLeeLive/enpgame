#pragma once
#include <atlstr.h>

#include "GDxHelperEx.h"
#include "GPlaneRect.h"
#include "GInput.h"
#define GUI_ITEM_INFO_LINES 5

class GUIManager
{
public:
	vector<GControlUI*>	m_pUIList;
	T_STR_VECTOR				m_ImageList;
	GControlUI*					m_pSelectPlane;
	void GetStringWeNeed(VOID* pOutStr, VOID* pInStr);
public:
	virtual bool		Init();
	virtual bool		Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual bool		Render();
	virtual bool		Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual HRESULT		DeleteResource();
public:
	BOOL	ExtractSubString(CString& rString, LPCTSTR lpszFullString, int iSubString, TCHAR chSep);
	virtual void	UILoad(T_STR* strFile, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc, float ScrWidth, float ScrHeight);
	virtual void	UICreate(GUI_TYPE type, T_STR* strFile, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc,
		D3DXVECTOR3 vScl = D3DXVECTOR3(100 - 1.0f, 50 - 1.0f, 1 - 1.0f), D3DXVECTOR3 vTrans = D3DXVECTOR3(0, 0, 0),
		int iAutoRescale = 1
		);
#if defined(_DEBUG) || defined(DEBUG)
	virtual GControlUI* AddRect(GUI_TYPE type, TCHAR* strImage, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual GControlUI* AddRect(GUI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual GControlUI* SelectRect();
#endif
public:
	GUIManager();
	virtual ~GUIManager();
};

