
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "KEffectToolDoc.h"
#include "KEffectToolView.h"
#include "ControlView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 탭 스크롤 고정
BEGIN_MESSAGE_MAP(CSplitterX, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()
CSplitterX::CSplitterX() {}
CSplitterX::~CSplitterX() {}

LRESULT CSplitterX::OnNcHitTest(CPoint point)
{
	return HTNOWHERE;
}
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//return m_wndSplitter.Create(this,
	//	2, 2,               // TODO: 행 및 열의 개수를 조정합니다.
	//	CSize(10, 10),      // TODO: 최소 창 크기를 조정합니다.
	//	pContext);
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CKEffectToolView), CSize(768, 768), pContext))
	{
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CControlView), CSize(1280 - 768, 768), pContext))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.x = 100;
	cs.y = 100;
	cs.cx = 1024;
	cs.cy = 768;
	cs.style &= ~FWS_ADDTOTITLE;
	LPCTSTR TitleName = _T("mapTool");
	SetTitle(TitleName);

	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

