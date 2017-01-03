
// GciCharTool.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GciCharTool.h"
#include "MainFrm.h"

#include "GciCharToolDoc.h"
#include "GciCharToolView.h"

//파일 입출력 때문에 추가함
#include <iostream>
#include <fstream>

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
	// 아래의 경고는 GetDevice()->ClearState();를 호출하지 않을 때 발생한다.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

CGciCharToolApp::CGciCharToolApp()
{
	m_FileExt = G_TOOL_EXT_GCI;

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
#ifdef G_MACRO_MODELVIEW

	//m_pMainCamera = make_shared<GModelViewCamera>();
	//m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	if (FAILED(m_pDirectionLine.Create(GetDevice(), L"data/shader/Line.hlsl")))
	{
		MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	//if (FAILED(m_pPlane.Create(GetDevice(), L"data/shader/Plane.hlsl", L"../../data/Sand.jpg")))
	//{
	//	MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}
	//if (FAILED(m_pBox.Create(GetDevice(), L"data/shader/Box.hlsl", L"../../data/checker_with_numbers.bmp")))
	//{
	//	MessageBox(0, _T("m_pBox 실패"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}

	// 초기화
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






	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGciCharToolApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
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
	GFrame();
	GRender();
	return TRUE;
}


bool CGciCharToolApp::Frame() {
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

#ifdef G_MACRO_MODELVIEW
	//m_pMainCamera->Update(g_fSecPerFrame);

	// 90도 회전
#ifdef	G_MACRO_MODELROT
	D3DXMatrixRotationY(&m_World[0], t*0.1f);
#else
	D3DXMatrixIdentity(&m_World[0]);
#endif


	//--------------------------------------------------------------------------------------
	// 카메라 타입 선택
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_LCONTROL) == KEY_UP)
	{
		m_iCameraType++;
		if (m_iCameraType > 3) m_iCameraType = 0;
		m_fCameraYaw = m_pCamera[m_iCameraType]->m_fCameraYawAngle;
		m_fCameraPitch = m_pCamera[m_iCameraType]->m_fCameraPitchAngle;
		// 카메라 타입이 교체되면 교체되는 카메라 타켓위치로 메인카메라의 타켓을 변경한다.
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
	// 반지름( 카메라의 목표 위치로 부터 떨어진 거리 ) 
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
	// 카메라 Y, X 축 회전 앵글
	//--------------------------------------------------------------------------------------
	if (I_Input.m_MouseState[0])
	{
		m_fCameraYaw += m_Timer.GetSPF() * I_Input.m_DIMouseState.lX;
		m_fCameraPitch += m_Timer.GetSPF() * I_Input.m_DIMouseState.lY;
	}
	//--------------------------------------------------------------------------------------
	// 카메라 행렬 계산
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
		// 현재 세팅된 뷰포트 정보 저장
		//-----------------------------------------------------------------------
		D3D11_VIEWPORT vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
		UINT nViewPorts = 1;
		m_pImmediateContext->RSGetViewports(&nViewPorts, vpOld);
		//-----------------------------------------------------------------------
		// 뷰포트
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
		// 기본 뷰포트 정보로 복원
		//-----------------------------------------------------------------------
		m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);
		//-----------------------------------------------------------------------
		// 뷰포트 번호 출력
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
		// 적용되어 있는 카메라 타입 표시
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
		// 적용되어 있는 카메라의 방향벡터 표시
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


	//확장자를 검출하기 위해 추가한 코드
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//I_CharMgr.Release();

	Load();
}




void CGciCharToolApp::OnCharsave()
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

				//CString name = "wqwkejqpwe"; // 매번 다른 이름
				//name.ReleaseBuffer();
				fprintf(fp, "\n");
			}

			fclose(fp);
		}

	}
	SetCurrentDirectory(current_path); // 원래 경로로 돌아 간다.

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
	// 기본 뷰포트 정보로 복원
	//-----------------------------------------------------------------------
	m_pImmediateContext->RSSetViewports(nViewPorts, vpOld);
	return GCoreLibV2::DrawDebug();
}
BOOL CGciCharToolApp::InitCamera() {
	// 4 종류의 카메라 세팅
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);

	//  좌측 뷰포트 4개의 각 카메라 행렬
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

	// 뷰포트에 들어 맞게 카메라 조정.
	m_pCamera[0].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[1].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[2].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));
	m_pCamera[3].get()->SetObjectView(D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(-2.0f, -2.0f, -2.0f));

	// 메인 카메라 뷰 행렬 세팅
	m_pMainCamera = make_shared<GModelCamera>();
	m_pMainCamera->SetViewMatrix(m_pCamera[m_iCameraType].get()->m_vCameraPos,
		m_pCamera[m_iCameraType].get()->m_vTargetPos,
		vUpVector);
	m_fRadius = D3DXVec3Length(&(m_pMainCamera.get()->m_vCameraPos - m_pMainCamera.get()->m_vTargetPos));

	// 투영행렬 세팅
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
