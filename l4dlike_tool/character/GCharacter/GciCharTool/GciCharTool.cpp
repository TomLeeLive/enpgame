
// GciCharTool.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_CHARLOAD, &CGciCharToolApp::OnCharload)
	ON_COMMAND(ID_CHARSAVE, &CGciCharToolApp::OnCharsave)
END_MESSAGE_MAP()


// CAIToolApp 생성

CGciCharToolApp::CGciCharToolApp()
{
	m_bHiColorIcons = TRUE;

	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GciCharTool.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CAIToolApp 개체입니다.

CGciCharToolApp theApp;


// CAIToolApp 초기화

BOOL CGciCharToolApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("GCICHARTOOL"));
	
	CleanState();

	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGciCharToolDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CGciCharToolView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//  코어 연동에 필요한 처리
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
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 10.0f, 100.0f));

	float fAspectRatio = m_iWindowWidth / (FLOAT)m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	m_pMainCamera->SetWindow(m_iWindowWidth, m_iWindowHeight);





	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGciCharToolApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	I_CharMgr.Release();
	return true;


	AfxOleTerm(FALSE);
	TRelease();
	return CWinAppEx::ExitInstance();
}

// CAIToolApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CGciCharToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAIToolApp 사용자 지정 로드/저장 메서드

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

// CAIToolApp 메시지 처리기





BOOL CGciCharToolApp::OnIdle(LONG lCount)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	__super::OnIdle(lCount);
	TFrame();
	TRender();
	return TRUE;
}


bool CGciCharToolApp::Frame() {
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	I_CharMgr.Release();

	Load();
}




void CGciCharToolApp::OnCharsave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
