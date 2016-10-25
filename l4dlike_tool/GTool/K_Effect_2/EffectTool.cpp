// EffectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Practice.h"
#include "EffectTool.h"
#include "afxdialogex.h"
#include "EffectListBox.h"


// EffectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(EffectTool, CDialogEx)

EffectTool::EffectTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EffectTool, pParent)
{

}

EffectTool::~EffectTool()
{
}

void EffectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectTool, CDialogEx)
	ON_BN_CLICKED(IDC_Open, &EffectTool::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_Save, &EffectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_Play, &EffectTool::OnBnClickedPlay)
END_MESSAGE_MAP()


// EffectTool 메시지 처리기입니다.


void EffectTool::OnBnClickedOpen()
{
	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)

	UpdateData(FALSE);
	m_strValue = OpenBn.GetPathName();	//리스트에 넘길 부분

	ListBox = (CListBox*)GetDlgItem(IDC_OpenList);
	ListBox->InsertString(0, m_strValue);
	m_strValue = _T("");
	//UpdateData(FALSE);
	/*EffectListBox EffectListBox;
	EffectListBox.m_CListBox.AddString(m_strValue);*/

	//m_CListBox.AddString(m_strValue);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void EffectTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// CFile file;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.tga"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.tga)|*.tga|"), NULL);
	
	
	if (dlg.DoModal() == IDOK)
	{
		 ListIndex = ListBox->GetCurSel(); //마우스 누른 부분
			if (ListIndex != LB_ERR)
			{ 
				ListBox = (CListBox *)GetDlgItem(IDC_OpenList);
				ListBox->GetText(ListIndex, m_strPath);	// m_strPath에 원하는 마우스 왼쪽 클릭한 리스트에 파일의 경로가  들어있습니다. 
			}
			if (m_strPath.Right(4) != ".tga")
			{
				m_strPath += ".tga";
			}
			file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
			// 에디트 박스에 있는 것을 저장한다. 
			//UpdateData(TRUE);
			// 종료한다. 
			file.Close();
	}
}


void EffectTool::OnBnClickedPlay() 
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPracticeApp* p_CParctice = (CPracticeApp*)AfxGetApp();

	ListBoxList = (CListBox *)GetDlgItem(IDC_OpenList);
	ListIndex2 = ListBoxList->GetCurSel();
	ListBoxList->GetText(ListIndex2, m_strPath2);

	/*p_CParctice->m_pPlane = make_shared<GPlaneShape>();
	p_CParctice->m_pPlane->Create(p_CParctice->GetDevice(), L"../output/data/shader/plane.hlsl",m_strPath2);*/

	
	//play 버튼시 init() 부분
	p_CParctice->m_pSprite->Create(p_CParctice->GetDevice(), L"../output/data/shader/plane.hlsl", m_strPath2);
	// 애니메이션 관련, 가로4x4
	p_CParctice->m_pSprite->SetRectAnimation( 1.0f, 4, 128, 4, 128 );


	p_CParctice->check = true;
}
