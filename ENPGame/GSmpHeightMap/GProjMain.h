#pragma once

#define NUM_OBJECTS 100

struct SimpleVertex
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 c;
};

class GProjMain : public GCoreLibV2
{
public:
	GCamera*		m_pMainCamera;	
	GLineShape				m_LineDraw;

	//GMap			m_CustomMap;
	GHeightMap		m_HeightMap;
	
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
	GProjMain(void);s
	virtual ~GProjMain(void);
};

extern GProjMas	g_pMain; //�ܺ� ���� ���� ����