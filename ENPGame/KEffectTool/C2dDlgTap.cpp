// C2dDlgTap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "C2dDlgTap.h"
#include "afxdialogex.h"


// C2dDlgTap ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(C2dDlgTap, CDialog)

C2dDlgTap::C2dDlgTap(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

C2dDlgTap::~C2dDlgTap()
{
}

void C2dDlgTap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C2dDlgTap, CDialog)
	ON_BN_CLICKED(IDC_OnBnClick2DOpen, &C2dDlgTap::OnBnClickedOnbnclick2dopen)
	ON_BN_CLICKED(IDC_OnBnClick2DSave, &C2dDlgTap::OnBnClickedOnbnclick2dsave)
	ON_BN_CLICKED(IDC_OnBnClick2DPlay, &C2dDlgTap::OnBnClickedOnbnclick2dplay)
END_MESSAGE_MAP()


// C2dDlgTap �޽��� ó�����Դϴ�.


void C2dDlgTap::OnBnClickedOnbnclick2dopen()
{
	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)
		UpdateData(FALSE);
	m_strValue = OpenBn.GetPathName();	//����Ʈ�� �ѱ� �κ�

	int Inserti = 0;
	InsertList = (CListBox*)GetDlgItem(IDC_LISTBOX);
	InsertList->InsertString(Inserti, m_strValue);
	Inserti = Inserti + 1;
	m_strValue = _T("");
}



void C2dDlgTap::OnBnClickedOnbnclick2dsave()
{
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.tga"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.tga)|*.tga|"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		SaveListIndex = SaveList->GetCurSel(); //���콺 ���� �κ�
		if (SaveListIndex != LB_ERR)
		{
			SaveList = (CListBox *)GetDlgItem(IDC_LISTBOX);
			SaveList->GetText(SaveListIndex, m_strPath);	// m_strPath�� ���ϴ� ���콺 ���� Ŭ���� ����Ʈ�� ������ ��ΰ�  ����ֽ��ϴ�. 
		}
		if (m_strPath.Right(4) != ".tga")
		{
			m_strPath += ".tga";
		}
		file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
		file.Close();
	}
}

void C2dDlgTap::OnBnClickedOnbnclick2dplay()
{
	CKEffectToolApp* p_CParctice = (CKEffectToolApp*)AfxGetApp();

	PlayList = (CListBox *)GetDlgItem(IDC_LISTBOX);
	PlayListIndex = PlayList->GetCurSel();
	PlayList->GetText(PlayListIndex, m_strPath2);

	//play ��ư�� init() �κ�
	p_CParctice->m_pSprite->Create(p_CParctice->GetDevice(), L"../../output/data/shader/plane.hlsl", m_strPath2);
	// �ִϸ��̼� ����, ����4x4
	p_CParctice->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);


	p_CParctice->check = true;

}
