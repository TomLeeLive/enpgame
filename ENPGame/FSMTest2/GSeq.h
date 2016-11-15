#pragma once
class GSeq 
{
public:
	static GSeq* CreateInstance() { return 0; }
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;

	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	GShape*		m_Box1;
	GShape*		m_Box2;
	GShape*		m_Box3;
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	virtual HRESULT		CreateResource() = 0;
	virtual HRESULT		DeleteResource() = 0;

	virtual int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	virtual ~GSeq();
protected:
	GSeq();
};

