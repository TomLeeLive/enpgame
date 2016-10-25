// EffectListBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Practice.h"
#include "EffectListBox.h"
#include "afxdialogex.h"


// EffectListBox 대화 상자입니다.

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


// EffectListBox 메시지 처리기입니다.
