#pragma once
#include "GDevice.h"

class GWindow : public GDevice
{
public:
	bool					m_bMaximized;				//ó�� ���� �ִ�ȭ ����
	UINT					m_iInitialWidth;			//ó�� ������ ����ũ��
	UINT					m_iInitialHeight;			//ó�� ������ ����ũ��
	//--------------------------------------------
	// Global Variables
	//--------------------------------------------
	HINSTANCE               m_hInstance;		// �ν��Ͻ� �ڵ�
	HWND                    m_hWnd;				// ������ �ڵ�
	DWORD					m_dwWindowStyle;	// ������ ��Ÿ��
	RECT					m_rcWindowBounds;   // ������ ����
	RECT					m_rcWindowClient;   // Ŭ���̾�Ʈ ����	
	UINT					m_iWindowWidth;		// Ŭ���̾�Ʈ ���� ����ũ��
	UINT					m_iWindowHeight;	// �����̾�Ʈ ���� ����ũ��
public:
	//--------------------------------------------
	// ������ ����
	//--------------------------------------------
	bool				InitWindow(		HINSTANCE hInstance, 
										int nCmdShow, 
										TCHAR* strWindowTitle = _T("GCore GProjMain"), 										
										int iWidth = 800,
										int iHeight=600,
										bool bMaximized = false,
										BOOL IsFullScreen = FALSE);	
	//--------------------------------------------
	// ������ ��ġ ȭ�� �߾����� �̵�
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