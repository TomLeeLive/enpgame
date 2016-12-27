#pragma once

#define NUM_OBJECTS 100

enum G_OBJECT {
	G_OBJ_LAB = 0,	
	G_OBJ_DROPSHIP,
	G_OBJ_CAR1,
	G_OBJ_CAR2,

	G_OBJ_LAB1,
	G_OBJ_LAB2,
	G_OBJ_LAB3,
	G_OBJ_LAB4,

	G_OBJ_LAB5,
	G_OBJ_LAB6,
	G_OBJ_LAB7,
	G_OBJ_LAB8,
	G_OBJ_LAB9,
	G_OBJ_LAB10,
	G_OBJ_LAB11,
	G_OBJ_LAB12,
	G_OBJ_LAB13,
	G_OBJ_LAB14,

	G_OBJ_LAB15,
	G_OBJ_LAB16,
	G_OBJ_LAB17,
	G_OBJ_LAB18,
	G_OBJ_LAB19,
	G_OBJ_LAB20,
	G_OBJ_LAB21,
	G_OBJ_LAB22,
	G_OBJ_LAB23,
	G_OBJ_LAB24,
	G_OBJ_LAB25,

	G_OBJ_LAB26,
	G_OBJ_LAB27,
	G_OBJ_LAB28,

G_OBJ_CNT


	

};

//������Ʈ ��ġ
#define G_OBJ_LOC_LAB _T("data/object/building/lab.GBS")
#define G_OBJ_LOC_DROPSHIP_LAND _T("data/object/dropship/dropship_land.GBS")
#define G_OBJ_LOC_CAR _T("data/object/car/car.GBS")

//������Ʈ �Ŵ��� ��� �̸�.
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_OBJ_NAME_DROPSHIP_LAND L"dropship_land.GBS"
#define G_OBJ_NAME_CAR L"car.GBS"

//���̴� ���� ��ġ
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
	bool					m_bDebugMode;
	GCamera*				m_pMainCamera;	
	GLineShape				m_LineDraw;
		
	//--------------------------------------------------------------------------------------
	// ��
	//--------------------------------------------------------------------------------------
	GHeightMap		m_HeightMap;

	
	//--------------------------------------------------------------------------------------
	// ������Ʈ
	//--------------------------------------------------------------------------------------
	GModel*		m_Obj[G_OBJ_CNT];
	D3DXMATRIX	m_matObjOBB[G_OBJ_CNT];
	D3DXMATRIX	m_matObjWld[G_OBJ_CNT];
	D3DXMATRIX  m_matObjScl[G_OBJ_CNT], m_matObjRot[G_OBJ_CNT], m_matObjTrans[G_OBJ_CNT];
	bitset<G_OBJ_CNT> m_Objbit;
	
	
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