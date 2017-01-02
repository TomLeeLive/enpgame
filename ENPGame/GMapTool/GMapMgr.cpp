#include "stdafx.h"
//#include "_stdafx.h"
#include "GMapMgr.h"


bool			GMapMgr::Init()
{





	return true; 
}

bool GMapGroup::CreateInit(int Width, int Height, float Distance, CString strTex, GCamera* pCamera)
{
	Init();

	//--------------------------------------------------------------------------------------
	//  맵 생성
	//--------------------------------------------------------------------------------------

	wchar_t szCharPath[MAX_PATH] = G_DEFINE_MAP_DIR;
	wchar_t szChar[MAX_PATH];
	//CString strString;
	//strString = "test";
	_tcscpy_s(szChar, 16, strTex.GetBuffer());
	_tcscat_s(szCharPath, szChar);

	//theApp.m_MapDesc.strTextureFile = m_strCharName;

	//m_MapDesc = { Width, Height, Distance, 0.1f,L"data/sand.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,		
		//Distance, 0.1f,
		20.0f, 1.0f,
		szCharPath, 
		G_DEFINE_MAP_SHADER };

	if (!m_HeightMap.Load(m_MapDesc))
	{
		return false;
	}
	//m_CustomMap.Init(g_pd3dDevice, g_pImmediateContext);
	//if (FAILED(m_CustomMap.Load(m_MapDesc))) { return false; }
	//--------------------------------------------------------------------------------------
	//  쿼드 트리
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(m_MapDesc.iNumCols, m_MapDesc.iNumRows);
	m_QuadTree.Update(g_pd3dDevice, pCamera);


}
bool			GMapMgr::Frame(GCamera* pCamera, GInput* pInput)
{



	//--------------------------------------------------------------------------------------
	// add
	//--------------------------------------------------------------------------------------
	//2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;


	//if (m_vecMapGroup.size() == 0)
	//	return false;
	if (m_iMapSelected == -1)
		return false;
	
	//for(int i = 0; i < m_vecMapGroup.size(); i++)
	m_vecMapGroup[m_iMapSelected]->Frame(pCamera, pInput);


	if (m_pObjSelected !=NULL && pInput !=NULL)
	{
		bool m_bChanged = false;
		D3DXMATRIX matScl, matRot;
		D3DXMatrixIdentity(&matScl);
		D3DXMatrixIdentity(&matRot);

		if (I_Input.KeyCheck(DIK_Y) == KEY_PUSH)
		{
			m_pObjSelected->m_iScl += 1;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_U) == KEY_PUSH)
		{
			m_pObjSelected->m_iScl -= 1;

			if (m_pObjSelected->m_iScl < 1)
				m_pObjSelected->m_iScl = 1;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_H) == KEY_PUSH)
		{
			m_pObjSelected->m_fRotY += 5;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_J) == KEY_PUSH)
		{
			m_pObjSelected->m_fRotY -= 5;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._43 += 200 * g_fSecPerFrame;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._43 += -200 * g_fSecPerFrame;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._41 += -200 * g_fSecPerFrame;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
		{
			m_pObjSelected->m_matObjTrans._41 += 200 * g_fSecPerFrame;

			m_bChanged = true;
		}
		if (m_bChanged) {
			D3DXMatrixScaling(&matScl, m_pObjSelected->m_iScl, m_pObjSelected->m_iScl, m_pObjSelected->m_iScl);
			D3DXMatrixRotationY(&matRot, D3DXToRadian(m_pObjSelected->m_fRotY));

			m_pObjSelected->m_matObjWld = matScl * matRot * m_pObjSelected->m_matObjTrans;
			return true;
		}
	}
	return false;
}

