// EffectListBox.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Practice.h"
#include "EffectListBox.h"
#include "afxdialogex.h"


// EffectListBox ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(EffectListBox, CDialogEx)

EffectListBox::EffectListBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EffectTool, pParent)
{

}

EffectListBox::~EffectListBox()
{
}

void EffectListBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EffectListBox, CDialogEx)
END_MESSAGE_MAP()


// EffectListBox �޽��� ó�����Դϴ�.
