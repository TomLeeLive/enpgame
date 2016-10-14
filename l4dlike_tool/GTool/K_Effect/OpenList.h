#pragma once


// OpenList 대화 상자입니다.

class OpenList : public CDialogEx
{
	DECLARE_DYNAMIC(OpenList)

public:
	OpenList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~OpenList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_OpenList };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
