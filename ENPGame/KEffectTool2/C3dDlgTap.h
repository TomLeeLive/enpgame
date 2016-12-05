#pragma once


// C3dDlgTap 대화 상자입니다.

class C3dDlgTap : public CDialog
{
	DECLARE_DYNAMIC(C3dDlgTap)

public:
	C3dDlgTap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~C3dDlgTap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
