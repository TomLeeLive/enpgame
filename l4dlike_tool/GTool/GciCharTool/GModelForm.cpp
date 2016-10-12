// GModelForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GciCharTool.h"
#include "GModelForm.h"


// GModelForm

IMPLEMENT_DYNCREATE(GModelForm, CFormView)

//추가함_S
GModelForm* GModelForm::CreateOne(CWnd* pParent) {

	GModelForm* pane = new GModelForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E



GModelForm::GModelForm()
	: CFormView(IDD_GMODELFORM)
{

}

GModelForm::~GModelForm()
{
}

void GModelForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GModelForm, CFormView)
END_MESSAGE_MAP()


// GModelForm 진단입니다.

#ifdef _DEBUG
void GModelForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GModelForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GModelForm 메시지 처리기입니다.
