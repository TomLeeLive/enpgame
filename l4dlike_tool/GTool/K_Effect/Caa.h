#pragma once


// Caa ��ȭ �����Դϴ�.

class Caa : public CDialogEx
{
	DECLARE_DYNAMIC(Caa)

public:
	Caa(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Caa();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
