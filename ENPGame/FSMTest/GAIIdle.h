#pragma once
#include "GSeq.h"
class GAIIdle : public GSeq
{
private:
	static GAIIdle *pInstance_;
public:
	static GSeq* CreateInstance()
	{
		if (pInstance_ == 0) pInstance_ = new GAIIdle;
		return pInstance_;
	}
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	GShape*		m_Box1;
	GShape*		m_Box2;
	GShape*		m_Box3;
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIIdle();
protected:
	GAIIdle();
};


