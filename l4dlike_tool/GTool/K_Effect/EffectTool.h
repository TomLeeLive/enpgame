#pragma once
#include "afxwin.h"


// EffectTool 대화 상자입니다.

class EffectTool : public CDialogEx
{
	DECLARE_DYNAMIC(EffectTool)

public:
	EffectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~EffectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	CEdit m_Time;
	CEdit m_FadeIn;
	CEdit m_FadeOut;
};
