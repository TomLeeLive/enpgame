#pragma once
#include "GBasisLib_0.h"
#include "GHeroObj.h"
#include "GCamera.h"


class Sample : public GBasisLib_0
{
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GHeroObj>>	m_HeroObj;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();	
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	Sample(void);
	virtual ~Sample(void);
};
