#include "stdafx.h"
//#include "_stdafx.h"
#include "GMapMgr.h"

#ifdef G_DEFINE_SHADOW_ADD
bool			GMapMgr::RenderObject(GCoreLibV2* pMain, GCamera* pCamera,bool bDebug ) {
	if (m_iMapSelected == -1)
		return false;


	D3DXMATRIX matInvView;
	ApplySS(pMain->GetContext(), GDxState::g_pSSClampLinear, 1);
	ApplySS(pMain->GetContext(), GDxState::g_pSSShadowMap, 2);
	ApplyRS(pMain->GetContext(), GDxState::g_pRSNoneCullSolid);

	//������Ʈ ������.
	for (int i = 0; i < m_vecMapGroup[m_iMapSelected]->m_vecObj.size(); i++)
	{
		if (true == m_vecMapGroup[m_iMapSelected]->m_vecObjRender[i])
		{
			D3DXMatrixInverse(&matInvView, 0, pCamera->GetViewMatrix());
			D3DXMATRIX matWVPT1 = m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_matObjWld * pMain->m_matShadowView * pMain->m_matShadowProj * pMain->m_matTexture;
			D3DXMatrixTranspose(&pMain->m_cbShadow.g_matShadow, &matWVPT1);
			//m_cbShadow.g_ShadowID = m_fObjID[iObj];
			pMain->m_cbShadow.g_iNumKernel = 3;
			pMain->GetContext()->UpdateSubresource(pMain->m_pShadowConstantBuffer.Get(), 0, NULL, &pMain->m_cbShadow, 0, 0);
			pMain->GetContext()->VSSetConstantBuffers(2, 1, pMain->m_pShadowConstantBuffer.GetAddressOf());
			pMain->GetContext()->PSSetConstantBuffers(2, 1, pMain->m_pShadowConstantBuffer.GetAddressOf());
			pMain->GetContext()->PSSetShaderResources(1, 1, pMain->m_RT.m_pDsvSRV.GetAddressOf());

			m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->SetMatrix(&m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_matObjWld, pCamera->GetViewMatrix(), pCamera->GetProjMatrix());
			m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->Render(pMain->GetContext());

			if (bDebug)
				m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->m_OBB.Render(&m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_matObjWld, pCamera->GetViewMatrix(), pCamera->GetProjMatrix());
		}
	}
	//���� ������.
	m_vecMapGroup[m_iMapSelected]->Render(pCamera, bDebug, pMain);

	return true;
	
}
bool			GMapMgr::RenderShadow(GCoreLibV2* pMain, D3DXMATRIX* matView, D3DXMATRIX* matProj,bool bDebug) {
	if (m_iMapSelected == -1)
		return false;

	ApplyDSS(pMain->GetContext(), GDxState::g_pDSSDepthEnable);
	//ApplyRS(GetContext(), TDxState::g_pRSBackCullSolid);
	ApplyBS(pMain->GetContext(), GDxState::g_pAlphaBlend);
	ApplyRS(pMain->GetContext(), GDxState::g_pRSSlopeScaledDepthBias);

	m_vecMapGroup[m_iMapSelected]->m_HeightMap.SetMatrix(NULL, matView, matProj);
	m_vecMapGroup[m_iMapSelected]->m_HeightMap.PreRender(pMain->GetContext());
	pMain->GetContext()->VSSetShader(pMain->m_pShadowVS.Get(), NULL, 0);
		//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
		// ���̽��ٽ� ���۸� ���ҽ��� �����ϸ� �Ǳ� ������ �Ƚ����̴��� ������� �ʾƵ� �ȴ�.
		// ������, ȭ�鿡 ����� ���̸� ����� Ȯ���ϰ��� �� ���忡�� �Ƚ����̴��� Ȱ��ȭ �Ͽ���.
		pMain->GetContext()->PSSetShader(NULL, NULL, 0);
	m_vecMapGroup[m_iMapSelected]->m_HeightMap.PostRender(pMain->GetContext());

	//������Ʈ ������.
	for (int i = 0; i < m_vecMapGroup[m_iMapSelected]->m_vecObj.size(); i++)
	{
		//if (true == m_vecMapGroup[m_iMapSelected]->m_vecObjRender[i])
		//{
			m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->SetMatrix(&m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_matObjWld, matView, matProj);
			m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->Render(pMain->GetContext());

			//m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->PreRender(pMain->GetContext());
			//pMain->GetContext()->VSSetShader(pMain->m_pShadowVS.Get(), NULL, 0);
			//pMain->GetContext()->PSSetShader(NULL, NULL, 0);
			//m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj->Draw(pMain->GetContext(), m_vecMapGroup[m_iMapSelected]->m_vecObj[i]->m_pObj);
		//}
	}

	return true;
}
#endif
bool			GMapMgr::Init()
{





	return true; 
}

