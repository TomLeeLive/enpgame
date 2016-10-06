#pragma once
#include "GTemplate.h"
#include "GCharacter.h"
#include "GParser.h"

class GCharacterLoader : public GParser
{
public:
	BOOL			GetDataFromSkinMeshString( TCHAR* pString, VOID* pData0, VOID* pData1 ); 
public:
	GCharacterLoader() {};
	~GCharacterLoader() {};
};

class TCharMgr  : public GTemplateMap< GCharacter >, public GSingleton< TCharMgr >
{
private:
	friend class GSingleton<TCharMgr>;
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
	TCharMgr();
	virtual~TCharMgr();
};
#define I_CharMgr TCharMgr::GetInstance()
