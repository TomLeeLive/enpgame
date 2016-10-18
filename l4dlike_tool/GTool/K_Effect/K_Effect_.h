
// K_Effect_.h : K_Effect_ 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "GBasisLib_0.h"
#include "GCamera.h"



// CK_Effect_App:
// 이 클래스의 구현에 대해서는 K_Effect_.cpp을 참조하십시오.
//

class CK_Effect_App : public CWinApp, public GBasisLib_0
{
public:
	CK_Effect_App();
	shared_ptr<GCamera> m_pMainCamera;
	D3DXMATRIX m_matWorld;

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnIdle(LONG lCount);
};


extern CK_Effect_App theApp;
