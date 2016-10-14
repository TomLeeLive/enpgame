// EffectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "EffectTool.h"
#include "afxdialogex.h"


// EffectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(EffectTool, CDialogEx)

EffectTool::EffectTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

EffectTool::~EffectTool()
{
}

void EffectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Time);
	DDX_Control(pDX, IDC_EDIT2, m_FadeIn);
	DDX_Control(pDX, IDC_EDIT3, m_FadeOut);
}


BEGIN_MESSAGE_MAP(EffectTool, CDialogEx)
	ON_BN_CLICKED(IDC_Open, &EffectTool::OnBnClickedOpen)
END_MESSAGE_MAP()


// EffectTool 메시지 처리기입니다.


void EffectTool::OnBnClickedOpen()
{
	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)
		MessageBox(OpenBn.GetPathName());


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
