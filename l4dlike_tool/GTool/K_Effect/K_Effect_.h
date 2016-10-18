
// K_Effect_.h : K_Effect_ ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "GBasisLib_0.h"
#include "GCamera.h"



// CK_Effect_App:
// �� Ŭ������ ������ ���ؼ��� K_Effect_.cpp�� �����Ͻʽÿ�.
//

class CK_Effect_App : public CWinApp, public GBasisLib_0
{
public:
	CK_Effect_App();
	shared_ptr<GCamera> m_pMainCamera;
	D3DXMATRIX m_matWorld;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnIdle(LONG lCount);
};


extern CK_Effect_App theApp;
