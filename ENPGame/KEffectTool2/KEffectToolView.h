
// KEffectToolView.h : CKEffectToolView Ŭ������ �������̽�
//

#pragma once


class CKEffectToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CKEffectToolView();
	DECLARE_DYNCREATE(CKEffectToolView)

// Ư���Դϴ�.
public:
	CKEffectToolDoc* GetDocument() const;

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
	virtual ~CKEffectToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // KEffectToolView.cpp�� ����� ����
inline CKEffectToolDoc* CKEffectToolView::GetDocument() const
   { return reinterpret_cast<CKEffectToolDoc*>(m_pDocument); }
#endif

