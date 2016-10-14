// OpenButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "OpenButton.h"
#include "afxdialogex.h"


// OpenButton 대화 상자입니다.

IMPLEMENT_DYNAMIC(OpenButton, CDialogEx)

OpenButton::OpenButton(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

OpenButton::~OpenButton()
{
}

void OpenButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OpenButton, CDialogEx)
END_MESSAGE_MAP()


// OpenButton 메시지 처리기입니다.
