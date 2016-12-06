#include "GPlaneRect.h"

HRESULT GControlUI::SetBlendState() {
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = TRUE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	//EnterCriticalSection(&g_CSd3dDevice);
	if (FAILED(hr = g_pd3dDevice->CreateBlendState(&BlendState, &m_pAlphaBlend)))
	{
		//LeaveCriticalSection(&g_CSd3dDevice);
		return hr;
	}
	//LeaveCriticalSection(&g_CSd3dDevice);
	return hr;
}
void GControlUI::SetAmbientColor(float fR, float fG, float fB, float fA)
{
	m_pShape->m_cbData.Color = D3DXVECTOR4(fR, fG, fB, fA);
}
void GControlUI::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
		m_pShape->m_vCenter.x = pWorld->_41;
		m_pShape->m_vCenter.y = pWorld->_42;
		m_pShape->m_vCenter.z = pWorld->_43;
	}
	if (pView != NULL)
	{
		m_pShape->m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_pShape->m_matProj = *pProj;
	}
	D3DXMatrixTranspose(&m_pShape->m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_pShape->m_cbData.matView, &m_pShape->m_matView);
	D3DXMatrixTranspose(&m_pShape->m_cbData.matProj, &m_pShape->m_matProj);
}
bool		GControlUI::Init()
{
	HRESULT hr;

	if (FAILED(hr = SetBlendState()))
	{
		return hr;
	}

	m_vScale.x = 1; m_vScale.y = 1; m_vScale.z = 1;
	m_vRotate.x = 0; m_vRotate.y = 0; m_vRotate.z = 0;
	m_vTrans.x = 0; m_vTrans.y = 0; m_vTrans.z = 0;
	
	D3DXMatrixScaling(&m_matWorld, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matWorld._41 = 0;
	m_matWorld._42 = 0;
	m_matWorld._41 = 0;
	// 충돌 평면 구성
	m_Vertices[0].p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_Vertices[0].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_Vertices[1].p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);	m_Vertices[1].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_Vertices[2].p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);	m_Vertices[2].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[2].t = D3DXVECTOR2(1.0f, 1.0f);
	m_Vertices[3].p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_Vertices[3].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertices[3].t = D3DXVECTOR2(0.0f, 1.0f);

	D3DXVECTOR3 vEye = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	D3DXVECTOR3 vAt = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_matView, &vEye, &vAt, &vUp);
	return true;
}
bool		GControlUI::Set(UINT iWidth, UINT iHeight)
{
	m_iWidthVP = iWidth;
	m_iHeightVP = iHeight;
	D3DXMatrixIdentity(&m_matViewPort);

	m_matViewPort._11 = 1;
	m_matViewPort._22 = -1;
	m_matViewPort._41 = (m_iWidthVP / 2.0f);
	m_matViewPort._42 = (m_iHeightVP / 2.0f);

	CreateResource(iWidth, iHeight);
	return true;
}
void		GControlUI::Move(float x, float y, float z)
{
	m_vTrans.x += x; //-200, 150, 0
	m_vTrans.y += y;
	m_vTrans.z += z;
	
}
void		GControlUI::Scale(float x, float y, float z)
{
	// 200, 150, 1
	m_vScale.x += x;
	m_vScale.y += y;
	m_vScale.z += z;
}
void		GControlUI::Rotate(float x, float y, float z)
{

}
bool		GControlUI::Update()
{
	D3DXMATRIX matScale, matRotate;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matRotate, m_vRotate.x,	m_vRotate.y, m_vRotate.z);
	m_matWorld = matScale * matRotate;
	m_matWorld._41 = m_vTrans.x;
	m_matWorld._42 = m_vTrans.y;
	m_matWorld._43 = m_vTrans.z;

	// 2D 클라이언트 좌표계 변환하여 충돌 영역 지정.
	D3DXVECTOR3 v[4];
	for (int iVer = 0; iVer < 4; iVer++)
	{
		D3DXVec3TransformCoord(&v[iVer],&m_Vertices[iVer].p, &m_matWorld);
		D3DXVec3TransformCoord(&v[iVer],&v[iVer], &m_matViewPort);
	}
	m_rt.left = v[0].x;
	m_rt.right = v[1].x;
	m_rt.top = v[0].y;
	m_rt.bottom = v[2].y;
	return true;
}
bool		GControlUI::Begin(ID3D11DeviceContext* pContext) {
	assert(m_pShape);
	m_pShape->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
	return m_pShape->PreRender(pContext);
}
bool		GControlUI::End(ID3D11DeviceContext* pContext) {
	assert(m_pShape);
	return m_pShape->PostRender(pContext);
}
bool		GControlUI::Render(ID3D11DeviceContext* pContext) {	
	// Store the old render targets
	ID3D11RenderTargetView* pOldRTV;
	ID3D11DepthStencilView* pOldDSV;

	//EnterCriticalSection(&g_CSImmediateContext);
	g_pImmediateContext->OMGetRenderTargets(1, &pOldRTV, &pOldDSV);

	ApplyRS(g_pImmediateContext, GDxState::g_pRSBackCullSolid);
	g_pImmediateContext->OMSetBlendState(m_pAlphaBlend, 0, -1);
	//LeaveCriticalSection(&g_CSImmediateContext);


	Begin(pContext);
	End(pContext);


	//-----------------------------------------------------------------------
	// 기본 render targets 정보로 복원
	//-----------------------------------------------------------------------
	//EnterCriticalSection(&g_CSImmediateContext);
	g_pImmediateContext->OMSetRenderTargets(1, &pOldRTV, pOldDSV);
	//LeaveCriticalSection(&g_CSImmediateContext);
	// OMGetRenderTargets함수를 사용하였다면 반드시 아래와 같이 소멸시켜야 한다.
	SAFE_RELEASE(pOldRTV);
	SAFE_RELEASE(pOldDSV);

	return true;
}
bool		GControlUI::Release() {
	SAFE_RELEASE(m_pAlphaBlend);
	assert(m_pShape);
	m_pShape->Release();
	return true;
}
void GControlUI::Rescale() {
	m_vScale.x = m_vScale.x * m_iWidthAfter / m_iWidthBefore;
	m_vScale.y = m_vScale.y * m_iHeightAfter / m_iHeightBefore;

	m_vTrans.x = m_vTrans.x * m_iWidthAfter / m_iWidthBefore;
	m_vTrans.y = m_vTrans.y * m_iHeightAfter / m_iHeightBefore;
}
void GControlUI::Retrans() {
	// 0  |  1
	//---------
	// 2  |  3

	if (m_vTrans.x < 0 && m_vTrans.y > 0) //0
	{

		int iX = m_iWidthBefore - (-m_vTrans.x);
		m_vTrans.x = -(m_iWidthAfter - iX);
		int iY = m_iHeightBefore - m_vTrans.y;
		m_vTrans.y = m_iHeightAfter - iY;

	}
	else if (m_vTrans.x > 0 && m_vTrans.y > 0) //1 
	{
		int iX = m_iWidthBefore - m_vTrans.x;
		m_vTrans.x = m_iWidthAfter - iX;
		int iY = m_iHeightBefore - m_vTrans.y;
		m_vTrans.y = m_iHeightAfter - iY;
	}
	else if (m_vTrans.x < 0 && m_vTrans.y < 0) //2
	{
		int iX = m_iWidthBefore - (-m_vTrans.x);
		m_vTrans.x = -(m_iWidthAfter - iX);

		int iY = m_iHeightBefore - (-m_vTrans.y);
		m_vTrans.y = -(m_iHeightAfter - iY);
	}
	else if (m_vTrans.x > 0 && m_vTrans.y < 0)//3
	{
		int iX = m_iWidthBefore - m_vTrans.x;
		m_vTrans.x = m_iWidthAfter - iX;
		int iY = m_iHeightBefore - (-m_vTrans.y);
		m_vTrans.y = -(m_iHeightAfter - iY);
	}
	else {

	}
}
HRESULT GControlUI::CreateResource(int iRectWidth, int iRectHeight)
{
	HRESULT hr = S_OK;

	//viewport 업데이트
	m_matViewPort._41 = (iRectWidth / 2.0f);
	m_matViewPort._42 = (iRectHeight / 2.0f);


	iRectWidth = iRectWidth / 2;
	iRectHeight = iRectHeight / 2;

	//D3DXMatrixOrthoLH(&m_Projection[1], iRectWidth * 2, iRectHeight * 2, 0.0f, 1000.0f);
	// 화면 중앙이 원점으로 계산되기 때문에 넓이 및 높이가 -1 ~ 1 범위로 직교투영된다. 
	D3DXMatrixOrthoOffCenterLH(&m_matProj, -iRectWidth, iRectWidth, -iRectHeight, iRectHeight, 0.0f, 1000.0f);

	m_iWidthAfter = iRectWidth;
	m_iHeightAfter = iRectHeight;

	if (m_iWidthBefore == NULL
		&& m_iHeightBefore == NULL) {
		m_iWidthAfter = m_iWidthBefore = iRectWidth;
		m_iHeightAfter = m_iHeightBefore = iRectHeight;

		return hr;
	}
	else if(m_bAutoRescale){
		Rescale();
	}
	else if (m_bAutoRetrans) {
		Retrans();
	}
	else {
	}


	m_iWidthBefore = m_iWidthAfter;
	m_iHeightBefore = m_iHeightAfter;



	return hr;
}
GControlUI::GControlUI()
{
	m_pAlphaBlend = NULL;

	m_iWidthBefore = NULL;
	m_iWidthAfter = NULL;
	m_iHeightBefore = NULL;
	m_iHeightAfter = NULL;
	m_bAutoRescale = true;
	m_bAutoRetrans = false;
	//m_bRelTrans = false;	// relativity(상대) 좌표 저장
	//m_bRelScale = false;
	//m_vRelTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_vRelScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_pShape = nullptr;
	Init();	
}


