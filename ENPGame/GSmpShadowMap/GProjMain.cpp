#include "GProjMain.h"

GProjMain* g_pMain;

const float g_fMaxSize = 1024;
bool GProjMain::Init()
{
	TMapDesc MapDesc = { 33, 33, 1.0f,1.0f, L"../../data/write.png", L"CustomizeMap.hlsl" };
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
	if( FAILED( m_pQuad->Create(GetDevice(), L"../../data/shader/plane.hlsl", L"../../data/castle.jpg") ) )
	{
		MessageBox( 0, _T("m_pLIne ����"), _T("Fatal error"), MB_OK );
		return false;
	}
	
	for( int iObj=0; iObj < MAX_OBJECT_CNT; iObj++ )
	{
		D3DXMatrixIdentity(&m_matWorld[iObj]);
	}
	//--------------------------------------------------------------------------------------
	// �ڽ� ������Ʈ ����
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pBoxShape, GBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"DepthMapShadow.hlsl", L"../../data/castle.jpg")))
	{
		MessageBox(0, _T("m_pBoxShape ����"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ComPtr<ID3DBlob> pVSBlob;
	m_pShadowVS.Attach(DX::LoadVertexShaderFile(GetDevice(), L"CustomizeMap.hlsl", pVSBlob.GetAddressOf(), "SHADOW_VS"));
	m_pShadowPS.Attach(DX::LoadPixelShaderFile(GetDevice(), L"CustomizeMap.hlsl", "SHADOW_PS"));
	
	// Create Source and Dest textures
	m_RT.m_DSFormat = DXGI_FORMAT_R32_TYPELESS;
	m_RT.Create(GetDevice(), g_fMaxSize, g_fMaxSize);// m_bColorTexRender );	
	//--------------------------------------------------------------------------------------
	// ī�޶�  ��� 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -20.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 3000.0f);


	//m_ShaderEditer.Create( L"CustomizeMap.fx", m_hWnd );
	m_matTexture = D3DXMATRIX(	  0.5f, 0.0f, 0.0f, 0.0f
								, 0.0f,-0.5f, 0.0f, 0.0f
								, 0.0f, 0.0f, 1.0f, 0.0f
								, 0.5f, 0.5f, 0.0f, 1.0f);
	m_pConstantBuffer.Attach(DX::CreateConstantBuffer(m_pd3dDevice, &m_cbShadow, 1, sizeof(SHADOW_CONSTANT_BUFFER)));


	m_vLightPos = D3DXVECTOR3( 15, 40, -35 );

	float fWidthLength = m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumCols*
		m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumCols;
	float fHeightLength = m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumRows*
		m_CustomMap.m_fSellDistance*m_CustomMap.m_iNumRows;
	
	// ������ �밢���� ����, �ؽ�ó�� �����ϰ� ��ġ�Ϸ��� �۾��Ѵ�.
	float fMaxViewDistance = sqrt(fWidthLength + fHeightLength);
	//D3DXMatrixPerspectiveFovLH( &m_matShadowProj, D3DX_PI*0.25f, 1.0f, 20.0f, 200.0f );
	//D3DXMatrixOrthoLH( &m_matShadowProj, fMaxViewDistance, fMaxViewDistance, 0.0f, 100.0f );
	D3DXMatrixOrthoOffCenterLH( &m_matShadowProj,	
		-fMaxViewDistance/2, fMaxViewDistance/2, -fMaxViewDistance/2, fMaxViewDistance/2, 0.0f, 100.0f );

	D3DXMATRIX matScale, matRotation;
	for( int iObj=0; iObj < MAX_OBJECT_CNT; iObj++ )
	{
		D3DXMatrixTranslation( &m_matWorld[iObj],	randstep(-15.0f, 15.0f), 
													randstep(0, 20), 
													randstep(-15.0f, 15.0f) );
		D3DXMatrixScaling( &matScale,	randstep(1.0f, 5.0f), 
										randstep(1.0f, 5.0f), 
										randstep(1.0f, 5.0f) );
		m_matWorld[iObj]._11 = matScale._11;
		m_matWorld[iObj]._22 = matScale._22;
		m_matWorld[iObj]._33 = matScale._33;

		m_matWorld[iObj]._41 = 0.0f;
		m_matWorld[iObj]._42 = m_matWorld[iObj]._22*(iObj+1);
		m_matWorld[iObj]._43 = 0.0f;		
	}

	return true;
}
bool GProjMain::Render()
{	
	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	GetContext()->PSSetShaderResources(0, 16, pSRVs);

	D3DXVECTOR4 vClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vLookat = D3DXVECTOR3( 0, 0, 0);
	D3DXVECTOR3 vUp     = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	//-----------------------------------------------------
	// ���� �� ������Ʈ�� �׸��ڸ� ����
	//-----------------------------------------------------		
	if( m_RT.Begin(m_pImmediateContext,vClearColor) )
	{					
		D3DXMatrixLookAtLH( &m_matShadowView, &m_vLightPos, &vLookat, &vUp );		
		RenderShadow( NULL, &m_matShadowView, &m_matShadowProj );
		m_RT.End(m_pImmediateContext);
	}	
	////-----------------------------------------------------
	//// ������Ʈ + ������ ������
	////-----------------------------------------------------	
	RenderObject( m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	////-----------------------------------------------------
	//// 1�н�: ���� + ������ ������
	////-----------------------------------------------------		
	ApplySS(GetContext(), GDxState::g_pSSClampLinear, 1);
	ApplySS(GetContext(), GDxState::g_pSSShadowMap, 2);
	ApplyRS(GetContext(), GDxState::g_pRSBackCullSolid);

	m_CustomMap.SetMatrix( NULL,m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());	
	D3DXMATRIX matWVPT = m_matShadowView * m_matShadowProj * m_matTexture;
	D3DXMatrixTranspose(&m_cbShadow.g_matShadow, &matWVPT);
	m_cbShadow.g_ShadowID = 0;
	m_cbShadow.g_iNumKernel = 3;
	GetContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
	GetContext()->VSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());
	GetContext()->PSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());

	m_CustomMap.PreRender(GetContext());
		GetContext()->PSSetShaderResources(1, 1, m_RT.m_pDsvSRV.GetAddressOf());
	m_CustomMap.PostRender(GetContext());
	
	/////////////////////////////////////////
	// �����
	/////////////////////////////////////////
	if( m_bColorTexRender )
	{
		m_pQuad->SetMatrix(NULL, NULL, NULL );
		m_pQuad->PreRender(GetContext());
		//GetContext()->PSSetShaderResources(0, 1, m_RT.m_pSRV.GetAddressOf());
		GetContext()->PSSetShaderResources(0, 1, m_RT.m_pDsvSRV.GetAddressOf());
		m_pQuad->PostRender(GetContext());
	}
	return true;
}
void GProjMain::RenderObject( D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	D3DXMATRIX matInvView;
	ApplySS(GetContext(), GDxState::g_pSSClampLinear, 1);
	ApplySS(GetContext(), GDxState::g_pSSShadowMap, 2);
	ApplyRS(GetContext(), GDxState::g_pRSBackCullSolid);

	m_pBoxShape->PreRender(GetContext());
	for( int iObj=0; iObj < MAX_OBJECT_CNT; iObj++ )
	{
		D3DXMatrixInverse(&matInvView, 0, matView );
		D3DXMATRIX matWVPT1 = m_matWorld[iObj] * m_matShadowView * m_matShadowProj * m_matTexture;
		D3DXMatrixTranspose(&m_cbShadow.g_matShadow, &matWVPT1);
		m_cbShadow.g_ShadowID = m_fObjID[iObj];
		m_cbShadow.g_iNumKernel = 3;
		GetContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, NULL, &m_cbShadow, 0, 0);
		GetContext()->VSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());
		GetContext()->PSSetConstantBuffers(1, 1, m_pConstantBuffer.GetAddressOf());
		GetContext()->PSSetShaderResources(1, 1, m_RT.m_pDsvSRV.GetAddressOf() );

		m_pBoxShape->SetMatrix(&m_matWorld[iObj], matView, matProj);		
		m_pBoxShape->PostRender(GetContext());
	}
}
void GProjMain::RenderShadow( D3DXMATRIX* matShadow, 
						   D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	ApplyDSS(GetContext(), GDxState::g_pDSSDepthEnable);
	//ApplyRS(GetContext(), TDxState::g_pRSBackCullSolid);
	ApplyBS(GetContext(), GDxState::g_pAlphaBlend);
	ApplyRS(GetContext(), GDxState::g_pRSSlopeScaledDepthBias);

	m_CustomMap.SetMatrix( NULL,matView, matProj);
	m_CustomMap.PreRender(GetContext());
		GetContext()->VSSetShader(m_pShadowVS.Get(), NULL, 0);
		//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
		// ���̽��ٽ� ���۸� ���ҽ��� �����ϸ� �Ǳ� ������ �Ƚ����̴��� ������� �ʾƵ� �ȴ�.
		// ������, ȭ�鿡 ����� ���̸� ����� Ȯ���ϰ��� �� ���忡�� �Ƚ����̴��� Ȱ��ȭ �Ͽ���.
		GetContext()->PSSetShader( NULL, NULL, 0);
	m_CustomMap.PostRender(GetContext());

	for( int iObj=0; iObj < MAX_OBJECT_CNT; iObj++ )
	{
		m_pBoxShape->SetMatrix( &m_matWorld[iObj], matView, matProj );
		m_pBoxShape->PreRender(GetContext());
			GetContext()->VSSetShader(m_pShadowVS.Get(), NULL, 0);
			//GetContext()->PSSetShader(m_pShadowPS.Get(), NULL, 0);
			// ���̽��ٽ� ���۸� ���ҽ��� �����ϸ� �Ǳ� ������ �Ƚ����̴��� ������� �ʾƵ� �ȴ�.
			// ������, ȭ�鿡 ����� ���̸� ����� Ȯ���ϰ��� �� ���忡�� �Ƚ����̴��� Ȱ��ȭ �Ͽ���.
			GetContext()->PSSetShader( NULL, NULL, 0);
		m_pBoxShape->PostRender(GetContext());
	}
}
bool GProjMain::Release()
{	
	SAFE_DEL(m_pQuad);
	SAFE_DEL(m_pBoxShape);
	return m_CustomMap.Release();
}
bool GProjMain::Frame()
{
	// 2�ʴ� 1ȸ��( 1 �� * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;	
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
	SAFE_ZERO(m_pBoxShape);
	SAFE_ZERO(m_pQuad);
	m_bColorTexRender = true;
}

GProjMain::~GProjMain(void)
{
}

GCORE_RUN(GBasisSample ShadowMap)