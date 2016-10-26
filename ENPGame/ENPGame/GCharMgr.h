#pragma once
//#include "GTemplate.h"
//#include "GCharacter.h"
//#include "GParser.h"

class GCharacterLoader : public GParser
{
public:
	BOOL			GetDataFromSkinMeshString( TCHAR* pString, VOID* pData0, VOID* pData1 ); 
public:
	GCharacterLoader() {};
	~GCharacterLoader() {};
};

class GCharMgr  : public GTemplateMap< GCharacter >, public GSingleton< GCharMgr >
{
private:
	friend class GSingleton<GCharMgr>;
public:
	GCharacterLoader				m_Parser;	
public:	
	int			Create(	ID3D11Device* pd3dDevice, 
						ID3D11DeviceContext*    pImmediateContext,
						const TCHAR* strFileName, 
						const TCHAR* strShaderName, 
						int iMatrixIndex = -1);
	bool		Load(	ID3D11Device* pd3dDevice, 
						ID3D11DeviceContext*    pImmediateContext,
						const TCHAR* strFileName);
private:
	GCharMgr();
	virtual~GCharMgr();
};
#define I_CharMgr GCharMgr::GetInstance()
