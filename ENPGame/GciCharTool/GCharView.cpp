// TCharView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GciCharTool.h"
#include "GCharView.h"
#include "afxdialogex.h"


// TCharView 대화 상자입니다.

IMPLEMENT_DYNAMIC(GCharView, CDialogEx)

GCharView::GCharView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHARACTERVIEW, pParent)
	, m_strCharName(_T(""))
	, m_bSolidRender(FALSE)
	, m_iState0(FALSE)
{

}

GCharView::~GCharView()
{
}

void GCharView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CHARNAME, m_strCharName);
	DDX_Control(pDX, IDC_TREE1, m_TreeCharCtl);
	DDX_Control(pDX, IDC_LIST1, m_CharListCtl);
	DDX_Check(pDX, IDC_CHECK1, m_bSolidRender);
	DDX_Radio(pDX, IDC_RADIO3, m_iState0);
}


BEGIN_MESSAGE_MAP(GCharView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &GCharView::OnBnClickedButton1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &GCharView::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// TCharView 메시지 처리기입니다.


void GCharView::OnBnClickedButton1()
{
	// 파일 선택 대화상자
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strCharName = dlg.GetFileName();
		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}

	HTREEITEM hItem;
	hItem = m_TreeCharCtl.InsertItem(L"bip01", 0, 0, TVI_ROOT );
			m_TreeCharCtl.InsertItem(L"bip02", 0, 0, hItem);
			hItem = m_TreeCharCtl.InsertItem(L"bip03", 0, 0, hItem);
					m_TreeCharCtl.InsertItem(L"bip04", 0, 0, hItem);
					m_TreeCharCtl.InsertItem(L"bip05", 0, 0, hItem);

					m_TreeCharCtl.EnsureVisible(hItem);

	hItem = m_TreeCharCtl.InsertItem(L"bip_01", 0, 0, TVI_ROOT);
					m_TreeCharCtl.InsertItem(L"bip_02", 0, 0, hItem);
					hItem = m_TreeCharCtl.InsertItem(L"bip_03", 0, 0, hItem);
					m_TreeCharCtl.InsertItem(L"bip_04", 0, 0, hItem);
					m_TreeCharCtl.InsertItem(L"bip_05", 0, 0, hItem);

					m_TreeCharCtl.EnsureVisible(hItem);
	
	//
					m_CharListCtl.InsertItem(0, L"aaaaa",0);
					m_CharListCtl.InsertItem(1, L"bbbb", 0);
					m_CharListCtl.InsertItem(2, L"ccc", 0);
					m_CharListCtl.InsertItem(3, L"dddd", 0);
}


void GCharView::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString item = 
		m_TreeCharCtl.GetItemText(pNMTreeView->itemNew.hItem);
	m_strCharName = item;
	UpdateData(FALSE);

	//GetDlgItem(IDC_CHARNAME)->SetWindowText(item);

	*pResult = 0;
}
