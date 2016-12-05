#include "GWindow.h"
#include "GWindow.h"

GWindow* g_pWindow = NULL;

namespace GCORESTD
{
	HWND		g_hWnd;
	HINSTANCE	g_hInstance;
};

//--------------------------------------------------------------------------------------
// ���� ������ ���ν���
//--------------------------------------------------------------------------------------
LRESULT WINAPI StaticWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{		
	assert(g_pWindow);
	return g_pWindow->WindowMsgProc(  hWnd,  msg,  wParam,  lParam );   
}
//--------------------------------------------------------------------------------------
// �����Լ� ������ ���ν���
//--------------------------------------------------------------------------------------
int GWindow::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return -1;
}
//--------------------------------------------------------------------------------------
// ������ ���ν���
//--------------------------------------------------------------------------------------
LRESULT GWindow::WindowMsgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	int iReturn = WndProc(  hWnd,  message,  wParam,  lParam );
	if( iReturn >= 0 )
	{
		return iReturn;
	}

    switch( message )
    {
		case WM_KEYDOWN:
        {
			switch( wParam )
			{
				case '0':
				{
					if( GetSwapChain() )
					{	
						BOOL IsScreenMode = FALSE;
						GetSwapChain()->GetFullscreenState( &IsScreenMode, NULL );

						if(!IsScreenMode){
							int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
							int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
							if (FAILED(ResizeDevice(iScreenWidth, iScreenHeight))) {}

							SetFullScreenFlag(!IsScreenMode);
							GetSwapChain()->SetFullscreenState(!IsScreenMode, NULL);
							
							assert(GetFullScreenFlag() == !IsScreenMode);
							if (IsScreenMode)
							{
								ShowWindow(hWnd, SW_SHOW);
							}
#if !defined (DEBUG) && !defined (_DEBUG)
							ClipMouse(true);
#endif
						}
						else {
							SetFullScreenFlag(!IsScreenMode);
							GetSwapChain()->SetFullscreenState(!IsScreenMode, NULL);
							assert(GetFullScreenFlag() == !IsScreenMode);
							if (!IsScreenMode)
							{
								ShowWindow(hWnd, SW_SHOW);
							}
#if !defined (DEBUG) && !defined (_DEBUG)
							ClipMouse(true);
#endif
						}

					}
				}break;
			}
		}break;
		case WM_GETMINMAXINFO: {
			int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
			int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

			if(m_bMaximized){
				RECT rc = { 0,0, iScreenWidth ,iScreenHeight };
				AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
				((MINMAXINFO*)lParam)->ptMaxTrackSize.x = rc.right - rc.left; 
				((MINMAXINFO*)lParam)->ptMaxTrackSize.y = rc.bottom - rc.top; 
				((MINMAXINFO*)lParam)->ptMinTrackSize.x = rc.right - rc.left; 
				((MINMAXINFO*)lParam)->ptMinTrackSize.y = rc.bottom - rc.top;
			}
			else {
				RECT rc = { 0,0, m_iInitialWidth ,m_iInitialHeight };
				AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
				((MINMAXINFO*)lParam)->ptMaxTrackSize.x = rc.right - rc.left;
				((MINMAXINFO*)lParam)->ptMaxTrackSize.y = rc.bottom - rc.top;
				((MINMAXINFO*)lParam)->ptMinTrackSize.x = rc.right - rc.left;
				((MINMAXINFO*)lParam)->ptMinTrackSize.y = rc.bottom - rc.top;
			}
			return FALSE;
		}
		case WM_SYSCOMMAND:
		{
			if (SC_RESTORE == wParam || SC_MAXIMIZE == wParam) {
				m_bMaximized = !m_bMaximized;
			}
		}
		break;
		case WM_SIZE:
		{
			if (SIZE_MINIMIZED != wParam) // �ּ�ȭ
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				GetWindowRect(m_hWnd, &m_rcWindowBounds);
				GetClientRect(m_hWnd, &m_rcWindowClient);
				
				if (GetFullScreenFlag()== FALSE)
					if (FAILED(ResizeDevice(width, height))){}
			}
		}break;
		//case WM_EXITSIZEMOVE:		
		//	// Save the new client area dimensions.
		//	//mClientWidth  = LOWORD(lParam);
		//	//mClientHeight = HIWORD(lParam);
		//	//if( md3dDevice )
		//	//{
		//	//	if( wParam == SIZE_MINIMIZED )
		//	//	{
		//	//		mAppPaused = true;
		//	//		mMinimized = true;
		//	//		mMaximized = false;
		//	//	}
		//	//	else if( wParam == SIZE_MAXIMIZED )
		//	//	{
		//	//		mAppPaused = false;
		//	//		mMinimized = false;
		//	//		mMaximized = true;
		//	//		OnResize();
		//	//	}
		//	//	else if( wParam == SIZE_RESTORED )
		//	//	{
		//	//		
		//	//		// Restoring from minimized state?
		//	//		if( mMinimized )
		//	//		{
		//	//			mAppPaused = false;
		//	//			mMinimized = false;
		//	//			OnResize();
		//	//		}

		//	//		// Restoring from maximized state?
		//	//		else if( mMaximized )
		//	//		{
		//	//			mAppPaused = false;
		//	//			mMaximized = false;
		//	//			OnResize();
		//	//		}
		//	//		else if( mResizing )
		//	//		{
		//	//			// If user is dragging the resize bars, we do not resize 
		//	//			// the buffers here because as the user continuously 
		//	//			// drags the resize bars, a stream of WM_EXITSIZEMOVE messages are
		//	//			// sent to the window, and it would be pointless (and slow)
		//	//			// to resize for each WM_EXITSIZEMOVE message received from dragging
		//	//			// the resize bars.  So instead, we reset after the user is 
		//	//			// done resizing the window and releases the resize bars, which 
		//	//			// sends a WM_EXITSIZEMOVE message.
		//	//		}
		//	//		else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
		//	//		{
		//	//			OnResize();
		//	//		}
		//	//	}
		//	//}
		//	//return 0;


		//	//if( SIZE_MAXHIDE == wParam ) // �ٸ� �����찡 �ִ�ȭ�Ǿ� ���� �����찡 ��������
		//	//if( SIZE_MAXIMIZED == wParam ) // �ִ�ȭ
		//	//if( SIZE_MAXSHOW == wParam ) // �ִ�ȭ �Ǿ� �� �����츦 ������ �� �ٽ� ���� ũ���� �����Ǿ� �� �����찡 ���϶�
		//	//if( SIZE_RESTORED == wParam )// ũ�Ⱑ ����Ǿ���� �� 
		//	if( SIZE_MINIMIZED != wParam ) // �ּ�ȭ
  //          {			
		//		UINT width	= LOWORD(lParam);
		//		UINT height = HIWORD(lParam);	
		//		GetWindowRect( m_hWnd, &m_rcWindowBounds );
		//		GetClientRect( m_hWnd, &m_rcWindowClient );

		//		//m_iWindowWidth		= 	width;//GetViewPort().Width;
		//		//m_iWindowHeight		=	height;//GetViewPort().Height;

		//		if( FAILED( ResizeDevice(width, height) ))
		//		{					
		//		}
		//	}
		//	break;
		case WM_CLOSE:
        {
            HMENU hMenu;
            hMenu = GetMenu( hWnd );
            if( hMenu != NULL )      DestroyMenu( hMenu );
            DestroyWindow( hWnd );
            UnregisterClass( L"GCore3D11_Project", NULL );            
            return 0;
        }
		case WM_DESTROY:
            PostQuitMessage( 0 );
            break;        
    }
	
    return DefWindowProc( hWnd, message, wParam, lParam );
}
void GWindow::CenterWindow(HWND hwnd)
{
	// get the width and height of the screen
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight= GetSystemMetrics(SM_CYFULLSCREEN);

	// do the centering math
	int iDestX = (iScreenWidth-(m_rcWindowBounds.right-m_rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight-(m_rcWindowBounds.bottom-m_rcWindowBounds.top)) / 2;

	// center the window
	MoveWindow( hwnd, iDestX, iDestY, 
				m_rcWindowBounds.right-m_rcWindowBounds.left,
				m_rcWindowBounds.bottom-m_rcWindowBounds.top,
				true);
}
bool GWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, TCHAR* strWindowTitle,  int iWidth, int iHeight, bool bMaximized, BOOL IsFullScreen)
{
	m_bMaximized = bMaximized;
	m_iInitialHeight = iHeight;
	m_iInitialWidth = iWidth;

	g_hInstance = hInstance;
	  // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &StaticWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GCore3D11_Project";
    wcex.hIconSm = LoadIcon( wcex.hInstance,MAKEINTRESOURCE(IDI_APPLICATION) );
    if( !RegisterClassEx( &wcex ) )
        return false;

    // Create window
    m_hInstance = hInstance;
    RECT rc = { 0, 0, iWidth, iHeight };
	// �۾�����(  Ÿ��Ʋ ��/��輱/�޴�/��ũ�� �� ���� ������ ������ ����), ������ ��Ÿ��, �޴�����
	// AdjustWindowRect()�Լ��� ȣ���� �ֱ� ������ ������ �۾������� D3D ����̽��� ������� ������ ��ġ�ϰԵȴ�.
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    m_hWnd = CreateWindow( L"GCore3D11_Project",strWindowTitle, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !m_hWnd )
        return false;

	g_hWnd = m_hWnd;
	// Save window properties
	m_dwWindowStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	GetWindowRect( m_hWnd, &m_rcWindowBounds );
	GetClientRect( m_hWnd, &m_rcWindowClient );

	CenterWindow(m_hWnd);
	UpdateWindow(m_hWnd);	

	m_iWindowWidth		= 	m_rcWindowClient.right - m_rcWindowClient.left;
	m_iWindowHeight		=	m_rcWindowClient.bottom-m_rcWindowClient.top;

	ShowWindow( m_hWnd, nCmdShow );
	return true;
}

void GWindow::ClipMouse(bool bClip) {
	if (bClip) {
		//���콺Ŀ�� ���α�
		RECT Clip;
		GetClientRect(g_hWnd, &Clip);
		ClientToScreen(g_hWnd, (LPPOINT)&Clip);
		ClientToScreen(g_hWnd, (LPPOINT)(&Clip.right));
		ClipCursor(&Clip);
	}
	else {
		//���콺 ��������
		ClipCursor(NULL);
	}

}
GWindow::GWindow(void)
{
	m_bMaximized		= false;
	m_iInitialWidth		= 0;
	m_iInitialHeight	= 0;
	m_hInstance			= NULL;
	m_hWnd				= NULL;
	g_pWindow			= this;
}

GWindow::~GWindow(void)
{
}
