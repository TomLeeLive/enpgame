#include "GModel.h"

//조명 [Start]

void GModel::FrameLight() {
	if (G_LIGHT_TYPE_DIFFUSE == m_LightType) {
		//float t = m_Timer.GetElapsedTime() * D3DX_PI;
		D3DXMATRIX mLightWorld, mTranslate, mRotation;
		D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
		//D3DXMatrixRotationY(&mRotation, t*0.1f);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixMultiply(&mLightWorld, &mRotation, &mTranslate);

		m_vLightVector.x = mLightWorld._41;
		m_vLightVector.y = mLightWorld._42;
		m_vLightVector.z = mLightWorld._43;

		D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
		m_vLightVector *= -1.0f;

	}
	else if (G_LIGHT_TYPE_SPECULAR == m_LightType) {
		D3DXMATRIX mLightWorld, mTranslate, mRotation;
		D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
		//D3DXMatrixRotationY(&mRotation, t * 0);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixMultiply(&mLightWorld, &mRotation, &mTranslate);

		m_vLightVector.x = mLightWorld._41;
		m_vLightVector.y = mLightWorld._42;
		m_vLightVector.z = mLightWorld._43;

		D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
		m_vLightVector *= -1.0f;
	}
}
void GModel::SetLight(G_LIGHT_TYPE type) {
	m_LightType = type;

	if (G_LIGHT_TYPE_DIFFUSE == m_LightType) {
		D3DXMATRIX mLightWorld, mTranslate, mRotation;
		D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
		D3DXMatrixIdentity(&mRotation);
		//D3DXMatrixRotationY(&mRotation, D3DXToRadian(90.0f));
		D3DXMatrixMultiply(&mLightWorld, &mRotation, &mTranslate);
		m_vLightVector.x = mLightWorld._41;
		m_vLightVector.y = mLightWorld._42;
		m_vLightVector.z = mLightWorld._43;
		D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
		m_vLightVector *= -1.0f;

		m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
		m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
	}
	else if (G_LIGHT_TYPE_SPECULAR == m_LightType) {
		m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1);
		m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(1, 1, 1, 1);

		m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight.g_cSpecularLightColor = D3DXVECTOR4(1, 1, 1, 1);
	}
	m_pConstantBufferLight.Attach(DX::CreateConstantBuffer(
		m_pd3dDevice, &m_cbLight, 1, sizeof(LIGHT_CONSTANT_BUFFER)));
}
void GModel::UpdateLightConstantBuffer( D3DXMATRIX matWorld)
{
	if (G_LIGHT_TYPE_DIFFUSE == m_LightType) {
		m_cbLight.g_vLightDir.x = m_vLightVector.x;
		m_cbLight.g_vLightDir.y = m_vLightVector.y;
		m_cbLight.g_vLightDir.z = m_vLightVector.z;
		m_cbLight.g_vLightDir.w = 1;
		D3DXMATRIX matInvWorld;
		D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
		D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
		D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

		g_pImmediateContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
		g_pImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
		g_pImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
	}
	else if (G_LIGHT_TYPE_SPECULAR == m_LightType) {
		m_cbLight.g_vLightDir.x = m_vLightVector.x;
		m_cbLight.g_vLightDir.y = m_vLightVector.y;
		m_cbLight.g_vLightDir.z = m_vLightVector.z;
		m_cbLight.g_vLightDir.w = 1.0f;

		D3DXMATRIX matInvWorld;
		D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
		D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
		D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

		//m_cbLight.g_vEyeDir.x = m_pMainCamera->m_vLookVector.x;
		//m_cbLight.g_vEyeDir.y = m_pMainCamera->m_vLookVector.y;
		//m_cbLight.g_vEyeDir.z = m_pMainCamera->m_vLookVector.z;
		m_cbLight.g_vEyeDir.w = 10.0f; // 강도
		m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(3.0f, 1.0f, 1.0f, 1);
		g_pImmediateContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
		g_pImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
		g_pImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
	}
}
//조명 [End]


bool GModel::Convert(ID3D11Device* pDevice) {
	return true;
};

bool GModel::Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, G_LIGHT_TYPE type) {
	m_LightType = type;
	return Convert(pDevice);
}

bool GModel::Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread)
{
	return Convert(pDevice);
};

