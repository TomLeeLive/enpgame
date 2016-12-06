#pragma once


// CPartiCleTap 대화 상자입니다.

class CPartiCleTap : public CDialog
{
	DECLARE_DYNAMIC(CPartiCleTap)

public:
	CPartiCleTap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPartiCleTap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
