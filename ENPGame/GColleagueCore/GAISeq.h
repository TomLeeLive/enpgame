//#include "GNewZombie.h"

#pragma once


class GAISeq 
{
public:
	CStopwatch m_Stopwatch;//for debug

	bool		m_bDebug;
	bool		m_bTime;

	//bool		m_bRTime;
	//bool		m_bRDebug;

	float fTime;
	GCharacter*	 pChar0;

	virtual bool Init(GNewZombie* iMyIndex) = 0;
	virtual bool Frame(GNewZombie* iMyIndex,D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
	void		InitGSeq() {

		m_bDebug = false;
		m_bTime = false;

	};

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GAISeq();
	GAISeq();
};

