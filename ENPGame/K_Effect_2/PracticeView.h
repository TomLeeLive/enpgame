
// PracticeView.h : CPracticeView Ŭ������ �������̽�
//

#pragma once


class CPracticeView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPracticeView();
	DECLARE_DYNCREATE(CPracticeView)

// Ư���Դϴ�.
public:
	CPracticeDoc* GetDocument() const;

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
	virtual ~CPracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // PracticeView.cpp�� ����� ����
inline CPracticeDoc* CPracticeView::GetDocument() const
   { return reinterpret_cast<CPracticeDoc*>(m_pDocument); }
#endif

