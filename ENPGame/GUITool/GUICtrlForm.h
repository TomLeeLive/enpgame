#pragma once



// GUICtrlForm 폼 뷰입니다.

class GUICtrlForm : public CFormView
{
	DECLARE_DYNCREATE(GUICtrlForm)

protected:
	GUICtrlForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GUICtrlForm();

	// 추가함_S
public:
	static GUICtrlForm* CreateOne(CWnd* pParent);
	//추가함_E
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


