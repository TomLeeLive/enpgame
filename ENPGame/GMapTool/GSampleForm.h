#pragma once



// GSampleForm �� ���Դϴ�.

class GSampleForm : public CFormView
{
	DECLARE_DYNCREATE(GSampleForm)

protected:
	GSampleForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GSampleForm();
public :
	static GSampleForm* CreateOne(CWnd* pParent);
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLEFORM };
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
};


