
// GciCharTool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GciCharTool.h"
#include "MainFrm.h"

#include "GciCharToolDoc.h"
#include "GciCharToolView.h"

//���� ����� ������ �߰���
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAIToolApp

BEGIN_MESSAGE_MAP(CGciCharToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGciCharToolApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_CHARLOAD, &CGciCharToolApp::OnCharload)
	ON_COMMAND(ID_CHARSAVE, &CGciCharToolApp::OnCharsave)
END_MESSAGE_MAP()



////////////////////////////////////////////////////////
// ���ڿ� ó�� ���� �Լ� �߰���.

//Ȯ���ڸ� ��� ����.
string getExt(string pathname) {
	return pathname.substr(pathname.find_last_of(".") + 1);
}
typedef std::basic_string<TCHAR> tstring;

// string to TChar
TCHAR* StringToTCHAR(string& s)
{
	tstring tstr;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}

// TChar to string
std::string TCHARToString(const TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);
	char* psz = new char[2 * len + 1];
	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;
	delete[] psz;
	return s;
}
////////////////////////////////////////////////////////

// CAIToolApp ����

HRESULT CGciCharToolApp::CreateResource()
{
#ifdef G_MACRO_MODELVIEW
	HRESULT hr;
	if (FAILED(hr = ScreenViewPort(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height)))
	{
		return hr;
	}
#endif
	return S_OK;
}

HRESULT CGciCharToolApp::DeleteResource()
{
	HRESULT hr = S_OK;
	// �Ʒ��� ���� GetDevice()->ClearState();�� ȣ������ ���� �� �߻��Ѵ�.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

CGciCharToolApp::CGciCharToolApp()
{
	m_FileExt = G_TOOL_EXT_GCI;

	m_bHiColorIcons = TRUE;

	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GciCharTool.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CAIToolApp ��ü�Դϴ�.

CGciCharToolApp theApp;


// CAIToolApp �ʱ�ȭ

BOOL CGciCharToolApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("GCICHARTOOL"));
	
	CleanState();

	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGciCharToolDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CGciCharToolView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//  �ھ� ������ �ʿ��� ó��
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CGciCharToolView* pView = (CGciCharToolView*)pFrame->GetActiveView();
	GWindow::m_hInstance = AfxGetInstanceHandle();
	GWindow::m_hWnd = pView->m_hWnd;
	g_hInstance = GWindow::m_hInstance;
	g_hWnd = GWindow::m_hWnd;
	I_Input.m_hWnd = pFrame->m_hWnd;
	CRect   rcClient;
	pView->GetClientRect(rcClient);
	GWindow::m_iWindowWidth = rcClient.Width();
	GWindow::m_iWindowHeight = rcClient.Height();
	m_LineShaderFile = L"data/shader/line.hlsl";
	GCoreLibV2::GInit();
	
	GCoreLibV2::m_bDebugInfoPrint = false;
	GCoreLibV2::m_bDebugFpsPrint = false;

	GCoreLibV2::m_fScreenColor[0] = 0.0f;
	GCoreLibV2::m_fScreenColor[1] = 0.125f;
	GCoreLibV2::m_fScreenColor[2] = 0.3f;
	GCoreLibV2::m_fScreenColor[3] = 1.0f;

	//Load();


	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
#ifdef G_MACRO_MODELVIEW

	//m_pMainCamera = make_shared<GModelViewCamera>();
	//m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	if (FAILED(m_pDirectionLine.Create(GetDevice(), L"data/shader/Line.hlsl")))
	{
		MessageBox(0, _T("m_pDirectionLIne ����"), _T("Fatal error"), MB_OK);
		return 0;
	}

	//if (FAILED(m_pPlane.Create(GetDevice(), L"data/shader/Plane.hlsl", L"../../data/Sand.jpg")))
	//{
	//	MessageBox(0, _T("m_pPlane ����"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}
	//if (FAILED(m_pBox.Create(GetDevice(), L"data/shader/Box.hlsl", L"../../data/checker_with_numbers.bmp")))
	//{
	//	MessageBox(0, _T("m_pBox ����"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}

	// �ʱ�ȭ
	m_iCameraType = 3; // User Camera	
	m_fCameraYaw = 0.0f;
	m_fCameraPitch = 0.0f;
	m_fCameraRoll = 0.0f;
	m_fRadius = 0.0f;
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_vObjectPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	InitCamera();

#else
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 10.0f, 100.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);
#endif






	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGciCharToolApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	I_CharMgr.Release();

	if (m_FileExt == G_TOOL_EXT_GCI) {

		//return true;

		for (int i = 0; i < m_vecStr.size(); i++) {

			m_vecStr[i].ReleaseBuffer();
		}
	}
	if (m_FileExt == G_TOOL_EXT_GBS) {
		m_tbsobj.Release();
	}


	

	AfxOleTerm(FALSE);
	GRelease();
	return CWinAppEx::ExitInstance();
}

// CAIToolApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CGciCharToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAIToolApp ����� ���� �ε�/���� �޼���

void CGciCharToolApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGciCharToolApp::LoadCustomState()
{
}

void CGciCharToolApp::SaveCustomState()
{
}

// CAIToolApp �޽��� ó����





BOOL CGciCharToolApp::OnIdle(LONG lCount)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	__super::OnIdle(lCount);
	GFrame();
	GRender();
	return TRUE;
}


bool CGciCharToolApp::Frame() {
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

#ifdef G_MACRO_MODELVIEW
	//m_pMainCamera->Update(g_fSecPerFrame);

	// 90�� ȸ��
#ifdef	G_MACRO_MODELROT
	D3DXMatrixRotationY(&m_World[0], t*0.1f);
#else
	D3DXMatrixIdentity(&m_World[0]);
#endif


	//--------------------------------------------------------------------------------------
	// ī�޶� Ÿ�� ����
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_UP)
	{
		m_iCameraType++;
		if (m_iCameraType > 3) m_iCameraType = 0;
		m_fCameraYaw = m_pCamera[m_iCameraType]->m_fCameraYawAngle;
		m_fCameraPitch = m_pCamera[m_iCameraType]->m_fCameraPitchAngle;
		// ī�޶� Ÿ���� ��ü�Ǹ� ��ü�Ǵ� ī�޶� Ÿ����ġ�� ����ī�޶��� Ÿ���� �����Ѵ�.
		m_vObjectPosition = m_pCamera[m_iCameraType]->m_vTargetPos;
	}

	if (I_Input.KeyCheck(DIK_A))
	{
		m_vObjectPosition.x += (m_Timer.GetSPF() * 20.0f);
	}
	if (I_Input.KeyCheck(DIK_D))
	{
		m_vObjectPosition.x += (-m_Timer.GetSPF() * 20.0f);
	}
	if (I_Input.KeyCheck(DIK_Z))
	{
		m_vObjectPosition.y += (m_Timer.GetSPF() * 20.0f);
	}
	if (I_Input.KeyCheck(DIK_X))
	{
		m_vObjectPosition.y += (-m_Timer.GetSPF() * 20.0f);
	}
	m_pMainCamera->SetTargetPos(m_vObjectPosition);
	//--------------------------------------------------------------------------------------
	// ������( ī�޶��� ��ǥ ��ġ�� ���� ������ �Ÿ� ) 
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_W))
	{
		m_fRadius += (m_Timer.GetSPF() * 20.0f);
	}
	if (I_Input.KeyCheck(DIK_S))
	{
		m_fRadius += (-m_Timer.GetSPF() * 20.0f);
	}

	//m_fRadius += m_Timer.GetSPF() * I_Input.m_DIMouseState.lZ;

	//--------------------------------------------------------------------------------------
	// ī�޶� Y, X �� ȸ�� �ޱ�
	//--------------------------------------------------------------------------------------
	if (I_Input.m_MouseState[0])
	{
		m_fCameraYaw += m_Timer.GetSPF() * I_Input.m_DIMouseState.lX;
		m_fCameraPitch += m_Timer.GetSPF() * I_Input.m_DIMouseState.lY;
	}
	//--------------------------------------------------------------------------------------
	// ī�޶� ��� ���
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Update(D3DXVECTOR4(m_fCameraPitch, m_fCameraYaw, m_fCameraRoll, m_fRadius /*6.0f*/));

#else
	m_pMainCamera->Frame();

	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;
