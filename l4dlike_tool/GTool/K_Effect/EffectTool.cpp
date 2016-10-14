// EffectTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "EffectTool.h"
#include "afxdialogex.h"


// EffectTool ��ȭ �����Դϴ�.

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


// EffectTool �޽��� ó�����Դϴ�.


void EffectTool::OnBnClickedOpen()
{
	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)
		MessageBox(OpenBn.GetPathName());


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
