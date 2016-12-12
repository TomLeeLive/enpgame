#pragma once

//������Ʈ ��ġ
#define G_OBJ_LOC_LAB _T("data/object/lab/lab.GBS")
#define G_OBJ_LOC_DROPSHIP_LAND _T("data/object/dropship/dropship_land.GBS")
#define G_OBJ_LOC_CAR _T("data/object/car/car.GBS")

//������Ʈ �Ŵ��� ��� �̸�.
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_OBJ_NAME_DROPSHIP_LAND L"dropship_land.GBS"
#define G_OBJ_NAME_CAR L"car.GBS"

#define G_SHA_OBJ_DIFFUSE L"data/shader/Obj_Diffuse.hlsl"

class GProjMain : public GCoreLibV2
{
public:
	bool DrawDebug();
	GLineShape		m_LineDraw;

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
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};

extern GProjMain*	g_pMain; //�ܺ� ���� ���� ����