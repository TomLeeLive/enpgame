#pragma once
#include "EffectTool.h"

// EffectListBox 대화 상자입니다.

class EffectListBox : public CDialogEx
{
	DECLARE_DYNAMIC(EffectListBox)

public:
	EffectListBox(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~EffectListBox();
public:
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EffectTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
