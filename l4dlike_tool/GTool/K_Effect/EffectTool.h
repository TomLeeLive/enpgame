#pragma once
#include "afxwin.h"


// EffectTool ��ȭ �����Դϴ�.

class EffectTool : public CDialogEx
{
	DECLARE_DYNAMIC(EffectTool)

public:
	EffectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~EffectTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	CEdit m_Time;
	CEdit m_FadeIn;
	CEdit m_FadeOut;
};
