#pragma once



// GObjectForm �� ���Դϴ�.

class GObjectForm : public CFormView
{
	DECLARE_DYNCREATE(GObjectForm)

protected:
	GObjectForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GObjectForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTFORMVIEW };
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
	afx_msg void OnBnClickedAddObject();
	afx_msg void OnBnClickedAddObb();
};


