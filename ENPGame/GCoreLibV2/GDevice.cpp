#include "GDevice.h"
namespace GCORESTD
{
	//CRITICAL_SECTION		g_CSImmediateContext;
	//CRITICAL_SECTION		g_CSd3dDevice;
	ID3D11Device*			g_pd3dDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	UINT					g_iClientWidth;
	UINT					g_iClientHeight;
}

static HMODULE                              s_hModDXGI = NULL;
static HMODULE                              s_hModD3D11 = NULL;

typedef HRESULT(WINAPI* LPCREATEDXGIFACTORY)(REFIID, void**);
typedef HRESULT(WINAPI* LPD3D11CREATEDEVICE)(__in_opt IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	__out_opt ID3D11Device** ppDevice,
	__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
	__out_opt ID3D11DeviceContext** ppImmediateContext);

static LPCREATEDXGIFACTORY                  s_DynamicCreateDXGIFactory = NULL;
static LPD3D11CREATEDEVICE                  s_DynamicD3D11CreateDevice = NULL;

static bool EnsureD3D10APIs(void)
{
	if (s_hModD3D11 != NULL || s_hModDXGI != NULL)
		return true;

	// This may fail if Direct3D 10 isn't installed
	s_hModD3D11 = LoadLibrary(L"d3d11.dll");
	if (s_hModD3D11 != NULL)
	{
		s_DynamicD3D11CreateDevice = (LPD3D11CREATEDEVICE)GetProcAddress(s_hModD3D11, "D3D11CreateDevice");
	}

	s_hModDXGI = LoadLibrary(L"dxgi.dll");
	if (s_hModDXGI)
	{
		s_DynamicCreateDXGIFactory = (LPCREATEDXGIFACTORY)GetProcAddress(s_hModDXGI, "CreateDXGIFactory");
	}
	return (s_hModDXGI != NULL) && (s_hModD3D11 != NULL);
}



HRESULT GDevice::InitDevice( HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen )
{	
	HRESULT hr = S_OK;	
	if( FAILED( hr = CreateDevice() ))
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return hr;
	}	
	if( FAILED( hr = CreateSwapChain(hWnd,iWidth, iHeight, IsFullScreen) ) )
	{
		MessageBox( 0, _T("CreateSwapChain  실패"), _T("Fatal error"), MB_OK );
		return hr;
	}	
	if( FAILED( hr = SetRenderTargetView() ) )
	{
		MessageBox( 0, _T("SetRenderTargetView  실패"), _T("Fatal error"), MB_OK );
		return hr;
	}
	if( FAILED( hr = SetViewPort() ) )
	{
		MessageBox( 0, _T("SetViewPort  실패"), _T("Fatal error"), MB_OK );
		return hr;
	}	
	// 각종 뷰 리소스 적용
	if( FAILED( hr = CreateDxResource() ))
	{
		return hr;
	}
	// Alt + Enter 키를 막는다.
	if( FAILED( hr = GetGIFactory()->MakeWindowAssociation( hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER  )))
	{
		return hr;
	}
	return hr;
}

