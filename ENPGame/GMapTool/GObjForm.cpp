// GObjForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"

#include "MapTool.h"
#include "GObjForm.h"


// GObjForm

IMPLEMENT_DYNCREATE(GObjForm, CFormView)

GObjForm::GObjForm()
	: CFormView(IDD_OBJFORM)
{

}

GObjForm::~GObjForm()
{
}

GObjForm * GObjForm::CreateOne(CWnd * pParent)
{
	GObjForm* pane = new GObjForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;	
}

void GObjForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GObjForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &GObjForm::OnBnClickedButtonload)
END_MESSAGE_MAP()


// GObjForm �����Դϴ�.

#ifdef _DEBUG
void GObjForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GObjForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GObjForm �޽��� ó�����Դϴ�.


void GObjForm::OnBnClickedButtonload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	//if(!pApp->LoadFileDlg(_T("*"),_T("�̹���")))
}
