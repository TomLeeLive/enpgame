#pragma once
#include "afxwin.h"


// C2dDlgTap 대화 상자입니다.

class C2dDlgTap : public CDialog
{
	DECLARE_DYNAMIC(C2dDlgTap)
public:
	C2dDlgTap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~C2dDlgTap();

public:
	CKEffectToolApp* p_CParctice = (CKEffectToolApp*)AfxGetApp();
	CListBox m_list;
	CString m_strOpen;
	CString m_strSave;
	CString m_strPlay;
	CString m_result;
	CString m_temp;
	CString m_FileName;

	CStdioFile file;

	CListBox *OpenList;
	CListBox *SaveList;
	CListBox *PlayList;

public:
	int SaveListIndex;
	int PlayListIndex;

#ifdef AFX_DESIGN_TIME// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOnbnclick2dopen();
	afx_msg void OnBnClickedOnbnclick2dsave();
	afx_msg void OnBnClickedOnbnclick2dplay();
	afx_msg void OnEnUpdate2dX();
	float LblValue_X;
	float LblValue_Y;
	float LblValue_Z;
};
