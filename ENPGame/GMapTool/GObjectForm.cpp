// GObjectForm.cpp : 구현 파일입니다.
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


// GObjectForm 진단입니다.

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


// GObjectForm 메시지 처리기입니다.


void GObjectForm::OnBnClickedAddObject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void GObjectForm::OnBnClickedAddObb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
