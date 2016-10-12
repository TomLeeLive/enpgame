#pragma once
#include "afxwin.h"


// TCreateMapDlg 대화 상자입니다.

class GCreateMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GCreateMapDlg)

public:
	GCreateMapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GCreateMapDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_iTileWidth;
	int m_iTileHeight;
	virtual BOOL OnInitDialog();
	int m_iCellSize;
	CComboBox m_CBCellCount;
	CString m_iCellCnt;
	CString m_strBaseTexName;
	afx_msg void OnBnClickedButton1();
};
