#pragma once


// C2dDlgTap ��ȭ �����Դϴ�.

class C2dDlgTap : public CDialog
{
	DECLARE_DYNAMIC(C2dDlgTap)
public:
	C2dDlgTap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~C2dDlgTap();

public:
	CListBox m_list;
	//CString m_strValue;
	//CString m_strPath;
	//CString m_strPath2;
	CStdioFile file;
	CListBox *InsertList;
	CListBox *SaveList;
	CListBox *PlayList;

public:
	int SaveListIndex;
	int PlayListIndex;

#ifdef AFX_DESIGN_TIME// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOnbnclick2dopen();
	afx_msg void OnBnClickedOnbnclick2dsave();
	afx_msg void OnBnClickedOnbnclick2dplay();
	afx_msg void OnBnClickedButton1();
};
