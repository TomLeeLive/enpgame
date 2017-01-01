
// MapTool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MapTool.h"
#include "MainFrm.h"

#include "MapToolDoc.h"
#include "MapToolView.h"
#include "GCreateMapDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolApp

BEGIN_MESSAGE_MAP(CMapToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMapToolApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

bool CMapToolApp::LoadFileDlg(TCHAR* szExt, TCHAR* szTitle)
{
	//OPENFILENAME    ofn;
	//TCHAR           szFile[MAX_PATH] = { 0, };
	//TCHAR			szFileTitle[MAX_PATH] = { 0, };
	//static TCHAR    *szFilter;

	//TCHAR lpCurBuffer[256] = { 0, };
	//GetCurrentDirectory(256, lpCurBuffer);

	//ZeroMemory(&ofn, sizeof(OPENFILENAME));
	//_tcscpy_s(szFile, _T("*."));
	//_tcscat_s(szFile, szExt);
	//_tcscat_s(szFile, _T("\0"));

	//ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = GetActiveWindow();
	//ofn.lpstrFilter = szFilter;
	//ofn.lpstrCustomFilter = NULL;
	//ofn.nMaxCustFilter = 0L;
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFile = szFile;
	//ofn.nMaxFile = MAX_PATH;
	//ofn.lpstrFileTitle = szFileTitle;
	//ofn.nMaxFileTitle = MAX_PATH;
	//ofn.lpstrInitialDir = _T("../../data/Character/");
	//ofn.lpstrTitle = szTitle;
	//ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	//ofn.nFileOffset = 0;
	//ofn.nFileExtension = 0;
	//ofn.lpstrDefExt = szExt;

	//if (!GetOpenFileName(&ofn))
	//{
	//	return false;
	//}
	//TCHAR* load = _tcstok(szFile, _T("\n"));
	//T_STR dir = szFile;
	//load = &load[_tcslen(load) + 1];
	//if (*load == 0)
	//{
	//	m_LoadFiles.push_back(dir);
	//}

	//while (*load != 0)
	//{
	//	T_STR dir = szFile;
	//	load = _tcstok(load, _T("\n"));
	//	dir += _T("\\");
	//	dir += load;
	//	m_LoadFiles.push_back(dir);
	//	load = &load[_tcslen(load) + 1];
	//}
	//SetCurrentDirectory(lpCurBuffer);


	////Ȯ���ڸ� �����ϱ� ���� �߰��� �ڵ�
	//string extension = getExt(TCHARToString(dir.c_str()));

	//if (0 == extension.compare("GUI") || extension.compare("gui") == 0)
	//{
	//	m_FileExt = G_TOOL_EXT_GUI;
	//	return true;
	//}
	//if (0 == extension.compare("GBS") || extension.compare("gbs") == 0) {
	//	m_FileExt = G_TOOL_EXT_GBS;
	//	return true;
	//}

	return true;
}




// CMapToolApp ����
bool CMapToolApp::Init()
{
	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GMapCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 0.1f, 20000.0f);


	//--------------------------------------------------------------------------------------
	// ī�޶� ���ν��� �������� �ڽ� ������Ʈ ����
	//--------------------------------------------------------------------------------------
	m_pMainCamera->CreateRenderBox(g_pd3dDevice, g_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(g_pd3dDevice, L"data/shader/box.hlsl", "PS_Color"));


	m_MapMgr.Init();
	

	//���� ĳ���� �߰�[S]
	I_CharMgr.Init();

	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("data/CharZombie.gci")))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

	shared_ptr<GZombie> pObjA = make_shared<GZombie>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);
	//���� ĳ���� �߰�[E]

	return true;
}
bool CMapToolApp::Frame()
{
	//--------------------------------------------------------------------------------------
	// default
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	m_MapMgr.Frame(&I_Input.GetInstance(), m_pMainCamera.get());

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->Frame();
	}

	if (theApp.m_MapMgr.m_pObjSelected != NULL) {
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_wndObjCtrl.m_wndForm->m_fScl = theApp.m_MapMgr.m_pObjSelected->m_iScl;
		pFrame->m_wndObjCtrl.m_wndForm->m_fRotY = theApp.m_MapMgr.m_pObjSelected->m_fRotY;
		pFrame->m_wndObjCtrl.m_wndForm->m_fTransX = theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._41;
		pFrame->m_wndObjCtrl.m_wndForm->m_fTransY = theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._42;
		pFrame->m_wndObjCtrl.m_wndForm->m_fTransZ = theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._43;

		pFrame->m_wndObjCtrl.m_wndForm->UpdateData(FALSE);
	}
	return true; 
}
bool CMapToolApp::Render()
{	
	m_MapMgr.Render(m_pMainCamera.get());

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_HeroObj[iChar]->m_matWorld._42 = 36.2f;
		m_HeroObj[iChar]->SetMatrix(&m_HeroObj[iChar]->m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_HeroObj[iChar]->Render(m_pImmediateContext);
	}
	return true;
}
bool CMapToolApp::Release()
{
	m_MapMgr.Release();
	
	I_CharMgr.Release();
	return true;
}



//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT CMapToolApp::CreateResource()
{

	HRESULT hr;

	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 0.1f, 20000.0f);
	}

	m_MapMgr.CreateResource();

	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT CMapToolApp::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();

	m_MapMgr.DeleteResource();

	return S_OK;
}


CMapToolApp::CMapToolApp()
{
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
	SetAppID(_T("MapTool.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CMapToolApp ��ü�Դϴ�.

CMapToolApp theApp;


// CMapToolApp �ʱ�ȭ

BOOL CMapToolApp::InitInstance()
{

	GCoreLibV2::m_bDebugInfoPrint = false;
	//GCoreLibV2::m_bDebugFpsPrint = false;

	//SAFE_ZERO(m_pBoxs);
	//SAFE_ZERO(m_pMapObj);

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
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	//�߰��� �޴��� ��ҵǼ� ������ �ʾƼ� �߰���[S]
	CleanState();
	//�߰��� �޴��� ��ҵǼ� ������ �ʾƼ� �߰���[E]

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
		RUNTIME_CLASS(CMapToolDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CMapToolView));
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

	//�ھ� ������ �ʿ��� ó��
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolView* pView = (CMapToolView*)pFrame->GetActiveView();

	GWindow::m_hInstance = AfxGetInstanceHandle();
	GWindow::m_hWnd = pView->m_hWnd;
	g_hInstance = GWindow::m_hInstance;
	g_hWnd = GWindow::m_hWnd;
	I_Input.m_hWnd = pFrame->m_hWnd;

	CRect rcClient;
	pView->GetClientRect(rcClient);
	GWindow::m_iWindowWidth = rcClient.Width();
	GWindow::m_iWindowHeight = rcClient.Height();

	GCoreLibV2::GInit();






	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMapToolApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);
	GRelease();

	return CWinAppEx::ExitInstance();
}

// CMapToolApp �޽��� ó����


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
void CMapToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CMapToolApp::OnIdle(LONG lCount)
{
	__super::OnIdle(lCount);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GFrame();
	GRender();

	return TRUE;
}

// CMapToolApp ����� ���� �ε�/���� �޼���

void CMapToolApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMapToolApp::LoadCustomState()
{
}

void CMapToolApp::SaveCustomState()
{
}

// CMapToolApp �޽��� ó����



