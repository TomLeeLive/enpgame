#pragma once
#include "GObjForm.h"


// GObjControl

class GObjControl : public CDockablePane
{
	DECLARE_DYNAMIC(GObjControl)

public:
	GObjControl();
	virtual ~GObjControl();

	GObjForm* m_wndForm;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


