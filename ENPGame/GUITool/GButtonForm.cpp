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
	: CFormView(IDD_GMODELFORM)
	, m_fMinX(0)
	, m_fMinY(0)
	, m_fMinZ(0)
	, m_fMaxX(0)
	, m_fMaxY(0)
	, m_fMaxZ(0)
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
}

BEGIN_MESSAGE_MAP(GButtonForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &GButtonForm::OnBnClickedButton1)
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
