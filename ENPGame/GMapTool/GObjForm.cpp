// GObjForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"

#include "MapTool.h"
#include "GObjForm.h"
#include "GMapMgr.h"

#include "MainFrm.h"

// GObjForm

IMPLEMENT_DYNCREATE(GObjForm, CFormView)

GObjForm::GObjForm()
	: CFormView(IDD_OBJFORM)
	, m_fScl(0)
	//, m_fSclY(0)
	//, m_fSclZ(0)
	//, m_fRotX(0)
	, m_fRotY(0)
	//, m_fRotZ(0)
	, m_fTransX(0)
	, m_fTransY(0)
	, m_fTransZ(0)
{

}

GObjForm::~GObjForm()
{
}

GObjForm * GObjForm::CreateOne(CWnd * pParent)
{
	GObjForm* pane = new GObjForm;
	if (!pane->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 1000, 1000), pParent, 0, NULL))
	{
		return NULL;
	}
	return pane;	
}

void GObjForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTOBJ, m_listObj);
	DDX_Text(pDX, IDC_ObjSacleX, m_fScl);
	//DDX_Text(pDX, IDC_ObjScaleY, m_fSclY);
	//DDX_Text(pDX, IDC_ObjScaleZ, m_fSclZ);
	//DDX_Text(pDX, IDC_ObjRotationX, m_fRotX);
	DDX_Text(pDX, IDC_ObjRotationY, m_fRotY);
	//DDX_Text(pDX, IDC_ObjRotationZ, m_fRotZ);
	DDX_Text(pDX, IDC_ObjTransX, m_fTransX);
	DDX_Text(pDX, IDC_ObjTransY, m_fTransY);
	DDX_Text(pDX, IDC_ObjTransZ, m_fTransZ);
	DDX_Control(pDX, IDC_LISTMAP, m_listMap);
}

BEGIN_MESSAGE_MAP(GObjForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &GObjForm::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTON1, &GObjForm::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LISTOBJ, &GObjForm::OnLbnSelchangeListobj)
	ON_LBN_SELCHANGE(IDC_LISTMAP, &GObjForm::OnLbnSelchangeListmap)
	ON_BN_CLICKED(IDC_CHECK1, &GObjForm::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &GObjForm::OnBnClickedCheck2)
END_MESSAGE_MAP()


// GObjForm 진단입니다.

#ifdef _DEBUG
void GObjForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GObjForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GObjForm 메시지 처리기입니다.


void GObjForm::OnBnClickedButtonload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	
	pApp->GetSwapChain()->GetDesc(&SwapChainDesc);

	//if(!pApp->LoadFileDlg(_T("*"),_T("이미지")))

	
	CString strObjFile;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T(		"All Files(*.*)|*.*|		GBS File(*.gbs)|*.gbs|		|		"));

	//CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		//dlg.GetPathName();
		FILE *fp;
		//strObjFile = dlg.GetFileName();
		strObjFile = dlg.GetPathName();

	}
	else {
		return;
	}



	TCHAR * TChr = NULL;
	//CString -> TCHAR
	TChr = (TCHAR*)(LPCTSTR)strObjFile;

	TCHAR strFile[MAX_PATH] = L""; //= L"data\\object\\building\\";

	_tcsncat(strFile, (TCHAR*)TChr, _tcsclen((TCHAR*)TChr));

	theApp.m_MapMgr.GetStringFileNameWithPath(strFile, strFile);
	
	I_ObjMgr.Load(g_pd3dDevice, strFile, G_SHA_OBJ_DIFFUSE_REVERSE);



	auto objData = make_shared<GObjData>();
	_tcsncpy_s(objData->m_strName, strFile, MAX_PATH);

	theApp.m_MapMgr.GetStringFileName(strFile, strFile);

	objData->m_pObj = (GGbsObj*)I_ObjMgr.GetPtr(strFile);

	//s, r, t 설정.

	D3DXMATRIX matScl, matRot;
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);

	objData->m_fScl = 1.0;
	objData->m_fRotY = 0.0f;

	D3DXMatrixScaling(&matScl, objData->m_fScl, objData->m_fScl, objData->m_fScl);
	D3DXMatrixRotationY(&matRot, D3DXToRadian(objData->m_fRotY));



	D3DXMatrixTranslation(&objData->m_matObjTrans, 0.0f, 0.0f, 0.0f);
	objData->m_matObjWld = matScl * matRot * objData->m_matObjTrans;


	if (theApp.m_MapMgr.m_iMapSelected == -1) {
		AfxMessageBox(
			L"선택된 맵이 없습니다.\n"
			L"맵을 우선 선택해주시겠습니까?", MB_OK);
		return;
	}



	theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.push_back(objData);
	theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObjRender.push_back(false);

	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.size() - 1, strFile/*L" GBS"*/);
	m_listObj.AddString(szRet);
}



void GObjForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//값셋팅.
	D3DXMATRIX matScl, matRot;
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);



	CString strScl, strRot, strTransX, strTransY, strTransZ;

	GetDlgItem(IDC_ObjSacleX)->GetWindowText(strScl);
	GetDlgItem(IDC_ObjRotationY)->GetWindowText(strRot);
	GetDlgItem(IDC_ObjTransX)->GetWindowText(strTransX);
	GetDlgItem(IDC_ObjTransY)->GetWindowText(strTransY);
	GetDlgItem(IDC_ObjTransZ)->GetWindowText(strTransZ);

	m_fScl = _ttof(strScl);
	m_fRotY = _ttof(strRot);
	m_fTransX = _ttof(strTransX);
	m_fTransY = _ttof(strTransY);
	m_fTransZ = _ttof(strTransZ);

	if (theApp.m_MapMgr.m_pObjSelected != NULL) {
		theApp.m_MapMgr.m_pObjSelected->m_fScl = m_fScl;
		theApp.m_MapMgr.m_pObjSelected->m_fRotY = m_fRotY;
		theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._41 = m_fTransX;
		theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._42 = m_fTransY;
		theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._43 = m_fTransZ;

		D3DXMatrixScaling(&matScl, theApp.m_MapMgr.m_pObjSelected->m_fScl, theApp.m_MapMgr.m_pObjSelected->m_fScl, theApp.m_MapMgr.m_pObjSelected->m_fScl);
		D3DXMatrixRotationY(&matRot, D3DXToRadian(theApp.m_MapMgr.m_pObjSelected->m_fRotY));
		theApp.m_MapMgr.m_pObjSelected->m_matObjWld = matScl * matRot * theApp.m_MapMgr.m_pObjSelected->m_matObjTrans;
	}
	else {
		AfxMessageBox(
			L"선택된 오브젝트가 없습니다.\n"
			L"오브젝트를 우선 선택해주시겠습니까?", MB_OK);
	}
}


void GObjForm::OnLbnSelchangeListobj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelected = m_listObj.GetCurSel();
	if (iSelected == -1)
		return;

	if (theApp.m_MapMgr.m_vecMapGroup.size() == 0)
		return;

	if (theApp.m_MapMgr.m_iMapSelected == -1) {
		AfxMessageBox(
			L"선택된 맵이 없습니다.\n"
			L"맵을 우선 선택해주시겠습니까?", MB_OK);
		return;
	}

	theApp.m_MapMgr.m_pObjSelected = theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj[iSelected].get();

	m_fScl = theApp.m_MapMgr.m_pObjSelected->m_fScl;
	m_fRotY = theApp.m_MapMgr.m_pObjSelected->m_fRotY;
	m_fTransX = theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._41;
	m_fTransY= theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._42;
	m_fTransZ = theApp.m_MapMgr.m_pObjSelected->m_matObjTrans._43;

	if(theApp.m_MapMgr.m_pObjSelected->m_bLightReverse == TRUE)
		CheckDlgButton(IDC_CHECK1, TRUE);
	else
		CheckDlgButton(IDC_CHECK1, FALSE);

	if (theApp.m_MapMgr.m_pObjSelected->m_bLightSpecular == TRUE)
		CheckDlgButton(IDC_CHECK2, TRUE);
	else
		CheckDlgButton(IDC_CHECK2, FALSE);

	UpdateData(FALSE);
}


void GObjForm::OnLbnSelchangeListmap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelected = m_listMap.GetCurSel();
	if (iSelected == -1)
		return;

	if (theApp.m_MapMgr.m_vecMapGroup.size() == 0)
		return;

	theApp.m_MapMgr.m_iMapSelected = iSelected;

	theApp.m_MapMgr.m_pObjSelected = NULL;

	m_listObj.ResetContent();

	for (int i = 0; i < theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.size(); i++) {

		TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count

		TCHAR strObjName[MAX_PATH];

		_tcsncpy_s(strObjName, theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj[i]->m_strName, MAX_PATH);

		theApp.m_MapMgr.GetStringFileName(strObjName, strObjName);

		_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), i, strObjName);
		m_listObj.AddString(szRet);

	}
	m_listObj.UpdateData(FALSE);


}


void GObjForm::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK1);

	if (theApp.m_MapMgr.m_pObjSelected != NULL) {
		if (bCheck == TRUE) {
			theApp.m_MapMgr.m_pObjSelected->m_bLightReverse = TRUE;
		}
		else {
			theApp.m_MapMgr.m_pObjSelected->m_bLightReverse = FALSE;
		}
	}
	else {
		AfxMessageBox(
			L"선택된 오브젝트가 없습니다.\n"
			L"오브젝트를 우선 선택해주시겠습니까?", MB_OK);
	}


}


void GObjForm::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BOOL bCheck = IsDlgButtonChecked(IDC_CHECK1);

	if (theApp.m_MapMgr.m_pObjSelected != NULL) {
		if (bCheck == TRUE) {
			theApp.m_MapMgr.m_pObjSelected->m_bLightSpecular = TRUE;
		}
		else {
			theApp.m_MapMgr.m_pObjSelected->m_bLightSpecular = FALSE;
		}
	}
	else {
		AfxMessageBox(
			L"선택된 오브젝트가 없습니다.\n"
			L"오브젝트를 우선 선택해주시겠습니까?", MB_OK);
	}
}
