#pragma once



// GAniCtrlForm �� ���Դϴ�.

class GAniCtrlForm : public CFormView
{
	DECLARE_DYNCREATE(GAniCtrlForm)

protected:
	GAniCtrlForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GAniCtrlForm();

	// �߰���_S
public:
	static GAniCtrlForm* CreateOne(CWnd* pParent);
	//�߰���_E
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GANICTRLFORM };
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


