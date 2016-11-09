// C2dDlgTap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "C2dDlgTap.h"
#include "afxdialogex.h"
#include <atlstr.h>

// C2dDlgTap ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(C2dDlgTap, CDialog)

C2dDlgTap::C2dDlgTap(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, LblValue_X(0)
	, LblValue_Y(0)
	, LblValue_Z(0)
{

}

C2dDlgTap::~C2dDlgTap()
{
}

void C2dDlgTap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_2D_X, LblValue_X);
	DDX_Text(pDX, IDC_2D_Y, LblValue_Y);
	DDX_Text(pDX, IDC_2D_Z, LblValue_Z);
	p_CParctice->ChagePositionData(LblValue_X, LblValue_Y, LblValue_Z);
	UpdateData(TRUE);
}


BEGIN_MESSAGE_MAP(C2dDlgTap, CDialog)
	ON_BN_CLICKED(IDC_OnBnClick2DOpen, &C2dDlgTap::OnBnClickedOnbnclick2dopen)
	ON_BN_CLICKED(IDC_OnBnClick2DSave, &C2dDlgTap::OnBnClickedOnbnclick2dsave)
	ON_BN_CLICKED(IDC_OnBnClick2DPlay, &C2dDlgTap::OnBnClickedOnbnclick2dplay)
	ON_EN_UPDATE(IDC_2D_X, &C2dDlgTap::OnEnUpdate2dX)
END_MESSAGE_MAP()


// C2dDlgTap �޽��� ó�����Դϴ�.


void C2dDlgTap::OnBnClickedOnbnclick2dopen()
{
	CFileDialog OpenBn(TRUE);
	int Inserti = 0;
	if (OpenBn.DoModal() == IDOK)
		UpdateData(FALSE);
	
	m_strOpen = OpenBn.GetFileName();

	OpenList = (CListBox*)GetDlgItem(IDC_LISTBOX);
	OpenList->InsertString(Inserti, m_strOpen);
	Inserti = Inserti + 1;

	m_temp = m_strOpen;
	m_strOpen = _T("");
	//a = 0;
	
}



void C2dDlgTap::OnBnClickedOnbnclick2dsave()
{
	CFileException ex;
	CFileDialog dlg(FALSE, NULL, _T("*.dds"), OFN_FILEMUSTEXIST |OFN_CREATEPROMPT| OFN_OVERWRITEPROMPT , _T("DDSFiles(*.dds)"), NULL);
	
	SaveList = (CListBox *)GetDlgItem(IDC_LISTBOX);
	
	if (dlg.DoModal() == IDOK)
	{
		SaveListIndex = SaveList->GetCurSel(); //���콺 ���� �κ�
	

		if (SaveListIndex != LB_ERR)
		{
			SaveList->GetText(SaveListIndex, m_strSave);// m_strPath�� ���ϴ� ���콺 ���� Ŭ���� ����Ʈ�� ������ ��ΰ�  ����ֽ��ϴ�. 
		}
		file.Open(dlg.GetFileName(), CFile::modeCreate | CFile::modeReadWrite, &ex);
		UpdateData(TRUE);
		//file.Close();
	}
}

void C2dDlgTap::OnBnClickedOnbnclick2dplay()
{
	m_strPlay = m_temp;

	//play ��ư�� init() �κ�
	p_CParctice->m_pSprite->Create(p_CParctice->GetDevice(), L"data/shader/plane.hlsl", m_strPlay);
	// �ִϸ��̼� ����, ����4x4
	p_CParctice->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);

	m_temp = _T(" ");


	p_CParctice->check = true;

}
void C2dDlgTap::OnEnUpdate2dX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�Ͽ�, IParam ����ũ�� OR �����Ͽ� ������ ENM_SCROLL �÷��׸� �����Ͽ� ��Ʈ�ѿ� EM_SETEVENTMASK �޽����� ������ ������
	// ���� ��Ʈ���� �ٲ� �ؽ�Ʈ�� ǥ���Ϸ��� ���� ��Ÿ���ϴ�.
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
