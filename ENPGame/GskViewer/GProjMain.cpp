#include "GProjMain.h"

bool GProjMain::LoadFileDlg( TCHAR* szExt, TCHAR* szTitle )
{
	OPENFILENAME    ofn;
	TCHAR           szFile[MAX_PATH]={0,};
	TCHAR			szFileTitle[MAX_PATH]={0,};
	static TCHAR    *szFilter;

	TCHAR lpCurBuffer[256] = {0,};
	GetCurrentDirectory( 256, lpCurBuffer );		

	ZeroMemory( &ofn, sizeof(OPENFILENAME) );
	_tcscpy_s(szFile, _T("*."));
	_tcscat_s(szFile, szExt );
	_tcscat_s(szFile, _T("\0"));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetActiveWindow();
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0L;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = _T("data/Character/");
	ofn.lpstrTitle = szTitle;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = szExt;

	if( !GetOpenFileName( &ofn ) ) 
	{
		return false;
	}
	TCHAR* load = _tcstok( szFile, _T("\n"));
	T_STR dir = szFile;
	load = &load[_tcslen(load)+1];
	if( *load == 0 )
	{
		m_LoadFiles.push_back(dir );
	}

	while(*load != 0)
	{
		T_STR dir = szFile;
		load = _tcstok( load, _T("\n"));
		dir += _T("\\");
		dir += load;
		m_LoadFiles.push_back(dir );
		load = &load[_tcslen(load)+1];		
	}
	SetCurrentDirectory( lpCurBuffer );
	return true;
}
bool GProjMain::Load()
{
	if( !LoadFileDlg(_T("gsk"), _T("GSK Viewer")) )
	{
		return false;
	}
	int iLoad = m_LoadFiles.size()-1;
	if(!m_GObject.Load(GetDevice(), m_LoadFiles[iLoad].c_str(), L"SkinViewer.hlsl" )  )	
	{
		return false;
	}	
	return true;
}
bool GProjMain::Init()
{
	m_GObject.Init();		
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GModelViewCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);
	return Load();
}
bool GProjMain::Render()
{	
	m_GObject.SetMatrix( NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_GObject.Render(m_pImmediateContext);

	//m_AxisLine.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_AxisLine.Render(m_pImmediateContext);
	return true;
}
bool GProjMain::Release()
{
	m_GObject.Release();
	return true;
}

bool GProjMain::Frame()
{	
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	m_pMainCamera->Update(g_fSecPerFrame);
	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	/////////m_GObject.SetControlWorldMatrix( *m_pMainCamera->GetWorldMatrix());
	m_GObject.Frame();	

	if( I_Input.KeyCheck( DIK_O ) == KEY_UP)
	{
		Load();
	}
	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
}

GProjMain::~GProjMain(void)
{
}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}
GBASIS_RUN(GSK Viewer);



