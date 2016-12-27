
// MapTool.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
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


	////확장자를 검출하기 위해 추가한 코드
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


bool CMapToolApp::CreateInit(int Width, int Height, float Distance, CString strTex)
{
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 3000.0f);
	//--------------------------------------------------------------------------------------
	//  맵 생성
	//--------------------------------------------------------------------------------------

	wchar_t szCharPath[MAX_PATH] = L"data/";
	wchar_t szChar[MAX_PATH];
	//CString strString;
	//strString = "test";
	_tcscpy_s(szChar, 16, strTex.GetBuffer());
	_tcscat_s(szCharPath, szChar);
	//theApp.m_MapDesc.strTextureFile = m_strCharName;

	//m_MapDesc = { Width, Height, Distance, 0.1f,L"data/sand.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_MapDesc = { Width, Height, Distance, 0.1f,szCharPath, L"data/shader/CustomizeMap.hlsl" };
	m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	if (FAILED(m_CustomMap.Load(m_MapDesc))) { return false; }
	//--------------------------------------------------------------------------------------
	//  쿼드 트리
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(m_MapDesc.iNumCols, m_MapDesc.iNumRows);
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	return true;
}

// CMapToolApp 생성
bool CMapToolApp::Init()
{
	//--------------------------------------------------------------------------------------
	// 디버그 라인 생성
	//--------------------------------------------------------------------------------------
	if (FAILED(m_DrawLine.Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_DrawLine 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
	m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 3000.0f);

	//--------------------------------------------------------------------------------------
	// 카메라 프로스텀 랜더링용 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_pMainCamera->CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/box.hlsl", "PS_Color"));
	
	return true;
}
bool CMapToolApp::Frame()
{
	//--------------------------------------------------------------------------------------
	// default
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();

	//--------------------------------------------------------------------------------------
	// add
	//--------------------------------------------------------------------------------------
	//2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;

	//--------------------------------------------------------------------------------------
	// QuadTree Frame
	//--------------------------------------------------------------------------------------
	if (m_MapDesc.iNumCols > 0 || m_MapDesc.iNumRows > 0)
	{
		g_pImmediateContext->UpdateSubresource(
			m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

		m_CustomMap.Frame();

		// 쿼드트리
		if (I_Input.KeyCheck(DIK_F4) == KEY_UP)
		{
			if (++m_iDrawDepth > 7)	m_iDrawDepth = -1;
			m_QuadTree.SetRenderDepth(m_iDrawDepth);
		}
		m_QuadTree.Frame();
	}
	
	return true; 
}
bool CMapToolApp::Render()
{	
	//--------------------------------------------------------------------------------------
	//  QuadTree Render
	//--------------------------------------------------------------------------------------
	if (m_MapDesc.iNumCols > 0 || m_MapDesc.iNumRows > 0)
	{

		m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
			m_pMainCamera->GetProjMatrix());
		m_CustomMap.Render(m_pImmediateContext);

		//DrawQuadLine(m_QuadTree.m_pRootNode);
	}
	return true;
}
bool CMapToolApp::Release()
{
	m_CustomMap.Release();
	m_QuadTree.Release();
	return true;
}

bool CMapToolApp::DrawQuadLine(GNode* pNode)
{
	if (pNode == NULL) return true;

	if (m_QuadTree.m_iRenderDepth == pNode->m_iDepth ||
		(pNode->m_isLeaf &&  m_QuadTree.m_iRenderDepth < 0))
	{
		m_DrawLine.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		D3DXVECTOR4 vColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 1) vColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 2) vColor = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 3) vColor = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 4) vColor = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 5) vColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 6) vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 7) vColor = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 8) vColor = D3DXVECTOR4(1.0f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 9) vColor = D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f);

		D3DXVECTOR3 vPoint[8];
		vPoint[0] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[1] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[2] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMin.z);
		vPoint[3] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMin.z);
		vPoint[4] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[5] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[6] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMax.z);
		vPoint[7] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMin.y, pNode->m_tBox.vMax.z);

		m_DrawLine.Draw(m_pImmediateContext, vPoint[0], vPoint[1], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[1], vPoint[2], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[2], vPoint[3], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[3], vPoint[0], vColor);

		m_DrawLine.Draw(m_pImmediateContext, vPoint[4], vPoint[5], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[5], vPoint[6], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[6], vPoint[7], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[7], vPoint[0], vColor);

		m_DrawLine.Draw(m_pImmediateContext, vPoint[0], vPoint[4], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[1], vPoint[5], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[2], vPoint[6], vColor);
		m_DrawLine.Draw(m_pImmediateContext, vPoint[3], vPoint[7], vColor);
	}
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		DrawQuadLine(pNode->m_ChildList[iNode]);
	}
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
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 3000.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT CMapToolApp::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
bool CMapToolApp::DrawDebug()
{
	//-----------------------------------------------------------------------
	// 적용되어 있는 카메라의 방향벡터 표시
	//-----------------------------------------------------------------------
	T_STR	str;
	RECT	rc;
	str.clear();
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Depth Control Key[F4] : Current Depth: %d %d\n"), m_iDrawDepth, g_InputData.iMouseValue[1]);
	str += pBuffer;

	//_stprintf_s(pBuffer, _T("Look:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vLookVector.x,
	//	m_pMainCamera->m_vLookVector.y,
	//	m_pMainCamera->m_vLookVector.z);
	//str += pBuffer;

	//memset(pBuffer, 0, sizeof(TCHAR) * 256);
	//_stprintf_s(pBuffer, _T("Up:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vUpVector.x,
	//	m_pMainCamera->m_vUpVector.y,
	//	m_pMainCamera->m_vUpVector.z);
	//str += pBuffer;

	//memset(pBuffer, 0, sizeof(TCHAR) * 256);
	//_stprintf_s(pBuffer, _T("Right:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vRightVector.x,
	//	m_pMainCamera->m_vRightVector.y,
	//	m_pMainCamera->m_vRightVector.z);
	//str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("p:%10.4f,%10.4f,%10.4f "), m_pMainCamera->m_vCameraPos.x,
		m_pMainCamera->m_vCameraPos.y,
		m_pMainCamera->m_vCameraPos.z);
	str += pBuffer;

	//rc.left = 0;
	//rc.top = 100;
	//rc.right = m_DefaultRT.m_vp.Width;
	//rc.bottom = m_DefaultRT.m_vp.Height;
	//DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	return GCoreLibV2::DrawDebug();
}

CMapToolApp::CMapToolApp()
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
	SetAppID(_T("MapTool.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CMapToolApp 개체입니다.

CMapToolApp theApp;


// CMapToolApp 초기화

BOOL CMapToolApp::InitInstance()
{
	m_iDrawDepth = 0;
	m_bDebugRender = false;
	GCoreLibV2::m_bDebugInfoPrint = false;
	//GCoreLibV2::m_bDebugFpsPrint = false;

	//SAFE_ZERO(m_pBoxs);
	//SAFE_ZERO(m_pMapObj);

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
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
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
		RUNTIME_CLASS(CMapToolDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CMapToolView));
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

	//코어 연동에 필요한 처리
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

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMapToolApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);
	GRelease();

	return CWinAppEx::ExitInstance();
}

// CMapToolApp 메시지 처리기


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
void CMapToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CMapToolApp::OnIdle(LONG lCount)
{
	__super::OnIdle(lCount);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GFrame();
	GRender();

	return TRUE;
}

// CMapToolApp 사용자 지정 로드/저장 메서드

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

// CMapToolApp 메시지 처리기



