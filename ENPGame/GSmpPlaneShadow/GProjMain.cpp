#include "GProjMain.h"

GProjMain* g_pMain;

D3DXMATRIX* WINAPI TD3DXMatrixShadow(D3DXMATRIX *pout, 
	 CONST D3DXVECTOR4 *plight, 
	 CONST D3DXPLANE *pplane)
 {
     D3DXPLANE Nplane;
     FLOAT dot;
 
     D3DXPlaneNormalize(&Nplane, pplane);
     dot = D3DXPlaneDot(&Nplane, plight);
     pout->m[0][0] = dot - Nplane.a * plight->x;
     pout->m[0][1] = -Nplane.a * plight->y;
     pout->m[0][2] = -Nplane.a * plight->z;
     pout->m[0][3] = -Nplane.a * plight->w;
     pout->m[1][0] = -Nplane.b * plight->x;
     pout->m[1][1] = dot - Nplane.b * plight->y;
     pout->m[1][2] = -Nplane.b * plight->z;
     pout->m[1][3] = -Nplane.b * plight->w;
     pout->m[2][0] = -Nplane.c * plight->x;
     pout->m[2][1] = -Nplane.c * plight->y;
     pout->m[2][2] = dot - Nplane.c * plight->z;
     pout->m[2][3] = -Nplane.c * plight->w;
     pout->m[3][0] = -Nplane.d * plight->x;
     pout->m[3][1] = -Nplane.d * plight->y;
     pout->m[3][2] = -Nplane.d * plight->z;
     pout->m[3][3] = dot - Nplane.d * plight->w;
     return pout;
}

D3DXMATRIX GProjMain::CreateMatrixShadow( D3DXVECTOR4 plane, 
											D3DXVECTOR4 Light )
{
	D3DXMATRIX mat;	
	D3DXVECTOR3 vPlane, vLight;
	D3DXVec4Normalize(&plane, &plane );

	vPlane = -D3DXVECTOR3( plane.x, plane.y, plane.z );
	vLight = D3DXVECTOR3( Light.x, Light.y, Light.z );// 라이트 디렉션이 바뀌지 않는다.

	float w = -D3DXVec3Dot( &vPlane, &D3DXVECTOR3(0.0f, 0.0f, 0.0f ))-0.01f;
	float a = D3DXVec3Dot( &vPlane, &vLight );	
	float b = w - a;
	mat._11 = vPlane.x * Light.x+b;	mat._12 = vPlane.x * Light.y;	
	mat._13 = vPlane.x * Light.z;	mat._14 = vPlane.x * Light.w;
	mat._21 = vPlane.y * Light.x;	mat._22 = vPlane.y * Light.y+b;	
	mat._23 = vPlane.y * Light.z;	mat._24 = vPlane.y * Light.w;	
	mat._31 = vPlane.z * Light.x;	mat._32 = vPlane.z * Light.y;	
	mat._33 = vPlane.z * Light.z+b;	mat._34 = vPlane.z * Light.w;
	mat._41 = -(a+b) * Light.x;	mat._42 = -(a+b) * Light.y;	
	mat._43 = -(a+b) * Light.z;	mat._44 = -a;

	
	//D3DXMATRIX mat;	
	D3DXVec4Normalize(&plane, &plane );
	plane *= -1.0f;
	float D = -D3DXVec4Dot( &plane, &Light );	
	mat._11 = plane.x * Light.x+D;	mat._12 = plane.x * Light.y;	
	mat._13 = plane.x * Light.z;	mat._14 = plane.x * Light.w;
	mat._21 = plane.y * Light.x;	mat._22 = plane.y * Light.y+D;	
	mat._23 = plane.y * Light.z;	mat._24 = plane.y * Light.w;	
	mat._31 = plane.z * Light.x;	mat._32 = plane.z * Light.y;	
	mat._33 = plane.z * Light.z+D;	mat._34 = plane.z * Light.w;
	mat._41 = plane.w * Light.x;	mat._42 = plane.w * Light.y;	
	mat._43 = plane.w * Light.z;	mat._44 = plane.w * Light.w+D;
	return mat;
}
 
