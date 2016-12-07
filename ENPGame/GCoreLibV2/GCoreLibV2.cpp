#include "GCoreLibV2.h"

#define G_MACRO_DEBUG_STR_INTERVAL 30

T_STR RasterizerState[] =
{
	_T("RS_BackCullSolid"),
	_T("RS_NoneCullSolid"),
	_T("RS_FrontCullSolid"),
};

T_STR SamplerState[] =
{
	_T("SS_WrapLinear"),
	_T("SS_WrapPoint"),
	_T("SS_MirrorLinear"),
	_T("SS_MirrorPoint"),
	_T("SS_ClampLinear"),
	_T("SS_ClampPoint"),
};

int GCoreLibV2::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	return -1;
}
bool GCoreLibV2::PreInit()
{
	if( FAILED( InitDevice(m_hWnd,this->m_iWindowWidth, this->m_iWindowHeight) ) )
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return false;
	}



#if defined( DEBUG ) || defined( _DEBUG )
	// ─────────────────────────────────
	// for HW 정보 출력.
	// ─────────────────────────────────
	FILE	*fp;
	fp = _tfopen(_T("HWInfo.txt"), _T("wt"));
	if (!fp)
	{
		MessageBox(NULL, _T("HWInfo.txt 파일을 생성 실패."), _T("파일생성에러"), MB_ICONERROR);
		return FALSE;
	}
	GEnumAdapter* pAdapterInfo;
	_ftprintf(fp, L"Num Adapter : %d\n", m_Enumeration.m_AdapterInfoList.size());

	for (int i = 0; i < m_Enumeration.m_AdapterInfoList.size(); i++)
	{
		pAdapterInfo = m_Enumeration.m_AdapterInfoList[i];
		_ftprintf(fp, L"Description[%d] : %s,  Num Output:%d\n", i, pAdapterInfo->m_AdapterDesc.Description,
			pAdapterInfo->m_OutputInfoList.size());

		GEnumOutput* pOutputInfo;
		for (int i = 0; i < pAdapterInfo->m_OutputInfoList.size(); i++)
		{
			pOutputInfo = pAdapterInfo->m_OutputInfoList[i];
			_ftprintf(fp, L"\n\tOutput[%d] m_Desc:%s\t DesktopCoordinates:%d,%d,%d,%d : NumDisplayMode:%d\t\n", i, pOutputInfo->m_Desc.DeviceName,
				pOutputInfo->m_Desc.DesktopCoordinates.left,
				pOutputInfo->m_Desc.DesktopCoordinates.top,
				pOutputInfo->m_Desc.DesktopCoordinates.right,
				pOutputInfo->m_Desc.DesktopCoordinates.bottom,
				pOutputInfo->m_DisplayModeList.size());

			// 연장시는 left:1680, right == 3360;

			DXGI_MODE_DESC* pModeDesc;
			for (int i = 0; i < pOutputInfo->m_DisplayModeList.size(); i++)
			{
				pModeDesc = &pOutputInfo->m_DisplayModeList[i];
				_ftprintf(fp, L"\t\tDisplayMode[%d] Width:%d height:%d FORMAT:%d RefreshRate:%d-%d\t\n", i,
					pModeDesc->Width, pModeDesc->Height,
					pModeDesc->Format,
					pModeDesc->RefreshRate.Numerator, pModeDesc->RefreshRate.Denominator);
			}
		}
	}

	fclose(fp);
	//MessageBox(NULL, _T("DeviceInfo.txt 파일을 성공적으로 생성하였습니다."), _T("파일생성"), MB_OK);
#endif

	if( !m_Timer.Init() )	return false;	

	// DirectX Input 초기화
	if( !I_Input.Init() )
	{
		return false;
	}

	if (FAILED(m_AxisLine.Create(GetDevice(), m_LineShaderFile.c_str())))
	{
		MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	return true;
}
bool GCoreLibV2::Init()
{
	return true;
}
bool GCoreLibV2::PostInit()
{
	return true;
}
bool GCoreLibV2::GInit()
{
	if( !PreInit() ) return false;
	if( !Init() ) return false;
	if( !PostInit() ) return false;
	return true;
}

