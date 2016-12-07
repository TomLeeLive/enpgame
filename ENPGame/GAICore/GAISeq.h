//#include "GNewZombie.h"

#pragma once


class GAISeq 
{
public:
	CStopwatch m_Stopwatch;//for debug

	//float m_fDistance;
	//float m_fRandTime;
	//D3DXVECTOR3 m_vRDestLook;
	//D3DXVECTOR3 m_vZRight;
	//D3DXVECTOR3 m_vZUp;
	//D3DXVECTOR3 m_vLook;

	bool		m_bDebug;
	bool		m_bTime;

	//bool		m_bRTime;
	//bool		m_bRDebug;

	float fTime;
	GCharacter*	 pChar0;

	//static GAISeq* CreateInstance() { return 0; }
	//virtual bool Init(int iMyIndex) = 0;
	//virtual bool Frame(int iMyIndex) = 0;
	virtual bool Init(GNewZombie* iMyIndex) = 0;
	virtual bool Frame(GNewZombie* iMyIndex) = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
	void		InitGSeq() {
		//m_fDistance = 0.0f;
		m_bDebug = false;
		m_bTime = false;
		//m_vRDestLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//m_vZRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		//m_vZUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	};

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GAISeq();
	GAISeq();
protected:

};

