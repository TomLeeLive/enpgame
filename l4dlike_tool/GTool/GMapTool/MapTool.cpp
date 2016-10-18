
// MapTool.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MapTool.h"
#include "MainFrm.h"

#include "MapToolDoc.h"
#include "MapToolView.h"

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


// CMapToolApp ����

//bool CMapToolApp::Init()
//{
//
//	if (FAILED(m_LineDraw.Create(GetDevice(), L"data/shader/line.hlsl")))
//	{
//		MessageBox(0, _T("m_LineDraw ����"), _T("Fatal error"), MB_OK);
//		return 0;
//	}
//
//	 TMapDesc�� 1Ÿ�Ͽ� ���� ������ ����ü�� n���� ����, ���� �� ���� 1.0f�� CellDistance, 0.1f??
//	TMapDesc MapDesc = { 8, 8, 1.0f, 0.1f,L"data/castle.jpg", L"CustomizeMap.hlsl" };
//	m_CustomMap.Init(GetDevice(), m_pImmediateContext);
//	if (FAILED(m_CustomMap.Load(MapDesc)))
//	{
//		return false;
//	}
//	if (FAILED(CreateResource()))
//	{
//		return false;
//	}
//	--------------------------------------------------------------------------------------
//	 ī�޶�  ��� 
//	--------------------------------------------------------------------------------------
//	SAFE_NEW(m_pMainCamera, GCamera);
//	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 30.0f, 0.0f),
//		D3DXVECTOR3(0.0f, 0.0f, 1.0f));
//	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
//		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
//		1.0f, 1000.0f);
//	return true;
//}
//
//bool CMapToolApp::Frame()
//{
//	 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
//	float t = cosf(m_Timer.GetElapsedTime())*0.5f;// *D3DX_PI;
//	for (int z = 0; z < m_CustomMap.m_iNumRows; z++)
//	{
//		for (int x = 0; x < m_CustomMap.m_iNumCols; x++)
//		{
//			int iIndex = z*m_CustomMap.m_iNumCols + x;
//			float fCos = cosf(t*x);
//			float fSin = sinf(t*z);
//			m_CustomMap.m_VertexList[iIndex].p.y =	fCos + fSin;
//		}
//	}
//	g_pImmediateContext->UpdateSubresource(
//		m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);
//
//	m_pMainCamera->Frame();
//	return m_CustomMap.Frame();
//
//}
//bool CMapToolApp::Render()
//{
//	DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthEnable);
//	DX::ApplyBS(m_pImmediateContext, DX::TDxState::g_pAlphaBlend);
//	m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
//	return m_CustomMap.Render(m_pImmediateContext);
//
//}
//
//bool CMapToolApp::Release()
//{
//	return m_CustomMap.Release();
//	return true;
//}
//bool CMapToolApp::DrawDebug()
//{
//	DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthDisable);
//
//	m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
//
//	D3DXVECTOR3 vStart(0, 0, 0);
//	D3DXVECTOR3 vEnd(1000, 0, 0);
//
//	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(1, 0, 0, 1.0f));
//	vEnd = D3DXVECTOR3(0, 1000, 0);
//
//	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 1, 0, 1.0f));
//	vEnd = D3DXVECTOR3(0, 0, 1000);
//
//	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 0, 1, 1.0f));
//	if (!GBasisLib_0::DrawDebug()) return false;
//	return true;
//}
//HRESULT CMapToolApp::CreateResource()
//{
//	HRESULT hr;
//	if (m_pMainCamera != nullptr)
//	{
//		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
//			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 1000.0f);
//	}
//	return S_OK;
//}
//HRESULT CMapToolApp::DeleteResource()
//{
//	HRESULT hr = S_OK;
//	if (m_pImmediateContext) m_pImmediateContext->ClearState();
//	return S_OK;
//}