bool GCoreLibV2::PreFrame()
{
	if( !m_Timer.Frame() ) return false;
	if( !I_Input.Frame() ) return false;	
	//EnterCriticalSection(&g_CSImmediateContext);
	if (!Update(m_pImmediateContext)) return false;
	//LeaveCriticalSection(&g_CSImmediateContext);
	return true;
}
bool GCoreLibV2::Update(ID3D11DeviceContext*    pContext)
{
#if defined(_DEBUG) || defined(DEBUG)
	if (I_Input.KeyCheck(DIK_1) == KEY_UP)
	{
		m_bWireFrameRender = !m_bWireFrameRender;
	}
	if (I_Input.KeyCheck(DIK_2) == KEY_UP)
	{
		++m_iPrimitiveType;
		if (m_iPrimitiveType > 5)
		{
			m_iPrimitiveType = 1;
		}
		m_iPrimitiveType = min(m_iPrimitiveType, 5);
	}
	if (I_Input.KeyCheck(DIK_3) == KEY_UP)
	{
		++m_iCullMode;
		if (m_iCullMode > 3)
		{
			m_iCullMode = 1;
		}
		m_iCullMode = min(m_iCullMode, 3);
		m_bWireFrameRender = false;
	}

	if (I_Input.KeyCheck(DIK_4) == KEY_UP)
	{
		++m_iSamplerMode;
		if (m_iSamplerMode >= 6)
		{
			m_iSamplerMode = 0;
		}
	}
#endif
	if (I_Input.KeyCheck(DIK_V) == KEY_PUSH)
	{
		m_bDebugFpsPrint = !m_bDebugFpsPrint;
	}

	if (I_Input.KeyCheck(DIK_I) == KEY_PUSH)
	{
		m_bDebugInfoPrint = !m_bDebugInfoPrint;
	}


	if (m_bWireFrameRender)
	{
		ApplyRS(pContext, GDxState::g_pRSWireFrame);
	}
	else
	{
		ApplyRS(pContext, GDxState::g_pRS[m_iCullMode - 1]);
	}
	ApplySS(pContext, GDxState::g_pSS[m_iSamplerMode]);
	pContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_iPrimitiveType);
	return true;
}
bool GCoreLibV2::PostFrame()
{
	return true;
}
bool GCoreLibV2::Frame()
{
	return true;
}
bool GCoreLibV2::Release()
{
	return true;
}
bool GCoreLibV2::GRelease()
{
	CleanupDevice();
	if( !m_Timer.Release() ) return false;		
	//if( !m_Font.Release() ) return false;	
	if( !m_Font.Release() ) return false;	
	if( !I_Input.Release() ) return false;	
	return Release();
}
bool GCoreLibV2::GFrame()
{
	if(!m_bRenderManually){
		PreFrame();
		Frame();
		PostFrame();
	}
	return true;
}
bool GCoreLibV2::GRender()
{
	if (!m_bRenderManually) {
		I_Input.Render();
		m_Timer.Render();

		PreRender();
		Render();

		if (m_bDebugFpsPrint)	DrawDebug();
		if (m_bDebugInfoPrint)	DrawInfo();
		PostRender();
	}
	return true;
}

