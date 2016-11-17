// GSaveMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GSaveMapDlg.h"
#include "afxdialogex.h"


// GSaveMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GSaveMapDlg, CDialogEx)

GSaveMapDlg::GSaveMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SAVEMAP, pParent)
	, m_strCharName(_T(""))
{

}

GSaveMapDlg::~GSaveMapDlg()
{

}

void GSaveMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strCharName);
}


BEGIN_MESSAGE_MAP(GSaveMapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &GSaveMapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &GSaveMapDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// GSaveMapDlg �޽��� ó�����Դϴ�.

//find ���µ� �ƴ�
void GSaveMapDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strCharName = dlg.GetFileName();
		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}

}


void GSaveMapDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
	
}
