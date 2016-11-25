// GImageForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GImageForm.h"


// GImageForm

IMPLEMENT_DYNCREATE(GImageForm, CFormView)


//추가함_S
GImageForm* GImageForm::CreateOne(CWnd* pParent) {

	GImageForm* pane = new GImageForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E

GImageForm::GImageForm()
	: CFormView(IDD_GANICTRLFORM)
{

}

GImageForm::~GImageForm()
{
}

void GImageForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GImageForm, CFormView)
END_MESSAGE_MAP()


// GImageForm 진단입니다.

#ifdef _DEBUG
void GImageForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GImageForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GImageForm 메시지 처리기입니다.
