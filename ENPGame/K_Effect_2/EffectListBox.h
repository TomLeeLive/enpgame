#pragma once
#include "EffectTool.h"

// EffectListBox ��ȭ �����Դϴ�.

class EffectListBox : public CDialogEx
{
	DECLARE_DYNAMIC(EffectListBox)

public:
	EffectListBox(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~EffectListBox();
public:
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EffectTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
