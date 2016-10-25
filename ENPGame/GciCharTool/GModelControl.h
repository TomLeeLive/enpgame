#pragma once


// GModelControl
#include "GModelForm.h"

class GModelControl : public CDockablePane
{
	DECLARE_DYNAMIC(GModelControl)

public:
	GModelForm* m_wndForm;
public:
	GModelControl();
	virtual ~GModelControl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


