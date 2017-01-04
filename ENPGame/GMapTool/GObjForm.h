#pragma once
#include "afxwin.h"



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
	CListBox m_listObj;
	//float m_fSclY;
	//float m_fSclZ;
	//float m_fRotX;
	//float m_fRotZ;
	float m_fScl;
	float m_fRotY;
	float m_fTransX;
	float m_fTransY;
	float m_fTransZ;
	afx_msg void OnBnClickedButton1();
	CListBox m_listMap;
	afx_msg void OnLbnSelchangeListobj();
	afx_msg void OnLbnSelchangeListmap();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
};