BOOL GDevice::GetFullScreenFlag()
{
	return m_IsFullScreenMode;
}
void GDevice::SetFullScreenFlag( BOOL bFlag )
{
	m_IsFullScreenMode = bFlag;
}
HRESULT GDevice::ResizeDevice( UINT iWidth, UINT iHeight)
{
	if( m_pd3dDevice == NULL ) return true;
	HRESULT hr;
	// 바인딩되어 있는 각종 뷰리소스를 해제한다.
	if( FAILED( hr= DeleteDxResource()))
	{
		return hr;
	}
	//--------------------------------------------------------------------------------------
	// 랜더타켓과 깊이스텐실 버퍼를 해제한다.
	//--------------------------------------------------------------------------------------
	//EnterCriticalSection(&g_CSImmediateContext);
	m_pImmediateContext->OMSetRenderTargets( 0, NULL, NULL );
	//LeaveCriticalSection(&g_CSImmediateContext);
	m_DefaultRT.m_pRenderTargetView.ReleaseAndGetAddressOf();	

	//--------------------------------------------------------------------------------------
	// 백버퍼의 크기를 조정한다.
	//--------------------------------------------------------------------------------------
	if (FAILED(hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags)))
	{
		return hr;
	}
	if (FAILED(hr = m_pSwapChain->GetDesc(&m_SwapChainDesc)))
	{
		return hr;
	}
	GCORESTD::g_iClientWidth = m_SwapChainDesc.BufferDesc.Width;
	GCORESTD::g_iClientHeight = m_SwapChainDesc.BufferDesc.Height;

	// 랜더타켓뷰 생성 및 적용한다.
    if( FAILED( hr = SetRenderTargetView() ) ) 
	{
		return hr;
	}
	// 뷰포트를 세팅하고 적용한다.
	if( FAILED( hr = SetViewPort() ) )
	{
		return hr;
	}

	if( FAILED( hr= CreateDxResource()))
	{
		return hr;
	}
	return S_OK;
}
ID3D11Device* GDevice::GetDevice()
{
	assert( m_pd3dDevice );
	return m_pd3dDevice; 
}
ID3D11DeviceContext* GDevice::GetContext()
{
	assert( m_pImmediateContext );
	return m_pImmediateContext; 
}
IDXGISwapChain* GDevice::GetSwapChain()
{ 
	assert( m_pSwapChain );
	return m_pSwapChain; 
}
ID3D11RenderTargetView* GDevice::GetRenderTargetView()	
{ 
	return m_DefaultRT.m_pRenderTargetView.Get();
}
IDXGIFactory* GDevice::GetGIFactory()
{
	assert(m_pGIFactory);
	return m_pGIFactory;
}


bool GDevice::Start() {
	if (!EnsureD3D10APIs()) {
		WCHAR strBuffer[512];
		wcscpy_s(strBuffer, ARRAYSIZE(strBuffer),
			L"This application requires a Direct3D 11 class\ndevice (hardware or reference rasterizer) running on Windows Vista Or Window7 (or later).");
		MessageBox(0, strBuffer, L"Could not initialize Direct3D 11", MB_OK);
		return false;
	}
	return false;
}
DXGI_MODE_DESC GDevice::FindClosestMatchingMode(DXGI_MODE_DESC& Desc, ID3D11Device* pd3dDevice) {
	HRESULT	hr;
	DXGI_MODE_DESC FindDesc;
	GEnumAdapter* pAdapterInfo;

	for (int i = 0; i < m_Enumeration.m_AdapterInfoList.size(); i++)
	{
		pAdapterInfo = m_Enumeration.m_AdapterInfoList[i];

		LARGE_INTEGER DriverVersion;//user mode driver version 
		if (pAdapterInfo->m_pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &DriverVersion) != DXGI_ERROR_UNSUPPORTED)
		{
			continue;
		}
		GEnumOutput* pOutputInfo;
		for (int i = 0; i < pAdapterInfo->m_OutputInfoList.size(); i++)
		{
			pOutputInfo = pAdapterInfo->m_OutputInfoList[i];
			if (SUCCEEDED(pOutputInfo->m_pOutput->FindClosestMatchingMode(&Desc, &FindDesc, pd3dDevice)))
			{
				return FindDesc;
			}
		}
	}
	return FindDesc;
}