GControlUI::~GControlUI()
{
	m_pShape->Release();
}

HRESULT		GButtonHalfCtl::Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	if (pLoadShaderFile == nullptr)
	{
		if (FAILED(hr = m_Box.Create(pDevice, L"data/shader/UI.hlsl", pLoadTextureString)))
		{
			return hr;
		}
	}
	else
	{
		if (FAILED(hr = m_Box.Create(pDevice, pLoadShaderFile, pLoadTextureString)))
		{
			return hr;
		}
	}
	m_pShape = &m_Box;

	m_Vertices[0].p = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	m_Vertices[3].p = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	return hr;
}
HRESULT		GButtonHalfCtl::Create(ID3D11Device* pDevice, D3DXVECTOR3 initScl, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString)
{
	m_vScale = m_initScl = initScl;
	HRESULT hr = S_OK;
	if (pLoadShaderFile == nullptr)
	{
		if (FAILED(hr = m_Box.Create(pDevice, L"data/shader/UI.hlsl", pLoadTextureString)))
		{
			return hr;
		}
	}
	else
	{
		if (FAILED(hr = m_Box.Create(pDevice, pLoadShaderFile, pLoadTextureString)))
		{
			return hr;
		}
	}
	m_pShape = &m_Box;

	m_Vertices[0].p = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	m_Vertices[3].p = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	return hr;
}

