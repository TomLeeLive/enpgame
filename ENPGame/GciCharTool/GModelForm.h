#pragma once



// GModelForm �� ���Դϴ�.

class GModelForm : public CFormView
{
	DECLARE_DYNCREATE(GModelForm)

protected:
	GModelForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GModelForm();

	// �߰���_S
public:
	static GModelForm* CreateOne(CWnd* pParent);
	
public:
	void UpdateTextOBBInfo(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	//�߰���_E
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMODELFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	float m_fMinX;
	float m_fMinY;
	float m_fMinZ;
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxZ;
};


