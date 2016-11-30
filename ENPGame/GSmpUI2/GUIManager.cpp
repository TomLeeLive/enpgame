//#include "stdafx.h"
#include "_stdafx.h"

//파일 입출력 때문에 추가함
#include <iostream>
#include <fstream>


BOOL GUIManager::ExtractSubString(CString& rString, LPCTSTR lpszFullString,
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

void GUIManager::GetStringWeNeed(VOID* pOutStr, VOID* pInStr) {

	vector<TCHAR*> vString;

	TCHAR* token = NULL;
	token = _tcstok((TCHAR*)pInStr, L"\\");
	while (token != NULL)
	{
		token = _tcstok(NULL, L"\\");
		vString.push_back(token);
	}
	_tcscpy((TCHAR*)pOutStr, vString[vString.size() - 2]);

	TCHAR strDir[MAX_PATH] = L"data\\";
	_tcsncat(strDir, (TCHAR*)pOutStr, _tcsclen((TCHAR*)pOutStr));

	_tcscpy((TCHAR*)pOutStr, strDir);
}


void	GUIManager::UILoad(T_STR* strFile, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {


	vector<CString> vecStr;

	ifstream ifile;

	char line[MAX_PATH]; // 한 줄씩 읽어서 임시로 저장할 공간

	ifile.open(strFile->c_str());  // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			//cout << line << endl; // 내용 출력
			CString str;
			str = line;
			vecStr.push_back(str);
		}
	}
	ifile.close(); // 파일 닫기

	for (int i = 0; i < vecStr.size()/GUI_ITEM_INFO_LINES; i++) {
		int iItem = i * GUI_ITEM_INFO_LINES;
		//vecStr[iItem + 0];//GUI_TYPE		#GUI_TYPE_IMAGE
		//vecStr[iItem + 1];//IMAGE 경로		D:\_github\l4dlike\Output\data\baseColor.jpg
		//vecStr[iItem + 2];//Auto Rescale 여부 1:true 0:false. 반전 값이 Autotrans에 들어감.
		//vecStr[iItem + 3];//SCL				#SCL 400.000000 300.000000 1.000000
		//vecStr[iItem + 4];//TRANS			#TRANS -21.257725 16.128735 100.000000

		TCHAR pOutStr[MAX_PATH] = { 0, };
		TCHAR* pInStr = (TCHAR*)(LPCTSTR)vecStr[iItem + 1];
		GetStringWeNeed(pOutStr, pInStr);

		int iAutoRescale = _ttoi(vecStr[iItem + 2]);
		CString strSclX, strSclY, strSclZ, strTransX, strTransY, strTransZ;
		ExtractSubString(strSclX, vecStr[iItem + 3], 0, '/');
		ExtractSubString(strSclY, vecStr[iItem + 3], 1, '/');
		ExtractSubString(strSclZ, vecStr[iItem + 3], 2, '/');
		ExtractSubString(strTransX, vecStr[iItem + 4], 0, '/');
		ExtractSubString(strTransY, vecStr[iItem + 4], 1, '/');
		ExtractSubString(strTransZ, vecStr[iItem + 4], 2, '/');

		T_STR imgFile = pOutStr;

		float fSclX, fSclY, fSclZ, fTransX, fTransY, fTransZ = 0.0f;

		fSclX = _wtof(strSclX);
		fSclY = _wtof(strSclY);
		fSclZ = _wtof(strSclZ);

		fTransX = _wtof(strTransX);
		fTransY = _wtof(strTransY);
		fTransZ = _wtof(strTransZ);

		if (!_tcscmp(vecStr[iItem + 0], L"#GUI_TYPE_IMAGE")) {
			UICreate(GUI_TYPE_IMAGE, &imgFile, SwapChainDesc,D3DXVECTOR3(fSclX, fSclY, fSclZ), D3DXVECTOR3(fTransX, fTransY, fTransZ), iAutoRescale);
		}
		else if (!_tcscmp(vecStr[iItem + 0], L"#GUI_TYPE_BUTTON")) {
			UICreate(GUI_TYPE_BUTTON, &imgFile, SwapChainDesc, D3DXVECTOR3(fSclX, fSclY, fSclZ), D3DXVECTOR3(fTransX, fTransY, fTransZ), iAutoRescale);
		}
		else if (!_tcscmp(vecStr[iItem + 0], L"#GUI_TYPE_BUTTONHALF")) {
			UICreate(GUI_TYPE_BUTTONHALF, &imgFile, SwapChainDesc, D3DXVECTOR3(fSclX, fSclY, fSclZ), D3DXVECTOR3(fTransX, fTransY, fTransZ), iAutoRescale);
		}
	}
}
void	GUIManager::UICreate(GUI_TYPE type, T_STR* strFile, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc,
	D3DXVECTOR3 vScl, D3DXVECTOR3 vTrans, int iAutoRescale
	) {
	int iType = type;

	switch (iType) {
		case GUI_TYPE_BUTTON:
		{
			GButtonCtl* pBoxCtl = new GButtonCtl();
			pBoxCtl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
			pBoxCtl->Create(g_pd3dDevice, nullptr, (*strFile).c_str());
			pBoxCtl->Scale(vScl.x, vScl.y, vScl.z);
			pBoxCtl->Move(vTrans.x, vTrans.y, vTrans.z);
			if (iAutoRescale == 1)
			{
				pBoxCtl->m_bAutoRescale = true;
				pBoxCtl->m_bAutoRetrans = false;
			}
			else {
				pBoxCtl->m_bAutoRescale = false;
				pBoxCtl->m_bAutoRetrans = true;
			}

			m_pUIList.push_back(pBoxCtl);
			m_ImageList.push_back((*strFile).c_str());
		}
		break;
		case GUI_TYPE_IMAGE:
		{
			GImageCtl* pImageCtl = new GImageCtl();
			pImageCtl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
			pImageCtl->Create(g_pd3dDevice, nullptr, (*strFile).c_str());
			pImageCtl->Scale(vScl.x, vScl.y, vScl.z);
			pImageCtl->Move(vTrans.x, vTrans.y, vTrans.z);
			if (iAutoRescale == 1)
			{
				pImageCtl->m_bAutoRescale = true;
				pImageCtl->m_bAutoRetrans = false;
			}
			else {
				pImageCtl->m_bAutoRescale = false;
				pImageCtl->m_bAutoRetrans = true;
			}
			m_pUIList.push_back(pImageCtl);
			m_ImageList.push_back((*strFile).c_str());
		}
		break;
		case GUI_TYPE_BUTTONHALF:
		{
			GButtonHalfCtl* pBoxCtl = new GButtonHalfCtl();
			pBoxCtl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
			pBoxCtl->Create(g_pd3dDevice,D3DXVECTOR3(vScl.x, vScl.y, vScl.z), nullptr, (*strFile).c_str());
			//pBoxCtl->Scale(100 - 1.0f, 50 - 1.0f, 1 - 1.0f);
			pBoxCtl->Move(vTrans.x, vTrans.y, vTrans.z);
			if (iAutoRescale == 1)
			{
				pBoxCtl->m_bAutoRescale = true;
				pBoxCtl->m_bAutoRetrans = false;
			}
			else {
				pBoxCtl->m_bAutoRescale = false;
				pBoxCtl->m_bAutoRetrans = true;
			}
			m_pUIList.push_back(pBoxCtl);
			m_ImageList.push_back((*strFile).c_str());
		}
		break;
	}

}
bool		GUIManager::Init() {

	/*
	GImageCtl* pImageCtl = new GImageCtl();
	pImageCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pImageCtl->Create(GetDevice(), nullptr, L"data/ui/hud.dds");
	pImageCtl->Scale(400 - 1.0f, 300 - 1.0f, 1.0f - 1.0f);
	pImageCtl->Move(0, 0, 100);
	m_pUIList.push_back(pImageCtl);

	GButtonCtl* pBoxCtl = new GButtonCtl();
	pBoxCtl->Set(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	pBoxCtl->Create(GetDevice(), nullptr, L"data/ui/exit_lg.bmp");
	pBoxCtl->Scale(100 - 1.0f, 50 - 1.0f, 1 - 1.0f);
	pBoxCtl->Move(0, 0, 0);
	m_pUIList.push_back(pBoxCtl);
	*/
	return true;
};
bool		GUIManager::Frame(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {

#if defined(_DEBUG)	|| defined(DEBUG)
	if (I_Input.KeyCheck(DIK_P) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_BUTTON, SwapChainDesc);
	}
	if (I_Input.KeyCheck(DIK_O) == KEY_UP)
	{
	m_pSelectPlane = AddRect(GUI_TYPE_IMAGE, SwapChainDesc);
	}


	GControlUI* pSelect = SelectRect();

	if (pSelect != NULL && m_pSelectPlane != pSelect)
	{
		m_pSelectPlane = pSelect;
	}

	if (m_pSelectPlane)
	{
		D3DXVECTOR3 vPos(0, 0, 0);
		D3DXVECTOR3 vScale(0, 0, 0);
		if (g_InputData.bQKey)
		{
			vScale.x += 50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.x = m_pSelectPlane->m_vScale.x;

		}
		if (g_InputData.bEKey)
		{
			vScale.x += -50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.x = m_pSelectPlane->m_vScale.x;
		}
		if (g_InputData.bZKey)
		{
			vScale.y += 50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.y = m_pSelectPlane->m_vScale.y;
		}
		if (g_InputData.bCKey)
		{
			vScale.y += -50 * g_fSecPerFrame;

			if (m_pSelectPlane->m_type == GUI_TYPE_BUTTONHALF)
				((GButtonHalfCtl*)m_pSelectPlane)->m_initScl.y = m_pSelectPlane->m_vScale.y;
		}
		if (g_InputData.bWKey)
		{
			vPos.y = 50 * g_fSecPerFrame;
		}
		if (g_InputData.bSKey)
		{
			vPos.y = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bAKey)
		{
			vPos.x = -50 * g_fSecPerFrame;
		}
		if (g_InputData.bDKey)
		{
			vPos.x = 50 * g_fSecPerFrame;
		}
		m_pSelectPlane->Move(vPos.x, vPos.y, vPos.z);
		m_pSelectPlane->Scale(vScale.x, vScale.y, vScale.z);
	}
#endif
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Update();
	}
	return true;

};
bool		GUIManager::Render() {
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Render(g_pImmediateContext);
	}
	return true;
};
bool		GUIManager::Release() {
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		pRect->Release();
		delete pRect;
	}
	return true;
};
//bool		PlaneRender(D3DXMATRIX 
//---------------------------------
// 변경된 클라이언트 영역를 재설정을
//---------------------------------
HRESULT		GUIManager::CreateResource(DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {
	HRESULT hr;
	// 투영행렬도 윈도우 사이즈가 변경되면 반드시 업테이트 해야 한다.


	int iRectWidth = SwapChainDesc->BufferDesc.Width;
	int iRectHeight = SwapChainDesc->BufferDesc.Height;
	for (int iPlane = 0; iPlane < m_pUIList.size(); iPlane++)
	{
		GControlUI* pRect = m_pUIList[iPlane];
		if (pRect) pRect->CreateResource(iRectWidth, iRectHeight);
	}
	return S_OK;
};
HRESULT		GUIManager::DeleteResource() {
	HRESULT hr;
	return S_OK;
};
#if defined(_DEBUG) || defined(DEBUG)
GControlUI* GUIManager::AddRect(GUI_TYPE type, TCHAR* strImage, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {
	GControlUI* pUIControl = NULL;
	switch (type)
	{
	case GUI_TYPE_BUTTON: {
		pUIControl = new GButtonCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, strImage);
		pUIControl->Scale(50, 50, 0);
	}
	case GUI_TYPE_IMAGE: {
		pUIControl = new GEditCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, strImage);
		pUIControl->Scale(50, 50, 0);
	}
	}
	pUIControl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
	m_pUIList.push_back(pUIControl);
	return pUIControl;
};

