// GSampleForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "GSampleForm.h"


// GSampleForm

IMPLEMENT_DYNCREATE(GSampleForm, CFormView)
//�߰���_S

GSampleForm* GSampleForm::CreateOne(CWnd* pParent) {

	GSampleForm* pane = new GSampleForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//�߰���_E


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


// GSampleForm �����Դϴ�.

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
