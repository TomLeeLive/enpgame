// GImageControl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GUITool.h"
#include "GImageControl.h"


// GImageControl

IMPLEMENT_DYNAMIC(GImageControl, CDockablePane)

GImageControl::GImageControl()
{

}

GImageControl::~GImageControl()
{
}


BEGIN_MESSAGE_MAP(GImageControl, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// GImageControl �޽��� ó�����Դϴ�.




void GImageControl::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	// �߰���_S
	if (m_wndForm) {

		//�������ø� ����..
		m_wndForm->SetWindowPos(
			NULL,
			0, 0, cx, cy, SWP_NOZORDER);
	}
	// �߰���_E
}


int GImageControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	// �߰���_S
	m_wndForm = GImageForm::CreateOne(this);
	// �߰���_E

	return 0;
}


int GImageControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//�߰���_S
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
	//�߰���_E
}