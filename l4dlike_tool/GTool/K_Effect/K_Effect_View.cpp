
// K_Effect_View.cpp : CK_Effect_View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "K_Effect_.h"
#endif

#include "K_Effect_Doc.h"
#include "K_Effect_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CK_Effect_View

IMPLEMENT_DYNCREATE(CK_Effect_View, CView)

BEGIN_MESSAGE_MAP(CK_Effect_View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CK_Effect_View ����/�Ҹ�

CK_Effect_View::CK_Effect_View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CK_Effect_View::~CK_Effect_View()
{
}

BOOL CK_Effect_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CK_Effect_View �׸���

void CK_Effect_View::OnDraw(CDC* /*pDC*/)
{
	CK_Effect_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CK_Effect_View �μ�

BOOL CK_Effect_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CK_Effect_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CK_Effect_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CK_Effect_View ����

#ifdef _DEBUG
void CK_Effect_View::AssertValid() const
{
	CView::AssertValid();
}

void CK_Effect_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK_Effect_Doc* CK_Effect_View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK_Effect_Doc)));
	return (CK_Effect_Doc*)m_pDocument;
}
#endif //_DEBUG


// CK_Effect_View �޽��� ó����
