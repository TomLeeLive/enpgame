#pragma once


// C3dDlgTap ��ȭ �����Դϴ�.

class C3dDlgTap : public CDialog
{
	DECLARE_DYNAMIC(C3dDlgTap)

public:
	C3dDlgTap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~C3dDlgTap();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
