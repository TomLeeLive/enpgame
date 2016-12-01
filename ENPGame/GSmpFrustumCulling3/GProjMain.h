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
	GMap			m_CustomMap;
	GLineShape				m_LineDraw;

	ComPtr<ID3D11PixelShader>   m_pPixelShader;// ���ν��� ���� �Ƚ����̴�
	G_BOX m_gBoxBase;

	D3DXMATRIX					m_matBoxWorld[NUM_OBJECTS];
	D3DXVECTOR3					m_vBoxPosition[NUM_OBJECTS];
	D3DXVECTOR4					m_vBoxColor[NUM_OBJECTS];

	G_BOX						m_GBox[NUM_OBJECTS];
	GShape*						m_pBoxShape;

	//MapBB
	GBBox						m_pBBox;
	GBoxShape					m_pBox;
	D3DXMATRIX					m_matWorld;
	vector<GBBox>						m_pBBox2;
	vector<GBoxShape>					m_pBox2;
	TMapDesc MapDesc;
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
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����