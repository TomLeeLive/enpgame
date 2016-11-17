#pragma once
#include "MapTool.h"

// GSaveMapDlg 대화 상자입니다.

class GSaveMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GSaveMapDlg)

public:
	GSaveMapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GSaveMapDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVEMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();	
	CString m_strCharName;
	afx_msg void OnBnClickedOk();
};
