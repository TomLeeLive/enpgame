#pragma once
#include "GImeUI.h"
#include "GShape.h"
#include "GTimer.h"
using namespace DX;

//#define G_MACRO_INVALID_INT_VALUE -1

enum GUI_TYPE {
	GUI_TYPE_BUTTON = 0,
	GUI_TYPE_BUTTONHALF,
	GUI_TYPE_EDIT,
	GUI_TYPE_LISTBOX,
	GUI_TYPE_STATICTEXT,
	GUI_TYPE_IMAGE,
	GUI_CNT
};

class GControlUI
{
public:
	HRESULT						SetBlendState();
	ID3D11BlendState*			m_pAlphaBlend;
public:
	int				m_iWidthBefore;
	int				m_iWidthAfter;
	int				m_iHeightBefore;
	int				m_iHeightAfter;
	bool			m_bAutoRescale;
	bool			m_bAutoRetrans;
	//bool			m_bRelTrans;	// relativity(���) ��ǥ ����
	//bool			m_bRelScale;	// relativity(���) ������ ����
	GUI_TYPE		m_type;
	void			Retrans();
	void			Rescale();
public:	
	GShape*			m_pShape;
	T_STR			m_Text;
	PCT_VERTEX		m_Vertices[4];
	RECT			m_rtSize[8];
	RECT			m_rt;
	D3DXMATRIX		m_matViewPort;
	D3DXMATRIX		m_matWorld;
	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRotate;
	D3DXVECTOR3		m_vTrans;
	UINT			m_iWidthVP;
	UINT			m_iHeightVP;
public: //event
	virtual void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual void		SetAmbientColor(float fR, float fG, float fB, float fA);
	virtual bool		Init();
	virtual HRESULT		Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile = nullptr,
							const TCHAR* pLoadTextureString = nullptr) 	{return S_OK;};
	virtual HRESULT		CreateResource(int iRectWidth, int iRectHeight);
	virtual bool		Set(UINT iWidth, UINT iHeight);
	virtual void		Move(float x, float y, float z);
	virtual void		Scale(float x, float y, float z);
	virtual void		Rotate(float x, float y, float z);
	virtual bool		Update();
	virtual bool		Begin(ID3D11DeviceContext* pContext);
	virtual bool		End(ID3D11DeviceContext* pContext);
	virtual bool		Render(ID3D11DeviceContext* pContext);
	virtual bool		Release();
public:
	GControlUI();
	virtual ~GControlUI();
};
class GButtonCtl : public GControlUI
{
public:
	GTimer*		m_Timer;
	bool		m_bClicked;
	float		m_fClickStTime;
	float		m_fCoolTime;
	void		Clicked(GTimer*	timer) {
		m_Timer = timer;
		m_fClickStTime = m_Timer->m_fDurationTime;
		m_bClicked = true;
	}
public:
	GBoxShape   m_Box;
	HRESULT		Create(ID3D11Device* pDevice,
		const TCHAR* pLoadShaderFile=nullptr,
		const TCHAR* pLoadTextureString = nullptr);
	bool		Render(ID3D11DeviceContext* pContext) {

		if (m_bClicked) {
			
			if (m_Timer->m_fDurationTime - m_fClickStTime > m_fCoolTime) {
				m_Box.SetShaded(false);
				m_bClicked = false;
				return false;
			}
			else
			{m_Box.SetShaded();}
		}

		GControlUI::Render(pContext);
	}
public:
	GButtonCtl() {
		m_fCoolTime = 0.5f;
		m_Timer = NULL;
		m_bClicked = false;
		m_fClickStTime = 0.0f;
		m_type = GUI_TYPE_BUTTON; };
	virtual ~GButtonCtl() {};
};

class GButtonHalfCtl : public GControlUI
{
public:
	D3DXVECTOR3		  m_initScl;
	GBoxHalfShape     m_Box;
	HRESULT		Create(ID3D11Device* pDevice,
		const TCHAR* pLoadShaderFile = nullptr,
		const TCHAR* pLoadTextureString = nullptr);

	HRESULT		Create(ID3D11Device* pDevice,
		D3DXVECTOR3 initScl,
		const TCHAR* pLoadShaderFile = nullptr,
		const TCHAR* pLoadTextureString = nullptr);

	void	SetXSize(float fValue) {//0~100������ �Է� ����.
		if (fValue <= 0.0f) {
			m_vScale.x = 0.0f;
			return;
		}

		if (fValue >= 100.0f) {
			m_vScale.x = m_initScl.x;
			return;
		}

		m_vScale.x = m_initScl.x / 100.0f *fValue;
	}

public:
	GButtonHalfCtl() { m_type = GUI_TYPE_BUTTONHALF; m_initScl = D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	virtual ~GButtonHalfCtl() {};
};

class GStaticTextCtl : public GButtonCtl
{
public:
	GPlaneShape   m_Plane;
	GStaticTextCtl() { m_type = GUI_TYPE_STATICTEXT; };
	virtual ~GStaticTextCtl() {};
};

class GEditCtl : public GButtonCtl
{
public:
	GPlaneShape   m_Plane;
	T_STR    m_CompString;
	T_STR    m_CompWord;
	T_STR    m_CurrentString;
public:
	HRESULT		Create(ID3D11Device* pDevice,
		const TCHAR* pLoadShaderFile = nullptr,
		const TCHAR* pLoadTextureString = nullptr);
	GEditCtl() { m_type = GUI_TYPE_EDIT; };
	virtual ~GEditCtl() {};
};

class GListBoxCtl : public GButtonCtl
{
public:
	std::vector<GButtonCtl*>  m_ListBox;
	GListBoxCtl() { m_type = GUI_TYPE_LISTBOX; };
	virtual ~GListBoxCtl() {};
};
class GImageCtl : public GButtonCtl
{
public:
	std::vector<GButtonCtl*>  m_ListBox;
	HRESULT		Create(ID3D11Device* pDevice,
		const TCHAR* pLoadShaderFile = nullptr,
		const TCHAR* pLoadTextureString = nullptr);
	GImageCtl() { m_type = GUI_TYPE_IMAGE; };
	virtual ~GImageCtl() {};
};
class GPanel // 1���� ��濡�� �ߴ� ��ȭ���� ����.
{
public:
	std::vector<GButtonCtl*>   m_ButtonCtl;
	std::vector<GImageCtl*>   m_ImageCtl;
	std::vector<GEditCtl*>   m_EditCtl;
	std::vector<GListBoxCtl*>   m_BoxCtl;
	std::vector<GStaticTextCtl*>   m_StaticTextCtl;
	GPanel() {};
	virtual ~GPanel() {};
};
class GSceneUI // ��� ȭ���� ��ü �Ǵ� ����
{
public:
	std::vector<GPanel*>  m_SceneList;
	std::vector<GImageCtl*>   m_ImageCtl;
	std::vector<GButtonCtl*>   m_ButtonCtl;
	std::vector<GEditCtl*>   m_EditCtl;
	std::vector<GListBoxCtl*>   m_listBoxCtl;
	std::vector<GStaticTextCtl*>   m_StaticTextCtl;
	GSceneUI() {};
	virtual ~GSceneUI() {};
};