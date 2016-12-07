#pragma once
#include "GWindow.h"
#include "GTimer.h"
#include "GInput.h"
#include "GDirectWrite.h"
#include "GShape.h"

class GCoreLibV2 : public GWindow
{
public:
	bool  m_bRenderManually;		// 수동렌더링 for loading bar 출력.
	float m_fScreenColor[4];		// 스크린 컬러 R,G,B,A
	TCHAR m_pFPSBuffer[256];		// FPS 출력
	TCHAR m_pHWInfoBuffer[256];		// HW 정보 출력
	TCHAR m_pScreenInfoBuffer[256];	// Screen Resolution 정보 출력

	GTimer					m_Timer;
	GDirectWrite			m_Font;
	UINT					m_iPrimitiveType;
	UINT					m_iCullMode;
	UINT					m_iSamplerMode;
	bool					m_bWireFrameRender;
	bool					m_bDebugFpsPrint;
	bool					m_bDebugInfoPrint;
	GDirectionLineShape		m_AxisLine;
	T_STR					m_LineShaderFile;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual int			WndProc( HWND, UINT, WPARAM, LPARAM );

	virtual bool		PreInit();	
	virtual bool		PostInit();	 
		
	virtual bool		PreFrame();		
	virtual bool		PostFrame();
	 
	virtual bool		Update(ID3D11DeviceContext*    pContext);
	virtual	bool		PreRender();
	virtual bool		DrawDebug();
	virtual	bool		DrawInfo();

	virtual bool		DrawDebugRect(RECT* rcDest = NULL, TCHAR* pString = 0, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	virtual bool		DrawDebugRect(RECT* rcDest = NULL, TCHAR* pString = 0, D3DXCOLOR color = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) );
	virtual	bool		PostRender();

	bool				GInit();
	bool				GFrame();
	bool				GRender();	
	bool				Run();		 
	bool				ToolRun();
	bool				GRelease();

				HRESULT		CreateDxResource();
				HRESULT		DeleteDxResource();
	virtual		HRESULT		CreateResource();
	virtual		HRESULT		DeleteResource();
	
public:
	GCoreLibV2(void);
	virtual ~GCoreLibV2(void);
};
