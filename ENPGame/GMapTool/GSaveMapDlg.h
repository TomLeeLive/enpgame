#pragma once
#include "MapTool.h"

// GSaveMapDlg ��ȭ �����Դϴ�.

class GSaveMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GSaveMapDlg)

public:
	GSaveMapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GSaveMapDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVEMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();	
	CString m_strCharName;
	afx_msg void OnBnClickedOk();
};
