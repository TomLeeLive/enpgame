#pragma once
#include "GImeUI.h"
#include "GShape.h"
using namespace DX;

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
	GUI_TYPE   m_type;
public:	
	GShape*     m_pShape;
	T_STR		m_Text;
	PCT_VERTEX  m_Vertices[4];
	RECT		m_rtSize[8];
	RECT		m_rt;
	D3DXMATRIX	m_matViewPort;
	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_matView;
	D3DXMATRIX  m_matProj;
	D3DXVECTOR3  m_vScale;
	D3DXVECTOR3  m_vRotate;
	D3DXVECTOR3  m_vTrans;
	UINT		 m_iWidthVP;
	UINT		 m_iHeightVP;
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
	GBoxShape     m_Box;
	HRESULT		Create(ID3D11Device* pDevice,
		const TCHAR* pLoadShaderFile=nullptr,
		const TCHAR* pLoadTextureString = nullptr);
public:
	GButtonCtl() { m_type = GUI_TYPE_BUTTON; };
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

	void	SetXSize(float fValue) {//0~100까지로 입력 받자.
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
class GPanel // 1개의 배경에서 뜨는 대화상자 개념.
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
class GSceneUI // 배경 화면이 교체 되는 단위
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