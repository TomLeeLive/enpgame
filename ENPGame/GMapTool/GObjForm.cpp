// GObjForm.cpp : 구현 파일입니다.
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


// GObjForm 진단입니다.

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


// GObjForm 메시지 처리기입니다.


void GObjForm::OnBnClickedButtonload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	//if(!pApp->LoadFileDlg(_T("*"),_T("이미지")))
}
