#pragma once


// CPartiCleTap ��ȭ �����Դϴ�.

class CPartiCleTap : public CDialog
{
	DECLARE_DYNAMIC(CPartiCleTap)

public:
	CPartiCleTap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPartiCleTap();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
