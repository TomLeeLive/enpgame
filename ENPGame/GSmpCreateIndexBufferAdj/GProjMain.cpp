#include "GProjMain.h"

GProjMain* g_pMain;

HRESULT GProjMain::CreateStateAndBuffer(ID3D11Device* pDevice)
{
	HRESULT hr=S_OK;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0;
	hr=pDevice->CreateBlendState(&blendDesc, m_pVolumeShadowBS.GetAddressOf());
	if (FAILED(hr)) 	return hr;

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr=pDevice->CreateBlendState(&blendDesc, m_pQuadBS.GetAddressOf());
	if (FAILED(hr)) 	return hr;


	// 깊이버퍼 상태값 세팅
	D3D11_DEPTH_STENCIL_DESC dsDescDepth;
	ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS;
	dsDescDepth.StencilEnable = TRUE;
	dsDescDepth.StencilReadMask = 0xff;
	dsDescDepth.StencilWriteMask = 0xff;
	dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;

	// 디폴트 값
	dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;

	if (FAILED(hr = pDevice->CreateDepthStencilState(&dsDescDepth, &m_pVolumeShadowDSS)))
	{
		return hr;
	}
	dsDescDepth.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_LESS;
	dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	if (FAILED(hr = pDevice->CreateDepthStencilState(&dsDescDepth, &m_pQuadDSS)))
	{
		return hr;
	}
	return hr;
}

