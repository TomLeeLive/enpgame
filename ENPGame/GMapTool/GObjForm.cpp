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
	, m_fSclX(0)
	, m_fSclY(0)
	, m_fSclZ(0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fRotZ(0)
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
	DDX_Text(pDX, IDC_ObjSacleX, m_fSclX);
	DDX_Text(pDX, IDC_ObjScaleY, m_fSclY);
	DDX_Text(pDX, IDC_ObjScaleZ, m_fSclZ);
	DDX_Text(pDX, IDC_ObjRotationX, m_fRotX);
	DDX_Text(pDX, IDC_ObjRotationY, m_fRotY);
	DDX_Text(pDX, IDC_ObjRotationZ, m_fRotZ);
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

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("GBS File(*.gbs)|*.gbs|All Files(*.*)|*.*||"));

	//CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		//dlg.GetPathName();
		FILE *fp;
		strObjFile = dlg.GetFileName();

	}
	else {
		return;
	}



	TCHAR * TChr = NULL;
	//CString -> TCHAR
	TChr = (TCHAR*)(LPCTSTR)strObjFile;

	TCHAR strFile[MAX_PATH] = L"data\\object\\building\\";

	_tcsncat(strFile, (TCHAR*)TChr, _tcsclen((TCHAR*)TChr));

	I_ObjMgr.Load(g_pd3dDevice, strFile, G_SHA_OBJ_DIFFUSE_REVERSE);

	

	auto objData = make_shared<GObjData>();
	objData->m_pObj = (GGbsObj*)I_ObjMgr.GetPtr(TChr);

	//s, r, t 설정.
	D3DXMatrixScaling(&objData->m_matObjScl, 1, 1, 1);
	D3DXMatrixRotationY(&objData->m_matObjRot, D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&objData->m_matObjTrans, 0.0f, 0.0f, 0.0f);
	objData->m_matObjWld = objData->m_matObjScl * objData->m_matObjRot * objData->m_matObjTrans;


	if (theApp.m_MapMgr.m_iMapSelected == -1) {
		AfxMessageBox(
			L"선택된 맵이 없습니다.\n"
			L"맵을 우선 선택해주시겠습니까?", MB_OK);
		return;
	}

	_tcsncpy_s(objData->m_strName, (TCHAR*)(LPCTSTR)strObjFile, strObjFile.GetLength());

	theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.push_back(objData);

	TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
	_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.size() - 1, TChr/*L" GBS"*/);
	m_listObj.AddString(szRet);
}



void GObjForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void GObjForm::OnLbnSelchangeListobj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelected = m_listMap.GetCurSel();
	if (iSelected == -1)
		return;

	if (theApp.m_MapMgr.m_vecMapGroup.size() == 0)
		return;

	theApp.m_MapMgr.m_pObjSelected = theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj[iSelected].get();
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

	m_listObj.ResetContent();

	for (int i = 0; i < theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj.size(); i++) {

		TCHAR szRet[30] = { 0 }; // "10"의 NULL 처리를 위한 3 count
		_stprintf_s(szRet, _countof(szRet), _T("%d - %s"), i, theApp.m_MapMgr.m_vecMapGroup[theApp.m_MapMgr.m_iMapSelected]->m_vecObj[i]->m_strName);
		m_listObj.AddString(szRet);

	}
	m_listObj.UpdateData(FALSE);


}
