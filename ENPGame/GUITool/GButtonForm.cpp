// GButtonForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GButtonForm.h"


// GButtonForm

IMPLEMENT_DYNCREATE(GButtonForm, CFormView)

//추가함_S
GButtonForm* GButtonForm::CreateOne(CWnd* pParent) {

	GButtonForm* pane = new GButtonForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E



GButtonForm::GButtonForm()
	: CFormView(IDD_GBUTTONFORM)
	, m_fMinX(0)
	, m_fMinY(0)
	, m_fMinZ(0)
	, m_fMaxX(0)
	, m_fMaxY(0)
	, m_fMaxZ(0)
	, m_fGuageValue(0)
{
}

GButtonForm::~GButtonForm()
{
}

void GButtonForm::UpdateTextOBBInfo(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax) {
	/*
	// CString -> int convert
	CString strNum = _T("5");
	int nNum = _ttoi(strNum);

	// int -> CString convert
	int nNum = 5;
	CString strNum;
	strNum.Format(_T("%d"), nNum);
	*/
	CString strMinX;
	strMinX.Format(_T("%f"), vMin.x);
	CString strMinY;
	strMinY.Format(_T("%f"), vMin.y);
	CString strMinZ;
	strMinZ.Format(_T("%f"), vMin.z);
	CString strMaxX;
	strMaxX.Format(_T("%f"), vMax.x);
	CString strMaxY;
	strMaxY.Format(_T("%f"), vMax.y);
	CString strMaxZ;
	strMaxZ.Format(_T("%f"), vMax.z);


	//SetDlgItemText(g_hWnd,IDC_MIN_X, strMinX);
	//SetDlgItemText(g_hWnd, IDC_MIN_Y, strMinY);
	//SetDlgItemText(g_hWnd, IDC_MIN_Z, strMinZ);
	//SetDlgItemText(g_hWnd, IDC_MAX_X, strMaxX);
	//SetDlgItemText(g_hWnd, IDC_MAX_Y, strMaxY);
	//SetDlgItemText(g_hWnd, IDC_MAX_Z, strMaxZ);

	GetDlgItem(IDC_MIN_X)->SetWindowText(strMinX);
	GetDlgItem(IDC_MIN_Y)->SetWindowText(strMinY);
	GetDlgItem(IDC_MIN_Z)->SetWindowText(strMinZ);
	GetDlgItem(IDC_MAX_X)->SetWindowText(strMaxX);
	GetDlgItem(IDC_MAX_Y)->SetWindowText(strMaxY);
	GetDlgItem(IDC_MAX_Z)->SetWindowText(strMaxZ);

}

void GButtonForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MIN_X, m_fMinX);
	DDX_Text(pDX, IDC_MIN_Y, m_fMinY);
	DDX_Text(pDX, IDC_MIN_Z, m_fMinZ);
	DDX_Text(pDX, IDC_MAX_X, m_fMaxX);
	DDX_Text(pDX, IDC_MAX_Y, m_fMaxY);
	DDX_Text(pDX, IDC_MAX_Z, m_fMaxZ);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Text(pDX, IDC_GUAGE_VALUE, m_fGuageValue);
}

BEGIN_MESSAGE_MAP(GButtonForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &GButtonForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &GButtonForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &GButtonForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GButtonForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &GButtonForm::OnBnClickedButton5)
	ON_LBN_DBLCLK(IDC_LIST2, &GButtonForm::OnLbnDblclkList2)
	ON_EN_CHANGE(IDC_GUAGE_VALUE, &GButtonForm::OnEnChangeGuageValue)
END_MESSAGE_MAP()


// GButtonForm 진단입니다.

#ifdef _DEBUG
void GButtonForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GButtonForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GButtonForm 메시지 처리기입니다.


void GButtonForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 텍스트 정보 가져와서 바운딩 박스 업데이트 함.

	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();


	CString strMinX, strMinY, strMinZ, strMaxX, strMaxY, strMaxZ;

	GetDlgItem(IDC_MIN_X)->GetWindowText(strMinX);
	GetDlgItem(IDC_MIN_Y)->GetWindowText(strMinY);
	GetDlgItem(IDC_MIN_Z)->GetWindowText(strMinZ);
	GetDlgItem(IDC_MAX_X)->GetWindowText(strMaxX);
	GetDlgItem(IDC_MAX_Y)->GetWindowText(strMaxY);
	GetDlgItem(IDC_MAX_Z)->GetWindowText(strMaxZ);

	m_fMinX = _ttof(strMinX);
	m_fMinY = _ttof(strMinY);
	m_fMinZ = _ttof(strMinZ);
	m_fMaxX = _ttof(strMaxX);
	m_fMaxY = _ttof(strMaxY);
	m_fMaxZ = _ttof(strMaxZ);

	D3DXVECTOR3 vMin = D3DXVECTOR3(m_fMinX, m_fMinY, m_fMinZ);
	D3DXVECTOR3 vMax = D3DXVECTOR3(m_fMaxX, m_fMaxY, m_fMaxZ);

	if (pApp->m_FileExt == G_TOOL_EXT_GUI) {
//		GBBOXFUNC::initBox(&pApp->m_HeroObj[0].get()->m_OBB, vMin, vMax);
	}
	if (pApp->m_FileExt == G_TOOL_EXT_GBS) {
//		GBBOXFUNC::initBox(&pApp->m_tbsobj.m_OBB, vMin, vMax);
	}

}



void GButtonForm::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	if (!pApp->LoadFileDlg(_T("*"), _T("이미지 image add")))
	{
		return;
	}

	int iLoad = pApp->m_LoadFiles.size() - 1;

	pApp->m_UIManager.UICreate(GUI_TYPE_IMAGE, &pApp->m_LoadFiles[iLoad], &SwapChainDesc);

	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), pApp->m_UIManager.m_pUIList.size() - 1, L" 이미지");
	m_List.AddString(szRet);
}


void GButtonForm::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	if (!pApp->LoadFileDlg(_T("*"), _T("버튼 image add")))
	{
		return;
	}
	int iLoad = pApp->m_LoadFiles.size() - 1;

	pApp->m_UIManager.UICreate(GUI_TYPE_BUTTON, &pApp->m_LoadFiles[iLoad], &SwapChainDesc);

	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), pApp->m_UIManager.m_pUIList.size() - 1,L" 버튼");
	m_List.AddString(szRet);
}


void GButtonForm::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC	SwapChainDesc;
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	if (!pApp->LoadFileDlg(_T("*"), _T("Guage image add")))
	{
		return;
	}
	int iLoad = pApp->m_LoadFiles.size() - 1;

	pApp->m_UIManager.UICreate(GUI_TYPE_BUTTONHALF, &pApp->m_LoadFiles[iLoad], &SwapChainDesc);

	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), pApp->m_UIManager.m_pUIList.size()-1, L" Guage");
	m_List.AddString(szRet);
}


void GButtonForm::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;

	GetDlgItem(IDC_GUAGE_VALUE)->GetWindowText(strValue);

	m_fGuageValue = _ttof(strValue);

	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();

	if (pApp->m_UIManager.m_pSelectPlane != NULL )
	{
		if (pApp->m_UIManager.m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF) {
			((GButtonHalfCtl*)pApp->m_UIManager.m_pSelectPlane)->SetXSize(m_fGuageValue);
			//pApp->m_UIManager.m_pSelectPlane->Update();
		}
		else {
			//MessageBox(g_hWnd, "마우스 왼쪽 버튼을 눌렀습니다", "메시지 박스", MB_OK);
		}
	}
}


void GButtonForm::OnLbnDblclkList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelected = m_List.GetCurSel();
	CGUIToolApp *pApp = (CGUIToolApp *)AfxGetApp();
	
	GControlUI* pSelect = pApp->m_UIManager.m_pUIList[iSelected];

	if (pSelect != NULL && pApp->m_UIManager.m_pSelectPlane != pSelect)
	{
		pApp->m_UIManager.m_pSelectPlane = pSelect;
	}
}


void GButtonForm::OnEnChangeGuageValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
