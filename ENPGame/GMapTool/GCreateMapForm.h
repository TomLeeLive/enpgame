#pragma once



// GCreateMapForm �� ���Դϴ�.

class GCreateMapForm : public CFormView
{
	DECLARE_DYNCREATE(GCreateMapForm)

protected:
	GCreateMapForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GCreateMapForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRAETEMAPFORMVIEW };
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
};


