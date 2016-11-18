#pragma once
#include "afxcmn.h"


// TCharView ��ȭ �����Դϴ�.

class GCharView : public CDialogEx
{
	DECLARE_DYNAMIC(GCharView)
public:
	GCharView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GCharView();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
