//#include "GAICol.h"

#pragma once


class GAIColSeq 
{
public:
	CStopwatch m_Stopwatch;//for debug

	bool		m_bDebug;
	bool		m_bTime;

	//bool		m_bRTime;
	//bool		m_bRDebug;

	float fTime;
	GCharacter*	 pChar0;

	virtual bool Init(GAICol* iMyIndex) = 0;
	virtual bool Frame(GAICol* iMyIndex,D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
	void		InitGSeq() {

		m_bDebug = false;
		m_bTime = false;

	};

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GAIColSeq();
	GAIColSeq();
};

