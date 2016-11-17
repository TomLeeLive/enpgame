// GSaveMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GSaveMapDlg.h"
#include "afxdialogex.h"


// GSaveMapDlg 대화 상자입니다.

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


// GSaveMapDlg 메시지 처리기입니다.

//find 였는데 아님
void GSaveMapDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	
}
