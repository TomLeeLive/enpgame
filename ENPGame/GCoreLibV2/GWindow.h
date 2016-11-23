#pragma once
#include "GDevice.h"

class GWindow : public GDevice
{
public:
	bool					m_bMaximized;				//처음 셋팅 최대화 여부
	UINT					m_iInitialWidth;			//처음 셋팅한 가로크기
	UINT					m_iInitialHeight;			//처음 셋팅한 세로크기
	//--------------------------------------------
	// Global Variables
	//--------------------------------------------
	HINSTANCE               m_hInstance;		// 인스턴스 핸들
	HWND                    m_hWnd;				// 윈도우 핸들
	DWORD					m_dwWindowStyle;	// 윈도우 스타일
	RECT					m_rcWindowBounds;   // 윈도우 영역
	RECT					m_rcWindowClient;   // 클라이언트 영역	
	UINT					m_iWindowWidth;		// 클라이언트 영역 가로크기
	UINT					m_iWindowHeight;	// 을라이언트 영역 세로크기
public:
	//--------------------------------------------
	// 윈도우 생성
	//--------------------------------------------
	bool				InitWindow(		HINSTANCE hInstance, 
										int nCmdShow, 
										TCHAR* strWindowTitle = _T("GCore GProjMain"), 										
										int iWidth = 800,
										int iHeight=600,
										bool bMaximized = false,
										BOOL IsFullScreen = FALSE);	
	//--------------------------------------------
	// 윈도우 위치 화면 중앙으로 이동
	//--------------------------------------------
	void				CenterWindow(HWND hwnd);
	bool				CheckWindowSize();
	void				ClipMouse(bool bClip);

public:
	virtual int			WndProc( HWND, UINT, WPARAM, LPARAM );
			LRESULT		WindowMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
public:
	GWindow(void);
	virtual ~GWindow(void);
};