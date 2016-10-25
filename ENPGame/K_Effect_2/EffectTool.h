#pragma once
#include "GBasisStd.h"
// EffectTool 대화 상자입니다.

class EffectTool : public CDialogEx
{
	DECLARE_DYNAMIC(EffectTool)

public:
	EffectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
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
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EffectTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedPlay();
};
