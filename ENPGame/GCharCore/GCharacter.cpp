#include "GCharacter.h"
#include "GTimer.h"
#include "GObjMgr.h"

void GCharacter::SetActionFrame( int iStart, int iEnd, 
								 int iCharacterMatrixIndex,
								 int iModelMatrixIndex)
{
	m_iStartFrame	= iStart;
	m_iLastFrame	= iEnd;
	m_iCurrentFrame	= (float)iStart;	
	m_fFrame		= m_iStartFrame;	
	
	if( iCharacterMatrixIndex  >= 0)
	{
		m_iMatrixIndex  = iCharacterMatrixIndex; 		
	}
	if( iModelMatrixIndex >= 0 )
	{
		SeGModelMaterixID(iModelMatrixIndex);
	}
}
void GCharacter::SeGModelMaterixID(int iMatrixIndex)
{
	for( int iObj=0; iObj < m_pModelList.size(); iObj++ )
	{	
		m_pSubObjList[iObj]->SetMatrixIndex(iMatrixIndex );
	}
}

bool GCharacter::Add(	ID3D11Device* pd3dDevice,
						ID3D11DeviceContext*    pImmediateContext,
						const TCHAR* strSkinFileName, 
						const TCHAR* strSkinShaderName, 		
						int	iMatrixIndex,
						int iModelMatrixIndex,
						int iAniLoop,
						D3DXVECTOR3 vMin,
						D3DXVECTOR3 vMax )
{
	if( !_tcsicmp(strSkinFileName, _T("null")) )
	{
		return false;
	}
	
	if(!Load(pd3dDevice,strSkinFileName, strSkinShaderName )  )
	{
		return false;
	}	

	m_pBoneObject = (GBoneObj*)I_ObjMgr.GetPtr( iMatrixIndex );
	// 기본값 = 전체 프레임을 에니메이션 한다.
	SetActionFrame( m_pBoneObject->m_Scene.iFirstFrame, 
					m_pBoneObject->m_Scene.iLastFrame,
					iMatrixIndex,iModelMatrixIndex);
	m_iAniLoop = iAniLoop;
	m_vMin = vMin;
	m_vMax = vMax;
	return true;		
}
bool GCharacter::Init()
{
	GObject::Init();		
	return true;
}
bool GCharacter::Render(ID3D11DeviceContext*    pContext)
{	
	m_pBoneObject->m_pMatrix = m_pMatrix;
	// 메쉬 랜더링
	GObject::Render(pContext);
	// 본 오브젝트 랜더링
	m_pBoneObject->Render(pContext);	
	return true;
}
void GCharacter::SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj )
{	
	GObject::SetMatrix(pWorld, pView, pProj );
	m_pBoneObject->SetMatrix(pWorld, pView, pProj );		
}
bool GCharacter::Release()
{
	GObject::Release();	
	return true;
}

bool GCharacter::Frame()
{	
	_ASSERT( m_pBoneObject );
	//m_fLerpTime *= 0.1f;
	m_fFrame += ( g_fSecPerFrame * m_pBoneObject->m_Scene.iFrameSpeed );		
	m_iCurrentFrame = (int)m_fFrame;
	// 1프레임 사이 간격
	m_fLerpTime = m_fFrame - m_iCurrentFrame;

	if( m_pBoneObject->AniFrame(	m_iCurrentFrame,
										m_fLerpTime,
										m_iStartFrame,
										m_iLastFrame,
										m_pMatrix ))
	{
		m_iCurrentFrame = m_iStartFrame;
		m_fFrame = (float)m_iStartFrame;
	}
	
	GObject::Frame();	
	return true;
}

GCharacter::GCharacter(void)
{
	m_vMin = D3DXVECTOR3(-1.5f, -1.5f, -1.5f);
	m_vMax = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

	m_bAttack = false;
	m_iAniLoop = 1;
	m_iMatrixIndex = -1;
}

GCharacter::~GCharacter(void)
{
}

