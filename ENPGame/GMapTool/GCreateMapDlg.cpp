// GCreateMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "GCreateMapDlg.h"
#include "afxdialogex.h"


// GCreateMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GCreateMapDlg, CDialogEx)

GCreateMapDlg::GCreateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEMAP, pParent)
	, m_iTileWidth(0)
	, m_iTileHeight(0)
	, m_fCellDistance(0)
	, m_strCharName(_T(""))
{

}

GCreateMapDlg::~GCreateMapDlg()
{
}

void GCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iTileWidth);
	DDX_Text(pDX, IDC_EDIT6, m_iTileHeight);
	DDX_Control(pDX, IDC_COMBO2, m_cbCellCount);
	DDX_Text(pDX, IDC_EDIT3, m_fCellDistance);
	DDX_Text(pDX, IDC_EDIT7, m_strCharName);
}


BEGIN_MESSAGE_MAP(GCreateMapDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON1, &GCreateMapDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// GCreateMapDlg �޽��� ó�����Դϴ�.


BOOL GCreateMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_cbCellCount.InsertString(0, L"2*2");
	m_cbCellCount.InsertString(1, L"3*3");
	m_cbCellCount.InsertString(2, L"4*4");
	m_cbCellCount.InsertString(3, L"8*8");
	m_cbCellCount.InsertString(4, L"16*16");
	m_cbCellCount.InsertString(5, L"32*32");


	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_iTileWidth = 16;
	m_iTileHeight = 16;
	m_fCellDistance = 1.0f;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void GCreateMapDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	UpdateData(TRUE);

	CDialogEx::OnOK();
}



void GCreateMapDlg::OnBnClickedButton1()
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
