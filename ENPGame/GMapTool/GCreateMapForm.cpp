// GCreateMapForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GCreateMapForm.h"


// GCreateMapForm

IMPLEMENT_DYNCREATE(GCreateMapForm, CFormView)

GCreateMapForm::GCreateMapForm()
	: CFormView(IDD_CRAETEMAPFORMVIEW)
{

}

GCreateMapForm::~GCreateMapForm()
{
}

void GCreateMapForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GCreateMapForm, CFormView)
END_MESSAGE_MAP()


// GCreateMapForm �����Դϴ�.

#ifdef _DEBUG
void GCreateMapForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GCreateMapForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GCreateMapForm �޽��� ó�����Դϴ�.
