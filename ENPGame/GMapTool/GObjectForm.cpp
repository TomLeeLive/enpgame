// GObjectForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GObjectForm.h"


// GObjectForm

IMPLEMENT_DYNCREATE(GObjectForm, CFormView)

GObjectForm::GObjectForm()
	: CFormView(IDD_OBJECTFORMVIEW)
{

}

GObjectForm::~GObjectForm()
{
}

void GObjectForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GObjectForm, CFormView)
	ON_BN_CLICKED(IDC_ADD_OBJECT, &GObjectForm::OnBnClickedAddObject)
	ON_BN_CLICKED(IDC_ADD_OBB, &GObjectForm::OnBnClickedAddObb)
END_MESSAGE_MAP()


// GObjectForm �����Դϴ�.

#ifdef _DEBUG
void GObjectForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GObjectForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GObjectForm �޽��� ó�����Դϴ�.


void GObjectForm::OnBnClickedAddObject()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void GObjectForm::OnBnClickedAddObb()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
