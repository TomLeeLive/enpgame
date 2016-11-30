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
	//D3DXVECTOR3	m_vFrustum[8];	/// 프러스텀을 구성할 정점 8개
	//G_PLANE		m_Plane[6];

	ComPtr<ID3D11PixelShader>   m_pPixelShader;// 프로스텀 전용 픽쉘쉐이더
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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언