#pragma once



// GUICtrlForm �� ���Դϴ�.

class GUICtrlForm : public CFormView
{
	DECLARE_DYNCREATE(GUICtrlForm)

protected:
	GUICtrlForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GUICtrlForm();

	// �߰���_S
public:
	static GUICtrlForm* CreateOne(CWnd* pParent);
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


