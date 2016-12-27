// GCreateMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
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
	, m_strHeight(_T(""))
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
	DDX_Text(pDX, IDC_EDIT8, m_strHeight);
}


BEGIN_MESSAGE_MAP(GCreateMapDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON1, &GCreateMapDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT7, &GCreateMapDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON4, &GCreateMapDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// GCreateMapDlg �޽��� ó�����Դϴ�.


BOOL GCreateMapDlg::OnInitDialog()
{//1
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

//�������� Ȯ�� ��ư
void GCreateMapDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	UpdateData(TRUE);

	CDialogEx::OnOK();

	theApp.m_MapMgr.CreateInit(m_iTileWidth, m_iTileHeight, m_fCellDistance, m_strCharName,theApp.m_pMainCamera.get());
	//theApp.CreateInit(m_iTileWidth, m_iTileHeight, m_fCellDistance, m_strCharName);

}


// �ؽ��� ã��
void GCreateMapDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strCharName = dlg.GetFileName();
		//m_strCharName = dlg.GetPathName();

		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}

}


//HeightMap
void GCreateMapDlg::OnBnClickedButton4()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strHeight = dlg.GetFileName();
		//m_strCharName = dlg.GetPathName();

		UpdateData(FALSE);
		//MessageBox(dlg.GetPathName());
	}

	TCHAR * TChr = NULL;
	//CString -> TCHAR
	TChr = (TCHAR*)(LPCTSTR)m_strHeight;
	
	TCHAR strFile[MAX_PATH] = L"data\\map\\";

	_tcsncat(strFile, (TCHAR*)TChr, _tcsclen((TCHAR*)TChr));

	//HeightMap
	theApp.m_MapMgr.m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(theApp.m_MapMgr.m_HeightMap.CreateHeightMap(strFile)))
	{
		return;
	}

	theApp.m_MapMgr.m_HeightMap.m_bStaticLight = true;

	return;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void GCreateMapDlg::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



