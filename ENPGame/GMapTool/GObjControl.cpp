// GObjControl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GObjControl.h"


// GObjControl

IMPLEMENT_DYNAMIC(GObjControl, CDockablePane)

GObjControl::GObjControl()
{

}

GObjControl::~GObjControl()
{
}


BEGIN_MESSAGE_MAP(GObjControl, CDockablePane)
	ON_WM_SIZE()
//	ON_WM_CHARTOITEM()
ON_WM_CREATE()
ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// GObjControl �޽��� ó�����Դϴ�.




void GObjControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}

int GObjControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_wndForm = GObjForm::CreateOne(this);
	return 0;
}


int GObjControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}

	return MA_NOACTIVATE;
}
