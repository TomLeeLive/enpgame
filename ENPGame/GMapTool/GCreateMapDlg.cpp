// GCreateMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GCreateMapDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
// GCreateMapDlg 대화 상자입니다.

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


// GCreateMapDlg 메시지 처리기입니다.


BOOL GCreateMapDlg::OnInitDialog()
{//1
	CDialogEx::OnInitDialog();


	//m_cbCellCount.InsertString(0, L"2*2");
	//m_cbCellCount.InsertString(1, L"3*3");
	//m_cbCellCount.InsertString(2, L"4*4");
	//m_cbCellCount.InsertString(3, L"8*8");
	//m_cbCellCount.InsertString(4, L"16*16");
	//m_cbCellCount.InsertString(5, L"32*32");



	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_iTileWidth = 16;
	//m_iTileHeight = 16;
	//m_fCellDistance = 1.0f;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//지형생성 확인 버튼
void GCreateMapDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	UpdateData(TRUE);

	CDialogEx::OnOK();

	//if (theApp.m_MapMgr.m_iMapSelected == -1) {
	//	AfxMessageBox(
	//		L"선택된 맵이 없습니다.\n"
	//		L"맵을 우선 선택해주시겠습니까?", MB_OK);

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


	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d"), theApp.m_MapMgr.m_vecMapGroup.size() - 1);
	pFrame->m_wndObjCtrl.m_wndForm->m_listMap.AddString(szRet);

}


// 텍스쳐 찾기
void GCreateMapDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void GCreateMapDlg::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



