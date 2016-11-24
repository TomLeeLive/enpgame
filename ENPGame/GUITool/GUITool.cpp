
// GUITool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GUITool.h"
#include "MainFrm.h"

#include "GUIToolDoc.h"
#include "GUIToolView.h"

//���� ����� ������ �߰���
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAIToolApp

BEGIN_MESSAGE_MAP(CGUIToolApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGUIToolApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_CHARLOAD, &CGUIToolApp::OnCharload)
	ON_COMMAND(ID_CHARSAVE, &CGUIToolApp::OnCharsave)
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

HRESULT CGUIToolApp::CreateResource()
{
	//�߰��� for UI [start]
	HRESULT hr;
	// ������ĵ� ������ ����� ����Ǹ� �ݵ�� ������Ʈ �ؾ� �Ѵ�.
	int iRectWidth = m_SwapChainDesc.BufferDesc.Width;
	int iRectHeight = m_SwapChainDesc.BufferDesc.Height;
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		if (pRect) pRect->CreateResource(iRectWidth, iRectHeight);
	}
	//�߰��� for UI [end]
	return S_OK;
}

HRESULT CGUIToolApp::DeleteResource()
{
	HRESULT hr = S_OK;
	// �Ʒ��� ���� GetDevice()->ClearState();�� ȣ������ ���� �� �߻��Ѵ�.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

CGUIToolApp::CGUIToolApp()
{
	m_FileExt = G_TOOL_EXT_GUI;

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
	SetAppID(_T("GUITool.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CAIToolApp ��ü�Դϴ�.

CGUIToolApp theApp;


// CAIToolApp �ʱ�ȭ

BOOL CGUIToolApp::InitInstance()
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
	SetRegistryKey(_T("GUITOOL"));
	
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
		RUNTIME_CLASS(CGUIToolDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CGUIToolView));
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
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	I_Ime.ImeUi_Initialize(m_hWnd);

	GImageCtl* pImageCtl = new GImageCtl();
	pImageCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pImageCtl->Create(GetDevice(), nullptr, L"data/ui/hud.dds");
	pImageCtl->Scale(400 - 1.0f, 300 - 1.0f, 1.0f - 1.0f);
	pImageCtl->Move(0, 0, 100);
	m_pUIList.push_back(pImageCtl);

	GButtonCtl* pBoxCtl = new GButtonCtl();
	pBoxCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pBoxCtl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
	pBoxCtl->Scale(100 - 1.0f, 50 - 1.0f, 1 - 1.0f);
	pBoxCtl->Move(0, 0, 0);
	m_pUIList.push_back(pBoxCtl);

#pragma region g_pTextureSRV
	m_pTextureSRV[0].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/Background.bmp"));
	m_pTextureSRV[1].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/_connect.bmp"));
	m_pTextureSRV[2].Attach(CreateShaderResourceView(GetDevice(), L"data/ui/_exit_lg.bmp"));
#pragma endregion








	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGUIToolApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.

	//�߰��� for UI [start]
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Release();
		delete pRect;
	}
	I_Ime.Uninitialize();
	//�߰��� for UI [end]



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
void CGUIToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAIToolApp ����� ���� �ε�/���� �޼���

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

// CAIToolApp �޽��� ó����





BOOL CGUIToolApp::OnIdle(LONG lCount)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	__super::OnIdle(lCount);
	GFrame();
	GRender();
	return TRUE;
}


bool CGUIToolApp::Frame() {
	//�߰��� for UI [start]
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;


	if (I_Input.KeyCheck(DIK_P) == KEY_UP)
	{
		m_pSelectPlane = AddRect(G_BUTTON);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		m_pSelectPlane = AddRect(G_EDIT);
	}

	GControlUI* pSelect = SelectRect();

	if (pSelect != NULL && m_pSelectPlane != pSelect)
	{
		m_pSelectPlane = pSelect;
	}

	if (m_pSelectPlane)
	{
		D3DXVECTOR3 vPos(0, 0, 0);
		D3DXVECTOR3 vScale(0, 0, 0);
		if (g_InputData.bQKey)
		{
			vScale.x += 50 * g_fSecPerFrame;
		}
		if (g_InputData.bEKey)
		{
			vScale.x += -50 * g_fSecPerFrame;
		}
		if (g_InputData.bZKey)
		{
			vScale.y += 50 * g_fSecPerFrame;
		}
		if (g_InputData.bCKey)
		{
			vScale.y += -50 * g_fSecPerFrame;
		}
		if (g_InputData.bWKey)
		{
			vPos.y = 50 * g_fSecPerFrame;
		}
		if (g_InputData.bSKey)
		{
			vPos.y = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bAKey)
		{
			vPos.x = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bDKey)
		{
			vPos.x = 50 * g_fSecPerFrame;
		}
		m_pSelectPlane->Move(vPos.x, vPos.y, vPos.z);
		m_pSelectPlane->Scale(vScale.x, vScale.y, vScale.z);
	}

	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Update();
	}
	//�߰��� for UI [end]



	return true;
}
bool CGUIToolApp::Render() {
	//�߰��� for UI [start]
	D3DXMATRIX matTrans, matRotation, matZ;
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

	//D3DXMatrixTranspose(&m_cbData.matProj, &m_Projection[1]);
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Render(m_pImmediateContext);
	}
	//�߰��� for UI [end]
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


	//Ȯ���ڸ� �����ϱ� ���� �߰��� �ڵ�
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//I_CharMgr.Release();

	Load();
}



//�߰��� for UI [start]
void CGUIToolApp::OnCharsave()
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

				//CString name = "wqwkejqpwe"; // �Ź� �ٸ� �̸�
				//name.ReleaseBuffer();
				fprintf(fp, "\n");
			}

			fclose(fp);
		}

	}
	SetCurrentDirectory(current_path); // ���� ��η� ���� ����.

}


GControlUI* CGUIToolApp::AddRect(GUI_TYPE type)
{
	GControlUI* pUIControl = NULL;
	switch (type)
	{
	case G_BUTTON: {
		pUIControl = new GButtonCtl();
		pUIControl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	case G_EDIT: {
		pUIControl = new GEditCtl();
		pUIControl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	}
	pUIControl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	m_pUIList.push_back(pUIControl);
	return pUIControl;
}
GControlUI* CGUIToolApp::SelectRect()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(m_hWnd, &mouse);
	for (int iRect = 0; iRect < m_pUIList.size(); iRect++)
	{
		GControlUI* pRect = m_pUIList[iRect];
		if (I_Input.m_MouseState[0] == KEY_HOLD)
		{
			RECT rt = pRect->m_rt;
			// ������ �� ���
			if (pRect->m_rt.left > pRect->m_rt.right)
			{
				rt.left = pRect->m_rt.right;
				rt.right = pRect->m_rt.left;
			}
			if (pRect->m_rt.top > pRect->m_rt.bottom)
			{
				rt.top = pRect->m_rt.bottom;
				rt.bottom = pRect->m_rt.top;
			}
			if (rt.left <= mouse.x && rt.right >= mouse.x)
			{
				if (rt.top <= mouse.y && rt.bottom >= mouse.y)
				{
					return pRect;
				}
			}
		}
	}
	return NULL;
}
//�߰��� for UI [end]
