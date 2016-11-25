
// GUITool.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GUITool.h"
#include "MainFrm.h"

#include "GUIToolDoc.h"
#include "GUIToolView.h"

//파일 입출력 때문에 추가함
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAIToolApp

BEGIN_MESSAGE_MAP(CGUIToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGUIToolApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_CHARLOAD, &CGUIToolApp::OnCharload)
	ON_COMMAND(ID_CHARSAVE, &CGUIToolApp::OnCharsave)
END_MESSAGE_MAP()



////////////////////////////////////////////////////////
// 문자열 처리 관련 함수 추가함.

//확장자를 얻기 위해.
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

// CAIToolApp 생성

HRESULT CGUIToolApp::CreateResource()
{
	//추가함 for UI [start]
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
	GetSwapChain()->GetDesc(&SwapChainDesc);
	m_UIManager.CreateResource(&SwapChainDesc);

	//추가함 for UI [end]
	return S_OK;
}

HRESULT CGUIToolApp::DeleteResource()
{
	HRESULT hr = S_OK;
	// 아래의 경고는 GetDevice()->ClearState();를 호출하지 않을 때 발생한다.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

CGUIToolApp::CGUIToolApp()
{
	m_FileExt = G_TOOL_EXT_GUI;

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
	SetAppID(_T("GUITool.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CAIToolApp 개체입니다.

CGUIToolApp theApp;


// CAIToolApp 초기화

BOOL CGUIToolApp::InitInstance()
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
	SetRegistryKey(_T("GUITOOL"));
	
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
		RUNTIME_CLASS(CGUIToolDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CGUIToolView));
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
	CGUIToolView* pView = (CGUIToolView*)pFrame->GetActiveView();
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
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_UIManager.Init();









	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGUIToolApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.

	//추가함 for UI [start]
	m_UIManager.Release();
	//추가함 for UI [end]



	if (m_FileExt == G_TOOL_EXT_GUI) {

		//return true;

		for (int i = 0; i < m_vecStr.size(); i++) {

			m_vecStr[i].ReleaseBuffer();
		}
	}
	if (m_FileExt == G_TOOL_EXT_GBS) {

	}


	

	AfxOleTerm(FALSE);
	GRelease();
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
void CGUIToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAIToolApp 사용자 지정 로드/저장 메서드

void CGUIToolApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGUIToolApp::LoadCustomState()
{
}

void CGUIToolApp::SaveCustomState()
{
}

// CAIToolApp 메시지 처리기





BOOL CGUIToolApp::OnIdle(LONG lCount)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	__super::OnIdle(lCount);
	GFrame();
	GRender();
	return TRUE;
}


bool CGUIToolApp::Frame() {
	//추가함 for UI [start]
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = m_Timer.GetElapsedTime() * D3DX_PI;

	DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
	GetSwapChain()->GetDesc(&SwapChainDesc);
	m_UIManager.Frame(&SwapChainDesc);
	//추가함 for UI [end]



	return true;
}
bool CGUIToolApp::Render() {
	//추가함 for UI [start]
	m_UIManager.Render();
	return true;
}

bool CGUIToolApp::LoadFileDlg(TCHAR* szExt, TCHAR* szTitle)
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


	//확장자를 검출하기 위해 추가한 코드
	string extension = getExt(TCHARToString(dir.c_str()));

	if (0 == extension.compare("GUI") || extension.compare("gui") == 0)
	{
		m_FileExt = G_TOOL_EXT_GUI;
		return true;
	}
	if (0 == extension.compare("GBS") || extension.compare("gbs") == 0) {
		m_FileExt = G_TOOL_EXT_GBS;
		return true;
	}
	return true;
}


bool CGUIToolApp::Load()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();


	if (!LoadFileDlg(_T("gci"), _T("GCI Viewer")))
	{
		return false;
	}


	if (m_FileExt == G_TOOL_EXT_GUI) {
		{
			int iLoad = m_LoadFiles.size() - 1;

			ifstream ifile;

			char line[MAX_PATH]; // 한 줄씩 읽어서 임시로 저장할 공간

			ifile.open(m_LoadFiles[iLoad].c_str());  // 파일 열기

			if (ifile.is_open())
			{
				while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
				{
					//cout << line << endl; // 내용 출력
					CString str;
					str = line;
					m_vecStr.push_back(str);
				}
			}

			ifile.close(); // 파일 닫기

		}


		int iLoad = m_LoadFiles.size() - 1;
		/*
		if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, m_LoadFiles[iLoad].c_str()/*_T("CharTable.gci")))
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
		*/

	}
	if (m_FileExt == G_TOOL_EXT_GBS) {
		int iLoad = m_LoadFiles.size() - 1;

		/*
		m_tbsobj.Init();
		if (!m_tbsobj.Load(GetDevice(), m_LoadFiles[iLoad].c_str(), L"data/shader/box.hlsl"))
		{
			return false;
		}
		m_tbsobj.m_OBB.Init(D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		pFrame->m_wndButtonCtrl.m_wndForm->UpdateTextOBBInfo(D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		*/
	}

	return true;
}

void CGUIToolApp::OnCharload()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//I_CharMgr.Release();

	Load();
}



//추가함 for UI [start]
void CGUIToolApp::OnCharsave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();


	TCHAR current_path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH, current_path); // 현재 경로 저장

	CFileDialog dlg(false, _T("gci"), _T("*.gci"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("GCI File(*.gci)|*.gci||"));

	if (dlg.DoModal() == IDOK) { // OK 를 하는 순간 현재 경로가 변경된다.
		// 여기서 파일 저장 작업.
		// 여기서 얻는 dlg.GetFileName() 함수는 상대 경로로의 파일 이름을 반환해 준다.

		// 선택한 파일의 이름..
		// dlg.GetFileName();

		// 선택한 파일의 이름을 포함한 경로..
		CString str = dlg.GetPathName();

		{

			FILE* fp = fopen((CStringA)str, "wt+");

			for (int i = 0; i< m_vecStr.size(); i++)
			{
				CString str;
				CString strNum;
				
				

				if (i == 7) {
					str = "#OBB_MIN_X	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMinX);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 8) {
					str = "#OBB_MIN_Y	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMinY);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 9) {
					str = "#OBB_MIN_Z	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMinZ);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 10) {
					str = "#OBB_MAX_X	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMaxX);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 11) {
					str = "#OBB_MAX_Y	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMaxY);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}
				if (i == 12) {
					str = "#OBB_MAX_Z	";
					strNum.Format(_T("%f\n"), pFrame->m_wndButtonCtrl.m_wndForm->m_fMaxZ);
					str.Append(strNum);
					fprintf(fp, (CStringA)str);
					continue;
				}



				
				fprintf(fp, (CStringA)m_vecStr[i]);

				//CString name = "wqwkejqpwe"; // 매번 다른 이름
				//name.ReleaseBuffer();
				fprintf(fp, "\n");
			}

			fclose(fp);
		}

	}
	SetCurrentDirectory(current_path); // 원래 경로로 돌아 간다.

}


