
// GciCharTool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GciCharTool.h"
#include "MainFrm.h"

#include "GciCharToolDoc.h"
#include "GciCharToolView.h"

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


// CAIToolApp ����

CGciCharToolApp::CGciCharToolApp()
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
	GBasisLib_0::TInit();


	

	Load();


	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 10.0f, 100.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);





	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGciCharToolApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	I_CharMgr.Release();
	return true;


	AfxOleTerm(FALSE);
	TRelease();
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
	TFrame();
	TRender();
	return TRUE;
}


bool CGciCharToolApp::Frame() {
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	//m_pMainCamera->Update(g_fSecPerFrame);
	m_pMainCamera->Frame();
	m_matWorld = *m_pMainCamera->GetWorldMatrix();
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;

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
	return true;
}
bool CGciCharToolApp::Render() {
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	g_pImmediateContext->ClearRenderTargetView(GetRenderTargetView(), ClearColor);

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		//m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_HeroObj[iChar]->SetMatrix(&m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_HeroObj[iChar]->Render(m_pImmediateContext);
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
	return true;
}
bool CGciCharToolApp::Load()
{
	I_CharMgr.Init();

	if (!LoadFileDlg(_T("gci"), _T("GCI Viewer")))
	{
		return false;
	}

	//int iLoad = m_LoadFiles.size() - 1;
	//if (!m_tObject.Load(GetDevice(), m_LoadFiles[iLoad].c_str(), L"MatrixViewer.hlsl"))
	//{
	//	return false;
	//}

	int iLoad = m_LoadFiles.size() - 1;

	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, m_LoadFiles[iLoad].c_str()/*_T("CharTable.gci")*/))
	{
		return false;
	}

	GCharacter* pChar0 = I_CharMgr.GetPtr(L"TESTCHAR6");
	//GCharacter* pChar1 = I_CharMgr.GetPtr(L"TEST_CHAR1");
	//GCharacter* pChar2 = I_CharMgr.GetPtr(L"TEST_CHAR2");
	//GCharacter* pChar3 = I_CharMgr.GetPtr(L"TEST_CHAR3");

	shared_ptr<GHeroObj> pObjA = make_shared<GHeroObj>();
	pObjA->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);
	/*
	shared_ptr<GHeroObj> pObjB = make_shared<GHeroObj>();
	pObjB->Set(pChar1,
	pChar1->m_pBoneObject,
	pChar1->m_pBoneObject->m_Scene.iFirstFrame,
	60);
	m_HeroObj.push_back(pObjB);


	shared_ptr<GHeroObj> pObjC = make_shared<GHeroObj>();
	pObjC->Set(pChar1,
	pChar1->m_pBoneObject,
	61,
	90);
	m_HeroObj.push_back(pObjC);

	shared_ptr<GHeroObj> pObjD = make_shared<GHeroObj>();
	pObjD->Set(pChar1,
	pChar1->m_pBoneObject,
	62,
	116);
	m_HeroObj.push_back(pObjD);


	shared_ptr<GHeroObj> pObjE = make_shared<GHeroObj>();
	pObjE->Set(	pChar2,
	pChar2->m_pBoneObject,
	pChar2->m_pBoneObject->m_Scene.iFirstFrame,
	pChar2->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjE);

	shared_ptr<GHeroObj> pObjF = make_shared<GHeroObj>();
	pObjF->Set( pChar3,
	pChar3->m_pBoneObject,
	pChar3->m_pBoneObject->m_Scene.iFirstFrame,
	pChar3->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjF);*/
	return true;
}

void CGciCharToolApp::OnCharload()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	I_CharMgr.Release();

	Load();
}




void CGciCharToolApp::OnCharsave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
