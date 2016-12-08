// C2dDlgTap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "C2dDlgTap.h"
#include "afxdialogex.h"

#include "KEffectTool.h"

// C2dDlgTap 대화 상자입니다.

IMPLEMENT_DYNAMIC(C2dDlgTap, CDialog)

C2dDlgTap::C2dDlgTap(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

C2dDlgTap::~C2dDlgTap()
{
}

void C2dDlgTap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C2dDlgTap, CDialog)
	ON_BN_CLICKED(IDC_OnBnClick2DOpen, &C2dDlgTap::OnBnClickedOnbnclick2dopen)
	ON_BN_CLICKED(IDC_OnBnClick2DSave, &C2dDlgTap::OnBnClickedOnbnclick2dsave)
	ON_BN_CLICKED(IDC_OnBnClick2DPlay, &C2dDlgTap::OnBnClickedOnbnclick2dplay)
	ON_BN_CLICKED(IDC_BUTTON1, &C2dDlgTap::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &C2dDlgTap::OnBnClickedButton5)
END_MESSAGE_MAP()


// C2dDlgTap 메시지 처리기입니다.


void C2dDlgTap::OnBnClickedOnbnclick2dopen()
{
	CKEffectToolApp *pApp = (CKEffectToolApp *)AfxGetApp();

	auto Effect = make_shared<KEffect>();
	Effect->Init();
	pApp->m_EffMgr.m_List.push_back(Effect);

	CString strValue;


	CFileDialog OpenBn(TRUE);
	if (OpenBn.DoModal() == IDOK)
		UpdateData(FALSE);
	strValue = OpenBn.GetPathName();	//리스트에 넘길 부분

	int Inserti = 0;
	InsertList = (CListBox*)GetDlgItem(IDC_LISTBOX);
	InsertList->InsertString(Inserti, strValue);
	Inserti = Inserti + 1;
	strValue = _T("");
}
void MatrixDecompose(D3DXVECTOR3* scl, D3DXVECTOR3* trans, D3DXMATRIX* mat) {
	D3DXQUATERNION quat;
	D3DXMatrixDecompose(scl, &quat, trans, mat);
}