//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT GDevice::CreateSwapChain( HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{	
	HRESULT hr = S_OK;
	if (m_pGIFactory == NULL) return E_FAIL;

	SetFullScreenFlag( IsFullScreen );

	DXGI_MODE_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Width = iWidth;
	BufferDesc.Height = iHeight;
	BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	BufferDesc.RefreshRate.Numerator = 60;
	BufferDesc.RefreshRate.Denominator = 1;

	//적절한 화면 모드를 검색한다.
	//DXGI_MODE_DESC FindBufferDesc;
	ZeroMemory(&m_FindBufferDesc, sizeof(m_FindBufferDesc));

	//EnterCriticalSection(&g_CSd3dDevice);
	m_FindBufferDesc = FindClosestMatchingMode(BufferDesc, m_pd3dDevice);
	//LeaveCriticalSection(&g_CSd3dDevice);

	if( m_pGIFactory == NULL ) return S_FALSE;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc = m_FindBufferDesc;
	sd.BufferDesc.Width = iWidth;
	sd.BufferDesc.Height = iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
     sd.Windowed = !m_IsFullScreenMode;
	// 추가
	sd.Flags	= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//EnterCriticalSection(&g_CSd3dDevice);
	if( FAILED( hr = m_pGIFactory->CreateSwapChain( m_pd3dDevice, &sd, &m_pSwapChain ) ))
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr;
	}	
	//LeaveCriticalSection(&g_CSd3dDevice);

	if (FAILED(hr = m_pSwapChain->GetDesc(&m_SwapChainDesc)))
	{
		return hr;
	}
	GCORESTD::g_iClientWidth = m_SwapChainDesc.BufferDesc.Width;
	GCORESTD::g_iClientHeight = m_SwapChainDesc.BufferDesc.Height;
	return hr;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT GDevice::CreateDeviceAndSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{	
	HRESULT hr = S_OK;

    UINT createDeviceFlags =  D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount				= 1;
    sd.BufferDesc.Width			= iWidth;
    sd.BufferDesc.Height		= iHeight;
    sd.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage				= DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow				= hWnd;
    sd.SampleDesc.Count			= 1;
    sd.SampleDesc.Quality		= 0;
    sd.Windowed = !m_IsFullScreenMode;
	// 추가
	sd.Flags	= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        m_driverType = driverTypes[driverTypeIndex];

		//EnterCriticalSection(&g_CSd3dDevice);
		//EnterCriticalSection(&g_CSImmediateContext);
        hr = D3D11CreateDeviceAndSwapChain( NULL, m_driverType, NULL, createDeviceFlags,featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_FeatureLevel, &m_pImmediateContext );
		//LeaveCriticalSection(&g_CSImmediateContext);
		//LeaveCriticalSection(&g_CSd3dDevice);

        if( SUCCEEDED( hr ) )
		{
            if( FAILED( hr ) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				//EnterCriticalSection(&g_CSImmediateContext);
				if( m_pImmediateContext ) m_pImmediateContext->Release();
				//LeaveCriticalSection(&g_CSImmediateContext);

				//EnterCriticalSection(&g_CSd3dDevice);
				if( m_pd3dDevice ) m_pd3dDevice->Release();
				//LeaveCriticalSection(&g_CSd3dDevice);
				continue;
			}
			break;
		}
    }
    if( FAILED( hr ) )
	{
        return hr;
	}
	if (FAILED(hr = m_pSwapChain->GetDesc(&m_SwapChainDesc)))
	{
		return hr;
	}
	

	GCORESTD::g_pd3dDevice = m_pd3dDevice;
	GCORESTD::g_pImmediateContext = m_pImmediateContext;
	GCORESTD::g_iClientWidth = m_SwapChainDesc.BufferDesc.Width;
	GCORESTD::g_iClientHeight = m_SwapChainDesc.BufferDesc.Height;
	return hr;
}

//--------------------------------------------------------------------------------------
// ID3D11Device 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT GDevice::CreateDevice()
{
	HRESULT hr;
	  UINT createDeviceFlags =  D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	// win10->설정->시스템/앱 및 기능/선택적 기능 관리/기능 추가/그래픽 도구(DirectX Graphics Tools지원 추가) 추가 선택하면 된다.
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        m_driverType = driverTypes[driverTypeIndex];

		//InitializeCriticalSection(&(GCORESTD::g_CSImmediateContext));
		//InitializeCriticalSection(&(GCORESTD::g_CSd3dDevice));

		//EnterCriticalSection(&g_CSd3dDevice);
		//EnterCriticalSection(&g_CSImmediateContext);
        if( SUCCEEDED( hr = D3D11CreateDevice(	NULL, m_driverType, NULL, createDeviceFlags,
												featureLevels, numFeatureLevels,
												D3D11_SDK_VERSION, &m_pd3dDevice, &m_FeatureLevel, &m_pImmediateContext ) ))
		{	
			//LeaveCriticalSection(&g_CSImmediateContext);
			//LeaveCriticalSection(&g_CSd3dDevice);
			if( FAILED( hr ) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if( m_pImmediateContext ) m_pImmediateContext->Release();
				//EnterCriticalSection(&g_CSd3dDevice);
				if( m_pd3dDevice ) m_pd3dDevice->Release();
				//LeaveCriticalSection(&g_CSd3dDevice);
				continue;
			}
			break;
		}
		//LeaveCriticalSection(&g_CSImmediateContext);
		//LeaveCriticalSection(&g_CSd3dDevice);
    }
    if( FAILED( hr ) )       return hr;

	GCORESTD::g_pd3dDevice = m_pd3dDevice;
	GCORESTD::g_pImmediateContext = m_pImmediateContext;

	//EnterCriticalSection(&g_CSd3dDevice);
	if (FAILED(hr = GDxState::SetState(m_pd3dDevice))) { 
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr; 
	}
	//LeaveCriticalSection(&g_CSd3dDevice);

	return CreateGIFactory();
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT GDevice::CreateGIFactory()
{	
	if(m_pd3dDevice==NULL) return E_FAIL;
	HRESULT hr;// = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory) );
	IDXGIDevice * pDXGIDevice;

	//EnterCriticalSection(&g_CSd3dDevice);
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	//LeaveCriticalSection(&g_CSd3dDevice);

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pGIFactory);
	
	// 추가 for HW info 출력
	if (FAILED(m_Enumeration.Enumerate(m_pGIFactory)))
	{
		return hr;
	}


	pDXGIDevice->Release();
	pDXGIAdapter->Release();

	return S_OK;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------

