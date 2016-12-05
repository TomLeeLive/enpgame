// PartiCleTap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "PartiCleTap.h"
#include "afxdialogex.h"


// CPartiCleTap 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPartiCleTap, CDialog)

CPartiCleTap::CPartiCleTap(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG3, pParent)
{

}

CPartiCleTap::~CPartiCleTap()
{
}

void CPartiCleTap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPartiCleTap, CDialog)
END_MESSAGE_MAP()


// CPartiCleTap 메시지 처리기입니다.
