#pragma once

#include "GImageForm.h"
// GImageControl

class GImageControl : public CDockablePane
{
	DECLARE_DYNAMIC(GImageControl)

public:
	GImageControl();
	virtual ~GImageControl();

	GImageForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


