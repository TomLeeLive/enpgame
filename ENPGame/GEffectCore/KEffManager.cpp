//#include "stdafx.h"
//#include "_stdafx.h"
#include "KEffManager.h"

void		KEffManager::Create(G_EFFECT_TYPE type, T_STR* strFile,
	D3DXVECTOR3 vScl, float fTime) {
	//D3DXVECTOR3 vScl, float fTime, int Width, int WidthSize, int Height, int HeightSize) {
	int iType = type;

	/*
	G_EFFECT_BULLET = 0,
	G_EFFECT_BLOOD,
	G_EFFECT_DUST,
	G_EFFECT_SMOG,
	*/
	switch (iType) {
	case G_EFFECT_BULLET:
	{
		auto Effect = make_shared<KEffect>();
		Effect->Init();
		

		//play 버튼시 init() 부분
		//EnterCriticalSection(&g_CSd3dDevice);
		Effect->m_pSprite->Create(g_pd3dDevice, L"data/shader/plane.hlsl", strFile->c_str());
		//LeaveCriticalSection(&g_CSd3dDevice);

		//이미지 이름을 저장해 놓는다. 나중에 save 할때 쓴다.
		//TCHAR  *tchr = (TCHAR*)(LPCTSTR)strFile;
		//p_CParctice->m_EffMgr.GetStringWeNeed(tchr, tchr);
		//m_ImageList.push_back(strFile->c_str());

		// 애니메이션 관련, 가로4x4
		Effect->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);
		/*
		// 애니메이션 관련, Width x Height
		if (Width <= 0 || WidthSize <= 0 || Height <= 0 || HeightSize <= 0)
		{
			Effect->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);
		}
		else
		{
			Effect->m_pSprite->SetRectAnimation(fTime, Width, WidthSize, Height, HeightSize);
		}
		*/

		Effect->m_bCheck = true;


		m_List.push_back(Effect);
		m_ImageList.push_back((*strFile).c_str());
	}
	break;
	case G_EFFECT_BLOOD:
	{

	}
	break;
	case G_EFFECT_DUST:
	{

	}
	break;
	}

}

BOOL KEffManager::ExtractSubString(CString& rString, LPCTSTR lpszFullString,
	int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;

	while (iSubString--)
	{
		lpszFullString = _tcschr(lpszFullString, chSep);
		if (lpszFullString == NULL)
		{
			rString.Empty();        // return empty string as well
			return FALSE;
		}
		lpszFullString++;       // point past the separator
	}
	LPCTSTR lpchEnd = _tcschr(lpszFullString, chSep);
	int nLen = (lpchEnd == NULL) ?
		lstrlen(lpszFullString) : (int)(lpchEnd - lpszFullString);
	assert(nLen >= 0);
	memcpy(rString.GetBufferSetLength(nLen), lpszFullString, nLen * sizeof(TCHAR));
	return TRUE;
}

