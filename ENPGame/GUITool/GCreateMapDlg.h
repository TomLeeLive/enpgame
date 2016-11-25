#pragma once
#include "afxwin.h"


// TCreateMapDlg ��ȭ �����Դϴ�.

class GCreateMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GCreateMapDlg)

public:
	GCreateMapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GCreateMapDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
