// OpenButton.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "OpenButton.h"
#include "afxdialogex.h"


// OpenButton ��ȭ �����Դϴ�.

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


// OpenButton �޽��� ó�����Դϴ�.
