#pragma once
#include "GMesh.h"
#include "GParser.h"
#include "GBBox.h"
#include "GLight.h"

typedef GData<PNCT_VERTEX>				tTbsData;
typedef vector<shared_ptr<tTbsData>>	tTbsMeshData;



class GGbsObj : public GModel
{
public:
	//D3DXMATRIX	m_matObjOBB;
	//D3DXMATRIX	m_matObjWld;
	//D3DXMATRIX  m_matObjScl;
	//D3DXMATRIX  m_matObjRot;
	//D3DXMATRIX  m_matObjTrans;

	GBBox			m_OBB;
	bool			m_bAniLoop;
	void			ResetAni();
public:	
	tTbsMeshData	m_pData;
	GParser			m_Parser;
	vector<GMtrl>	m_Material;	
	DWORD			m_dwNumChildren;
public:
	bool		Frame();
	bool		Render(ID3D11DeviceContext*    pContext);
	virtual bool		Draw(ID3D11DeviceContext*    pContext, GModel* pParent);
	bool		Release();
	bool		ResetResource();
	////////////////////////////////////////////////
	//  ������Ʈ �ε� ���� �Լ�
	////////////////////////////////////////////////
	int			GetMeshCounter() { return m_pData.size(); }
	bool		Load(ID3D11Device* pd3dDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread = false);
	bool		Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, G_LIGHT_TYPE type);
	//  �� ���� �ε�
	bool		LoadScene( const TCHAR* strFileName );
	//  ���͸��� ���� �ε�
	bool		LoadMaterial();
	void		LoadMaterialHeader(GMtrl* pMtrl);
	void		LoadTexMap(	GMtrl* pMtrl,T_STR szDirName );
	//  ������Ʈ ���� �ε�
	bool		LoadObject();
	int			LoadVertexIndex(tTbsData* pMesh);
	//  ���ϸ��̼� ���� �ε�
	void		LoadAnimation(GMesh* pMesh);
	bool		LoadAnimationTrack( int iNumTrack, vector<shared_ptr<GAnimTrack>>& pTrackList );
	//--------------------------------------------------------------------------------------
	// ������ ���� ���� ����
	//--------------------------------------------------------------------------------------
	// �ε� �� ������ TMesh�� ��ȯ
	bool		Convert(ID3D11Device* pd3dDevice);
	// ���͸��� ����
	bool		SetMaterial();
	int			GetMapID( GMtrl* pMtrl, int iTexMapType=ID_GCORE_DI ); // �� �ε��� �˻�
    // ��Ӱ��� ����
	bool		InheriteCollect();
	GMesh*		SearchToCollects(T_STR	m_strParentName );
	//--------------------------------------------------------------------------------------
	// ���ϸ��̼� ���� ���� �Լ� 
	//--------------------------------------------------------------------------------------
	GAnimTrack*	SetDoublyLinkedList( GAnimTrack* pCurrentTrack, GAnimTrack* pPrev );//���� ���� ����Ʈ ����
	bool		GetAnimationTrack(	float fFrame,vector<shared_ptr<GAnimTrack>> pTrackList,
									GAnimTrack** ppStartTrack, 
									GAnimTrack** ppEndTrack );
	D3DXMATRIX	Interpolate(GMesh* pMesh,D3DXMATRIX* matParent, float fFrameTick );
	bool		UpdateBuffer();
	bool		CombineBuffer(ID3D11Buffer* pVB, ID3D11Buffer* pIB);
public:
	GGbsObj(void);
	virtual ~GGbsObj(void);
};
