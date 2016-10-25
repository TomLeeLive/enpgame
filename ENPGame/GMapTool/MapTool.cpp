
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
	// 박스 오브젝트 생성( 100개 박스가 공유해서 사용함)
	//--------------------------------------------------------------------------------------
	//SAFE_NEW(m_pBoxs, GBoxShape);
	//if (m_pBoxs->Create(GetDevice(), L"data/shader/box.hlsl", L"data/oldwood.dds") == false)
	//{
	//	MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}
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


	//SAFE_NEW_ARRAY(m_pMapObj, GMapObject, NUM_OBJECTS);

	//--------------------------------------------------------------------------------------
	// 노이즈 맵 생성
	//--------------------------------------------------------------------------------------
	m_NoiseMap.Init(GetDevice(), m_pImmediateContext);
	//TMapDesc MapDesc = { pow(2.0f,7.0f) + 1, pow(2.0f,7.0f) + 1, 10.0f, 1.0f, L"data/sand.jpg", L"data/shader/box.hlsl" };
	TMapDesc MapDesc = { pow(2.0f,3.0f) + 1, pow(2.0f,3.0f) + 1, 10.0f, 1.0f, L"data/sand.jpg", L"data/shader/box.hlsl" };
	if (!m_NoiseMap.Load(MapDesc))
	{
		return false;
	}
	m_QuadTree.SetMinDivideSize(10);
	m_QuadTree.SetMaxDepthLimit(7);
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	m_QuadTree.Build(&m_NoiseMap, m_NoiseMap.m_iNumCols, m_NoiseMap.m_iNumRows); //가져오기

	//--------------------------------------------------------------------------------------
	// 쿼드트리에 오브젝트 추가
	//--------------------------------------------------------------------------------------		
	//for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	//{
	//	m_pMapObj[iBox].m_vPosition.y = m_NoiseMap.GetHeight(m_pMapObj[iBox].m_vPosition.x, m_pMapObj[iBox].m_vPosition.z) + 5.0f;
	//	m_pMapObj[iBox].Update();
	//	m_QuadTree.AddObject(&m_pMapObj[iBox]);
	//}

	//--------------------------------------------------------------------------------------
	// 미니맵 영역에 랜더링할 랜더타켓용 텍스처 생성( 기본 카메라 : 탑뷰 ) 
	//--------------------------------------------------------------------------------------
	//if (!m_MiniMap.Create(GetDevice(), L"data/shader/plane.hlsl"))
	//{
	//	return false;
	//}
	//m_MiniMap.Set(GetDevice(), 0, m_SwapChainDesc.BufferDesc.Height - 300, 300, 300);

	//DWORD dwWidth = m_MiniMap.m_pMiniMapRT->m_TexDesc.Width;
	//DWORD dwHeight = m_MiniMap.m_pMiniMapRT->m_TexDesc.Height;
	//D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	//m_MiniMap.SetViewMatrix(D3DXVECTOR3(0.0f, 3000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), vUpVector);
	//m_MiniMap.SetProjMatrix(D3DX_PI * 0.25f, (float)dwWidth / (float)dwHeight, 0.1f, 10000.0f);

	return true;
}
bool CMapToolApp::Frame()
{
	m_pMainCamera->Frame();
	if (I_Input.KeyCheck(DIK_F1) == KEY_UP)
	{
		if (++m_iDrawDepth > 7) m_iDrawDepth = -1;
		m_QuadTree.SetRenderDepth(m_iDrawDepth);
	}
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	//--------------------------------------------------------------------------------------
	// 화면 디버그 정보 출력 
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_F2) == KEY_UP)
		m_NoiseMap.SetHurstIndex(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F3) == KEY_UP)
		m_NoiseMap.SetHurstIndex(false); //가져오기
		m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F4) == KEY_UP)m_NoiseMap.SetLacunarity(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F5) == KEY_UP)m_NoiseMap.SetLacunarity(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F6) == KEY_UP)m_NoiseMap.SetOctaves(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F7) == KEY_UP)m_NoiseMap.SetOctaves(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);

	if (I_Input.KeyCheck(DIK_F8) == KEY_UP)m_NoiseMap.SetPersistence(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F9) == KEY_UP)m_NoiseMap.SetPersistence(false), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);


	if (I_Input.KeyCheck(DIK_U) == KEY_UP)
	{
		m_NoiseMap.SetNoiseType(0);
		m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	}
	if (I_Input.KeyCheck(DIK_I) == KEY_UP)
	{
		m_NoiseMap.SetNoiseType(1);
		m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
		m_bDebugRender = !m_bDebugRender;
	}
	if (I_Input.KeyCheck(DIK_GRAVE) == KEY_UP) //문턱값 사용 ~
	{
		m_QuadTree.SetThresHold(!m_QuadTree.m_bThresHoldValue);
	}



	m_QuadTree.Frame();
	if (m_QuadTree.m_bDynamicUpdateIB == true)
	{
		m_NoiseMap.UpdateIndexBuffer(m_pImmediateContext, m_QuadTree.m_IndexList, m_QuadTree.m_iNumFace);
	}
	m_NoiseMap.Frame();
	//--------------------------------------------------------------------------------------
	// 미니맵 갱신
	//--------------------------------------------------------------------------------------
	//m_MiniMap.Frame();
	return true; 
}
bool CMapToolApp::Render()
{
	m_NoiseMap.SetMatrix(0, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	if (m_QuadTree.m_bDynamicUpdateIB == true)
	{
		if (!m_NoiseMap.Render(m_pImmediateContext)) return false;
	}
	else
	{
		if (!m_QuadTree.Render(m_pImmediateContext)) return false;
	}
	//--------------------------------------------------------------------------------------
	// 쿼드트리의 임의의 레벨 선텍 랜더링
	//--------------------------------------------------------------------------------------
	DrawSelectTreeLevel(m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

	if (m_bDebugRender)
	{
		DrawQuadLine(m_QuadTree.m_pRootNode);
	}

	//--------------------------------------------------------------------------------------
	// 미니맵의 랜더타켓 텍스처에 탑뷰 랜더링
	//--------------------------------------------------------------------------------------
	//DrawMiniMap();
	return true;
}
bool CMapToolApp::Release()
{
	m_NoiseMap.Release();
	m_QuadTree.Release();
	//SAFE_DEL(m_pBoxs);
	//SAFE_DELETE_ARRAY(m_pMapObj);
	return true;
}
void CMapToolApp::DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	//for (int iObj = 0; iObj < m_QuadTree.m_DrawObjList.size(); iObj++)
	//{
	//	GMapObject* pBox = dynamic_cast<GMapObject*>(m_QuadTree.m_DrawObjList[iObj]);
	//	m_pBoxs->SetAmbientColor(pBox->m_vColor.x, pBox->m_vColor.y, pBox->m_vColor.z, pBox->m_vColor.w);
	//	m_pBoxs->SetMatrix(&pBox->m_matWorld, pView, pProj);
	//	m_pBoxs->Render(m_pImmediateContext);
	//}
}
void CMapToolApp::DrawMiniMap()
{
	// 아래와 같은 메세지 경고시 쉐이더 리소스를 초기화 하면 된다.
	//ID3D11Device::OMSetRenderTargets: Resource being set to OM RenderTarget slot 0 is still bound on input! [ STATE_SETTING WARNING #9: DEVICE_OMSETRENDERTARGETS_HAZARD ]
	ID3D11ShaderResourceView *const pSRV[1] = { NULL };
	m_pImmediateContext->PSSetShaderResources(0, 1, pSRV);
	ApplyBS(m_pImmediateContext, GDxState::g_pAlphaBlend);

	D3DXMATRIX matScale, matRotation;
	//if (m_MiniMap.BeginRender(m_pImmediateContext))
	//{
	//	m_NoiseMap.SetMatrix(0, &m_MiniMap.m_matView, &m_MiniMap.m_matProj);
	//	if (m_QuadTree.m_bDynamicUpdateIB == true)
	//	{
	//		m_NoiseMap.Render(m_pImmediateContext);
	//	}
	//	else
	//	{
	//		m_QuadTree.Render(m_pImmediateContext);
	//	}
	//	DrawSelectTreeLevel(&m_MiniMap.m_matView, &m_MiniMap.m_matProj);

	//	m_pMainCamera->SetMatrix(NULL, &m_MiniMap.m_matView, &m_MiniMap.m_matProj);
	//	m_pMainCamera->PreRender(m_pImmediateContext);
	//	{
	//		m_pImmediateContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);
	//		m_pMainCamera->PostRender(m_pImmediateContext);
	//	}
	//	m_MiniMap.EndRender(m_pImmediateContext);
	//}

	//--------------------------------------------------------------------------------------
	// 랜더타켓의 텍스처를 미니맵 영역에 랜더링
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// 랜더타켓의 텍스처를 미니맵 영역에 랜더링
	//--------------------------------------------------------------------------------------
	//ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthDisable);
	//ApplyBS(m_pImmediateContext, GDxState::g_pBSOneZero);
	//m_MiniMap.Render(m_pImmediateContext);
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
	RECT			rc;
	str.clear();
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Depth Control Key[F4] : Current Depth: %d %d\n"), m_iDrawDepth, g_InputData.iMouseValue[1]);
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
	m_bDebugRender = true;
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

	GBasisLib_0::GInit();

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



