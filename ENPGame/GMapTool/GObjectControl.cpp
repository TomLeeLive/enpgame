// GObjectControl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GObjectControl.h"


// GObjectControl

IMPLEMENT_DYNAMIC(GObjectControl, CDockablePane)

GObjectControl::GObjectControl()
{

}

GObjectControl::~GObjectControl()
{
}


BEGIN_MESSAGE_MAP(GObjectControl, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// GObjectControl �޽��� ó�����Դϴ�.




void GObjectControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int GObjectControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


int GObjectControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
