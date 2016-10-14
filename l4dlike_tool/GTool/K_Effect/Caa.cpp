// Caa.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "Caa.h"
#include "afxdialogex.h"


// Caa 대화 상자입니다.

IMPLEMENT_DYNAMIC(Caa, CDialogEx)

Caa::Caa(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

Caa::~Caa()
{
}

void Caa::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Caa, CDialogEx)
END_MESSAGE_MAP()


// Caa 메시지 처리기입니다.