void KEffManager::Load(T_STR* strFile) {
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
	}


	for (int i = 0; i < vecStr.size() / G_EFF_ITEM_INFO_LINES; i++) {
		int iItem = i * G_EFF_ITEM_INFO_LINES;
		//vecStr[iItem + 0];//EFF_TYPE			#KEFFECT_BULLET
		//vecStr[iItem + 1];//IMAGE 경로		D:\data\ds1.dds
		//vecStr[iItem + 2];//SCL				1.000000/1.000000/1.000000
		//vecStr[iItem + 3];//time				0.000000
		//vecStr[iItem + 4];//RectAniMation		1.000000/4/128/4/128

		TCHAR pOutStr[MAX_PATH] = { 0, };
		TCHAR* pInStr = (TCHAR*)(LPCTSTR)vecStr[iItem + 1];
		GetStringWeNeed(pOutStr, pInStr);

		//int iAutoRescale = _ttoi(vecStr[iItem + 2]);
		CString strSclX, strSclY, strSclZ, strTime;
		ExtractSubString(strSclX, vecStr[iItem + 2], 0, '/');
		ExtractSubString(strSclY, vecStr[iItem + 2], 1, '/');
		ExtractSubString(strSclZ, vecStr[iItem + 2], 2, '/');

		float fTime = _ttof(vecStr[iItem + 3]);

		/*
		CString strWid, strWidSize, strHeight, strHeightSize;

		ExtractSubString(strWid,vecStr[iItem + 4], 0, '/');
		ExtractSubString(strWidSize,vecStr[iItem + 4], 1, '/');
		ExtractSubString(strHeight,vecStr[iItem + 4], 2, '/');
		ExtractSubString(strHeightSize,vecStr[iItem + 4], 3, '/');
		*/



		T_STR imgFile = pOutStr;

		float fSclX, fSclY, fSclZ;

		fSclX = _wtof(strSclX);
		fSclY = _wtof(strSclY);
		fSclZ = _wtof(strSclZ);

		/*
		int  iWidth, iWidthSize, iHeight, iHeightSize;
		
		iWidth = _wtoi(strWid);
		iWidthSize = _wtoi(strWidSize);
		iHeight= _wtoi(strHeight);
		iHeightSize= _wtoi(strHeightSize);
		*/

		if (!_tcscmp(vecStr[iItem + 0], L"#KEFFECT_BULLET")) {
			//Create(G_EFFECT_BULLET, &imgFile,  D3DXVECTOR3(fSclX, fSclY, fSclZ), fTime, iWidth, iWidthSize, iHeight, iHeightSize);
			Create(G_EFFECT_BULLET, &imgFile, D3DXVECTOR3(fSclX, fSclY, fSclZ), fTime);
		}
		//else if (!_tcscmp(vecStr[iItem + 0], L"#KEFFECT_BLOOD")) {
		//	UICreate(GUI_TYPE_BUTTON, &imgFile, SwapChainDesc, D3DXVECTOR3(fSclX, fSclY, fSclZ), D3DXVECTOR3(fTransX, fTransY, fTransZ), iAutoRescale);
		//}
		//else if (!_tcscmp(vecStr[iItem + 0], L"#KEFFECT_DUST")) {
		//	UICreate(GUI_TYPE_BUTTONHALF, &imgFile, SwapChainDesc, D3DXVECTOR3(fSclX, fSclY, fSclZ), D3DXVECTOR3(fTransX, fTransY, fTransZ), iAutoRescale);
		//}
	}
}
void KEffManager::GetStringWeNeed(VOID* pOutStr, VOID* pInStr) {

	vector<TCHAR*> vString;

	TCHAR* token = NULL;
	token = _tcstok((TCHAR*)pInStr, L"\\");
	while (token != NULL)
	{
		token = _tcstok(NULL, L"\\");
		vString.push_back(token);
	}
	_tcscpy((TCHAR*)pOutStr, vString[vString.size() - 2]);

	TCHAR strDir[MAX_PATH] = L"data\\effect\\";
	_tcsncat(strDir, (TCHAR*)pOutStr, _tcsclen((TCHAR*)pOutStr));

	_tcscpy((TCHAR*)pOutStr, strDir);
}

bool		KEffManager::Init() {

	return true;
};
bool		KEffManager::Frame(GCamera* camera, GTimer* timer) { 
	for (int i = 0;i < m_List.size();i++)
		m_List[i]->Frame(camera, timer);
	return true;
};
bool		KEffManager::Render() { 
	
	for (int i = 0;i < m_List.size();i++)
		m_List[i]->Render();

	//EnterCriticalSection(&g_CSImmediateContext);
	ClearD3D11DeviceContext(g_pImmediateContext);
	//LeaveCriticalSection(&g_CSImmediateContext);

	return true; 

};
bool		KEffManager::Release() { return true; };

//창이 사이즈가 변경이되면 호출이 됨.
HRESULT		KEffManager::CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) { return S_OK; }

HRESULT		KEffManager::DeleteResource() { return S_OK; }


HRESULT KEffManager::SetBlendState()
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));

	//	멀티샘플링 기법 활성화 여부. 정렬하기가 어려운 다수의 랜더링 할때 유용하다.
	BlendState.AlphaToCoverageEnable = TRUE;

	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// 블랜딩 팩터는 기존의 존재하던 값과 새로운 픽셀값의 블랜딜을 성분별로 제어할 수
	// 있게 해주면 마스크는 기존의 렌더타켓이 업데이트 하기전에 샘플링하는 방법을 결정하는 사용자 
	//정의 마스크값이다.
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_BLEND_FACTOR;

	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	//계산된 최종 컬러값의 일부 요소만 렌더타겟에 기록할 수 있도록 한다.
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//EnterCriticalSection(&g_CSd3dDevice);
	if (FAILED(hr = g_pd3dDevice->CreateBlendState(&BlendState, &m_pAlphaBlendFactor)))
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr;
	}
	//LeaveCriticalSection(&g_CSd3dDevice);

	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//EnterCriticalSection(&g_CSd3dDevice);
	if (FAILED(hr = g_pd3dDevice->CreateBlendState(&BlendState, &m_pAlphaBlend)))
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr;
	}
	//LeaveCriticalSection(&g_CSd3dDevice);

	return hr;
}


void KEffManager::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	// Unbind all objects from the immediate context
	if (pd3dDeviceContext == NULL) return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Shaders
	pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
	pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

	// IA clear
	pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
	pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
	pd3dDeviceContext->IASetInputLayout(NULL);

	// Constant buffers
	pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
	pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

	// Resources
	pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

	// Samplers
	pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
	pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

	// Render targets
	pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

	// States
	FLOAT blendFactor[4] = { 0,0,0,0 };
	pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
	pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
	pd3dDeviceContext->RSSetState(NULL);
}

KEffManager::KEffManager()
{
}


KEffManager::~KEffManager()
{
}
