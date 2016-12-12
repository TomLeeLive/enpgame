#include "GProjMain.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	TMapDesc MapDesc = { 33, 33, 1.0f, 10.0f,L"data_test/base1.bmp", L"data_test/shader_shadow/HeightMap_2.hlsl" };
	m_CustomMap.Init( GetDevice(), m_pImmediateContext );
	if( FAILED( m_CustomMap.Load(MapDesc) ))
	{
		return false;
	}	
	if( FAILED( CreateResource() ))
	{
		return false;
	}	

	SAFE_NEW( m_pQuad, GPlaneShape );
	m_pQuad->SetScreenVertex(15, 15, 300, 300, 
		D3DXVECTOR2( m_iWindowWidth, m_iWindowHeight ) );
	if( FAILED( m_pQuad->Create(GetDevice(),L"data_test/shader/plane.hlsl", L"data_test/castle.jpg") ) )
	{
		MessageBox( 0, _T("m_pLIne 실패"), _T("Fatal error"), MB_OK );
		return false;
	}
	
	D3DXMatrixIdentity(&m_matWorld[0]);
	D3DXMatrixIdentity(&m_matWorld[1]);
	//--------------------------------------------------------------------------------------
	// 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	SAFE_NEW( m_pBoxShape, GBoxShape );
	if( FAILED( m_pBoxShape->Create(GetDevice(), L"data_test/shader_shadow/ProjShadow.hlsl", L"data_test/castle.jpg")) )
	{
		MessageBox( 0, _T("m_pBoxShape 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(),	L"data_test/shader_shadow/ProjShadow.hlsl", "PS_Color"));

	// Create Source and Dest textures
	m_RT[0].Create( GetDevice(), 1024, 1024 );
		// Create Source and Dest textures
	m_RT[1].Create( GetDevice(), 1024, 1024 );

	m_matTexture = D3DXMATRIX(	  0.5f, 0.0f, 0.0f, 0.0f
								, 0.0f,-0.5f, 0.0f, 0.0f
								, 0.0f, 0.0f, 1.0f, 0.0f
								, 0.5f, 0.5f, 0.0f, 1.0f);

	m_pConstantBuffer.Attach(DX::CreateConstantBuffer(m_pd3dDevice, &m_cbShadow, 1, sizeof(SHADOW_CONSTANT_BUFFER)));

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
	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	GetContext()->PSSetShaderResources(0, 16, pSRVs);

	D3DXMATRIX mV[2],mP;
	D3DXVECTOR4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if( m_RT[0].Begin(m_pImmediateContext,vClearColor) )
	{
		/////////////////////////////////////////
		// Plane Shadow Rendering( Point Light )
		/////////////////////////////////////////
		D3DXVECTOR3 vLight = D3DXVECTOR3( 5, 10, 5 );
		D3DXVECTOR4 pLight = D3DXVECTOR4( vLight.x, vLight.y, vLight.z, 1.0f );
		D3DXPLANE pPlane = D3DXPLANE(0, 1, 0, -0.01f );

		D3DXMATRIX mat;
		D3DXVECTOR4 p(pPlane.a, pPlane.b, pPlane.c, pPlane.d );
		m_matShadow[0] = (D3DXMATRIX)TMatrixShadow( (Vector4*)&p, (Vector4*)&pLight );
		//-----------------------------------------------------
		// 1패스:그림자맵 생성
		//-----------------------------------------------------		
		D3DXVECTOR3 vEye    = vLight;
		//D3DXVECTOR3 vLookat = D3DXVECTOR3( m_matWorld[0]._41, m_matWorld[0]._42, m_matWorld[0]._43 );
		D3DXVECTOR3 vLookat = D3DXVECTOR3( 0, 0, 0);
		D3DXVECTOR3 vUp     = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		D3DXMatrixLookAtLH( &mV[0], &vEye, &vLookat, &vUp );
		D3DXMatrixPerspectiveFovLH( &mP, D3DX_PI/2, 1, 0.1f, 1000.0f );
		//D3DXMatrixOrthoLH( &mP, 1024/2, 1024/2, 0.0f, 100.0f );
		//D3DXMatrixOrthoOffCenterLH( &mP,	-1024/2, 1024/2, -1024/2, 1024/2, 0.0f, 100.0f );
		RenderShadow( &m_matWorld[0], &m_matShadow[0], &mV[0], &mP );
		RenderShadow( &m_matWorld[1], &m_matShadow[0], &mV[0], &mP );	
		m_RT[0].End(m_pImmediateContext);
	}
	if( m_RT[1].Begin(m_pImmediateContext,vClearColor) )
	{
		/////////////////////////////////////////
		// Plane Shadow Rendering( Direction Light )
		/////////////////////////////////////////
		D3DXVECTOR3 vLight = D3DXVECTOR3( -5, 10, 5 );
		D3DXVec3Normalize(&vLight, &vLight );
		D3DXVECTOR4 pLight = D3DXVECTOR4( vLight.x, vLight.y, vLight.z, 0.0f );
		D3DXPLANE pPlane = D3DXPLANE(0, 1, 0, -0.01f );
		D3DXMATRIX mat;
		D3DXVECTOR4 p(pPlane.a, pPlane.b, pPlane.c, pPlane.d );
		m_matShadow[1] = (D3DXMATRIX)TMatrixShadow( (Vector4*)&p, (Vector4*)&pLight );
		//-----------------------------------------------------
		// 1패스:그림자맵 생성
		//-----------------------------------------------------		
		D3DXVECTOR3 vEye    = vLight;
		//D3DXVECTOR3 vLookat = D3DXVECTOR3( m_matWorld[0]._41, m_matWorld[0]._42, m_matWorld[0]._43 );
		D3DXVECTOR3 vLookat = D3DXVECTOR3( 0, 0, 0);
		D3DXVECTOR3 vUp     = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );		
		D3DXMatrixLookAtLH( &mV[1], &D3DXVECTOR3( -5, 10, 5 ), &D3DXVECTOR3( 0, 0, 0), &vUp );	
		RenderShadow( &m_matWorld[0], &m_matShadow[1], &mV[1], &mP );
		RenderShadow( &m_matWorld[1], &m_matShadow[1], &mV[1], &mP );		
		m_RT[1].End(m_pImmediateContext);
	}

	// Box 1
	RenderObject( &m_matWorld[0], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	RenderObject( &m_matWorld[1], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	/*D3DXMATRIX matWorldShadow = m_matWorld[0] * m_matShadow[1];		
	RenderObject( &matWorldShadow, &mV[1], &mP);	
	matWorldShadow = m_matWorld[1] * m_matShadow[1];
	RenderObject( &matWorldShadow, &mV[1], &mP);*/
	//-----------------------------------------------------
	// 1패스: 지형 + 쉐도우 랜더링
	//-----------------------------------------------------		
	m_CustomMap.SetMatrix( NULL,m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	//m_CustomMap.SetMatrix( NULL,&mV[1], &mP);
	// 각 오브젝트이 월드 행렬은 전달할 필요가 없다.
	m_cbShadow.g_matShadow[0] = mV[0] * mP * m_matTexture;
	m_cbShadow.g_matShadow[1] = mV[1] * mP * m_matTexture;
	D3DXMatrixTranspose(&m_cbShadow.g_matShadow[0], &m_cbShadow.g_matShadow[0]);
	D3DXMatrixTranspose(&m_cbShadow.g_matShadow[1], &m_cbShadow.g_matShadow[1]);
	GetContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
	GetContext()->VSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());

	ApplySS(GetContext(), GDxState::g_pSSClampLinear, 1);
	m_CustomMap.PreRender(GetContext());
	{
		ID3D11ShaderResourceView* pSRV[] = {
		m_RT[0].m_pSRV.Get(),
		m_RT[1].m_pSRV.Get()	};
		GetContext()->PSSetShaderResources(1, 2, pSRV);
	}
	m_CustomMap.PostRender(GetContext());
	/////////////////////////////////////////
	// 디버깅
	/////////////////////////////////////////
	m_pQuad->SetMatrix(NULL, NULL, NULL);
	m_pQuad->PreRender(GetContext());
	{
		GetContext()->PSSetShaderResources(0, 1, m_RT[0].m_pSRV.GetAddressOf());		
	}
	m_pQuad->PostRender(GetContext());
	return true;
}
void GProjMain::RenderObject( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	m_pBoxShape->SetMatrix( matWorld, matView, matProj );
	m_pBoxShape->Render(GetContext());
}
void GProjMain::RenderShadow( D3DXMATRIX* matWorld, D3DXMATRIX* matShadow, 
						   D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	ApplyDSS(GetContext(), GDxState::g_pDSSDepthEnable);
	ApplyRS(GetContext(), GDxState::g_pRSBackCullSolid);
	ApplyBS(GetContext(), GDxState::g_pAlphaBlend);

	//matShadow 행렬을 빼면 모두 포인트 라이트 쉐도우가 된다.
	D3DXMATRIX matWorldShadow = (*matWorld) * (*matShadow);		
	m_pBoxShape->SetMatrix( &matWorldShadow, matView, matProj );
	m_pBoxShape->PreRender(GetContext());
		GetContext()->PSSetShader(m_pPixelShader.Get(), NULL, 0);
	m_pBoxShape->PostRender(GetContext());
}
bool GProjMain::Release()
{	
	SAFE_DEL(m_pQuad);
	SAFE_DEL(m_pLine);
	SAFE_DEL(m_pBoxShape);
	return m_CustomMap.Release();
}
bool GProjMain::Frame()
{
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;	
	m_pMainCamera->Frame();
	D3DXMatrixTranslation( &m_matWorld[0], 0+cosf(t), 5, 0 );
	D3DXMatrixTranslation( &m_matWorld[1], 3+cosf(t), 5, 0 );

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
	SAFE_ZERO(m_pBoxShape);
	SAFE_ZERO(m_pQuad);
}

GProjMain::~GProjMain(void)
{
}
GCORE_RUN(GBasisSample ProjectionShadow)