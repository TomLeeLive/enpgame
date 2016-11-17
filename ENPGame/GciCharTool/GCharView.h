#pragma once
#include "afxcmn.h"


// TCharView 대화 상자입니다.

class GCharView : public CDialogEx
{
	DECLARE_DYNAMIC(GCharView)
public:
	GCharView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GCharView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_strCharName;
	CTreeCtrl m_TreeCharCtl;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_CharListCtl;
	BOOL m_bSolidRender;
	BOOL m_iState0;
};
