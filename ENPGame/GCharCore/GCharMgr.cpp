#include "GCharMgr.h"
#include "GObjMgr.h"

BOOL	GCharacterLoader::GetDataFromSkinMeshString( TCHAR* pString, VOID* pData0, VOID* pData1 ) 
{
	TCHAR szPath_0[MAX_PATH] = TEXT("");
	TCHAR szPath_1[MAX_PATH] = TEXT("");

	_fgetts( m_pBuffer, 256, m_pStream );		
	_stscanf(m_pBuffer, _T("%s%s%s"), m_pString, szPath_0, szPath_1 );		
	if(!_tcsicmp(m_pString,pString))
	{
		_tcscpy( (TCHAR*)pData0, &szPath_0[0] );																	
		_tcscpy( (TCHAR*)pData1, &szPath_1[0] );	
		return TRUE;
	}
	return FALSE;
}


int		GCharMgr::Create(	ID3D11Device* pd3dDevice, 
							ID3D11DeviceContext*    pImmediateContext,
							const TCHAR* strFileName, 
							const TCHAR* strShaderName, 
							int		iMatrixIndex )
{
	TCHAR szFileName[256];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];	

	// 종복 방지 
	if( strFileName )
	{
										
		_tsplitpath_s( strFileName, Drive, Dir, FName, Ext );						
		Ext[4]= 0;	
		_stprintf_s( szFileName, _T("%s%s"), FName, Ext );
		
		for( TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++) 
		{
			GCharacter *pPoint = (GCharacter *)(*itor).second;
			if( !_tcsicmp( pPoint->m_szName.c_str(), szFileName ) ) 
			{
				return (*itor).first;
			}
		}
	}

	GCharacter* pChild = 0; 
	SAFE_NEW( pChild, GCharacter );
	pChild->m_szName = szFileName;

	pChild->m_pBoneObject = (GBoneObj*)I_ObjMgr.GetPtr( iMatrixIndex );
	// 기본값 = 전체 프레임을 에니메이션 한다.
	pChild->SetActionFrame( pChild->m_pBoneObject->m_Scene.iFirstFrame, 
							pChild->m_pBoneObject->m_Scene.iLastFrame,
							iMatrixIndex);

	/*if( pChild->Add( pd3dDevice,pImmediateContext, 
					 strFileName, strShaderName, 
					 iMatrixIndex ) )*/
	{
		TMap.insert( make_pair( m_iCurIndex++, pChild ) );	
		return m_iCurIndex-1;
	}
	return -1;	
};
bool	GCharMgr::Load(	ID3D11Device* pd3dDevice, 
								ID3D11DeviceContext*    pImmediateContext,
								const TCHAR* strFileName )
{
	TCHAR* Sections[] = {   _T("#SKN_UPPER_BODY_COUNT"), 	_T("#SKN_UPPER_BODY"),
							_T("#SKN_LOWER_BODY_COUNT"),	_T("#SKN_LOWER_BODY"),
							_T("#SKN_ARM_COUNT"),		_T("#SKN_ARM"),
							_T("#SKN_HAND_COUNT"),		_T("#SKN_HAND"),
							_T("#SKN_FOOT_COUNT"),		_T("#SKN_FOOT"),
							_T("#SKN_FACE_COUNT"),		_T("#SKN_FACE"),
							_T("#SKN_HAIR_COUNT"),		_T("#SKN_HAIR"),
							_T("#SKN_WEAPON_COUNT"),	_T("#SKN_WEAPON"),
							_T("#SKN_DEFENSE_COUNT"),	_T("#SKN_DEFENSE"),
							_T("#SKN_ETCETERA_COUNT"),	_T("#SKN_ETCETERA"),};


	int iNumSection = sizeof(Sections) / sizeof(Sections[0]);

	m_Parser.OpenStream(strFileName);
	TCHAR	strCharacterName[MAX_PATH] = {0, };
	TCHAR	strMeshName[MAX_PATH] = {0, };
	TCHAR	strShaderName[MAX_PATH] = {0, };
	TCHAR	strMatrixName[MAX_PATH] = {0, };
	TCHAR	strActionName[MAX_PATH] = { 0, };

	int		iNumCharacter = 0;
	int		iNumActions = 0;
	int		iAniLoop = 1;

	float	fMinX = 0.0f;
	float	fMinY = 0.0f;
	float	fMinZ = 0.0f;
	float	fMaxX = 0.0f;
	float	fMaxY = 0.0f;
	float	fMaxZ = 0.0f;

	if( m_Parser.GetDataFromFileLoop(_T("#NUM_OF_CHARACTER"), &iNumCharacter, INT_DATA ) )
	{
		float a,b,c;
		for( int iNum=0; iNum < iNumCharacter; iNum++ )
		{
			m_Parser.GetDataFromFileLoop(_T("#CHAR_NAME"),  strCharacterName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("#SHADER_FILE"), strShaderName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("#MATRIX_FILE"), strMatrixName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("#ACTION_LOOP"), &iAniLoop, INT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#ACTION_TABLE"), &iNumActions, INT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MIN_X"), &fMinX, FLOAT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MIN_Y"), &fMinY, FLOAT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MIN_Z"), &fMinZ, FLOAT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MAX_X"), &fMaxX, FLOAT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MAX_Y"), &fMaxY, FLOAT_DATA);
			m_Parser.GetDataFromFileLoop(_T("#OBB_MAX_Z"), &fMaxZ, FLOAT_DATA);

			//m_Parser.GetDataFromFileLoop(_T("*WORLDPOSITION"), 
			//	&vPos, VERTEX_DATA);

			int		iNumSkin	= 0;
			GCharacter* pChar	= 0;
			int iCharacterIndex	= -1;
			int iMatrixIndex	= -1;
			// 케릭터 전체에서 사용
			if( _tcsicmp( strMatrixName, _T("null")) )
			{				
				iMatrixIndex = I_ObjMgr.Load(pd3dDevice, strMatrixName, _T("MatrixViewer.hlsl"));
			}	

			iCharacterIndex = Create(	pd3dDevice,pImmediateContext, 
										strCharacterName, strShaderName,
										iMatrixIndex);
			if( iCharacterIndex < 0) continue;
			pChar = GetPtr( iCharacterIndex );

			for( int iMesh = 0; iMesh < iNumSection; iMesh+=2 )
			{
				m_Parser.GetDataFromFileLoop( Sections[iMesh], &iNumSkin, INT_DATA);
				for( int iSkin=0; iSkin < iNumSkin; iSkin++ )
				{
					m_Parser.GetDataFromSkinMeshString(Sections[iMesh+1], strMeshName, strMatrixName);	
					int iModelMatrixIndex	= -1;
					if( _tcsicmp( strMatrixName, _T("null")) )
					{
						// 메쉬 단위로 별도의 매트릭스 사용시 적용됨.
						iModelMatrixIndex = I_ObjMgr.Load(pd3dDevice, strMatrixName, _T("MatrixViewer.hlsl"));						
					}					
					if( pChar  )
					{
						pChar->Add(	pd3dDevice, pImmediateContext,
									strMeshName, strShaderName, 
									iMatrixIndex, 
									iModelMatrixIndex,
									iAniLoop,
									D3DXVECTOR3(fMinX, fMinY, fMinZ),
									D3DXVECTOR3(fMaxX, fMaxY, fMaxZ));
					}			
				}
			}			
		}
	}
	m_Parser.CloseStream();	
	return true;
}
GCharMgr::GCharMgr()
{
}
GCharMgr::~GCharMgr()
{
}

