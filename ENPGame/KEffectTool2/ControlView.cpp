// ControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "ControlView.h"

#define SAFE_DELETE(p) {if(p){delete p; p=NULL;}}
// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(IDD_CONTROLVIEW)
{
	m_2dDlgTap = NULL;
	m_3dDlgTap = NULL;
	m_ParticleTap = NULL;
}

CControlView::~CControlView()
{
	SAFE_DELETE(m_2dDlgTap);
	SAFE_DELETE(m_3dDlgTap);
	SAFE_DELETE(m_ParticleTap);
	
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_ctlTap);
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CControlView::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CControlView 진단입니다.

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView 메시지 처리기입니다.


void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 탭 생성
	m_ctlTap.DeleteAllItems();
	m_ctlTap.InsertItem(0, L"2D");
	m_ctlTap.InsertItem(1, L"3D");
	m_ctlTap.InsertItem(2, L"Particle");

	CRect rect;
	//2D 탭 생성
	m_2dDlgTap = new C2dDlgTap;
	m_2dDlgTap->Create(IDD_DIALOG1, &m_ctlTap);
	m_2dDlgTap->GetWindowRect(&rect);
	m_2dDlgTap->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_2dDlgTap->ShowWindow(SW_SHOW);

	//2D 탭 생성
	m_3dDlgTap = new C3dDlgTap;
	m_3dDlgTap->Create(IDD_DIALOG2, &m_ctlTap);
	m_3dDlgTap->GetWindowRect(&rect);
	m_3dDlgTap->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_3dDlgTap->ShowWindow(SW_SHOW);

	//2D 탭 생성
	m_ParticleTap = new CPartiCleTap;
	m_ParticleTap->Create(IDD_DIALOG3, &m_ctlTap);
	m_ParticleTap->GetWindowRect(&rect);
	m_ParticleTap->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_ParticleTap->ShowWindow(SW_SHOW);
	UpdateData(FALSE);

	
}

void CControlView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int select = m_ctlTap.GetCurSel();

	switch (select)
	{
	case 0:
		m_2dDlgTap->ShowWindow(SW_SHOW);
		m_3dDlgTap->ShowWindow(SW_HIDE);
		m_ParticleTap->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_2dDlgTap->ShowWindow(SW_HIDE);
		m_3dDlgTap->ShowWindow(SW_SHOW);
		m_ParticleTap->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_2dDlgTap->ShowWindow(SW_HIDE);
		m_3dDlgTap->ShowWindow(SW_HIDE);
		m_ParticleTap->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
