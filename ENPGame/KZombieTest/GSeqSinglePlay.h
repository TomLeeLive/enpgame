#pragma once

//#define G_DEFINE_SHADOW 1

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
	int m_iEventNum;
		int m_iScriptNum;
	void							SetEventCamera(G_HERO hero);
	void							CheckHeroDead(int iChar);
//	bool							m_bGameOver;
	bool							m_bChatting;

	void							AddZomb(int iNum);
	void							ChangeZombState(int iNum, G_ZOMB_ST state);
	void							ChangeZombState(int iNum, TCHAR* str);

	TCHAR							m_pTextOutBuffer[256];
	int								m_iScore;					//점수 계산용
	int								m_fPlayTime;				//플레이 타임(생존시간) 출력용
	D3DXMATRIX						m_matWorld;
	bool							UpdateGunPosition();

	bool							FrameGun();
	GSelect							m_Select;
	G_RAY							m_Ray;
	bool							ChkOBBToRay(GBBox* pBox, G_RAY* pRay);
#ifdef G_MACRO_GAME_ADD
	bool							m_bDebugMode;		//디버그 모드 토글
	GGbsObj							m_ObjGun;

	G_HERO							m_CurrentHero;
	GCamera*						m_pCamera;
	shared_ptr<GCamera >			m_pDebugCamera;
	shared_ptr<GCamera >			m_pEventCamera;
	D3DXVECTOR3						m_vEventCamPos;
	vector<shared_ptr<GFPSCamera >> m_pFPSCamera;
#endif
#ifdef G_MACRO_EFFECT_ADD
#ifdef G_MACRO_EFFECT_TEST_ADD
	bool							UpdateGunEffectPosition();
#else
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
#endif
#ifdef G_MACRO_MAP_ADD
	//--------------------------------------------------------------------------------------
	// 스카이 박스
	//--------------------------------------------------------------------------------------
	shared_ptr<GN2Skybox>   		  m_pSkyBoxObj;
	//--------------------------------------------------------------------------------------
	// 오브젝트
	//--------------------------------------------------------------------------------------
	GGbsObj*		m_Obj[G_OBJ_CNT];
	//D3DXMATRIX	m_matObjOBB[G_OBJ_CNT];
	//D3DXMATRIX	m_matObjWld[G_OBJ_CNT];
	//D3DXMATRIX  m_matObjScl[G_OBJ_CNT], m_matObjRot[G_OBJ_CNT], m_matObjTrans[G_OBJ_CNT];
	bitset<G_OBJ_CNT> m_Objbit;

	GBBox m_Wall[G_BB_CNT];
	D3DXMATRIX m_matWallBB[G_BB_CNT];
	bitset<G_BB_CNT> m_Wallbit;
	//--------------------------------------------------------------------------------------
	// 쿼드트리
	//--------------------------------------------------------------------------------------
	GMap m_CustomMap;
	//GHeightMap		m_HeightMap;
	//GTileMap		m_HeightMap;
	//--------------------------------------------------------------------------------------
	// 쿼드트리
	//--------------------------------------------------------------------------------------
	//GQuadTree	m_QuadTree;
	
	//--------------------------------------------------------------------------------------
	// 디버깅 용도
	//--------------------------------------------------------------------------------------
	GLineShape		m_DrawLine;
	bool			m_bMapDebugRender;
	int				m_iDrawDepth;
	ComPtr<ID3D11PixelShader>   m_pPixelShader;// 프로스텀 전용 픽쉘쉐이더


	void		DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj);
	bool		DrawQuadLine(GNode* pNode);
#endif
#ifdef G_MACRO_CHAR_ADD	
public:
#ifdef G_MACRO_AI_ADD
	GAIZombieMgr		m_GAIZombMgr;
#else
	vector<shared_ptr<GN2Zombie>>	m_CharZombie;
#endif

	vector<shared_ptr<GHero>>		m_CharHero;
	bool		Load();
#endif
public:
	bool		InitValues();
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



