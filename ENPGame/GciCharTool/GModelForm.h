#pragma once



// GModelForm �� ���Դϴ�.

class GModelForm : public CFormView
{
	DECLARE_DYNCREATE(GModelForm)

protected:
	GModelForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GModelForm();

	// �߰���_S
public:
	static GModelForm* CreateOne(CWnd* pParent);
	//�߰���_E
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMODELFORM };
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


