#pragma once



// GImageForm �� ���Դϴ�.

class GImageForm : public CFormView
{
	DECLARE_DYNCREATE(GImageForm)

protected:
	GImageForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GImageForm();

	// �߰���_S
public:
	static GImageForm* CreateOne(CWnd* pParent);
	//�߰���_E
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GIMAGEFORM };
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