HRESULT		GButtonCtl::Create(ID3D11Device* pDevice,const TCHAR* pLoadShaderFile,const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	if (pLoadShaderFile == nullptr)
	{
		if (FAILED(hr = m_Box.Create(pDevice, L"data/shader/UI.hlsl", pLoadTextureString)))
		{
			return hr;
		}
	}
	else
	{
		if (FAILED(hr = m_Box.Create(pDevice, pLoadShaderFile, pLoadTextureString)))
		{
			return hr;
		}
	}
	m_pShape = &m_Box;
	return hr;
}

HRESULT		GEditCtl::Create(ID3D11Device* pDevice,const TCHAR* pLoadShaderFile,const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	if (pLoadShaderFile == nullptr)
	{
		if (FAILED(hr = m_Plane.Create(pDevice, L"data/shader/UI.hlsl",pLoadTextureString)))
		{
			return hr;
		}
	}
	else
	{
		if (FAILED(hr = m_Plane.Create(pDevice, pLoadShaderFile, pLoadTextureString)))
		{
			return hr;
		}
	}
	m_pShape = &m_Plane;
	return hr;
}
HRESULT		GImageCtl::Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	if (pLoadShaderFile == nullptr)
	{
		if (FAILED(hr = m_Box.Create(pDevice, L"data/shader/UI.hlsl", pLoadTextureString)))
		{
			return hr;
		}
	}
	else
	{
		if (FAILED(hr = m_Box.Create(pDevice, pLoadShaderFile, pLoadTextureString)))
		{
			return hr;
		}
	}
	m_pShape = &m_Box;
	return hr;
}