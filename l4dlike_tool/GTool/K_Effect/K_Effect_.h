
// K_Effect_.h : K_Effect_ ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CK_Effect_App:
// �� Ŭ������ ������ ���ؼ��� K_Effect_.cpp�� �����Ͻʽÿ�.
//

class CK_Effect_App : public CWinApp
{
public:
	CK_Effect_App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK_Effect_App theApp;
