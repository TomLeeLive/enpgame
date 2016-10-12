#pragma once
#include "GBasisLib_0.h"
#include "GModelViewCamera.h"
#include "GObject.h"

//�Ӽ�:�����:���->C:\Program Files\Autodesk\3ds Max 2016\3dsmax.exe
class Sample : public GBasisLib_0
{
public:
	GGbsObj		m_tbsobj;
	GObject     m_tObj;
	shared_ptr<GModelViewCamera >		m_pMainCamera;
	D3DXMATRIX m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
	void		AddObject();
public:
	Sample(void);
	virtual ~Sample(void);
};
