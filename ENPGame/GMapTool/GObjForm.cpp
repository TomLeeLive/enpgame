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
	, m_fSclX(0)
	, m_fSclY(0)
	, m_fSclZ(0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fRotZ(0)
	, m_fTransX(0)
	, m_fTransY(0)
	, m_fTransZ(0)
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
	DDX_Control(pDX, IDC_LISTOBJ, m_listObj);
	DDX_Text(pDX, IDC_ObjSacleX, m_fSclX);
	DDX_Text(pDX, IDC_ObjScaleY, m_fSclY);
	DDX_Text(pDX, IDC_ObjScaleZ, m_fSclZ);
	DDX_Text(pDX, IDC_ObjRotationX, m_fRotX);
	DDX_Text(pDX, IDC_ObjRotationY, m_fRotY);
	DDX_Text(pDX, IDC_ObjRotationZ, m_fRotZ);
	DDX_Text(pDX, IDC_ObjTransX, m_fTransX);
	DDX_Text(pDX, IDC_ObjTransY, m_fTransY);
	DDX_Text(pDX, IDC_ObjTransZ, m_fTransZ);
}

BEGIN_MESSAGE_MAP(GObjForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &GObjForm::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONLOAD2, &GObjForm::OnBnClickedButtonload2)
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

	
	CString strObjFile;

	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		//dlg.GetPathName();
		FILE *fp;
		strObjFile = dlg.GetFileName();

	}



	TCHAR * TChr = NULL;
	//CString -> TCHAR
	TChr = (TCHAR*)(LPCTSTR)strObjFile;

	TCHAR strFile[MAX_PATH] = L"data\\object\\building\\";

	_tcsncat(strFile, (TCHAR*)TChr, _tcsclen((TCHAR*)TChr));


}


void GObjForm::OnBnClickedButtonload2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