bool GProjMain::Init()
{	
	HRESULT hr;
	m_SampleObj.Init();
	//if (!m_SampleObj.Load(GetDevice(), _T("../../data/Obj/Turret_Deploy.tbs"), L"ObjectAdj.hlsl"))
	if (!m_SampleObj.Load(GetDevice(), _T("data_test/Obj/mob2.tbs"), L"data_test/shader_shadow/ObjectAdj.hlsl"))
	{
		return false;
	}
	ComPtr<ID3DBlob> vsBlob, gsBlob;
	m_pShadowVolumeVS.Attach(DX::LoadVertexShaderFile(GetDevice(), L"data_test/shader_shadow/ObjectAdj.hlsl", vsBlob.GetAddressOf(), "VS_VolumeShadow"));
	m_pShadowVolumeGS.Attach(DX::LoadGeometryShaderFile(GetDevice(), L"data_test/shader_shadow/ObjectAdj.hlsl", gsBlob.GetAddressOf(), "GS_VolumeShadow"));
	m_pShadowVolumePS.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data_test/shader_shadow/ObjectAdj.hlsl", "PS_VolumeShadow"));
	//--------------------------------------------------------------------------------------
	// 초기 라이트 위치 
	//--------------------------------------------------------------------------------------	
	m_vInitLightPos = D3DXVECTOR3(-100.0f, 200.0f, 0.0f);

	m_pSunLight = I_Light.GetPtr(I_Light.Add(m_vInitLightPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), L"TBasisSunLight"));
	if (!m_pSunLight->Init()) return false;

	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	// 높이맵의 정점 y 값을 텍스쳐로부터 얻는다.
	if (FAILED(m_HeightMap.CreateHeightMap(L"data_test/clods256.png")))
	{
		return false;
	}

	m_HeightMap.m_bStaticLight = true;
	TMapDesc MapDesc = { m_HeightMap.m_iNumRows,m_HeightMap.m_iNumCols,	1.0f, 0.2f,	L"data_test/baseColor.jpg",	L"data_test/shader_shadow/ObjectAdj.hlsl" };
	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}

	//--------------------------------------------------------------------------------------
	// 평면 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_pQuadObj = make_shared<GPlaneShape>();
	if (m_pQuadObj->Create(GetDevice(), L"data_test/shader_shadow/Quad.hlsl") == false)
	{
		MessageBox(0, _T("m_pQuadObj->Create"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 500.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 10000.0f);

	if (FAILED(CreateStateAndBuffer(GetDevice())))
	{
		return false;
	}
	GetWindowRect(m_hWnd, &m_rcWindowBounds);
	GetClientRect(m_hWnd, &m_rcWindowClient);
	//if (FAILED(ResizeDevice(width, height)))
	//{
	//}
	return true;
	
}
bool GProjMain::Render()
{	
	ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthEnable);
	ApplyBS(m_pImmediateContext, GDxState::g_pAlphaBlend);
	ApplyRS(m_pImmediateContext, GDxState::g_pRSNoneCullSolid);
	////--------------------------------------------------------------------------------------
	//// 지형 랜더링
	////--------------------------------------------------------------------------------------
	m_HeightMap.SetMatrix( m_pMainCamera->GetWorldMatrix(),m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());	
	m_HeightMap.Render(m_pImmediateContext);
	////--------------------------------------------------------------------------------------
	//// 오브젝트 랜더링
	////--------------------------------------------------------------------------------------
	m_SampleObj.m_cbData.Color.x = 1;
	m_SampleObj.m_cbData.Color.y = 1;
	m_SampleObj.m_cbData.Color.z = 1;

	D3DXMATRIX matWorld;
	//D3DXMatrixScaling(&matWorld, 1.0f, 1.0f, 1.0f);
	D3DXMatrixScaling(&matWorld, 10.0f, 10.0f, 10.0f);
	matWorld._42 = 10.0f;
	m_SampleObj.SetMatrix(&matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_SampleObj.Render(m_pImmediateContext);
	//--------------------------------------------------------------------------------------
	// 쉐도우 볼륨 랜더링
	//--------------------------------------------------------------------------------------
	ApplyDSS(m_pImmediateContext, m_pVolumeShadowDSS.Get());
	ApplyBS(m_pImmediateContext, m_pVolumeShadowBS.Get());
	ApplyRS(m_pImmediateContext, GDxState::g_pRSNoneCullSolid);

	m_HeightMap.PreRender(m_pImmediateContext);
	{
		m_HeightMap.m_cbData.Color.x = m_pSunLight->m_vPosition.x;
		m_HeightMap.m_cbData.Color.y = m_pSunLight->m_vPosition.y;
		m_HeightMap.m_cbData.Color.z = m_pSunLight->m_vPosition.z;
		m_pImmediateContext->VSSetConstantBuffers(0, 1, m_HeightMap.m_dxobj.g_pConstantBuffer.GetAddressOf());
		m_pImmediateContext->GSSetConstantBuffers(0, 1, m_HeightMap.m_dxobj.g_pConstantBuffer.GetAddressOf());
		m_pImmediateContext->VSSetShader(m_pShadowVolumeVS.Get(), NULL, 0);
		m_pImmediateContext->PSSetShader(m_pShadowVolumePS.Get(), NULL, 0);
		m_pImmediateContext->GSSetShader(m_pShadowVolumeGS.Get(), NULL, 0);
		if (m_HeightMap.m_bAdjacency)
		{
			m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
			m_pImmediateContext->IASetIndexBuffer(m_HeightMap.m_pIndexBufferAdj.Get(), DXGI_FORMAT_R32_UINT, 0);
			//m_pImmediateContext->GSSetConstantBuffers(0, 1, m_HeightMap.m_dxobj.g_pConstantBuffer.GetAddressOf());
		}
		else {
			m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_pImmediateContext->GSSetShader(NULL, NULL, 0);
		}

		if (m_HeightMap.m_bAdjacency)
			m_pImmediateContext->DrawIndexed(m_HeightMap.m_iNumFace * 3 * 2, 0, 0);
		else
			m_pImmediateContext->DrawIndexed(m_HeightMap.m_iNumFace * 3, 0, 0);
	}

	m_SampleObj.PreRender(m_pImmediateContext);
	{
		m_SampleObj.m_cbData.Color.x = m_pSunLight->m_vPosition.x;
		m_SampleObj.m_cbData.Color.y = m_pSunLight->m_vPosition.y;
		m_SampleObj.m_cbData.Color.z = m_pSunLight->m_vPosition.z;
		m_pImmediateContext->VSSetConstantBuffers(0, 1, m_SampleObj.m_dxobj.g_pConstantBuffer.GetAddressOf());
		m_pImmediateContext->GSSetConstantBuffers(0, 1, m_SampleObj.m_dxobj.g_pConstantBuffer.GetAddressOf());
		m_pImmediateContext->VSSetShader(m_pShadowVolumeVS.Get(), NULL, 0);
		m_pImmediateContext->PSSetShader(m_pShadowVolumePS.Get(), NULL, 0);
		m_pImmediateContext->GSSetShader(m_pShadowVolumeGS.Get(), NULL, 0);
		m_SampleObj.ShadowDraw(m_pImmediateContext, &m_SampleObj);
	}
	//--------------------------------------------------------------------------------------
	// 화면을 덮는 평면 쉐도우 랜더링( 스텐실 연산으로 그림자 판정 )
	//--------------------------------------------------------------------------------------
	ApplyDSS(m_pImmediateContext, m_pQuadDSS.Get(), 0);
	ApplyBS(m_pImmediateContext, m_pQuadBS.Get());
	ApplyRS(m_pImmediateContext, GDxState::g_pRSBackCullSolid);
	m_pQuadObj->SetMatrix(NULL, NULL, NULL);
	m_pQuadObj->Render(m_pImmediateContext);
	return true;
}


bool GProjMain::Frame()
{	
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	m_pMainCamera->Frame();

	D3DXMATRIX mTranslate, mRotation, mScale;
	//--------------------------------------------------------------------------------------
	// 라이트 벡터 계산
	//--------------------------------------------------------------------------------------	
	D3DXMatrixTranslation(&mTranslate, m_vInitLightPos.x, m_vInitLightPos.y, m_vInitLightPos.z);
	D3DXMatrixRotationY(&mRotation, t*0.1f);
	D3DXMatrixMultiply(&m_mLightWorld, &mTranslate, &mRotation);
	m_pSunLight->Update(&m_mLightWorld);

	m_SampleObj.Frame();
	return m_HeightMap.Frame();	
}

bool GProjMain::Release()
{	
	SAFE_RELEASE(m_pQuadObj);
	m_SampleObj.Release();
	return m_HeightMap.Release();
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr = S_OK;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	}
	return hr;
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
	m_pMainCamera = nullptr;
}

GProjMain::~GProjMain(void)
{
}
GCORE_RUN(L"GBasisSample HeightMapAdj");

