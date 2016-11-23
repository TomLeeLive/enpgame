#pragma once

#include "GUICtrlForm.h"
// GUICtrlControl

class GUICtrlControl : public CDockablePane
{
	DECLARE_DYNAMIC(GUICtrlControl)

public:
	GUICtrlControl();
	virtual ~GUICtrlControl();

	GUICtrlForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