void C2dDlgTap::OnBnClickedOnbnclick2dsave()
{
	/*
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.tga"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.tga)|*.tga|"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		SaveListIndex = SaveList->GetCurSel(); //마우스 누른 부분
		if (SaveListIndex != LB_ERR)
		{
			SaveList = (CListBox *)GetDlgItem(IDC_LISTBOX);
			SaveList->GetText(SaveListIndex, m_strPath);	// m_strPath에 원하는 마우스 왼쪽 클릭한 리스트에 파일의 경로가  들어있습니다. 
		}
		if (m_strPath.Right(4) != ".tga")
		{
			m_strPath += ".tga";
		}
		file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
		file.Close();
	}
	*/
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CKEffectToolApp *pApp = (CKEffectToolApp *)AfxGetApp();

	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();


	TCHAR current_path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH, current_path); // 현재 경로 저장

	CFileDialog dlg(false, _T("eff"), _T("*.eff"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("EFF File(*.eff)|*.eff||"));

	if (dlg.DoModal() == IDOK) { // OK 를 하는 순간 현재 경로가 변경된다.
								 // 여기서 파일 저장 작업.
								 // 여기서 얻는 dlg.GetFileName() 함수는 상대 경로로의 파일 이름을 반환해 준다.

								 // 선택한 파일의 이름..
								 // dlg.GetFileName();

								 // 선택한 파일의 이름을 포함한 경로..
		CString strFile = dlg.GetPathName();

		{

			FILE* fp = fopen((CStringA)strFile, "wt+");

			for (int iUiItem = 0; iUiItem<pApp->m_EffMgr.m_List.size(); iUiItem++)
			{
				G_EFFECT_TYPE type = pApp->m_EffMgr.m_List[iUiItem]->m_type;

				CString str;
				CString strNum;
				D3DXVECTOR3 scl;
				D3DXVECTOR3 trans;

				int Width = 0, WidthSize = 0, Height = 0, HeightSize = 0;

				MatrixDecompose(&scl, &trans, &pApp->m_EffMgr.m_List[iUiItem]->m_matBillboard);

				/*
					KEFFECT_BULLET = 0,
					KEFFECT_BLOOD,
					KEFFECT_DUST,
					KEFFECT_SMOG,
				*/
				switch (type)
				{
				case G_EFFECT_BULLET:
				{
					str = "#KEFFECT_BULLET\n";
					fprintf(fp, (CStringA)str);
				}
				break;
				case G_EFFECT_BLOOD:
				{
					str = "#KEFFECT_BLOOD\n";
					fprintf(fp, (CStringA)str);
				}
				break;
				case G_EFFECT_DUST:
				{
					str = "#KEFFECT_DUST\n";
					fprintf(fp, (CStringA)str);
				}
				break;
				case G_EFFECT_SMOG:
				{
					str = "#KEFFECT_SMOG\n";
					fprintf(fp, (CStringA)str);
				}
				break;
				}
				//str = "#IMAGE ";
				//str.Append(m_UIManager.m_ImageList[iUiItem].c_str());
				str = pApp->m_EffMgr.m_ImageList[iUiItem].c_str();
				str.Append(_T("\n"));
				fprintf(fp, (CStringA)str);
				
				
				strNum.Format(_T("%f"), scl.x);
				str = strNum;
				str.Append(_T("/"));
				strNum.Format(_T("%f"), scl.y);
				str.Append(strNum);
				str.Append(_T("/"));
				strNum.Format(_T("%f\n"), scl.z);
				str.Append(strNum);
				fprintf(fp, (CStringA)str);

				//"시간..";
				strNum.Format(_T("%f\n"), pApp->m_EffMgr.m_List[iUiItem]->m_fPlayTime);
				str = strNum;
				fprintf(fp, (CStringA)str);

				// Animation
				strNum.Format(_T("%d"), Width);
				str = strNum;
				str.Append(_T("/"));
				strNum.Format(_T("%d"), WidthSize);
				str.Append(strNum);
				str.Append(_T("/"));
				strNum.Format(_T("%d"), Height);
				str.Append(strNum);
				str.Append(_T("/"));
				strNum.Format(_T("%d"), HeightSize);
				str.Append(strNum);
				fprintf(fp, (CStringA)str);


				
			}

			fclose(fp);
			
			//strFile.Append(_T(" 저장완료"));
			//MessageBox(g_hWnd, strFile, L"저장 완료", MB_OK);
		}
		
	}
	SetCurrentDirectory(current_path); // 원래 경로로 돌아 간다.
}

void C2dDlgTap::OnBnClickedOnbnclick2dplay()
{
	CString strPath;

	CKEffectToolApp* p_CParctice = (CKEffectToolApp*)AfxGetApp();

	PlayList = (CListBox *)GetDlgItem(IDC_LISTBOX);
	PlayListIndex = PlayList->GetCurSel();
	PlayList->GetText(PlayListIndex, strPath);

	//play 버튼시 init() 부분
	p_CParctice->m_EffMgr.m_List[0]->m_pSprite->Create(p_CParctice->GetDevice(), L"data/shader/plane.hlsl", strPath);

	//이미지 이름을 저장해 놓는다. 나중에 save 할때 쓴다.
	TCHAR  *tchr = (TCHAR*)(LPCTSTR)strPath;
	//p_CParctice->m_EffMgr.GetStringWeNeed(tchr, tchr);
	p_CParctice->m_EffMgr.m_ImageList.push_back(tchr);

	// 애니메이션 관련, 가로4x4
	p_CParctice->m_EffMgr.m_List[0]->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);


	p_CParctice->m_EffMgr.m_List[0]->m_bCheck = true;

}


void C2dDlgTap::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CKEffectToolApp* pApp = (CKEffectToolApp*)AfxGetApp();

	if (!pApp->LoadFileDlg(_T("eff"), _T("EFF Load")))
	{
		return;
	}
	int iLoad = pApp->m_LoadFiles.size() - 1;

	pApp->m_EffMgr.Load(&pApp->m_LoadFiles[iLoad]);

}


void C2dDlgTap::OnBnClickedButton5()
{
	float  Ani_Time;
	int Width, WidthSize, Height, HeightSize;

	Ani_Time = IDC_Ani_Time;
	Width = IDC_Width;
	WidthSize = IDC_WidthSize;
	Height = IDC_Height;
	HeightSize = IDC_HeigthSize;


}
