#pragma once



// GObjectForm 폼 뷰입니다.

class GObjectForm : public CFormView
{
	DECLARE_DYNCREATE(GObjectForm)

protected:
	GObjectForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddObject();
	afx_msg void OnBnClickedAddObb();
};