bool			GMapMgr::Render(GCamera* pCamera)
{

	//if (m_vecMapGroup.size() == 0)
	//	return false;

	if (m_iMapSelected == -1)
		return false;

	//for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[m_iMapSelected]->Render(pCamera);

	return true;
}
bool			GMapMgr::Release()
{
	for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[i]->Release();
	return true;
}
HRESULT			GMapMgr::CreateResource()
{


	return S_OK;
}
HRESULT			GMapMgr::DeleteResource()
{
	return S_OK;
}

void GMapMgr::GetStringFileName(VOID* pOutStr, VOID* pInStr) {

	vector<TCHAR*> vString;

	TCHAR* token = NULL;
	token = _tcstok((TCHAR*)pInStr, L"\\");
	while (token != NULL)
	{
		token = _tcstok(NULL, L"\\");
		vString.push_back(token);
	}
	_tcscpy((TCHAR*)pOutStr, vString[vString.size() - 2]);

	//TCHAR strDir[MAX_PATH] = L"data\\ui\\";
	//_tcsncat(strDir, (TCHAR*)pOutStr, _tcsclen((TCHAR*)pOutStr));

	//_tcscpy((TCHAR*)pOutStr, strDir);
}
void GMapMgr::GetStringFileNameWithPath(VOID* pOutStr, VOID* pInStr) {

	vector<TCHAR*> vString;

	TCHAR* token = NULL;
	token = _tcstok((TCHAR*)pInStr, L"\\");
	while (token != NULL)
	{
		token = _tcstok(NULL, L"\\");
		vString.push_back(token);
	}
	_tcscpy((TCHAR*)pOutStr, vString[vString.size() - 3]);

	TCHAR strDir[MAX_PATH] = L"data\\object\\";
	TCHAR strSlash[MAX_PATH] = L"\\";

	_tcsncat(strDir, (TCHAR*)pOutStr, _tcsclen((TCHAR*)pOutStr));

	_tcsncat(strDir, strSlash, _tcsclen(strSlash));

	_tcscpy((TCHAR*)pOutStr, vString[vString.size() - 2]);
	_tcsncat(strDir, (TCHAR*)pOutStr, _tcsclen((TCHAR*)pOutStr));

	_tcscpy((TCHAR*)pOutStr, strDir);
}

