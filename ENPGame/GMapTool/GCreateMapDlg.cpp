// GCreateMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GCreateMapDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
// GCreateMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GCreateMapDlg, CDialogEx)

GCreateMapDlg::GCreateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEMAP, pParent)
	//, m_iTileWidth(0)
	//, m_iTileHeight(0)
	//, m_fCellDistance(0)
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
	//DDX_Text(pDX, IDC_EDIT1, m_iTileWidth);
	//DDX_Text(pDX, IDC_EDIT6, m_iTileHeight);
	//DDX_Control(pDX, IDC_COMBO2, m_cbCellCount);
	//DDX_Text(pDX, IDC_EDIT3, m_fCellDistance);
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


	//m_cbCellCount.InsertString(0, L"2*2");
	//m_cbCellCount.InsertString(1, L"3*3");
	//m_cbCellCount.InsertString(2, L"4*4");
	//m_cbCellCount.InsertString(3, L"8*8");
	//m_cbCellCount.InsertString(4, L"16*16");
	//m_cbCellCount.InsertString(5, L"32*32");



	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//m_iTileWidth = 16;
	//m_iTileHeight = 16;
	//m_fCellDistance = 1.0f;

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

	//if (theApp.m_MapMgr.m_iMapSelected == -1) {
	//	AfxMessageBox(
	//		L"���õ� ���� �����ϴ�.\n"
	//		L"���� �켱 �������ֽðڽ��ϱ�?", MB_OK);

	//}


	//HeightMap
	auto pMap = make_shared<GMapGroup>();

	pMap->m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(pMap->m_HeightMap.CreateHeightMap(theApp.m_MapMgr.m_strHeight)))
	{
		return;
	}

	pMap->m_HeightMap.m_bStaticLight = true;


	pMap->CreateInit(0, 0, 0, (LPCTSTR)theApp.m_MapMgr.m_strTex, theApp.m_pMainCamera.get());

	_tcsncpy_s(pMap->m_strHeight, theApp.m_MapMgr.m_strHeight, MAX_PATH);
	_tcsncpy_s(pMap->m_strTex, theApp.m_MapMgr.m_strTex, MAX_PATH);

	theApp.m_MapMgr.m_vecMapGroup.push_back(pMap);
	
	theApp.m_MapMgr.m_iMapSelected = theApp.m_MapMgr.m_vecMapGroup.size() - 1;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();


	TCHAR szRet[30] = { 0 }; // "10"�� NULL ó���� ���� 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d"), theApp.m_MapMgr.m_vecMapGroup.size() - 1);
	pFrame->m_wndObjCtrl.m_wndForm->m_listMap.AddString(szRet);

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
	else {
		return;
	}

	_tcsncpy(theApp.m_MapMgr.m_strTex, (TCHAR*)(LPCTSTR)m_strCharName, m_strCharName.GetLength());

}


//HeightMap
void GCreateMapDlg::OnBnClickedButton4()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_strHeight = dlg.GetFileName();

		UpdateData(FALSE);
	}
	else {
		return;
	}

	TCHAR * TChr = NULL;
	//CString -> TCHAR
	TChr = (TCHAR*)(LPCTSTR)m_strHeight;
	
	TCHAR strFile[MAX_PATH] = L"data\\map\\";

	_tcsncat(strFile, (TCHAR*)TChr, _tcsclen((TCHAR*)TChr));

	_tcsncpy_s(theApp.m_MapMgr.m_strHeight,strFile,MAX_PATH);


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