bool GMapGroup::CreateInit(GCoreLibV2* pMain, int Width, int Height, float Distance, CString strTex, GCamera* pCamera)
{
	Init();

	//--------------------------------------------------------------------------------------
	//  �� ����
	//--------------------------------------------------------------------------------------

	wchar_t szCharPath[MAX_PATH] = G_DEFINE_MAP_DIR;
	wchar_t szChar[MAX_PATH];
	//CString strString;
	//strString = "test";
	_tcscpy_s(szChar, 16, strTex.GetBuffer());
	_tcscat_s(szCharPath, szChar);

	//theApp.m_MapDesc.strTextureFile = m_strCharName;

	//m_MapDesc = { Width, Height, Distance, 0.1f,L"data/sand.jpg", L"data/shader/CustomizeMap.hlsl" };
#ifdef G_DEFINE_SHADOW_ADD
	m_MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//Distance, 0.1f,
		20.0f, 1.0f,
		szCharPath,
		G_SHA_MAP_DIFFUSE_SHADOW
};
#else
	m_MapDesc = {
		m_HeightMap.m_iNumRows,	m_HeightMap.m_iNumCols,
		//Distance, 0.1f,
		20.0f, 1.0f,
		szCharPath,
		G_DEFINE_MAP_SHADER
};
#endif

	//m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (!m_HeightMap.Load(m_MapDesc))
	{
		return false;
	}
	//m_CustomMap.Init(g_pd3dDevice, g_pImmediateContext);
	//if (FAILED(m_CustomMap.Load(m_MapDesc))) { return false; }
	//--------------------------------------------------------------------------------------
	//  ���� Ʈ��
	//--------------------------------------------------------------------------------------
	m_QuadTree.Build(m_MapDesc.iNumCols, m_MapDesc.iNumRows);
	m_QuadTree.Update(g_pd3dDevice, pCamera);

#ifdef G_DEFINE_SHADOW_ADD
	if (pMain != NULL) {
		float fWidthLength = m_HeightMap.m_fSellDistance*m_HeightMap.m_iNumCols*
			m_HeightMap.m_fSellDistance*m_HeightMap.m_iNumCols;
		float fHeightLength = m_HeightMap.m_fSellDistance*m_HeightMap.m_iNumRows*
			m_HeightMap.m_fSellDistance*m_HeightMap.m_iNumRows;

		// ������ �밢���� ����, �ؽ�ó�� �����ϰ� ��ġ�Ϸ��� �۾��Ѵ�.
		float fMaxViewDistance = sqrt(fWidthLength + fHeightLength);
		//D3DXMatrixPerspectiveFovLH( &m_matShadowProj, D3DX_PI*0.25f, 1.0f, 20.0f, 200.0f );
		//D3DXMatrixOrthoLH( &m_matShadowProj, fMaxViewDistance, fMaxViewDistance, 0.0f, 100.0f );

		D3DXMatrixOrthoOffCenterLH( &pMain->m_matShadowProj,
			-fMaxViewDistance/2, fMaxViewDistance/2, -fMaxViewDistance/2, fMaxViewDistance/2, 0.0f, 20000.0f );
		//D3DXMatrixOrthoOffCenterLH(&pMain->m_matShadowProj,
		//	-fMaxViewDistance * 2, fMaxViewDistance * 2, -fMaxViewDistance * 2, fMaxViewDistance * 2, 0.0f, 10000.0f);
	}
