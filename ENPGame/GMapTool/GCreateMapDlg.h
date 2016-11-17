#pragma once
#include "afxwin.h"
#include "MapTool.h"

// GCreateMapDlg ��ȭ �����Դϴ�.

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
