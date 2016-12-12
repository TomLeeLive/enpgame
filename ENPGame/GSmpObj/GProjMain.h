#pragma once

#define G_OBJ_LOC_LAB _T("data/object/lab/lab.GBS")
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_SHA_OBJ_DIFFUSE L"data/shader/Obj_Diffuse.hlsl"

class GProjMain : public GCoreLibV2
{
public:
	GCamera*					m_pMainCamera;
	GModel*		m_Obj;
	D3DXMATRIX	m_matObjOBB;
	D3DXMATRIX	m_matObjWld;
	D3DXMATRIX  m_matObjScl, m_matObjRot, m_matObjTrans;

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