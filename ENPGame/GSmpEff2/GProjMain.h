#pragma once



class GProjMain : public GCoreLibV2
{
public:
	GCamera*	m_pMainCamera;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();

	//--------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//-------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	GCamera*						m_pCamera;
	D3DXMATRIX						m_matWorld;
	GTimer							m_Timer;
public: //Effect
	GPlaneShape						m_BigPlane;
	shared_ptr<GSprite>				m_pSprite;
	ComPtr<ID3D11PixelShader>		m_pPS;
	D3DXVECTOR4						m_vMaterial;
	D3DXMATRIX						m_matPlaneWorld;
	D3DXMATRIX						m_mPlanWorld;
	shared_ptr<GPlaneShape>			m_pPlane;
	shared_ptr<GPlaneShape>			m_pScreen;

public:
	GProjMain();
	~GProjMain();
};

