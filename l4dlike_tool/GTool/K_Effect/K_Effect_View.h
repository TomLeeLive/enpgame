
// K_Effect_View.h : CK_Effect_View Ŭ������ �������̽�
//

#pragma once


class CK_Effect_View : public CView
{
protected: // serialization������ ��������ϴ�.
	CK_Effect_View();
	DECLARE_DYNCREATE(CK_Effect_View)

// Ư���Դϴ�.
public:
	CK_Effect_Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CK_Effect_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // K_Effect_View.cpp�� ����� ����
inline CK_Effect_Doc* CK_Effect_View::GetDocument() const
   { return reinterpret_cast<CK_Effect_Doc*>(m_pDocument); }
#endif

