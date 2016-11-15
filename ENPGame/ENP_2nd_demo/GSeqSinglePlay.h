#pragma once

enum G_OBJECT {
	G_OBJ_LAB = 0,
	G_OBJ_DROPSHIP,
	G_OBJ_CAR,
	G_OBJ_CAR1,	
	G_OBJ_CNT
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
	bool		m_bDebugCamera;
	GGbsObj		m_ObjGun;
	bool UpdateGunPosition();
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
	// 오브젝트
	//--------------------------------------------------------------------------------------
	//GGbsObj		m_tbsobj;

	GGbsObj		m_Obj[G_OBJ_CNT];
	D3DXMATRIX	m_matObjWorld[G_OBJ_CNT];
	D3DXMATRIX  matObjScale[G_OBJ_CNT], matObjRotation[G_OBJ_CNT], matObjTrans[G_OBJ_CNT];

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
	GCamera*				m_pCamera;
	shared_ptr<GCamera >	m_pDebugCamera;
	shared_ptr<GFPSCamera > m_pFPSCamera;
	D3DXMATRIX  m_matWorld;
#ifdef G_MACRO_CHAR_ADD	
public:


	//--------------------------------------------------------------------------------------
	// 파일 선택하여 로드( 단축기 : O )
	//--------------------------------------------------------------------------------------
	vector<shared_ptr<GHeroObj>>	m_HeroObj;
	T_STR_VECTOR m_LoadFiles;
	bool		Load();
	bool		LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);
#endif
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
	virtual ~GSeqSinglePlay();
protected:
	GSeqSinglePlay();

};



