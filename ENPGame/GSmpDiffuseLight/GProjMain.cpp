#include "GProjMain.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
	m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
	m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
	m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);

	m_pConstantBufferLight.Attach(DX::CreateConstantBuffer(
		m_pd3dDevice, &m_cbLight, 1, sizeof(LIGHT_CONSTANT_BUFFER)));

	if (FAILED(m_LineDraw.Create(GetDevice(), L"data_test/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 박스 오브젝트를 구 오브젝트로 변환(기하 쉐이더 및 스트림 아웃 처리)
	//--------------------------------------------------------------------------------------
	if (FAILED(m_SphereObj.Create(GetDevice(), L"data_test/shader_shadow/BoxSO.hlsl", L"data_test/tilea.jpg")))
	{
		MessageBox(0, _T("m_SphereObj 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	m_SphereObj.SetSO(GetDevice(),GetContext());
	//--------------------------------------------------------------------------------------
	// 높이맵 생성
	//--------------------------------------------------------------------------------------
	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	if (FAILED(m_HeightMap.CreateHeightMap(L"data_test/heightMap513.bmp")))
	{
		return false;
	}
	TMapDesc MapDesc = { m_HeightMap.m_iNumRows,m_HeightMap.m_iNumCols,	2.0f,0.5f,L"data_test/baseColor.jpg",	L"data_test/shader_shadow/DiffuseLight.hlsl" };
	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}
	//--------------------------------------------------------------------------------------
	// 메인 카메라 
	//--------------------------------------------------------------------------------------
	m_pMainCamera= make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 300.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, 
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 3000.0f);
	return true;
}
bool GProjMain::Render()
{
	DX::ApplyDSS(m_pImmediateContext, DX::GDxState::g_pDSSDepthEnable);
	DX::ApplyBS(m_pImmediateContext, DX::GDxState::g_pAlphaBlend);

	D3DXMATRIX matWorld, matScale;
	D3DXMatrixScaling(&matScale, 100, 100, 100);
	D3DXMatrixRotationY(&matWorld, m_Timer.GetElapsedTime());
	D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);
	matWorld._42 = 200.0f;

	m_cbLight.g_vLightDir.x = m_vLightVector.x;
	m_cbLight.g_vLightDir.y = m_vLightVector.y;
	m_cbLight.g_vLightDir.z = m_vLightVector.z;
	m_cbLight.g_vLightDir.w = 1;
	D3DXMATRIX matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
	D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
	D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
	m_pImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
	m_pImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
	m_SphereObj.SetMatrix(&matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_SphereObj.Render(m_pImmediateContext);

	D3DXMatrixIdentity(&m_cbLight.g_matInvWorld);
	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_HeightMap.Render(m_pImmediateContext);
	return true;
}
bool GProjMain::DrawDebug()
{
	if( I_Input.KeyCheck( DIK_P ) )
	{
		// 정점노말 표시
		m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		D3DXMATRIX invWorld;
		D3DXMatrixIdentity(&invWorld);
		D3DXMatrixInverse(&invWorld, 0, m_pMainCamera->GetWorldMatrix());
		D3DXMatrixTranspose(&invWorld, &invWorld);
		D3DXVECTOR3 vStart, vEnd, vDir, vEye;
		vEye = *m_pMainCamera->GetLookVector();
		for (UINT row = 0; row < m_HeightMap.m_iNumRows; row += 5)
		{
			for (UINT col = 0; col < m_HeightMap.m_iNumCols; col += 5)
			{
				D3DXVec3TransformCoord(&vStart, &m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].p, m_pMainCamera->GetWorldMatrix());
				D3DXVec3TransformNormal(&vDir, &m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].n, &invWorld);
				D3DXVec3Normalize(&vDir, &vDir);
				vEnd = vStart + vDir * 2.0f;
				float fDot = D3DXVec3Dot(&vEye, &vDir);
				if (fDot < 0)
				{
					vDir.x = vDir.x * 0.5f + 0.5f;
					vDir.y = vDir.y * 0.5f + 0.5f;
					vDir.z = vDir.z * 0.5f + 0.5f;
					m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(vDir.x, vDir.y, vDir.z, 1.0f));
				}
			}
		}
	}
	if (!GCoreLibV2::DrawDebug()) return false;
	return true;
}
bool GProjMain::Release()
{
	m_SphereObj.Release();
	return m_HeightMap.Release();
}

bool GProjMain::Frame()
{
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	m_pMainCamera->Frame();

	D3DXMATRIX mLightWorld, mTranslate, mRotation;
	D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
	D3DXMatrixRotationY(&mRotation, t*0.1f);
	D3DXMatrixMultiply(&mLightWorld, &mTranslate, &mRotation);

	m_vLightVector.x = mLightWorld._41;
	m_vLightVector.y = mLightWorld._42;
	m_vLightVector.z = mLightWorld._43;

	D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
	m_vLightVector *= -1.0f;

	if (I_Input.KeyCheck(DIK_F6) == KEY_UP)
	{
		for (UINT row = 0; row < m_HeightMap.m_iNumRows; row += 1)
		{
			for (UINT col = 0; col < m_HeightMap.m_iNumCols; col += 1)
			{
				m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].p.y *= -1.0f;
				m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].c = D3DXVECTOR4(1, 1, 1, 1);
			}
		}
		m_HeightMap.CalcVertexColor(m_HeightMap.m_vLightDir);
		m_HeightMap.ReLoadVBuffer();
	}

	m_SphereObj.Frame();
	return m_HeightMap.Frame();
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if(m_pMainCamera!=nullptr)
	m_pMainCamera->SetProjMatrix( (float)D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 1000.0f);
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
	m_pMainCamera = nullptr;
}

GProjMain::~GProjMain(void)
{
}

GCORE_RUN(L"GBasisSample DiffuseLight");