bool CMapToolApp::Init()
{
	SAFE_NEW(m_pLine, GLineShape);
	if (FAILED(m_pLine->Create(GetDevice(), L"data/shader/line.hlsl")))

	{
		MessageBox(0, _T("m_pLIne ����"), _T("Fatal error"), MB_OK);
		return false;
	}
	//--------------------------------------------------------------------------------------
	// ���̸� ����
	//--------------------------------------------------------------------------------------
	m_Map.Init(m_pd3dDevice, m_pImmediateContext);
	m_Map.m_bStaticLight = true;
	if (FAILED(m_Map.CreateHeightMap(L"data/heightMap513.bmp")))
	{
		return false;
	}
	TMapDesc MapDesc = { m_Map.m_iNumRows,m_Map.m_iNumCols,	50.0f, 20.0f,L"data/detail.bmp",	L"QuadTree.hlsl" };
	//--------------------------------------------------------------------------------------
	//  �� ����
	//--------------------------------------------------------------------------------------
	//m_Map.Init( GetDevice(), m_pImmediateContext );
	//TMapDesc MapDesc = { pow(2.0f,11.0f)+1, pow(2.0f,11.0f)+1, 100.0f,1.0f, L"data/sand.jpg", L"QuadTree.hlsl" };
	if (!m_Map.Load(MapDesc))
	{
		return false;
	}

	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(-5000.0f, 1000.0f, -3000.0f), D3DXVECTOR3(-5000.0f, 1000.0f, 3000.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 10000.0f);
	//--------------------------------------------------------------------------------------
	// ī�޶� ���ν��� �������� �ڽ� ������Ʈ ����
	//--------------------------------------------------------------------------------------
	m_pMainCamera->CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/box.hlsl", "PS_Color"));

	//--------------------------------------------------------------------------------------
	// �̴ϸ� ������ �������� ����Ÿ�Ͽ� �ؽ�ó ����( �⺻ ī�޶� : ž�� ) 
	//--------------------------------------------------------------------------------------
	if (!m_MiniMap.Create(GetDevice(), L"data/shader/plane.hlsl"))
	{
		return false;
	}
	m_MiniMap.Set(GetDevice(), 0, m_SwapChainDesc.BufferDesc.Height - 300, 300, 300);
	m_MiniMap.SetViewMatrix(D3DXVECTOR3(0.0f, 35000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_MiniMap.SetProjMatrix(D3DX_PI * 0.25f, 1.0f, 0.1f, 100000.0f);

	// ������ ���� �� ������ ���Ϸ� ���ҵǴ� ���� �����Ѵ�.
	// �������� �ּ� ������ = ������ ���� �� ������ * m_QuadTree.m_fMinDivideSize;
	m_QuadTree.m_iMaxDepthLimit = 5;
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	m_QuadTree.SetMinDivideSize(m_QuadTree.m_fMinDivideSize * m_Map.m_fSellDistance);
	m_QuadTree.Build(&m_Map, m_Map.m_iNumCols, m_Map.m_iNumRows);

	m_pTexture[0].Attach(DX::CreateShaderResourceView(GetDevice(), L"data/sand.jpg"));
	m_pTexture[1].Attach(DX::CreateShaderResourceView(GetDevice(), L"data/grass_2.jpg"));
	m_pTexture[2].Attach(DX::CreateShaderResourceView(GetDevice(), L"data/rock.jpg"));
	m_pTexture[3].Attach(DX::CreateShaderResourceView(GetDevice(), L"data/snow.jpg"));
	return true;
}

bool CMapToolApp::Render()
{
	ApplySS(m_pImmediateContext, GDxState::g_pSSMirrorLinear);
	m_Map.SetMatrix(0, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_Map.m_cbData.Color = D3DXVECTOR4(0.0f, 0.3f, 0.5f, 0.8f);
	m_pImmediateContext->PSSetConstantBuffers(0, 1, m_Map.m_dxobj.g_pConstantBuffer.GetAddressOf());

	m_pImmediateContext->PSSetShaderResources(1, 4, m_pTexture[0].GetAddressOf());
	//if( !m_Map.Render(m_pImmediateContext) ) return false;
	m_QuadTree.Render(m_pImmediateContext);

	//DrawQuadLine( m_QuadTree.m_pRootNode );
	//--------------------------------------------------------------------------------------
	// �̴ϸ��� ����Ÿ�� �ؽ�ó�� ž�� ������
	//--------------------------------------------------------------------------------------
	DrawMiniMap();
	return true;
}

void CMapToolApp::DrawMiniMap()
{
	ID3D11ShaderResourceView *const pSRV[1] = { NULL };
	m_pImmediateContext->PSSetShaderResources(0, 1, pSRV);
	ApplyBS(m_pImmediateContext, GDxState::g_pAlphaBlend);

	D3DXMATRIX matScale, matRotation;
	if (m_MiniMap.BeginRender(m_pImmediateContext))
	{
		m_Map.SetMatrix(0, &m_MiniMap.m_matView, &m_MiniMap.m_matProj);
		m_Map.Render(m_pImmediateContext);

		m_pMainCamera->SetMatrix(NULL, &m_MiniMap.m_matView, &m_MiniMap.m_matProj);
		m_pMainCamera->PreRender(m_pImmediateContext);
		{
			m_pImmediateContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);
			m_pMainCamera->PostRender(m_pImmediateContext);
		}
		m_MiniMap.EndRender(m_pImmediateContext);
	}
	//--------------------------------------------------------------------------------------
	// ����Ÿ���� �ؽ�ó�� �̴ϸ� ������ ������
	//--------------------------------------------------------------------------------------
	ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthDisable);
	ApplyBS(m_pImmediateContext, GDxState::g_pBSOneZero);
	m_MiniMap.Render(m_pImmediateContext);
}
bool CMapToolApp::DrawQuadLine(GNode* pNode)
{
	if (pNode == NULL) return true;

	if (m_QuadTree.m_iRenderDepth >= pNode->m_iDepth)
	{
		m_pLine->SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		D3DXVECTOR4 vColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 0) vColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 1) vColor = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 2) vColor = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 3) vColor = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 4) vColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		if (pNode->m_iDepth == 5) vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 6) vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		if (pNode->m_iDepth == 7) vColor = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 8) vColor = D3DXVECTOR4(1.0f, 0.5f, 0.5f, 1.0f);
		if (pNode->m_iDepth == 9) vColor = D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f);

		D3DXVECTOR3 vPoint[4];
		vPoint[0] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[0].y -= 1.0f * pNode->m_iDepth;
		vPoint[1] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMax.z);
		vPoint[1].y -= 1.0f * pNode->m_iDepth;
		vPoint[2] = D3DXVECTOR3(pNode->m_tBox.vMin.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[2].y -= 1.0f * pNode->m_iDepth;
		vPoint[3] = D3DXVECTOR3(pNode->m_tBox.vMax.x, pNode->m_tBox.vMax.y, pNode->m_tBox.vMin.z);
		vPoint[3].y -= 1.0f * pNode->m_iDepth;

		m_pLine->Draw(m_pImmediateContext, vPoint[0], vPoint[1], vColor);
		m_pLine->Draw(m_pImmediateContext, vPoint[1], vPoint[3], vColor);
		m_pLine->Draw(m_pImmediateContext, vPoint[2], vPoint[3], vColor);
		m_pLine->Draw(m_pImmediateContext, vPoint[0], vPoint[2], vColor);
	}
	for (int iNode = 0; iNode < pNode->m_ChildList.size(); iNode++)
	{
		DrawQuadLine(pNode->m_ChildList[iNode]);
	}
	return true;
}
bool CMapToolApp::Release()
{
	SAFE_DEL(m_pLine);
	m_Map.Release();
	return true;
}
bool CMapToolApp::Frame()
{
	m_pMainCamera->Frame();
	if (I_Input.KeyCheck(DIK_F4) == KEY_UP)
	{
		if (++m_iDrawDepth > 7) m_iDrawDepth = -1;
		m_QuadTree.SetRenderDepth(m_iDrawDepth);
	}
	m_QuadTree.Frame();
	//m_Map.Frame();
	//--------------------------------------------------------------------------------------
	// �̴ϸ� ����
	//--------------------------------------------------------------------------------------
	return m_MiniMap.Frame();
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
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
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
	RECT			rc;
	str.clear();
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Depth Control Key[F4] : Current Depth: %d\n"), m_iDrawDepth);
	str += pBuffer;

	_stprintf_s(pBuffer, _T("Look:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vLookVector.x,
		m_pMainCamera->m_vLookVector.y,
		m_pMainCamera->m_vLookVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Up:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vUpVector.x,
		m_pMainCamera->m_vUpVector.y,
		m_pMainCamera->m_vUpVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Right:%10.4f,%10.4f,%10.4f \n"), m_pMainCamera->m_vRightVector.x,
		m_pMainCamera->m_vRightVector.y,
		m_pMainCamera->m_vRightVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("p:%10.4f,%10.4f,%10.4f "), m_pMainCamera->m_vCameraPos.x,
		m_pMainCamera->m_vCameraPos.y,
		m_pMainCamera->m_vCameraPos.z);
	str += pBuffer;

	rc.left = 0;
	rc.top = 100;
	rc.right = m_DefaultRT.m_vp.Width;
	rc.bottom = m_DefaultRT.m_vp.Height;
	DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	return GBasisLib_0::DrawDebug();
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

	GBasisLib_0::GInit();

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