GControlUI* GUIManager::AddRect(GUI_TYPE type, DXGI_SWAP_CHAIN_DESC*	SwapChainDesc) {
	GControlUI* pUIControl = NULL;
	switch (type)
	{
	case GUI_TYPE_BUTTON: {
		pUIControl = new GButtonCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	case GUI_TYPE_IMAGE: {
		pUIControl = new GEditCtl();
		pUIControl->Create(g_pd3dDevice, nullptr, L"data/ui/exit_lg.bmp");
		pUIControl->Scale(50, 50, 0);
	}
	}
	pUIControl->Set(SwapChainDesc->BufferDesc.Width, SwapChainDesc->BufferDesc.Height);
	m_pUIList.push_back(pUIControl);
	return pUIControl;
};

GControlUI* GUIManager::SelectRect() {
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	for (int iRect = 0; iRect < m_pUIList.size(); iRect++)
	{
		GControlUI* pRect = m_pUIList[iRect];
		if (I_Input.m_MouseState[0] == KEY_HOLD)
		{
			RECT rt = pRect->m_rt;
			// 뒤집어 진 경우
			if (pRect->m_rt.left > pRect->m_rt.right)
			{
				rt.left = pRect->m_rt.right;
				rt.right = pRect->m_rt.left;
			}
			if (pRect->m_rt.top > pRect->m_rt.bottom)
			{
				rt.top = pRect->m_rt.bottom;
				rt.bottom = pRect->m_rt.top;
			}
			if (rt.left <= mouse.x && rt.right >= mouse.x)
			{
				if (rt.top <= mouse.y && rt.bottom >= mouse.y)
				{
					return pRect;
				}
			}
		}
	}
	return NULL;
};
#endif
GUIManager::GUIManager()
{
	m_pSelectPlane = NULL;
}


GUIManager::~GUIManager()
{
}