bool GModel::Create(ID3D11Device* pDevice,
	const TCHAR* pLoadShaderFile,
	G_LIGHT_TYPE type,
	const TCHAR* pLoadTextureString)
{

	m_pd3dDevice = pDevice;


	if (FAILED(LoadShaderFile(pDevice, pLoadShaderFile)))
	{
		MessageBox(0, _T("LoadShaderFile 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(SetInputLayout()))
	{
		MessageBox(0, _T("SetInputLayout 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!CreateVertexData())
	{
		MessageBox(0, _T("CreateVertexData 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!CreateIndexData())
	{
		MessageBox(0, _T("CreateIndexData 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateVertexBuffer()))
	{
		MessageBox(0, _T("CreateVertexBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		MessageBox(0, _T("CreateIndexBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		MessageBox(0, _T("CreateConstantBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(LoadTextures(pDevice, pLoadTextureString)))
	{
		MessageBox(0, _T("LoadTextures 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!UpdateBuffer())
	{
		MessageBox(0, _T("UpdateBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateResource()))
	{
		MessageBox(0, _T("CreateResource 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//조명 [Start]
	SetLight(type);
	//조명 [End]

	return Init();
}
bool GModel::Create(ID3D11Device* pDevice,
	const TCHAR* pLoadShaderFile,
	const TCHAR* pLoadTextureString)
{
	m_pd3dDevice = pDevice;

	if (FAILED(LoadShaderFile(pDevice, pLoadShaderFile)))
	{
		MessageBox(0, _T("LoadShaderFile 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(SetInputLayout()))
	{
		MessageBox(0, _T("SetInputLayout 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!CreateVertexData())
	{
		MessageBox(0, _T("CreateVertexData 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!CreateIndexData())
	{
		MessageBox(0, _T("CreateIndexData 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateVertexBuffer()))
	{
		MessageBox(0, _T("CreateVertexBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		MessageBox(0, _T("CreateIndexBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		MessageBox(0, _T("CreateConstantBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(LoadTextures(pDevice, pLoadTextureString)))
	{
		MessageBox(0, _T("LoadTextures 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (!UpdateBuffer())
	{
		MessageBox(0, _T("UpdateBuffer 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(CreateResource()))
	{
		MessageBox(0, _T("CreateResource 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	//조명 [Start]
	SetLight(G_LIGHT_TYPE_DIFFUSE);
	//조명 [End]

	

	return Init();
}
HRESULT GModel::LoadTextures(ID3D11Device* pDevice, const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	m_dxobj.g_pTextureSRV.Attach(DX::CreateShaderResourceView(pDevice, pLoadTextureString));
	return hr;
}
HRESULT GModel::LoadShaderFile(ID3D11Device* pDevice, const TCHAR* pShaderFile)
{
	m_dxobj.g_pVertexShader.Attach(DX::LoadVertexShaderFile(pDevice, pShaderFile, m_dxobj.g_pVSBlob.GetAddressOf()));
	m_dxobj.g_pPixelShader.Attach(DX::LoadPixelShaderFile(pDevice, pShaderFile));
	m_dxobj.g_pGeometryShader.Attach(DX::LoadGeometryShaderFile(pDevice, pShaderFile, m_dxobj.g_pGSBlob.GetAddressOf()));
	m_dxobj.g_pHullShader.Attach(DX::LoadHullShaderFile(pDevice, pShaderFile, m_dxobj.g_pHSBlob.GetAddressOf()));
	m_dxobj.g_pDomainShader.Attach(DX::LoadDomainShaderFile(pDevice, pShaderFile, m_dxobj.g_pDSBlob.GetAddressOf()));
	m_dxobj.g_pComputeShader.Attach(DX::LoadComputeShaderFile(pDevice, pShaderFile, m_dxobj.g_pCSBlob.GetAddressOf()));
	return S_OK;
}
bool	GModel::CreateVertexData()
{
	return true;
}
bool	GModel::CreateIndexData()
{
	return true;
}
HRESULT GModel::CreateVertexBuffer()
{
	if (m_dxobj.m_iNumVertex <= 0) return S_OK;
	void** pData = nullptr;
	if (m_VertexList.size() > 0) pData = (void**)&m_VertexList.at(0);

	//EnterCriticalSection(&g_CSd3dDevice);
	m_dxobj.g_pVertexBuffer.Attach(DX::CreateVertexBuffer(m_pd3dDevice,
		pData,
		m_dxobj.m_iNumVertex,
		m_dxobj.m_iVertexSize));
	//LeaveCriticalSection(&g_CSd3dDevice);
	return S_OK;
}
HRESULT	GModel::CreateIndexBuffer()
{
	if (m_dxobj.m_iNumIndex <= 0) return S_OK;
	void** pData = nullptr;
	if (m_IndexList.size() > 0) pData = (void**)&m_IndexList.at(0);

	//EnterCriticalSection(&g_CSd3dDevice);
	m_dxobj.g_pIndexBuffer.Attach(DX::CreateIndexBuffer(m_pd3dDevice,
		pData,
		m_dxobj.m_iNumIndex,
		m_dxobj.m_iIndexSize));
	//LeaveCriticalSection(&g_CSd3dDevice);

	return S_OK;
}
HRESULT GModel::CreateConstantBuffer()
{
	m_cbData.Color = D3DXVECTOR4(1, 1, 1, 1);

	//EnterCriticalSection(&g_CSd3dDevice);
	m_dxobj.g_pConstantBuffer.Attach(DX::CreateConstantBuffer(m_pd3dDevice, &m_cbData, 1, sizeof(VS_CONSTANT_BUFFER)));
	//LeaveCriticalSection(&g_CSd3dDevice);
	return S_OK;
}
bool GModel::Draw(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor) { return true; }
HRESULT GModel::SetInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//EnterCriticalSection(&g_CSd3dDevice);
	m_dxobj.g_pInputlayout.Attach(DX::CreateInputlayout(m_pd3dDevice, m_dxobj.g_pVSBlob.Get()->GetBufferSize(),
		m_dxobj.g_pVSBlob.Get()->GetBufferPointer(), layout, numElements));
	//LeaveCriticalSection(&g_CSd3dDevice);
	return hr;
}
bool GModel::UpdateBuffer() { return true; }
bool GModel::Init() { return true; }
bool GModel::Frame() { return true; }
bool GModel::Release() { return true; }
bool GModel::PreRender(ID3D11DeviceContext* pContext)
{
	pContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_dxobj.m_iPrimitiveType);
	m_dxobj.PreRender(pContext, m_dxobj.m_iVertexSize);
	return true;
}
void GModel::UpdateConstantBuffer(ID3D11DeviceContext* pContext, GModel* pParent)
{
	if( pParent != NULL )
	{
		pContext->UpdateSubresource(pParent->m_dxobj.g_pConstantBuffer.Get(), 0, NULL, &pParent->m_cbData, 0, 0);
	}
	else
	{
		pContext->UpdateSubresource(m_dxobj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
	}
}
bool GModel::PostRender(ID3D11DeviceContext* pContext)
{
	//조명 [Start]
	UpdateLightConstantBuffer(m_matWorld);
	//조명 [End]

	UpdateConstantBuffer(pContext);
	m_dxobj.PostRender(pContext, m_dxobj.m_iNumIndex);
	return true;
}
bool GModel::Render(ID3D11DeviceContext* pContext)
{
	PreRender(pContext);
	PostRender(pContext);
	return true;
}

void GModel::SetAmbientColor(float fR, float fG, float fB, float fA)
{
	m_cbData.Color = D3DXVECTOR4(fR, fG, fB, fA);
}
void GModel::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
		m_vCenter.x = pWorld->_41;
		m_vCenter.y = pWorld->_42;
		m_vCenter.z = pWorld->_43;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}
ID3D11Buffer* GModel::GetVB()
{
	return m_dxobj.g_pVertexBuffer.Get();
}
ID3D11Buffer* GModel::GetIB()
{
	return m_dxobj.g_pIndexBuffer.Get();
}
HRESULT GModel::CreateResource()
{
	m_dxobj.m_iPrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	return S_OK;
}
HRESULT GModel::DeleteResource()
{
	return S_OK;
}
GModel::GModel(void)
{
	m_LightType = G_LIGHT_TYPE_DIFFUSE;
	m_pd3dDevice = NULL;
	m_cbData.Color = D3DXVECTOR4(1, 1, 1, 1);
	m_vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matWorld);
	m_pd3dDevice = NULL;
	m_fElapseTime = 0.0f;
	m_iStartFrame = 0;
	m_iLastFrame = 0;
	m_iMaxVertex = 0;
	m_iMaxIndex = 0;
	m_iBeginPosVB = 0;
	m_iBeginPosIB = 0;
	m_ObjType = NULLFILE;
	m_bOptimization = true;
	m_iMatrixIndex = -1;
}

GModel::~GModel(void)
{
}
