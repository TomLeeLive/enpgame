// GAniCtrlForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GciCharTool.h"
#include "GAniCtrlForm.h"


// GAniCtrlForm

IMPLEMENT_DYNCREATE(GAniCtrlForm, CFormView)


//추가함_S
GAniCtrlForm* GAniCtrlForm::CreateOne(CWnd* pParent) {

	GAniCtrlForm* pane = new GAniCtrlForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;
}
//추가함_E

GAniCtrlForm::GAniCtrlForm()
	: CFormView(IDD_GANICTRLFORM)
{

}

GAniCtrlForm::~GAniCtrlForm()
{
}

void GAniCtrlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GAniCtrlForm, CFormView)
END_MESSAGE_MAP()


// GAniCtrlForm 진단입니다.

#ifdef _DEBUG
void GAniCtrlForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GAniCtrlForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GAniCtrlForm 메시지 처리기입니다.