HRESULT GDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	 // Create a render target view
    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    if( FAILED( hr ) )
        return hr;

	//EnterCriticalSection(&g_CSd3dDevice);
    hr = m_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, m_DefaultRT.m_pRenderTargetView.GetAddressOf() );
	//LeaveCriticalSection(&g_CSd3dDevice);

    pBackBuffer->Release();
    if( FAILED( hr ) )
        return hr;    
	return S_OK;
}

HRESULT GDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	m_DefaultRT.m_vp.Width	= m_SwapChainDesc.BufferDesc.Width;
	m_DefaultRT.m_vp.Height	= m_SwapChainDesc.BufferDesc.Height;
	m_DefaultRT.m_vp.MinDepth = 0.0f;
	m_DefaultRT.m_vp.MaxDepth = 1.0f;
	m_DefaultRT.m_vp.TopLeftX = 0;
	m_DefaultRT.m_vp.TopLeftY = 0;
	return S_OK;
}

bool GDevice::CleanupDevice()
{
	// 추가함 m_Enumeration은 HW info 출력을 위해 추가하였음.
	m_Enumeration.ClearAdapterInfoList();

	//EnterCriticalSection(&g_CSImmediateContext);
	ClearD3D11DeviceContext(m_pImmediateContext);
	//LeaveCriticalSection(&g_CSImmediateContext);

	// 바인딩되어 있는 각종 뷰리소스를 해제한다.
	if( FAILED( DeleteDxResource()))
	{
		return false;
	}
       // Clear state and flush
	// ComPtr에 Attach 이후에는 Release하면 안된다.
	//EnterCriticalSection(&g_CSImmediateContext);
    if( m_pImmediateContext )    m_pImmediateContext->ClearState();
    if( m_pImmediateContext )    m_pImmediateContext->Flush();  
    if( m_pSwapChain ) m_pSwapChain->Release();
	if( m_pImmediateContext ) m_pImmediateContext->Release();
	//LeaveCriticalSection(&g_CSImmediateContext);

	//EnterCriticalSection(&g_CSd3dDevice);
    if( m_pd3dDevice ) m_pd3dDevice->Release();
	//LeaveCriticalSection(&g_CSd3dDevice);

	if( m_pGIFactory ) m_pGIFactory->Release();
	m_pd3dDevice		= NULL;
	m_pSwapChain		= NULL;
	m_pImmediateContext = NULL;
	m_pGIFactory		= NULL;
	return true;
}
HRESULT GDevice::CreateDxResource()
{
	return S_OK;
}
HRESULT GDevice::DeleteDxResource()
{
	return S_OK;
}
GDevice::GDevice(void)
{
	m_driverType		= D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel		= D3D_FEATURE_LEVEL_11_0;
	m_pd3dDevice		= NULL;
	m_pSwapChain		= NULL;
	m_pImmediateContext = NULL;
}

GDevice::~GDevice(void)
{
}
