#pragma once


class GProjMain : public GCoreLibV2
{
public:
	GCamera*	m_pMainCamera;
	EffManager	m_EffManager;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	

public:
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //외부 연결 범위 선언