#pragma once


// GButtonControl
#include "GButtonForm.h"

class GButtonControl : public CDockablePane
{
	DECLARE_DYNAMIC(GButtonControl)

public:
	GButtonForm* m_wndForm;
public:
	GButtonControl();
	virtual ~GButtonControl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