#endif
}
bool			GMapMgr::Frame(GCamera* pCamera, GInput* pInput)
{



	//--------------------------------------------------------------------------------------
	// add
	//--------------------------------------------------------------------------------------
	//2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
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

		if (I_Input.KeyCheck(DIK_Y) == KEY_HOLD)
		{
			m_pObjSelected->m_fScl += 0.1;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_U) == KEY_HOLD)
		{
			m_pObjSelected->m_fScl -= 0.1;

			if (m_pObjSelected->m_fScl < 0.1)
				m_pObjSelected->m_fScl = 0.1;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_H) == KEY_HOLD)
		{
			m_pObjSelected->m_fRotY += 0.5;

			m_bChanged = true;
		}
		if (I_Input.KeyCheck(DIK_J) == KEY_HOLD)
		{
			m_pObjSelected->m_fRotY -= 0.5;

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
			D3DXMatrixScaling(&matScl, m_pObjSelected->m_fScl, m_pObjSelected->m_fScl, m_pObjSelected->m_fScl);
			D3DXMatrixRotationY(&matRot, D3DXToRadian(m_pObjSelected->m_fRotY));

			m_pObjSelected->m_matObjWld = matScl * matRot * m_pObjSelected->m_matObjTrans;
			return true;
		}
	}
	return false;
}

bool			GMapMgr::Render(GCamera* pCamera, bool bDebug,GCoreLibV2* pMain)
{

	//if (m_vecMapGroup.size() == 0)
	//	return false;

	if (m_iMapSelected == -1)
		return false;

	//for (int i = 0; i < m_vecMapGroup.size(); i++)
		m_vecMapGroup[m_iMapSelected]->Render(pCamera, bDebug);

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

bool	GMapMgr::LoadMap(T_STR* strFile,GCamera* pCamera, GCoreLibV2* pMain) {

	vector<CString> vecStr;

	FILE *pFile = NULL;

	const wchar_t * pStrFile = strFile->c_str();

	//int len = 256;
	char ctemp[MAX_PATH];

	//TCHAR -> char ��ȯ
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

			// char -> TCHAR ��ȯ
			TCHAR szUniCode[MAX_PATH] = { 0, };
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStr, strlen(pStr), szUniCode, MAX_PATH);

			// TCHAR -> CString ��ȯ
			CString str;
			str.Format(L"%s", szUniCode);
			str.TrimRight();//���๮�� ����
			vecStr.push_back(str);
		}
		fclose(pFile);
	}
	else
	{
		//���� ó��
		return false;
	}

	//����Ʈ�� ó�� & ��������..(with �ؽ�ó)
	auto pMap = make_shared<GMapGroup>();

	pMap->m_HeightMap.Init(g_pd3dDevice, g_pImmediateContext);
	if (FAILED(pMap->m_HeightMap.CreateHeightMap((TCHAR*)(LPCTSTR)vecStr[1]/*strHeight*/)))
	{
		return false;
	}

	pMap->m_HeightMap.m_bStaticLight = true;

	pMap->CreateInit(pMain, 0, 0, 0, vecStr[0]/*strTex*/, pCamera);

	_tcsncpy_s(pMap->m_strHeight, (TCHAR*)(LPCTSTR)vecStr[1], vecStr[1].GetLength());
	_tcsncpy_s(pMap->m_strTex, (TCHAR*)(LPCTSTR)vecStr[0], vecStr[0].GetLength());

	_tcsnset_s(m_strHeight, 0, MAX_PATH);
	_tcsnset_s(m_strTex, 0, MAX_PATH);
	_tcsncpy_s(m_strHeight, (TCHAR*)(LPCTSTR)vecStr[1], vecStr[1].GetLength());
	_tcsncpy_s(m_strTex, (TCHAR*)(LPCTSTR)vecStr[0], vecStr[0].GetLength());

	//������Ʈ ����..
	for (int i = 0; i < (vecStr.size() - MAP_TEX_INFO_LINES) / MAP_OBJ_INFO_LINES; i++) {
		int iItem = i * MAP_OBJ_INFO_LINES;
		
		//������Ʈ gbs �̸� ���								//vecStr[iItem +MAP_TEX_INFO_LINES + 0];
		//������Ʈ ���� reverse ���� �� ��� true: 1, false: 0  //vecStr[iItem +MAP_TEX_INFO_LINES + 1];
		//������Ʈ ���� reverse ���� �� ��� true: 1, false: 0  //vecStr[iItem +MAP_TEX_INFO_LINES + 2];
		//������Ʈ scl �� ���									//vecStr[iItem +MAP_TEX_INFO_LINES + 3];
		//������Ʈ rot �� ���									//vecStr[iItem +MAP_TEX_INFO_LINES + 4];
		//������Ʈ translation x �� ���						//vecStr[iItem +MAP_TEX_INFO_LINES + 5];
		//������Ʈ translation y �� ���						//vecStr[iItem +MAP_TEX_INFO_LINES + 6];
		//������Ʈ translation z �� ���						//vecStr[iItem +MAP_TEX_INFO_LINES + 7];

		int iLightReverse	= _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 1]);
		int	iLightSpecular  = _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 2]);
		float fScl			= _ttoi(vecStr[iItem + MAP_TEX_INFO_LINES + 3]);
		float fRotY			= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 4]);
		float fTransX		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 5]);
		float fTransY		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 6]);
		float fTransZ		= _ttof(vecStr[iItem + MAP_TEX_INFO_LINES + 7]);

