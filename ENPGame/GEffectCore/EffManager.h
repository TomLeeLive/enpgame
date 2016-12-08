#pragma once

#include <atlstr.h>

#include "GSprite.h"
#include "GTimer.h"
#include "GCamera.h"
#include "KEffect.h"

#define G_EFF_ITEM_INFO_LINES 5

enum G_EFF_TOOL_EXT {
	G_EFF_TOOL_EXT1,//.eff
	G_EFF_TOOL_EXT2,//.bff
};

using namespace std;

class EffManager
{
public:
	BOOL ExtractSubString(CString& rString, LPCTSTR lpszFullString,
		int iSubString, TCHAR chSep);
	T_STR_VECTOR				m_ImageList;
	HRESULT	SetBlendState();
	ID3D11BlendState*           m_pAlphaBlendFactor;
	ID3D11BlendState*			m_pAlphaBlend;
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);

	vector<shared_ptr<KEffect>> m_List;
	virtual void				Load(T_STR* strFile);
	virtual void		Create(G_EFFECT_TYPE type, T_STR* strFile,
		D3DXVECTOR3 vScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f), float fTime = 0.0f, int Width, int WidthSize, int Height, int HeightSize
		);
	static void			GetStringWeNeed(VOID* pOutStr, VOID* pInStr);
public:
	virtual bool		Init();
	virtual bool		Frame(GCamera* camera, GTimer* timer);
	virtual bool		Render();
	virtual bool		Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	virtual HRESULT		CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc);
	virtual HRESULT		DeleteResource();
public:
	EffManager();
	virtual ~EffManager();
};

