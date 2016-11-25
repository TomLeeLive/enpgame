#pragma once

struct SimpleVertex
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 c;
};

class GProjMain : public GCoreLibV2
{
public:
	GCamera	 m_MainCamera;
	GShape* m_pBoxShape;
	ComPtr<ID3D11PixelShader> m_pPixelShader;
	GShape* m_pLine;

	D3DXMATRIX m_matBoxWorld;
	D3DXVECTOR3 m_vBoxPosition[NUM_OBJECTS];
	D3DXVECTOR4 m_vBoxColor[NUM_OBJECTS];

	G_BOX m_GBox[NUM_OBJECTS];
	G_BOX m_GBoxBase;

	//GDxRT m_GBox[NUM_OBJECTS];
	HRESULT ScreenViewPort(UINT iWidth, UINT iHeight);

	float m_fCameraYaw;
	float m_fCameraPitch;
	float m_fCameraRoll;
	float m_fRadius;

	bool DrawDebug(bool bDrawString, bool bDrawLine);

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