#ifdef G_DEFINE_SHADOW_ADD
		if (iLightSpecular == 1) {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR_SHADOW_REVERSE, G_LIGHT_TYPE_SPECULAR);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR_SHADOW, G_LIGHT_TYPE_SPECULAR);
	}
		else {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE_SHADOW_REVERSE);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE_SHADOW);
		}
#else
		if (iLightSpecular == 1) {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR_REVERSE, G_LIGHT_TYPE_SPECULAR);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_SPECULAR, G_LIGHT_TYPE_SPECULAR);
	}
		else {
			if (iLightReverse == 1)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE_REVERSE);
			else if (iLightReverse == 0)
				I_ObjMgr.Load(g_pd3dDevice, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], G_SHA_OBJ_DIFFUSE);
		}
#endif
		


		auto objData = make_shared<GObjData>();

		_tcsncpy_s(objData->m_strName, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], vecStr[iItem + MAP_TEX_INFO_LINES + 0].GetLength());

		TCHAR strObjName[MAX_PATH];

		_tcsncpy_s(strObjName, (TCHAR*)(LPCTSTR)vecStr[iItem + MAP_TEX_INFO_LINES + 0], vecStr[iItem + MAP_TEX_INFO_LINES + 0].GetLength());

		GetStringFileName(strObjName, strObjName);

		objData->m_pObj = (GGbsObj*)I_ObjMgr.GetPtr(strObjName);

		//s, r, t ����.
		D3DXMATRIX matScl, matRot;
		D3DXMatrixIdentity(&matScl);
		D3DXMatrixIdentity(&matRot);
		objData->m_fScl = fScl;
		objData->m_fRotY = fRotY;
		D3DXMatrixScaling(&matScl, objData->m_fScl, objData->m_fScl, objData->m_fScl);
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
