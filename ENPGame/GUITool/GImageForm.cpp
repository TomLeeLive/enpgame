// GImageForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GImageForm.h"


// GImageForm

IMPLEMENT_DYNCREATE(GImageForm, CFormView)


//�߰���_S
GImageForm* GImageForm::CreateOne(CWnd* pParent) {

	GImageForm* pane = new GImageForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//�߰���_E

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


// GImageForm �����Դϴ�.

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


// GImageForm �޽��� ó�����Դϴ�.
