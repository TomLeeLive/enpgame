#pragma once



// GObjForm �� ���Դϴ�.

class GObjForm : public CFormView
{
	DECLARE_DYNCREATE(GObjForm)

protected:
	GObjForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GObjForm();

public:
	static GObjForm* CreateOne(CWnd* pParent);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonload();
};


