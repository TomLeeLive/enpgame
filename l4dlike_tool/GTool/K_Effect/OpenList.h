#pragma once


// OpenList ��ȭ �����Դϴ�.

class OpenList : public CDialogEx
{
	DECLARE_DYNAMIC(OpenList)

public:
	OpenList(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~OpenList();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_OpenList };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
