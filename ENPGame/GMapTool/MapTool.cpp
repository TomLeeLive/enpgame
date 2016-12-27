
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


bool CMapToolApp::CreateInit(int Width, int Height, float Distance, CString strTex)
{
	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 3000.0f);
	//--------------------------------------------------------------------------------------
	//  �� ����
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
	//  ���� Ʈ��
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(m_MapDesc.iNumCols, m_MapDesc.iNumRows);
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	return true;
}

// CMapToolApp ����
bool CMapToolApp::Init()
{
	//--------------------------------------------------------------------------------------
	// ����� ���� ����
	//--------------------------------------------------------------------------------------
	if (FAILED(m_DrawLine.Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_DrawLine ����"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
	m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 3000.0f);

	//--------------------------------------------------------------------------------------
	// ī�޶� ���ν��� �������� �ڽ� ������Ʈ ����
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
	//2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;

	//--------------------------------------------------------------------------------------
	// QuadTree Frame
	//--------------------------------------------------------------------------------------
	if (m_MapDesc.iNumCols > 0 || m_MapDesc.iNumRows > 0)
	{
		g_pImmediateContext->UpdateSubresource(
			m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

		m_CustomMap.Frame();

		// ����Ʈ��
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
	// ����Ǿ� �ִ� ī�޶��� ���⺤�� ǥ��
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
	m_iDrawDepth = 0;
	m_bDebugRender = false;
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



