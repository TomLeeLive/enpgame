#include "GProjMain.h"

bool GProjMain::Init()
{
	if (FAILED(m_LineDraw.Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	//GMapDesc MapDesc = { 50, 50, 1.0f, 0.1f,L"data/castle.jpg", L"CustomizeMap.hlsl" };
	//m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	//if (FAILED(m_CustomMap.Load(MapDesc)))
	//{
	//	return false;
	//}
	//if (FAILED(CreateResource()))
	//{
	//	return false;
	//}
	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	// 높이맵의 정점 y 값을 텍스쳐로부터 얻는다.
	if (FAILED(m_HeightMap.CreateHeightMap(L"data/heightMap513.bmp")))
	{
		return false;
	}
	m_HeightMap.m_bStaticLight = true;

	GMapDesc MapDesc = { m_HeightMap.m_iNumRows,
		m_HeightMap.m_iNumCols,
		1.0f,1.0f,
		L"data/baseColor.jpg",
		L"data/shader/HeightMap.hlsl" };
	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pMainCamera, GCamera);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 300.0f, -300.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 3000.0f);
	return true;
}
bool GProjMain::Render()
{
	//DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthEnable);
	//DX::ApplyBS(m_pImmediateContext, DX::TDxState::g_pAlphaBlend);
	//m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
	//	m_pMainCamera->GetProjMatrix());
	//return m_CustomMap.Render(m_pImmediateContext);
	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	return  m_HeightMap.Render(m_pImmediateContext);
}
bool GProjMain::Release()
{
	return m_HeightMap.Release();
}
bool GProjMain::Frame()
{
	 //2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;
	 m_pMainCamera->Frame();
	//for (int z = 0; z < m_CustomMap.m_iNumRows; z++)
	//{
	//	for (int x = 0; x < m_CustomMap.m_iNumCols; x++)
	//	{
	//		int iIndex = z*m_CustomMap.m_iNumCols + x;
	//		float fCos = cosf(t*x);
	//		float fSin = sinf(t*z);
	//		m_CustomMap.m_VertexList[iIndex].p.y =	fCos + fSin;
	//	}
	//}
	//g_pImmediateContext->UpdateSubresource(		m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);	
	//return m_CustomMap.Frame();
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
		 m_HeightMap.ReLoadVBuffer();
		 //m_HeightMap.UpdateBuffer();
	 }
	 return m_HeightMap.Frame();
}
bool GProjMain::DrawDebug()
{
	//DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthDisable);
	//m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	//D3DXVECTOR3 vStart(0, 0, 0);
	//D3DXVECTOR3 vEnd(1000, 0, 0);
	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(1, 0, 0, 1.0f));
	//vEnd = D3DXVECTOR3(0, 1000, 0);
	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 1, 0, 1.0f));
	//vEnd = D3DXVECTOR3(0, 0, 1000);
	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 0, 1, 1.0f));
	if (I_Input.KeyCheck(DIK_P))
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
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
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
	GCoreLibV2::m_bDebugInfoPrint = false;
	//GCoreLibV2::m_bDebugFpsPrint = false;
}

GProjMain::~GProjMain(void)
{
}
GCORE_RUN(L"TBasisSample CustomizeMap");

