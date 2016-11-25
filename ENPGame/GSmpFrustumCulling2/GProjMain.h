#pragma once

enum G_OBJECT {
	G_OBJ_LAB = 0,
	//G_OBJ_DROPSHIP,
	//G_OBJ_CAR1,
	//G_OBJ_CAR2,
	G_OBJ_CNT
};

//오브젝트 위치
#define G_OBJ_LOC_LAB _T("data/object/lab/lab.GBS")
#define G_OBJ_LOC_DROPSHIP_LAND _T("data/object/dropship/dropship_land.GBS")
#define G_OBJ_LOC_CAR _T("data/object/car/car.GBS")

//오브젝트 매니저 등록 이름.
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_OBJ_NAME_DROPSHIP_LAND L"dropship_land.GBS"
#define G_OBJ_NAME_CAR L"car.GBS"

//셰이더 파일 위치
#define G_SHA_PLANE L"data/shader/plane.hlsl"
#define G_SHA_LINE L"data/shader/line.hlsl"
#define G_SHA_BOX L"data/shader/box.hlsl"

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

	//obj
	GModel*		m_Obj[G_OBJ_CNT];
	D3DXMATRIX  m_matObjScl[G_OBJ_CNT], m_matObjRot[G_OBJ_CNT], m_matObjTrans[G_OBJ_CNT];
	D3DXMATRIX	m_matObjWld[G_OBJ_CNT];

	//frustum
	D3DXVECTOR3	m_vFrustum[8];	/// 프러스텀을 구성할 정점 8개
	G_PLANE		m_Plane[6];
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