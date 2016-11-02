#include "GProjMain.h"

bool GProjMain::Init()
{
	if (FAILED(m_LineDraw.Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	} //공통

	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext); // 추가

	if (FAILED(m_HeightMap.CreateHeightMap(L"data/heightMap513.bmp")))
	{
		return false;
	}// 추가
	m_HeightMap.m_bStaticLight = true; //추가

	GMapDesc MapDesc = { m_HeightMap.m_iNumRows,
		m_HeightMap.m_iNumCols,
		1.0f, 1.0f,
		L"data/baseColor.jpg",
		L"data/shader/HeightMap.hlsl"}; // 변경

	//m_CustomMap.Init(GetDevice(), m_pImmediateContext); // 기존
	//
	//if (FAILED(m_CustomMap.Load(MapDesc)))
	//{
	//	return false;
	//}//기존

	if (FAILED(!m_HeightMap.Load(MapDesc)))
	{
		return false;
	}	

	//if (FAILED(CreateResource()))	{		return false;	} // 없어짐


	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pMainCamera, GCamera);
	m_pMainCamera->SetViewMatrix(
		D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(
		D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height), 1.0f, 1000.0f);
	return true;
}
bool GProjMain::Render()
{
	DX::ApplyDSS(m_pImmediateContext, DX::GDxState::g_pDSSDepthEnable);
	DX::ApplyBS(m_pImmediateContext, DX::GDxState::g_pAlphaBlend);
	//m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
	//	m_pMainCamera->GetProjMatrix());
	//return m_CustomMap.Render(m_pImmediateContext);
	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	return m_HeightMap.Render(m_pImmediateContext);
}
}
bool GProjMain::DrawDebug()
{
	//DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthDisable);
	if (I_Input.KeyCheck(DIK_P))
	{
		m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		D3DXMATRIX invWorld;
		D3DXMatrixIdentity(&invWorld);
		D3DXMatrixInverse(&invWorld, 0, m_pMainCamera->GetWorldMatrix());
		D3DXMatrixTranspose(&invWorld, &invWorld);
		D3DXVECTOR3 vStart, vEnd, vDir, vEye;
		vEye = *m_pMainCamera->GetLookVector();
		for (UINT row = 0; row < m_HeightMap.m_iNumRows; row++)
		{
			for (UINT col = 0; col < m_HeightMap.m_iNumCols; col++)
			{
				D3DXVec3TransformCoord(&vStart, &m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].p, m_pMainCamera->GetWorldMatrix());
				D3DXVec3TransformNormal(&vDir, &m_HeightMap.m_VertexList[row* m_HeightMap.m_iNumCols + col].n, &invWorld);
				D3DXVec3Normalize(&vDir, &vDir);
				vEnd = vStart + vDir * 2.0f;
				float fDot = D3DXVec3Dot(&vEye, &vDir);
				if (fDot<0)
				{
					vDir.x = vDir.x*0.5f + 0.5f;
					vDir.y = vDir.y*0.5f + 0.5f;
					vDir.z = vDir.z*0.5f + 0.5f;
					m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(vDir.x, vDir.y, vDir.z, 1.0f));
				}
			}
		}
	}
	

	//D3DXVECTOR3 vStart(0, 0, 0);
	//D3DXVECTOR3 vEnd(1000, 0, 0);

	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(1, 0, 0, 1.0f));
	//vEnd = D3DXVECTOR3(0, 1000, 0);

	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 1, 0, 1.0f));
	//vEnd = D3DXVECTOR3(0, 0, 1000);

	//m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, D3DXVECTOR4(0, 0, 1, 1.0f));
	if (!GCoreLibV2::DrawDebug()) return false;
	return true;
}

bool GProjMain::Release()
{
	return m_CustomMap.Release();
}
bool GProjMain::Frame()
{
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	if (I_Input.KeyCheck(DIK_F6)==KEY_UP)
	{
		for (UINT row = 0; row < m_HeightMap.m_iNumRows; row++)
		{
			for (UINT col = 0; col < m_HeightMap.m_iNumCols; col++)
			{
				m_HeightMap.m_VertexList[row* m_HeightMap.m_iNumCols + col].p.y *= -1.0f;
				m_HeightMap.m_VertexList[row*m_HeightMap.m_iNumCols + col].c = D3DXVECTOR4(1, 1, 1, 1);
			}
		}
		m_HeightMap.ReLoadIBuffer();
	}
	return m_HeightMap.Frame(); //return true;
	
	//g_pImmediateContext->UpdateSubresource(
	//	m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

	//m_pMainCamera->Frame();
	//return m_CustomMap.Frame();
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
}

GProjMain::~GProjMain(void)
{
}
GCORE_RUN(L"TBasisSample CustomizeMap");

