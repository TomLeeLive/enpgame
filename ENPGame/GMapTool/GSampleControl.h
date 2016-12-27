#pragma once

#include "GSampleForm.h"
// GSampleControl

class GSampleControl : public CDockablePane
{
	DECLARE_DYNAMIC(GSampleControl)

public:
	GSampleControl();
	virtual ~GSampleControl();

	GSampleForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


