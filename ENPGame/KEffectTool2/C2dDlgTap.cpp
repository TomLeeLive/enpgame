// C2dDlgTap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "KEffectTool.h"
#include "C2dDlgTap.h"
#include "afxdialogex.h"

#include "KEffectTool.h"

// C2dDlgTap ��ȭ �����Դϴ�.

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


// C2dDlgTap �޽��� ó�����Դϴ�.


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
	strValue = OpenBn.GetPathName();	//����Ʈ�� �ѱ� �κ�

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
		SaveListIndex = SaveList->GetCurSel(); //���콺 ���� �κ�
		if (SaveListIndex != LB_ERR)
		{
			SaveList = (CListBox *)GetDlgItem(IDC_LISTBOX);
			SaveList->GetText(SaveListIndex, m_strPath);	// m_strPath�� ���ϴ� ���콺 ���� Ŭ���� ����Ʈ�� ������ ��ΰ�  ����ֽ��ϴ�. 
		}
		if (m_strPath.Right(4) != ".tga")
		{
			m_strPath += ".tga";
		}
		file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
		file.Close();
	}
	*/
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CKEffectToolApp *pApp = (CKEffectToolApp *)AfxGetApp();

	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();


	TCHAR current_path[MAX_PATH] = _T("");
	GetCurrentDirectory(MAX_PATH, current_path); // ���� ��� ����

	CFileDialog dlg(false, _T("eff"), _T("*.eff"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("EFF File(*.eff)|*.eff||"));

	if (dlg.DoModal() == IDOK) { // OK �� �ϴ� ���� ���� ��ΰ� ����ȴ�.
								 // ���⼭ ���� ���� �۾�.
								 // ���⼭ ��� dlg.GetFileName() �Լ��� ��� ��η��� ���� �̸��� ��ȯ�� �ش�.

								 // ������ ������ �̸�..
								 // dlg.GetFileName();

								 // ������ ������ �̸��� ������ ���..
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

				//"�ð�..";
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
			
			//strFile.Append(_T(" ����Ϸ�"));
			//MessageBox(g_hWnd, strFile, L"���� �Ϸ�", MB_OK);
		}
		
	}
	SetCurrentDirectory(current_path); // ���� ��η� ���� ����.
}

void C2dDlgTap::OnBnClickedOnbnclick2dplay()
{
	CString strPath;

	CKEffectToolApp* p_CParctice = (CKEffectToolApp*)AfxGetApp();

	PlayList = (CListBox *)GetDlgItem(IDC_LISTBOX);
	PlayListIndex = PlayList->GetCurSel();
	PlayList->GetText(PlayListIndex, strPath);

	//play ��ư�� init() �κ�
	p_CParctice->m_EffMgr.m_List[0]->m_pSprite->Create(p_CParctice->GetDevice(), L"data/shader/plane.hlsl", strPath);

	//�̹��� �̸��� ������ ���´�. ���߿� save �Ҷ� ����.
	TCHAR  *tchr = (TCHAR*)(LPCTSTR)strPath;
	//p_CParctice->m_EffMgr.GetStringWeNeed(tchr, tchr);
	p_CParctice->m_EffMgr.m_ImageList.push_back(tchr);

	// �ִϸ��̼� ����, ����4x4
	p_CParctice->m_EffMgr.m_List[0]->m_pSprite->SetRectAnimation(1.0f, 4, 128, 4, 128);


	p_CParctice->m_EffMgr.m_List[0]->m_bCheck = true;

}


void C2dDlgTap::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
