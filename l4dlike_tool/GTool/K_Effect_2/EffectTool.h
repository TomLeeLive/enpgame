#pragma once
#include "GBasisStd.h"
// EffectTool ��ȭ �����Դϴ�.

class EffectTool : public CDialogEx
{
	DECLARE_DYNAMIC(EffectTool)

public:
	EffectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~EffectTool();
	CListBox m_list;
	CString m_strValue;
	CString m_strPath;
	CString m_strPath2;
	CStdioFile file;
	CListBox *ListBox;
	CListBox *ListBoxList;
public:
	int ListIndex;
	int ListIndex2;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EffectTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedPlay();
};
