
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
	// �ڽ� ������Ʈ ����( 100�� �ڽ��� �����ؼ� �����)
	//--------------------------------------------------------------------------------------
	//SAFE_NEW(m_pBoxs, GBoxShape);
	//if (m_pBoxs->Create(GetDevice(), L"data/shader/box.hlsl", L"data/oldwood.dds") == false)
	//{
	//	MessageBox(0, _T("m_pDirectionLIne ����"), _T("Fatal error"), MB_OK);
	//	return 0;
	//}
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


	//SAFE_NEW_ARRAY(m_pMapObj, GMapObject, NUM_OBJECTS);

	//--------------------------------------------------------------------------------------
	// ������ �� ����
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
	m_QuadTree.Build(&m_NoiseMap, m_NoiseMap.m_iNumCols, m_NoiseMap.m_iNumRows); //��������

	//--------------------------------------------------------------------------------------
	// ����Ʈ���� ������Ʈ �߰�
	//--------------------------------------------------------------------------------------		
	//for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	//{
	//	m_pMapObj[iBox].m_vPosition.y = m_NoiseMap.GetHeight(m_pMapObj[iBox].m_vPosition.x, m_pMapObj[iBox].m_vPosition.z) + 5.0f;
	//	m_pMapObj[iBox].Update();
	//	m_QuadTree.AddObject(&m_pMapObj[iBox]);
	//}

	//--------------------------------------------------------------------------------------
	// �̴ϸ� ������ �������� ����Ÿ�Ͽ� �ؽ�ó ����( �⺻ ī�޶� : ž�� ) 
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
	// ȭ�� ����� ���� ��� 
	//--------------------------------------------------------------------------------------
	if (I_Input.KeyCheck(DIK_F2) == KEY_UP)
		m_NoiseMap.SetHurstIndex(), m_QuadTree.UpdateBoundingBox(m_QuadTree.m_pRootNode);
	if (I_Input.KeyCheck(DIK_F3) == KEY_UP)
		m_NoiseMap.SetHurstIndex(false); //��������
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
	if (I_Input.KeyCheck(DIK_GRAVE) == KEY_UP) //���ΰ� ��� ~
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
	// �̴ϸ� ����
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
	// ����Ʈ���� ������ ���� ���� ������
	//--------------------------------------------------------------------------------------
	DrawSelectTreeLevel(m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

	if (m_bDebugRender)
	{
		DrawQuadLine(m_QuadTree.m_pRootNode);
	}

	//--------------------------------------------------------------------------------------
	// �̴ϸ��� ����Ÿ�� �ؽ�ó�� ž�� ������
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
	// �Ʒ��� ���� �޼��� ���� ���̴� ���ҽ��� �ʱ�ȭ �ϸ� �ȴ�.
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
	// ����Ÿ���� �ؽ�ó�� �̴ϸ� ������ ������
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// ����Ÿ���� �ؽ�ó�� �̴ϸ� ������ ������
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
	// ����Ǿ� �ִ� ī�޶��� ���⺤�� ǥ��
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
	m_bDebugRender = true;
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



