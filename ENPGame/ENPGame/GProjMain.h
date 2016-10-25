#pragma once
#include "GBasisLib_0.h"
#include "GHeroObj.h"
#include "GCamera.h"

#define G_MACRO_MAP_ADD		1
#define G_MACRO_EFFECT_ADD   1

#ifdef G_MACRO_MAP_ADD
#include "GMiniMap.h"
#include "map/GNoiseMap.h"
#include "map/GQuadTreeIndex.h"
#include "map/GMapObject.h"
#endif

class GProjMain : public GBasisLib_0
{
#ifdef G_MACRO_MAP_ADD
	//--------------------------------------------------------------------------------------
	// 오브젝트
	//--------------------------------------------------------------------------------------
	//GMapObject*			m_pMapObj;
	//GBoxShape*			m_pBoxs;
	//--------------------------------------------------------------------------------------
	// 쿼드트리
	//--------------------------------------------------------------------------------------
	GQuadTreeIndex	m_QuadTree;
	//--------------------------------------------------------------------------------------
	// 노이즈 맵
	//--------------------------------------------------------------------------------------
	GNoiseMap		m_NoiseMap;
	//--------------------------------------------------------------------------------------
	// 미니맵
	//--------------------------------------------------------------------------------------
	//GMiniMap		m_MiniMap;
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
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	vector<shared_ptr<GHeroObj>>	m_HeroObj;
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
	//--------------------------------------------------------------------------------------
	// 파일 선택하여 로드( 단축기 : O )
	//--------------------------------------------------------------------------------------
	T_STR_VECTOR m_LoadFiles;
	bool		Load();
	bool		LoadFileDlg(TCHAR* szExt, TCHAR* szTitle);
public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
