#pragma once

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif

#include "GCoreLibV2.h"
#include "map/GMap.h"
#include "TMatrixEx.h"
#include "GCamera.h"

#include "GZombie.h"

const int MAX_OBJECT_CNT = 3;
//struct SHADOW_CONSTANT_BUFFER
//{
//	D3DXMATRIX			g_matShadow;
//	float				g_ShadowID;
//	float				g_iNumKernel;
//	float				fZ, fW;
//};

//오브젝트 위치
#define G_OBJ_LOC_LAB _T("data/object/building/lab.GBS")
#define G_OBJ_LOC_DROPSHIP_LAND _T("data/object/dropship/dropship_land.GBS")
#define G_OBJ_LOC_CAR _T("data/object/car/car.GBS")

//오브젝트 매니저 등록 이름.
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_OBJ_NAME_DROPSHIP_LAND L"dropship_land.GBS"
#define G_OBJ_NAME_CAR L"car.GBS"

#define G_SHA_OBJ_DIFFUSE L"data/shader_shadow/Obj_Diffuse_shadow.hlsl"
#define G_SHA_OBJ_DIFFUSE_SHADOW L"data/shader_shadow/Obj_Specular_shadow.hlsl"
#define G_SHA_OBJ_SPECULAR L"data/shader/Obj_Specular.hlsl"
#define G_SHA_OBJ_SPECULAR_SHADOW L"data/shader_shadow/Obj_Specular_shadow.hlsl"

class GProjMain : public GCoreLibV2
{
public:	
	GModel*		m_Obj;
	D3DXMATRIX	m_matObjOBB;
	D3DXMATRIX	m_matObjWld;
	D3DXMATRIX  m_matObjScl, m_matObjRot, m_matObjTrans;

	vector<shared_ptr<GZombie>>	m_HeroObj;


	shared_ptr<GCamera>	m_pMainCamera;
	GMap				m_CustomMap;	
	GBoxShape*			m_pBoxShape;
	D3DXVECTOR3			m_vLightPos;
	float				m_fObjID[MAX_OBJECT_CNT];
	D3DXMATRIX			m_matWorld[MAX_OBJECT_CNT];
	D3DXMATRIX			m_matShadow;
	D3DXMATRIX			m_matTexture;
	D3DXMATRIX			m_matShadowView;
	D3DXMATRIX			m_matShadowProj;
	bool				m_bColorTexRender;
	//--------------------------------------------------------------------------------------
	// 랜더타켓 및 깊이/스텐실 버퍼
	//--------------------------------------------------------------------------------------	
	GDxRT							m_RT;
	GPlaneShape*					m_pQuad;
	SHADOW_CONSTANT_BUFFER			m_cbShadow;
	ComPtr<ID3D11Buffer>			m_pShadowConstantBuffer;
	ComPtr<ID3D11VertexShader>		m_pShadowVS;
	ComPtr<ID3D11PixelShader>		m_pShadowPS;

	//ComPtr<ID3D11VertexShader>		m_pCharShadowVS;
	//ComPtr<ID3D11PixelShader>		m_pCharShadowPS;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	void		RenderShadow( D3DXMATRIX* matShadow,D3DXMATRIX* matView, D3DXMATRIX* matProj );
	void		RenderObject( D3DXMATRIX* matView, D3DXMATRIX* matProj );
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
public:
	GProjMain(void);
	~GProjMain(void);
};