bool GCoreLibV2::Render()
{
	return true;
}
bool GCoreLibV2::PreRender()
{
	// Just clear the backbuffer
    float ClearColor[4] = { m_fScreenColor[0], m_fScreenColor[1], m_fScreenColor[2], m_fScreenColor[3] }; //red,green,blue,alpha
	//EnterCriticalSection(&g_CSImmediateContext);
	m_pImmediateContext->ClearRenderTargetView( GetRenderTargetView(), ClearColor );	
	m_pImmediateContext->ClearDepthStencilView(m_DefaultRT.m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->OMSetRenderTargets(1, GetRenderTargetViewAddress(), m_DefaultRT.m_pDepthStencilView.Get() );
	m_pImmediateContext->RSSetViewports(1, &m_DefaultRT.m_vp);
	ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthEnable);
	//LeaveCriticalSection(&g_CSImmediateContext);
	return true;
}
bool GCoreLibV2::DrawInfo() {

	memset(m_pHWInfoBuffer, 0, sizeof(TCHAR) * 256);
	memset(m_pScreenInfoBuffer, 0, sizeof(TCHAR) * 256);
	//-----------------------------------------------------------------------
	// 적용되어 RasterizerState 타입 표시
	//-----------------------------------------------------------------------	
	RECT rc;
	rc.top = m_DefaultRT.m_vp.Height - 60;
	rc.bottom = m_DefaultRT.m_vp.Height;
	rc.left = 0;
	rc.right = m_DefaultRT.m_vp.Width;
	T_STR str = RasterizerState[m_iCullMode];
	//_tcsncat(pRSBuffer, str.c_str(), _tcslen(str.c_str()));
	DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//DrawDebugRect(&rc, pRSBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//-----------------------------------------------------------------------
	// 적용되어 SamplerState 타입 표시
	//-----------------------------------------------------------------------	
	rc.top = m_DefaultRT.m_vp.Height - G_MACRO_DEBUG_STR_INTERVAL;
	rc.bottom = m_DefaultRT.m_vp.Height;
	rc.left = 0;
	rc.right = m_DefaultRT.m_vp.Width;
	str = SamplerState[m_iSamplerMode];
	//_tcsncat(pSSBuffer, str.c_str(), _tcslen(str.c_str()));
	DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//DrawDebugRect(&rc, pSSBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));


	GEnumAdapter* pAdapterInfo;

	int iPos = G_MACRO_DEBUG_STR_INTERVAL;
	for (int i = 0; i < m_Enumeration.m_AdapterInfoList.size(); i++)
	{
		pAdapterInfo = m_Enumeration.m_AdapterInfoList[i];

		_stprintf_s(m_pHWInfoBuffer, L"Desc[%d] : %s,  DispCnt:%d\n", i, pAdapterInfo->m_AdapterDesc.Description, pAdapterInfo->m_OutputInfoList.size());
		iPos += (i * G_MACRO_DEBUG_STR_INTERVAL); rc.top = iPos;
		DrawDebugRect(&rc, m_pHWInfoBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

		_stprintf_s(m_pHWInfoBuffer, L"DXGI_FORMAT:%d, Refresh:%u/%u Hz\n", m_FindBufferDesc.Format, m_FindBufferDesc.RefreshRate.Numerator, m_FindBufferDesc.RefreshRate.Denominator);
		iPos += G_MACRO_DEBUG_STR_INTERVAL; rc.top = iPos;
		DrawDebugRect(&rc, m_pHWInfoBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	iPos += G_MACRO_DEBUG_STR_INTERVAL; rc.top = iPos;//rc.bottom = m_DefaultRT.m_vp.Height;rc.left = 0;rc.right = m_DefaultRT.m_vp.Width;

	switch (m_driverType)
	{
	case D3D_DRIVER_TYPE_UNKNOWN:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_UNKNOWN", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case D3D_DRIVER_TYPE_HARDWARE:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_HARDWARE", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case D3D_DRIVER_TYPE_REFERENCE:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_REFERENCE", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case D3D_DRIVER_TYPE_NULL:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_NULL", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case D3D_DRIVER_TYPE_SOFTWARE:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_SOFTWARE", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case D3D_DRIVER_TYPE_WARP:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_WARP", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		DrawDebugRect(&rc, L"D3D_DRIVER_TYPE_?????", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	}

	iPos += G_MACRO_DEBUG_STR_INTERVAL; rc.top = iPos;
	_stprintf_s(m_pScreenInfoBuffer, _T("(%d x %d)"), (int)m_DefaultRT.m_vp.Width, (int)m_DefaultRT.m_vp.Height);
	DrawDebugRect(&rc, m_pScreenInfoBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	return true;
}
bool GCoreLibV2::DrawDebug()
{
	//TCHAR pRSBuffer[256];
	//TCHAR pSSBuffer[256];

	memset(m_pFPSBuffer, 0, sizeof( TCHAR ) * 256 );

	//memset(pRSBuffer, 0, sizeof(TCHAR) * 256);
	//memset(pSSBuffer, 0, sizeof(TCHAR) * 256);

	//_stprintf_s(pRSBuffer, _T("RS:"));
	//_stprintf_s(pSSBuffer, _T("SS:"));

	_stprintf_s( m_pFPSBuffer, _T("FPS:%d"), m_Timer.GetFPS() );	
	
	m_Font.Begin();

	//m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	//RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};
	RECT rc1 = { 0,0, m_DefaultRT.m_vp.Width, m_DefaultRT.m_vp.Height };
	m_Font.SetText(D2D1::Point2F(rc1.right, rc1.bottom), m_pFPSBuffer, D2D1::ColorF(1, 1, 0, 1));
	m_Font.SetFont(L"Impact");
	m_Font.SetBold(true);
	//m_Font.SetFontSize(100);
	m_Font.SetItalic(true);
	m_Font.SetUnderline(true);
	m_Font.DrawText(D2D1::Point2F(rc1.left, rc1.top), D2D1::ColorF(1.0f, 0.0f, 0.0f,1.0f));
	m_Font.End();

	




	return true;
}

bool GCoreLibV2::DrawDebugRect(RECT* rcDest, TCHAR* pString, DWRITE_TEXT_ALIGNMENT align, D3DXCOLOR color)
{
	if (rcDest == NULL) return false;

	if (m_Font.m_pTextFormat)
	{
		D2D1_SIZE_F rtSize = m_Font.m_pRT->GetSize();
		//Draw a grid background.
		int width = static_cast <int> (rtSize.width);
		int height = static_cast <int> (rtSize.height);

		m_Font.Begin();
		m_Font.m_pTextFormat->SetTextAlignment(align);
		m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		//RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};

		m_Font.SetText(D2D1::Point2F(rcDest->right, rcDest->bottom), pString, D2D1::ColorF(1, 1, 0, 1));
		//m_Font.SetFont(L"Consolas");
		m_Font.SetBold(false);
		//m_Font.SetFontSize(100);
		m_Font.SetItalic(false);
		m_Font.SetUnderline(false);

		m_Font.DrawText(D2D1::Point2F(rcDest->left, rcDest->top), D2D1::ColorF(color.r, color.g, color.b, 1.0f));
		m_Font.End();
	}

	return true;
}

bool GCoreLibV2::DrawDebugRect(RECT* rcDest, TCHAR* pString, D3DXCOLOR color )
{
	if( rcDest == NULL ) return false;	

	if( m_Font.m_pTextFormat)
	{
		D2D1_SIZE_F rtSize = m_Font.m_pRT->GetSize ();
        //Draw a grid background.
        int width = static_cast <int> (rtSize.width);
        int height = static_cast <int> (rtSize.height);

		m_Font.Begin();
		m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		//RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};

		m_Font.SetText(D2D1::Point2F(rcDest->right, rcDest->bottom), pString, D2D1::ColorF(1, 1, 0, 1));
		//m_Font.SetFont(L"Consolas");
		m_Font.SetBold(false);
		//m_Font.SetFontSize(100);
		m_Font.SetItalic(false);
		m_Font.SetUnderline(false);

		m_Font.DrawText(D2D1::Point2F(rcDest->left, rcDest->top),  D2D1::ColorF(color.r,color.g,color.b,1.0f));
		m_Font.End();
	}

	return true;
}
bool GCoreLibV2::PostRender()
{	
	HRESULT hr;
	if (FAILED(hr = GetSwapChain()->Present(0, 0)))
	{
		H(hr);
	}
	return true;
}
bool GCoreLibV2::ToolRun()
{
	if( !GInit() ) return false;
	
	//GFrame();
    //GRender();        
	
	return true;
}
bool GCoreLibV2::Run()
{
	I_Input.m_hWnd = m_hWnd;

	GDevice::Start();

	if( !GInit() ) return false;

	

	// Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			GFrame();
            GRender();
        }
    }
	if( !GRelease() ) return false;
	return true;
}
HRESULT GCoreLibV2::CreateDxResource()
{
	IDXGISurface1*		pBackBuffer=NULL;
	HRESULT hr = GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);	
	m_Font.Set(m_hWnd, m_iWindowWidth,	m_iWindowHeight, pBackBuffer );		
	if( pBackBuffer )	pBackBuffer->Release();

	if (FAILED(hr = GetSwapChain()->GetDesc(&m_SwapChainDesc)))
	{
		return hr;
	}	

	//EnterCriticalSection(&g_CSd3dDevice);
	if (FAILED(hr = m_DefaultRT.UpdateDepthStencilView(m_pd3dDevice, m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height)))
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr;
	}
	//LeaveCriticalSection(&g_CSd3dDevice);

	return CreateResource();
}
HRESULT GCoreLibV2::DeleteDxResource()
{
	if( !m_Font.Release() ) return false;		
	return DeleteResource();
}
HRESULT GCoreLibV2::CreateResource()
{
	return S_OK;
}
HRESULT GCoreLibV2::DeleteResource()
{
	return S_OK;
}
GCoreLibV2::GCoreLibV2(void)
{
	m_bRenderManually = false;
	m_fScreenColor[0] = 0.5f; // R
	m_fScreenColor[1] = 1.0f; // G
	m_fScreenColor[2] = 0.5f; // B
	m_fScreenColor[3] = 1.0f; // A

	m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_iCullMode = 1;
	m_iSamplerMode = 0;
	m_bWireFrameRender = false;
	m_bDebugFpsPrint = true;
	m_bDebugInfoPrint = true;
	m_LineShaderFile = L"data/shader/line.hlsl";
}

GCoreLibV2::~GCoreLibV2(void)
{
}