bool GProjMain::Init()
{
	TMapDesc MapDesc = { 33, 33, 1.0f,10.0f, L"../../data/base1.bmp", L"HeightMap.hlsl" };
	m_CustomMap.Init( GetDevice(), m_pImmediateContext );
	if( FAILED( m_CustomMap.Load(MapDesc) ))
	{
		return false;
	}	
	if( FAILED( CreateResource() ))
	{
		return false;
	}	
	D3DXMatrixIdentity(&m_matWorld);
	//--------------------------------------------------------------------------------------
	// 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	SAFE_NEW( m_pBoxShape, GBoxShape );
	if( FAILED( m_pBoxShape->Create(GetDevice(), L"PlaneShadow.hlsl",L"../../data/castle.jpg") ) )
	{
		MessageBox( 0, _T("m_LineShape 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), 
		L"PlaneShadow.hlsl", "PS_Color"));

	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -20.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 3000.0f);
	return true;
}
bool GProjMain::Render()
{	
	m_CustomMap.SetMatrix( NULL,m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_CustomMap.Render(GetContext());
	// Box 1
	D3DXMatrixTranslation( &m_matWorld, 0, 5, 0 );
	m_pBoxShape->SetMatrix( &m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix() );
	m_pBoxShape->Render(GetContext());
	///////////////////////////////////////////
	//// Plane Shadow Rendering( Point Light )
	///////////////////////////////////////////
	D3DXVECTOR3 vLight = D3DXVECTOR3( 5, 10, 5 );
	D3DXVECTOR4 pLight = D3DXVECTOR4( vLight.x, vLight.y, vLight.z, 1.0f );
	D3DXPLANE pPlane = D3DXPLANE(0, 1, 0, -0.01f );

	D3DXMATRIX matShadow;
	D3DXVECTOR4 p(pPlane.a, pPlane.b, pPlane.c, pPlane.d );
	//matShadow = (D3DXMATRIX)m_mShadowPoint.CreateMatrixShadow( (Vector4*)&p, (Vector4*)&pLight );
	D3DXMatrixShadow( &matShadow, &pLight, &pPlane );
	RenderShadow( m_matWorld, matShadow, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix() );
	/////////////////////////////////////////
	//// Plane Shadow Rendering( Direction Light )
	///////////////////////////////////////////
	vLight = D3DXVECTOR3( -5, 10, 5 );
	D3DXVec3Normalize(&vLight, &vLight );	
	pLight = D3DXVECTOR4( vLight.x, vLight.y, vLight.z, 0.0f );		
	//D3DXMatrixShadow( &mat, &pLight, &pPlane );
	//TD3DXMatrixShadow( &mat, &pLight, &pPlane );
	//matShadow = (D3DXMATRIX)m_mShadowPoint.CreateMatrixShadowD( (Vector4*)&p, (Vector4*)&pLight );
	matShadow = (D3DXMATRIX)m_mShadowPoint.CreateMatrixShadow( (Vector4*)&p, (Vector4*)&pLight );
	RenderShadow( m_matWorld, matShadow, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix() );
	return true;
}

void GProjMain::RenderShadow( D3DXMATRIX matWorld, D3DXMATRIX matShadow, 
						   D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	ApplyDSS(GetContext(), GDxState::g_pDSSDepthEnable);
	ApplyRS(GetContext(), GDxState::g_pRSBackCullSolid);
	ApplyBS(GetContext(), GDxState::g_pAlphaBlend);
	m_matShadow = matWorld * matShadow;		
	m_pBoxShape->m_cbData.Color = D3DXVECTOR4(0, 0, 0, 0.5f);
	m_pBoxShape->SetMatrix( &m_matShadow, matView, matProj );
	m_pBoxShape->PreRender(GetContext());
	GetContext()->PSSetShader(m_pPixelShader.Get(), NULL, 0);
	m_pBoxShape->PostRender(GetContext());
}
bool GProjMain::Release()
{	
	SAFE_DEL( m_pLine  );
	SAFE_DEL( m_pBoxShape  );
	return m_CustomMap.Release();
}
bool GProjMain::Frame()
{
	m_pMainCamera->Frame();
	return m_CustomMap.Frame();
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 3000.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{
	SAFE_ZERO(m_pLine);
	SAFE_ZERO( m_pBoxShape  );
}

GProjMain::~GProjMain(void)
{
}

GCORE_RUN(GBasisSample PlaneShadow)