bool	GMapMgr::LoadMap(T_STR* strFile,GCamera* pCamera) {

	vector<CString> vecStr;

	FILE *pFile = NULL;

	const wchar_t * pStrFile = strFile->c_str();

	//int len = 256;
	char ctemp[MAX_PATH];

	//TCHAR -> char 변환
	WideCharToMultiByte(CP_ACP, 0, pStrFile, MAX_PATH, ctemp, MAX_PATH, NULL, NULL);

	pFile = fopen(ctemp, "r");
	if (pFile != NULL)
	{
		char strTemp[MAX_PATH];
		char *pStr;

		while (!feof(pFile))
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			if (pStr == NULL)
				break;

			// char -> TCHAR 변환
			TCHAR szUniCode[MAX_PATH] = { 0, };
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStr, strlen(pStr), szUniCode, MAX_PATH);

			// TCHAR -> CString 변환
			CString str;
			str.Format(L"%s", szUniCode);
			str.TrimRight();//개행문자 삭제
			vecStr.push_back(str);
		}
		fclose(pFile);
	}
	else
	{
		//에러 처리
		return false;
	}

	//하이트맵 처리 & 지형생성..(with 텍스처)
	auto pMap = make_shared<GMapGroup>();

	pMap->m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(pMap->m_HeightMap.CreateHeightMap((TCHAR*)(LPCTSTR)vecStr[1]/*strHeight*/)))
	{
		return false;
	}

	pMap->m_HeightMap.m_bStaticLight = true;

	pMap->CreateInit(0, 0, 0, vecStr[0]/*strTex*/, pCamera);

	_tcsncpy_s(pMap->m_strHeight, (TCHAR*)(LPCTSTR)vecStr[1], vecStr[1].GetLength());
	_tcsncpy_s(pMap->m_strTex, (TCHAR*)(LPCTSTR)vecStr[0], vecStr[0].GetLength());

	_tcsnset_s(m_strHeight, 0, MAX_PATH);
	_tcsnset_s(m_strTex, 0, MAX_PATH);
	_tcsncpy_s(m_strHeight, (TCHAR*)(LPCTSTR)vecStr[1], vecStr[1].GetLength());
	_tcsncpy_s(m_strTex, (TCHAR*)(LPCTSTR)vecStr[0], vecStr[0].GetLength());

	//오브젝트 생성..
	for (int i = 0; i < (vecStr.size() - MAP_TEX_INFO_LINES) / MAP_OBJ_INFO_LINES; i++) {
		int iItem = i * MAP_OBJ_INFO_LINES;
		
		//오브젝트 gbs 이름 출력								//vecStr[iItem +MAP_TEX_INFO_LINES + 0];
		//오브젝트 조명 reverse 여부 값 출력 true: 1, false: 0  //vecStr[iItem +MAP_TEX_INFO_LINES + 1];
		//오브젝트 조명 reverse 여부 값 출력 true: 1, false: 0  //vecStr[iItem +MAP_TEX_INFO_LINES + 2];
		//오브젝트 scl 값 출력									//vecStr[iItem +MAP_TEX_INFO_LINES + 3];
		//오브젝트 rot 값 출력									//vecStr[iItem +MAP_TEX_INFO_LINES + 4];
		//오브젝트 translation x 값 출력						//vecStr[iItem +MAP_TEX_INFO_LINES + 5];
		//오브젝트 translation y 값 출력						//vecStr[iItem +MAP_TEX_INFO_LINES + 6];
		//오브젝트 translation z 값 출력						//vecStr[iItem +MAP_TEX_INFO_LINES + 7];

		int iLightReverse	= _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 1]);
		int	iLightSpecular  = _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 2]);
		int iScl			= _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 3]);
		float fRotY			= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 4]);
		float fTransX		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 5]);
		float fTransY		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 6]);
		float fTransZ		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 7]);

		if (iLightSpecular == 1) {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR_REVERSE, G_LIGHT_TYPE_SPECULAR);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR,G_LIGHT_TYPE_SPECULAR);
		}
		else {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE_REVERSE);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE);
		}


		auto objData = make_shared<GObjData>();

		_tcsncpy_s(objData->m_strName, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], vecStr[iItem + MAP_TEX_INFO_LINES + 0].GetLength());

		TCHAR strObjName[MAX_PATH];

		_tcsncpy_s(strObjName, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], vecStr[iItem + MAP_TEX_INFO_LINES + 0].GetLength());

		GetStringFileName(strObjName, strObjName);

		objData->m_pObj = (GGbsObj*)I_ObjMgr.GetPtr(strObjName);

		//s, r, t 설정.
		D3DXMATRIX matScl, matRot;
		D3DXMatrixIdentity(&matScl);
		D3DXMatrixIdentity(&matRot);
		objData->m_iScl = iScl;
		objData->m_fRotY = fRotY;
		D3DXMatrixScaling(&matScl, objData->m_iScl, objData->m_iScl, objData->m_iScl);
		D3DXMatrixRotationY(&matRot, D3DXToRadian(objData->m_fRotY));
		D3DXMatrixTranslation(&objData->m_matObjTrans, fTransX, fTransY, fTransZ);
		objData->m_matObjWld = matScl * matRot * objData->m_matObjTrans;


		objData->m_bLightReverse = iLightReverse;
		objData->m_bLightSpecular = iLightSpecular;

		pMap->m_vecObj.push_back(objData);
		pMap->m_vecObjRender.push_back(false);
	}
	
	m_vecMapGroup.push_back(pMap);

	return true;
}

GMapMgr::GMapMgr()
{
	m_iMapSelected = -1;
	m_pObjSelected = NULL;
	m_bDebugRender = false;
}


GMapMgr::~GMapMgr()
{
}
