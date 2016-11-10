// C2dDlgTap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "C2dDlgTap.h"
#include "afxdialogex.h"
#include <atlstr.h>

// C2dDlgTap 대화 상자입니다.

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


// C2dDlgTap 메시지 처리기입니다.


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
		SaveListIndex = SaveList->GetCurSel(); //마우스 누른 부분
	

		if (SaveListIndex != LB_ERR)
		{
			SaveList->GetText(SaveListIndex, m_strSave);// m_strPath에 원하는 마우스 왼쪽 클릭한 리스트에 파일의 경로가  들어있습니다. 
		}
		file.Open(dlg.GetFileName(), CFile::modeCreate | CFile::modeReadWrite, &ex);
		UpdateData(TRUE);
		//file.Close();
	}
}

void C2dDlgTap::OnBnClickedOnbnclick2dplay()
{
	m_strPlay = m_temp;

	//play 버튼시 init() 부분
	p_CParctice->m_pSprite->Create(p_CParctice->GetDevice(), L"data/shader/plane.hlsl", m_strPlay);
	// 애니메이션 관련, 가로4x4
	p_CParctice->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);

	m_temp = _T(" ");


	p_CParctice->check = true;

}
void C2dDlgTap::OnEnUpdate2dX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
