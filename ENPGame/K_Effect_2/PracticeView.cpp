
// PracticeView.cpp : CPracticeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice.h"
#endif

#include "PracticeDoc.h"
#include "PracticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPracticeView

IMPLEMENT_DYNCREATE(CPracticeView, CView)

BEGIN_MESSAGE_MAP(CPracticeView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CPracticeView 생성/소멸

CPracticeView::CPracticeView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPracticeView::~CPracticeView()
{
}

BOOL CPracticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPracticeView 그리기

void CPracticeView::OnDraw(CDC* /*pDC*/)
{
	CPracticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPracticeView 인쇄

BOOL CPracticeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPracticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPracticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPracticeView 진단

#ifdef _DEBUG
void CPracticeView::AssertValid() const
{
	CView::AssertValid();
}

void CPracticeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPracticeDoc* CPracticeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPracticeDoc)));
	return (CPracticeDoc*)m_pDocument;
}
#endif //_DEBUG


// CPracticeView 메시지 처리기


void CPracticeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CPracticeApp* pApp = (CPracticeApp*)AfxGetApp();
	if (cx != 0 && cy != 0)
	{
		pApp->ResizeDevice(cx, cy);
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	}
}