#endif



	if (m_FileExt == G_TOOL_EXT_GBS) {
		m_tbsobj.Frame();
		m_tbsobj.m_OBB.Frame(&m_tbsobj.m_matWorld);
	}
	if (m_FileExt == G_TOOL_EXT_GCI) {




		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			if (I_Input.KeyCheck(DIK_ADD))
			{
				m_HeroObj[iChar]->m_fSpeed += g_fSecPerFrame;
			}
			if (I_Input.KeyCheck(DIK_SUBTRACT))
			{
				m_HeroObj[iChar]->m_fSpeed -= g_fSecPerFrame;
				if (m_HeroObj[iChar]->m_fSpeed < 0.0f) m_HeroObj[iChar]->m_fSpeed = 0.01f;
			}
			m_HeroObj[iChar]->Frame();
		}
		if (I_Input.KeyCheck(DIK_F3) == KEY_UP && m_HeroObj.size() > 1)
		{
			m_HeroObj[1]->SetActionFrame(120, 205);//jump		
		}
		if (I_Input.KeyCheck(DIK_F4) == KEY_UP&& m_HeroObj.size() > 1)
		{
			m_HeroObj[1]->SetActionFrame(205, 289);//attack		
		}

		if (I_Input.KeyCheck(DIK_F5) == KEY_UP)
		{
			for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
			{
				m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
			}
		}

		if (I_Input.KeyCheck(DIK_O) == KEY_UP)
		{
			I_CharMgr.Release();

			Load();

		}
	}
	return true;
}
bool CGciCharToolApp::Render() {
	//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	//g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);
	if (m_FileExt == G_TOOL_EXT_GBS) {
		m_tbsobj.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_tbsobj.Render(m_pImmediateContext);
		m_tbsobj.m_OBB.Render(&m_tbsobj.m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	}
	if (m_FileExt == G_TOOL_EXT_GCI)
	{
#ifdef G_MACRO_MODELVIEW
		HRESULT hr;

		m_World[0]._41 = m_World[1]._41 = m_vObjectPosition.x;
		m_World[0]._42 = m_World[1]._42 = m_vObjectPosition.y;

		D3DXMATRIX matTrans;
		D3DXMatrixIdentity(&matTrans);
		matTrans._41 = m_vObjectPosition.x;
		matTrans._42 = m_vObjectPosition.y;

		m_World[0] *= matTrans;
		m_World[1] *= matTrans;


		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			//m_matWorld._41 = -50.0f + iChar * 25.0f;
			m_HeroObj[iChar]->SetMatrix(&m_World[0], &m_pMainCamera.get()->m_matView, &m_pMainCamera.get()->m_matProj);
			m_HeroObj[iChar]->Render(m_pImmediateContext);


			m_HeroObj[iChar].get()->m_OBB.Render(&m_HeroObj[iChar]->m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		}

		if (GCoreLibV2::m_bDebugFpsPrint) {
			m_pDirectionLine.SetMatrix(&m_World[0], &m_pMainCamera.get()->m_matView, &m_pMainCamera.get()->m_matProj);
			m_pDirectionLine.Render(m_pImmediateContext);
		}

		//m_pBox.SetMatrix(&m_World[0], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_pBox.Render(m_pImmediateContext);

		//m_pPlane.SetMatrix(&m_World[1], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//m_pPlane.Render(m_pImmediateContext);

		//-----------------------------------------------------------------------
		// ���� ���õ� ����Ʈ ���� ����
		//-----------------------------------------------------------------------
		D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
		UINT nViewPorts = 1;
		m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);
		//-----------------------------------------------------------------------
		// ����Ʈ
		//-----------------------------------------------------------------------	
		m_World[0]._41 = m_World[1]._41 = 0.0f;
		for (int iVp = 0; iVp < 4; iVp++)
		{
			m_ViewPort[iVp].Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());

			for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
			{
				//m_matWorld._41 = -50.0f + iChar * 25.0f;
				m_HeroObj[iChar]->SetMatrix(&m_World[0], &m_pCamera[iVp].get()->m_matView, &m_pCamera[iVp].get()->m_matProj);
				m_HeroObj[iChar]->Render(m_pImmediateContext);
			}
			//m_pBox.SetMatrix(&m_World[0], &m_pCamera[iVp]->m_matView, &m_pCamera[iVp]->m_matProj);
			//m_pBox.Render(m_pImmediateContext);

			//m_pPlane.SetMatrix(&m_World[1], &m_pCamera[iVp]->m_matView, &m_pCamera[iVp]->m_matProj);
			//m_pPlane.Render(m_pImmediateContext);
		}

		//-----------------------------------------------------------------------
		// �⺻ ����Ʈ ������ ����
		//-----------------------------------------------------------------------
		m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);
		//-----------------------------------------------------------------------
		// ����Ʈ ��ȣ ���
		//-----------------------------------------------------------------------
		RECT rc;
		for (int iVp = 0; iVp < 4; iVp++)
		{
			rc.left = m_ViewPort[iVp].m_vp.TopLeftX + m_ViewPort[iVp].m_vp.Width*0.5f;
			rc.top = m_ViewPort[iVp].m_vp.TopLeftY;
			rc.right = m_ViewPort[iVp].m_vp.Width + rc.left;
			rc.bottom = m_ViewPort[iVp].m_vp.Height + rc.top;
			T_STR str = ViewStyle[iVp];
			TCHAR strNumber[32];
			str += _itow(iVp, strNumber, 10);// _wtoi
			DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()),D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		//-----------------------------------------------------------------------
		// ����Ǿ� �ִ� ī�޶� Ÿ�� ǥ��
		//-----------------------------------------------------------------------	
		rc.left = m_DefaultRT.m_vp.TopLeftX + m_DefaultRT.m_vp.Width*0.5f;
		rc.top = m_DefaultRT.m_vp.TopLeftY;
		rc.right = m_DefaultRT.m_vp.Width;
		rc.bottom = m_DefaultRT.m_vp.Height;
		T_STR str = ViewStyle[m_iCameraType];
		TCHAR strNumber[32];
		str += _itow(m_iCameraType, strNumber, 10);// _wtoi
		DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		//-----------------------------------------------------------------------
		// ����Ǿ� �ִ� ī�޶��� ���⺤�� ǥ��
		//-----------------------------------------------------------------------
		str.clear();
		TCHAR pBuffer[256];
		memset(pBuffer, 0, sizeof(TCHAR) * 256);
		_stprintf_s(pBuffer, _T("Look:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera.get()->m_vLookVector.x,
			m_pMainCamera.get()->m_vLookVector.y,
			m_pMainCamera.get()->m_vLookVector.z);
		str += pBuffer;

		memset(pBuffer, 0, sizeof(TCHAR) * 256);
		_stprintf_s(pBuffer, _T("Up:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera.get()->m_vUpVector.x,
			m_pMainCamera.get()->m_vUpVector.y,
			m_pMainCamera.get()->m_vUpVector.z);
		str += pBuffer;

		memset(pBuffer, 0, sizeof(TCHAR) * 256);
		_stprintf_s(pBuffer, _T("Right:%10.4f,%10.4f,%10.4f "), m_pMainCamera.get()->m_vRightVector.x,
			m_pMainCamera.get()->m_vRightVector.y,
			m_pMainCamera.get()->m_vRightVector.z);
		str += pBuffer;

		rc.left = m_DefaultRT.m_vp.TopLeftX + m_DefaultRT.m_vp.Width*0.5f;
		rc.top = m_DefaultRT.m_vp.Height - 75;
		rc.right = m_DefaultRT.m_vp.Width;
		rc.bottom = m_DefaultRT.m_vp.Height;
		DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));



#else
		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			//m_matWorld._41 = -50.0f + iChar * 25.0f;
			m_HeroObj[iChar]->SetMatrix(&m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
			m_HeroObj[iChar]->Render(m_pImmediateContext);
		}
#endif
	}

	return true;
}

bool CGciCharToolApp::LoadFileDlg(TCHAR* szExt, TCHAR* szTitle)
{
	OPENFILENAME    ofn;
	TCHAR           szFile[MAX_PATH] = { 0, };
	TCHAR			szFileTitle[MAX_PATH] = { 0, };
	static TCHAR    *szFilter;

	TCHAR lpCurBuffer[256] = { 0, };
	GetCurrentDirectory(256, lpCurBuffer);

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	_tcscpy_s(szFile, _T("*."));
	_tcscat_s(szFile, szExt);
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
	ofn.lpstrInitialDir = _T("../../data/Character/");
	ofn.lpstrTitle = szTitle;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = szExt;

	if (!GetOpenFileName(&ofn))
	{
		return false;
	}
	TCHAR* load = _tcstok(szFile, _T("\n"));
	T_STR dir = szFile;
	load = &load[_tcslen(load) + 1];
	if (*load == 0)
	{
		m_LoadFiles.push_back(dir);
	}

	while (*load != 0)
	{
		T_STR dir = szFile;
		load = _tcstok(load, _T("\n"));
		dir += _T("\\");
		dir += load;
		m_LoadFiles.push_back(dir);
		load = &load[_tcslen(load) + 1];
	}
	SetCurrentDirectory(lpCurBuffer);


	//Ȯ���ڸ� �����ϱ� ���� �߰��� �ڵ�
	string extension = getExt(TCHARToString(dir.c_str()));

	if (0 == extension.compare("GCI") || extension.compare("gci") == 0)
	{
		m_FileExt = G_TOOL_EXT_GCI;
		return true;
	}
	if (0 == extension.compare("GBS") || extension.compare("gbs") == 0) {
		m_FileExt = G_TOOL_EXT_GBS;
		return true;
	}
	return true;
}
#ifdef G_MACRO_MODELVIEW

HRESULT CGciCharToolApp::ScreenViewPort(UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;

	UINT iRectWidth = iWidth / 5;
	UINT iRectHeight = iHeight / 4;

	m_ViewPort[0].Set(GetDevice(), 0, 0, iRectWidth, iRectHeight, 0.0f, 1.0f);
	m_ViewPort[1].Set(GetDevice(), 0, iRectHeight, iRectWidth, iRectHeight, 0.0f, 1.0f);
	m_ViewPort[2].Set(GetDevice(), 0, iRectHeight * 2, iRectWidth, iRectHeight, 0.0f, 1.0f);
	m_ViewPort[3].Set(GetDevice(), 0, iRectHeight * 3, iRectWidth, iRectHeight, 0.0f, 1.0f);

	return hr;
}
#endif

bool CGciCharToolApp::Load()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	I_CharMgr.Init();

	if (!LoadFileDlg(_T("*"), _T("GCI Viewer")))
	{
		return false;
	}


	if (m_FileExt == G_TOOL_EXT_GCI) {
		{
			int iLoad = m_LoadFiles.size() - 1;

			ifstream ifile;

			char line[MAX_PATH]; // �� �پ� �о �ӽ÷� ������ ����

			ifile.open(m_LoadFiles[iLoad].c_str());  // ���� ����

			if (ifile.is_open())
			{
				while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
				{
					//cout << line << endl; // ���� ���
					CString str;
					str = line;
					m_vecStr.push_back(str);
				}
			}

			ifile.close(); // ���� �ݱ�

		}


		int iLoad = m_LoadFiles.size() - 1;

		if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, m_LoadFiles[iLoad].c_str()/*_T("data/CharTable.gci")*/))
		{
			return false;
		}

		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

		shared_ptr<GZombie> pObjA = make_shared<GZombie>();
		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);

		pObjA->m_OBB.Init(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);

		m_HeroObj.push_back(pObjA);

		//CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->m_wndModelCtrl.m_wndForm->UpdateTextOBBInfo(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);
		//CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		//CGciCharToolView *pView = (CGciCharToolView *)pFrame->GetActiveView();

		//pView->UpdateTextOBBInfo(pObjA->m_pChar->m_vMin, pObjA->m_pChar->m_vMax);
	}
	if (m_FileExt == G_TOOL_EXT_GBS) {
		int iLoad = m_LoadFiles.size() - 1;

		m_tbsobj.Init();
		if (!m_tbsobj.Load(GetDevice(), m_LoadFiles[iLoad].c_str(), L"data/shader/box.hlsl"))
		{
			return false;
		}
		m_tbsobj.m_OBB.Init(D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		pFrame->m_wndModelCtrl.m_wndForm->UpdateTextOBBInfo(D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	}

	return true;
}

void CGciCharToolApp::OnCharload()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//I_CharMgr.Release();

	Load();
}




void CGciCharToolApp::OnCharsave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.


	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();


	TCHAR current_path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH, current_path); // ���� ��� ����

	CFileDialog dlg(false, _T("gci"), _T("*.gci"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("GCI File(*.gci)|*.gci||"));

	if (dlg.DoModal() == IDOK) { // OK �� �ϴ� ���� ���� ��ΰ� ����ȴ�.
		// ���⼭ ���� ���� �۾�.
		// ���⼭ ��� dlg.GetFileName() �Լ��� ��� ��η��� ���� �̸��� ��ȯ�� �ش�.

		// ������ ������ �̸�..
		// dlg.GetFileName();

		// ������ ������ �̸��� ������ ���..
		CString str = dlg.GetPathName();

		{

			FILE* fp = fopen((CStringA)str, "wt+");

			for (int i = 0; i< m_vecStr.size(); i++)
			{
				CString str;
				CString strNum;
				
				

				if (i == 7) {
					str = "#OBB_MIN_X	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMinX);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 8) {
					str = "#OBB_MIN_Y	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMinY);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 9) {
					str = "#OBB_MIN_Z	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMinZ);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 10) {
					str = "#OBB_MAX_X	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMaxX);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 11) {
					str = "#OBB_MAX_Y	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMaxY);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 12) {
					str = "#OBB_MAX_Z	";
					strNum.Format(_T("%f\n"), pFrame->m_wndModelCtrl.m_wndForm->m_fMaxZ);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}



				
				fprintf(fp, (CStringA)m_vecStr[i]);

				//CString name = "wqwkejqpwe"; // �Ź� �ٸ� �̸�
				//name.ReleaseBuffer();
				fprintf(fp, "\n");
			}

			fclose(fp);
		}

	}
	SetCurrentDirectory(current_path); // ���� ��η� ���� ����.

}

