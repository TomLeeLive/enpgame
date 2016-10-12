// GAniCtrlControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GciCharTool.h"
#include "GAniCtrlControl.h"


// GAniCtrlControl

IMPLEMENT_DYNAMIC(GAniCtrlControl, CDockablePane)

GAniCtrlControl::GAniCtrlControl()
{

}

GAniCtrlControl::~GAniCtrlControl()
{
}


BEGIN_MESSAGE_MAP(GAniCtrlControl, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// GAniCtrlControl 메시지 처리기입니다.




void GAniCtrlControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// 추가함_S
	if (m_wndForm) {

		//리프레시를 위해..
		m_wndForm->SetWindowPos(
			NULL,
			0, 0, cx, cy, SWP_NOZORDER);
	}
	// 추가함_E
}


int GAniCtrlControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	// 추가함_S
	m_wndForm = GAniCtrlForm::CreateOne(this);
	// 추가함_E

	return 0;
}


int GAniCtrlControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//추가함_S
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
	//추가함_E
}
