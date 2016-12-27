// GSampleForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GSampleForm.h"


// GSampleForm

IMPLEMENT_DYNCREATE(GSampleForm, CFormView)
//추가함_S

GSampleForm* GSampleForm::CreateOne(CWnd* pParent) {

	GSampleForm* pane = new GSampleForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E


GSampleForm::GSampleForm()
	: CFormView(IDD_SAMPLEFORM)
{

}

GSampleForm::~GSampleForm()
{
}

void GSampleForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GSampleForm, CFormView)

END_MESSAGE_MAP()


// GSampleForm 진단입니다.

#ifdef _DEBUG
void GSampleForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GSampleForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
