// GUICtrlForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GUICtrlForm.h"


// GUICtrlForm

IMPLEMENT_DYNCREATE(GUICtrlForm, CFormView)


//�߰���_S
GUICtrlForm* GUICtrlForm::CreateOne(CWnd* pParent) {

	GUICtrlForm* pane = new GUICtrlForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//�߰���_E

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


// GUICtrlForm �����Դϴ�.

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


// GUICtrlForm �޽��� ó�����Դϴ�.
