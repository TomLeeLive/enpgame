#pragma once

#include "GAniCtrlForm.h"
// GAniCtrlControl

class GAniCtrlControl : public CDockablePane
{
	DECLARE_DYNAMIC(GAniCtrlControl)

public:
	GAniCtrlControl();
	virtual ~GAniCtrlControl();

	GAniCtrlForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


