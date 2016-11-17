#pragma once
#include "afxwin.h"
#include "MapTool.h"

// GCreateMapDlg 대화 상자입니다.

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
	//CMapToolApp MapTool;
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	int m_iTileWidth;
	int m_iTileHeight;
	CComboBox m_cbCellCount;
	float m_fCellDistance;
	afx_msg void OnBnClickedButton1();
	CString m_strCharName;
};
