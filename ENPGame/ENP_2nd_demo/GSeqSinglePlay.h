#pragma once

enum G_OBJECT {
	G_OBJ_LAB = 0,
	G_OBJ_DROPSHIP,
	G_OBJ_CAR1,
	G_OBJ_CAR2,	
	G_OBJ_CNT
};

enum G_HERO {
	G_HERO_TOM =0,
	G_HERO_JAKE,
	G_HERO_CNT
};

class GSeqSinglePlay : public GSeq
{
private:
	static GSeqSinglePlay *pInstance_;
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GSeqSinglePlay;
		return pInstance_;
	}

public:
	//텍스트----------------------------------------------------------------------------------------
#ifdef G_MACRO_TEXT_ADD
	GDirectWrite					m_Font;
	ComPtr<IDXGISurface1>			m_pBackBuffer = NULL;
#endif
	int								m_iScore;					//점수 계산용
	int								m_fPlayTime;				//플레이 타임(생존시간) 출력용
	//----------------------------------------------------------------------------------------------
	D3DXMATRIX						m_matWorld;
	bool							UpdateGunPosition();

	GSelect							m_Select;
	G_RAY							m_Ray;
	bool							ChkOBBToRay(GBBox* pBox, G_RAY* pRay);
#ifdef G_MACRO_GAME_ADD
	bool							m_bDebugCamera;
	GGbsObj							m_ObjGun;

	G_HERO							m_CurrentHero;
	GCamera*						m_pCamera;
	shared_ptr<GCamera >			m_pDebugCamera;
	vector<shared_ptr<GFPSCamera >> m_pFPSCamera;
#endif
#ifdef G_MACRO_EFFECT_ADD
public:
	GPlaneShape						m_BigPlane;
	shared_ptr<GSprite>				m_pSprite;
	ComPtr<ID3D11PixelShader>		m_pPS;
	D3DXVECTOR4						m_vMaterial;
	D3DXMATRIX						m_matPlaneWorld;
	D3DXMATRIX						m_mPlanWorld;
	

	shared_ptr<GPlaneShape>			m_pPlane;
	shared_ptr<GPlaneShape>			m_pScreen;
	//public:
	//	bool check; // play button check
	//	ComPtr<ID3D11BlendState>		m_pAlphaBlendFactor;
	//	ComPtr<ID3D11BlendState>		m_pAlphaBlend;
#endif
#ifdef G_MACRO_MAP_ADD
	//--------------------------------------------------------------------------------------
	// 스카이 박스
	//--------------------------------------------------------------------------------------
	shared_ptr<GN2Skybox>   		  m_pSkyBoxObj;
	//--------------------------------------------------------------------------------------
	// 오브젝트
	//--------------------------------------------------------------------------------------
	//GGbsObj		m_tbsobj;

	GGbsObj		m_Obj[G_OBJ_CNT];
	D3DXMATRIX	m_matObjOBB[G_OBJ_CNT];
	D3DXMATRIX	m_matObjWld[G_OBJ_CNT];
	D3DXMATRIX  m_matObjScl[G_OBJ_CNT], m_matObjRot[G_OBJ_CNT], m_matObjTrans[G_OBJ_CNT];

	//--------------------------------------------------------------------------------------
	// 쿼드트리
	//--------------------------------------------------------------------------------------
	GMap m_CustomMap;
	//--------------------------------------------------------------------------------------
	// 쿼드트리
	//--------------------------------------------------------------------------------------
	GQuadTree	m_QuadTree;
	
	//--------------------------------------------------------------------------------------
	// 디버깅 용도
	//--------------------------------------------------------------------------------------
	GLineShape		m_DrawLine;
	bool			m_bDebugRender;
	int				m_iDrawDepth;
	ComPtr<ID3D11PixelShader>   m_pPixelShader;// 프로스텀 전용 픽쉘쉐이더


	void		DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj);
	bool		DrawQuadLine(GNode* pNode);
#endif
#ifdef G_MACRO_CHAR_ADD	
public:
	vector<shared_ptr<GZombie>>	m_CharZombie;
	vector<shared_ptr<GHero>>	m_CharHero;
	bool		Load();
#endif
public:

	bool        InitGame();
	bool        InitMap();
	bool		InitChar();
	bool		InitObj();
	bool		InitEffect();

	bool        FrameGame();
	bool        FrameMap();
	bool		FrameChar();
	bool		FrameObj();
	bool		FrameEffect();

	bool        RenderGame();
	bool        RenderMap();
	bool		RenderChar();
	bool		RenderObj();
	bool		RenderEffect();

	bool        ReleaseGame();
	bool        ReleaseMap();
	bool		ReleaseChar();
	bool		ReleaseObj();
	bool		ReleaseEffect();

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
	virtual ~GSeqSinglePlay();
protected:
	GSeqSinglePlay();

};



