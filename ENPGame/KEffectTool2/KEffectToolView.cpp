
// KEffectToolView.cpp : CKEffectToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "KEffectTool.h"
#endif

#include "KEffectToolDoc.h"
#include "KEffectToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKEffectToolView

IMPLEMENT_DYNCREATE(CKEffectToolView, CView)

BEGIN_MESSAGE_MAP(CKEffectToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CKEffectToolView ����/�Ҹ�

CKEffectToolView::CKEffectToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CKEffectToolView::~CKEffectToolView()
{
}

BOOL CKEffectToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CKEffectToolView �׸���

void CKEffectToolView::OnDraw(CDC* /*pDC*/)
{
	CKEffectToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CKEffectToolView �μ�

BOOL CKEffectToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CKEffectToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CKEffectToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CKEffectToolView ����

#ifdef _DEBUG
void CKEffectToolView::AssertValid() const
{
	CView::AssertValid();
}

void CKEffectToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKEffectToolDoc* CKEffectToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKEffectToolDoc)));
	return (CKEffectToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CKEffectToolView �޽��� ó����
