// OpenList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "K_Effect_.h"
#include "OpenList.h"
#include "afxdialogex.h"


// OpenList 대화 상자입니다.

IMPLEMENT_DYNAMIC(OpenList, CDialogEx)

OpenList::OpenList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDC_OpenList, pParent)
{

}

OpenList::~OpenList()
{
}

void OpenList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OpenList, CDialogEx)
END_MESSAGE_MAP()


// OpenList 메시지 처리기입니다.
