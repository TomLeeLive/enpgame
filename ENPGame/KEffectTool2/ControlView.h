#pragma once
#include "afxcmn.h"

#include "C2dDlgTap.h"
#include "C3dDlgTap.h"
#include "PartiCleTap.h"

// CControlView 폼 뷰입니다.

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_ctlTap;

	C2dDlgTap *m_2dDlgTap;
	C3dDlgTap *m_3dDlgTap;
	CPartiCleTap *m_ParticleTap;
	
	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


