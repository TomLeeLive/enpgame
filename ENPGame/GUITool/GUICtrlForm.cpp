// GUICtrlForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GUICtrlForm.h"


// GUICtrlForm

IMPLEMENT_DYNCREATE(GUICtrlForm, CFormView)


//추가함_S
GUICtrlForm* GUICtrlForm::CreateOne(CWnd* pParent) {

	GUICtrlForm* pane = new GUICtrlForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E

GUICtrlForm::GUICtrlForm()
	: CFormView(IDD_GANICTRLFORM)
{

}

GUICtrlForm::~GUICtrlForm()
{
}

void GUICtrlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GUICtrlForm, CFormView)
END_MESSAGE_MAP()


// GUICtrlForm 진단입니다.

#ifdef _DEBUG
void GUICtrlForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GUICtrlForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GUICtrlForm 메시지 처리기입니다.
