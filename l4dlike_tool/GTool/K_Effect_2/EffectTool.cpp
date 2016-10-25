// EffectTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Practice.h"
#include "EffectTool.h"
#include "afxdialogex.h"
#include "EffectListBox.h"


// EffectTool ��ȭ �����Դϴ�.

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


// EffectTool �޽��� ó�����Դϴ�.


void EffectTool::OnBnClickedOpen()
{
	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)

	UpdateData(FALSE);
	m_strValue = OpenBn.GetPathName();	//����Ʈ�� �ѱ� �κ�

	ListBox = (CListBox*)GetDlgItem(IDC_OpenList);
	ListBox->InsertString(0, m_strValue);
	m_strValue = _T("");
	//UpdateData(FALSE);
	/*EffectListBox EffectListBox;
	EffectListBox.m_CListBox.AddString(m_strValue);*/

	//m_CListBox.AddString(m_strValue);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



void EffectTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// CFile file;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.tga"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.tga)|*.tga|"), NULL);
	
	
	if (dlg.DoModal() == IDOK)
	{
		 ListIndex = ListBox->GetCurSel(); //���콺 ���� �κ�
			if (ListIndex != LB_ERR)
			{ 
				ListBox = (CListBox *)GetDlgItem(IDC_OpenList);
				ListBox->GetText(ListIndex, m_strPath);	// m_strPath�� ���ϴ� ���콺 ���� Ŭ���� ����Ʈ�� ������ ��ΰ�  ����ֽ��ϴ�. 
			}
			if (m_strPath.Right(4) != ".tga")
			{
				m_strPath += ".tga";
			}
			file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
			// ����Ʈ �ڽ��� �ִ� ���� �����Ѵ�. 
			//UpdateData(TRUE);
			// �����Ѵ�. 
			file.Close();
	}
}


void EffectTool::OnBnClickedPlay() 
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CPracticeApp* p_CParctice = (CPracticeApp*)AfxGetApp();

	ListBoxList = (CListBox *)GetDlgItem(IDC_OpenList);
	ListIndex2 = ListBoxList->GetCurSel();
	ListBoxList->GetText(ListIndex2, m_strPath2);

	/*p_CParctice->m_pPlane = make_shared<GPlaneShape>();
	p_CParctice->m_pPlane->Create(p_CParctice->GetDevice(), L"../output/data/shader/plane.hlsl",m_strPath2);*/

	
	//play ��ư�� init() �κ�
	p_CParctice->m_pSprite->Create(p_CParctice->GetDevice(), L"../output/data/shader/plane.hlsl", m_strPath2);
	// �ִϸ��̼� ����, ����4x4
	p_CParctice->m_pSprite->SetRectAnimation( 1.0f, 4, 128, 4, 128 );


	p_CParctice->check = true;
}