#ifdef G_MACRO_MODELVIEW
bool CGciCharToolApp::DrawDebug()
{
	D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT nViewPorts = 1;
	m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);

	m_ViewPort[0].Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	m_pDirectionLine.SetMatrix(NULL, &m_pCamera[0]->m_matView, &m_pCamera[0]->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_ViewPort[1].Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	m_pDirectionLine.SetMatrix(NULL, &m_pCamera[1]->m_matView, &m_pCamera[1]->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_ViewPort[2].Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	m_pDirectionLine.SetMatrix(NULL, &m_pCamera[2]->m_matView, &m_pCamera[2]->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_ViewPort[3].Apply(m_pImmediateContext, GetRenderTargetView(), GetDepthStencilView());
	m_pDirectionLine.SetMatrix(NULL, &m_pCamera[3]->m_matView, &m_pCamera[3]->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	//-----------------------------------------------------------------------
	// �⺻ ����Ʈ ������ ����
	//-----------------------------------------------------------------------
	m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);
	return GCoreLibV2::DrawDebug();
}
BOOL CGciCharToolApp::InitCamera() {
	// 4 ������ ī�޶� ����
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);

	//  ���� ����Ʈ 4���� �� ī�޶� ���
	// Top g_matView	
	m_pCamera[0] = make_shared<GModelCamera>();
	m_pCamera[0].get()->SetViewMatrix(vCameraPosition, m_vObjectPosition, vUpVector);
	// Front g_matView
	m_pCamera[1] = make_shared<GModelCamera>();
	vCameraPosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_pCamera[1].get()->SetViewMatrix(vCameraPosition, m_vObjectPosition, vUpVector);
	// Side g_matView
	m_pCamera[2] = make_shared<GModelCamera>();
	vCameraPosition = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_pCamera[2].get()->SetViewMatrix(vCameraPosition, m_vObjectPosition, vUpVector);
	// User g_matView
	m_pCamera[3] = make_shared<GModelCamera>();
	vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	m_pCamera[3].get()->SetViewMatrix(vCameraPosition, m_vObjectPosition, vUpVector);

	// ����Ʈ�� ��� �°� ī�޶� ����.
	m_pCamera[0].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[1].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[2].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[3].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));

	// ���� ī�޶� �� ��� ����
	m_pMainCamera = make_shared<GModelCamera>();
	m_pMainCamera->SetViewMatrix(m_pCamera[m_iCameraType].get()->m_vCameraPos,
		m_pCamera[m_iCameraType].get()->m_vTargetPos,
		vUpVector);
	m_fRadius = D3DXVec3Length(&(m_pMainCamera.get()->m_vCameraPos - m_pMainCamera.get()->m_vTargetPos));

	// ������� ����
	DXGI_SWAP_CHAIN_DESC Desc;
	if (FAILED(GetSwapChain()->GetDesc(&Desc)))
	{
		return false;
	}
	for (int iCamera = 0; iCamera < 4; iCamera++)
	{
		m_pCamera[iCamera].get()->SetProjMatrix(D3DX_PI * 0.25f,
			(float)m_ViewPort[iCamera].m_vp.Width / (float)m_ViewPort[iCamera].m_vp.Height,
			1.0f,
			1000.0f);
	}
	m_pMainCamera.get()->SetProjMatrix(D3DX_PI * 0.25f,
		Desc.BufferDesc.Width / (float)(Desc.BufferDesc.Height),
		0.1f, 1000.0f);

	D3DXMATRIX matRotX, matScale;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90));
	D3DXMatrixScaling(&matScale, 2.0f, 2.0f, 2.0f);
	D3DXMatrixMultiply(&m_World[1], &matScale, &matRotX);

}
#endif
