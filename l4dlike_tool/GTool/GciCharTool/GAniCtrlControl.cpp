// GAniCtrlControl.cpp : ���� �����Դϴ�.
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



// GAniCtrlControl �޽��� ó�����Դϴ�.




void GAniCtrlControl::OnSize(UINT nType, int cx, int cy)
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


int GAniCtrlControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	// �߰���_S
	m_wndForm = GAniCtrlForm::CreateOne(this);
	// �߰���_E

	return 0;
}


int GAniCtrlControl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
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
