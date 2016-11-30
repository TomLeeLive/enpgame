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


	//frustum
	//D3DXVECTOR3	m_vFrustum[8];	/// ���������� ������ ���� 8��
	//G_PLANE		m_Plane[6];

	ComPtr<ID3D11PixelShader>   m_pPixelShader;// ���ν��� ���� �Ƚ����̴�
	G_BOX m_gBoxBase;

	D3DXMATRIX					m_matBoxWorld[NUM_OBJECTS];
	D3DXVECTOR3					m_vBoxPosition[NUM_OBJECTS];
	D3DXVECTOR4					m_vBoxColor[NUM_OBJECTS];

	G_BOX						m_GBox[NUM_OBJECTS];
	GShape*						m_pBoxShape;

	//MapBB
	vector<D3DXMATRIX>			m_matCellWorld;
	//vector<D3DXVECTOR3>			m_vCellPosition;
	vector<G_BOX>				m_GMapBox;
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