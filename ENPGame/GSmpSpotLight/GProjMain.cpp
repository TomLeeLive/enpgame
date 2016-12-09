#include "GProjMain.h"

GProjMain* g_pMain;

bool GProjMain::Init()
{
	m_pConstantBufferLight[0].Attach(DX::CreateConstantBuffer(
		m_pd3dDevice, &m_cbLight1, 1, sizeof(LIGHT_CONSTANT_BUFFER1)));
	m_pConstantBufferLight[1].Attach(DX::CreateConstantBuffer(
		m_pd3dDevice, &m_cbLight2, 1, sizeof(LIGHT_CONSTANT_BUFFER2)));
	m_pConstantBufferLight[2].Attach(DX::CreateConstantBuffer(
		m_pd3dDevice, &m_cbLight3, 1, sizeof(LIGHT_CONSTANT_BUFFER3)));

	if (FAILED(m_LineDraw.Create(GetDevice(), L"data_test/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 박스 오브젝트를 구 오브젝트로 변환(기하 쉐이더 및 스트림 아웃 처리)
	//--------------------------------------------------------------------------------------
	if (FAILED(m_SphereObj.Create(GetDevice(), L"data_test/shader/BoxSO_4.hlsl", L"data_test/tilea.jpg")))
	{
		MessageBox(0, _T("m_SphereObj 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	m_SphereObj.SetSO(GetDevice(), GetContext());
	//--------------------------------------------------------------------------------------
	// 높이맵 생성
	//--------------------------------------------------------------------------------------
	m_HeightMap.Init(m_pd3dDevice, m_pImmediateContext);
	if (FAILED(m_HeightMap.CreateHeightMap(L"data_test/HEIGHT_CASTLE.bmp")))
	{
		return false;
	}
	TMapDesc MapDesc = { m_HeightMap.m_iNumRows,m_HeightMap.m_iNumCols,	1.0f,0.1f,L"data_test/castle.jpg",	L"data_test/shader/Lighting.hlsl" };
	if (!m_HeightMap.Load(MapDesc))
	{
		return false;
	}

	float fLightRange = 200.0f;
	D3DXVECTOR3 vRotation = D3DXVECTOR3(-(D3DX_PI*0.2f), 0.0f, 0.0f);
	D3DXVECTOR3 vDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_PointLight[0].SetValue(&D3DXVECTOR3(0.0f, 10.0f, 0.0f),
		&vDir,
		&fLightRange,
		&D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		&D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		&vRotation,
		90.0f, // 내부
		120.0f);//외부
	fLightRange = 50.0f;
	vRotation = D3DXVECTOR3(0.0f, (D3DX_PI), 0.0f);
	vDir = D3DXVECTOR3(0.0f, 00.0f, 1.0f);
	m_PointLight[1].SetValue(&D3DXVECTOR3(-25.0f, 15.0f, -10.0f), &vDir, &fLightRange,
		&D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &vRotation,
		90.0f,
		120.0f);

	fLightRange = 30.0f;
	vRotation = D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI*0.5f));
	vDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_PointLight[2].SetValue(&D3DXVECTOR3(25.0f, 15.0f, -20.0f), &vDir, &fLightRange,
		&D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &vRotation,
		90.0f,
		120.0f);


	//--------------------------------------------------------------------------------------
	// 메인 카메라 
	//--------------------------------------------------------------------------------------
	m_pMainCamera = make_shared<GCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f, m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 10000.0f);
	return true;
}
bool GProjMain::Render()
{
	DX::ApplyDSS(m_pImmediateContext, DX::GDxState::g_pDSSDepthEnable);
	DX::ApplyBS(m_pImmediateContext, DX::GDxState::g_pAlphaBlend);

	for (int iLight = 0; iLight < g_iMaxLight; iLight++)
	{
		m_cbLight1.g_cAmbientMaterial[iLight] = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1);
		m_cbLight1.g_cDiffuseMaterial[iLight] = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight1.g_cSpecularMaterial[iLight] = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight1.g_cEmissionMaterial[iLight] = D3DXVECTOR4(0, 0, 0, 1);

		m_cbLight1.g_cAmbientLightColor[iLight] = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight1.g_cSpecularLightColor[iLight] = D3DXVECTOR4(1, 1, 1, 1);
		m_cbLight1.g_cDiffuseLightColor[iLight] = D3DXVECTOR4(m_PointLight[iLight].m_DiffuseColor.x,
			m_PointLight[iLight].m_DiffuseColor.y,
			m_PointLight[iLight].m_DiffuseColor.z, 1.0f);
	}
	for (int iLight = 0; iLight < g_iMaxLight; iLight++)
	{
		D3DXMATRIX matInvWorld;
		D3DXMatrixInverse(&matInvWorld, NULL, &m_PointLight[iLight].m_matWorld);
		D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
		D3DXMatrixTranspose(&m_cbLight2.g_matInvWorld[iLight], &matInvWorld);

		m_cbLight2.g_vEyeDir[iLight].x = m_pMainCamera->m_vLookVector.x;
		m_cbLight2.g_vEyeDir[iLight].y = m_pMainCamera->m_vLookVector.y;
		m_cbLight2.g_vEyeDir[iLight].z = m_pMainCamera->m_vLookVector.z;
		m_cbLight2.g_vEyeDir[iLight].w = 10.0f; // 강도

		m_cbLight2.g_vLightPos[iLight] = D3DXVECTOR4(m_PointLight[iLight].m_vPosition.x,
			m_PointLight[iLight].m_vPosition.y,
			m_PointLight[iLight].m_vPosition.z, m_PointLight[iLight].m_fRange);

		m_cbLight2.g_vLightDir[iLight] = D3DXVECTOR4(m_PointLight[iLight].m_vDirection.x,
			m_PointLight[iLight].m_vDirection.y,
			m_PointLight[iLight].m_vDirection.z, 1.0f);


	}
	for (int iLight = 0; iLight < g_iMaxLight; iLight++)
	{
		m_cbLight3.g_vSpotInfo[iLight].x = (m_PointLight[iLight].m_fTheta);// 내부 콘의 각도 범위	
		m_cbLight3.g_vSpotInfo[iLight].y = (m_PointLight[iLight].m_fPhi);// 외부 콘의 각도 범위	
		m_cbLight3.g_vSpotInfo[iLight].z = m_PointLight[iLight].m_fFalloff;	// 내부 콘과 외부 콘의 휘도( Luminance )	
		m_cbLight3.g_vSpotInfo[iLight].w = m_PointLight[iLight].m_fRange;// 범위	
	}
	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight[0].Get(), 0, NULL, &m_cbLight1, 0, 0);
	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight[1].Get(), 0, NULL, &m_cbLight2, 0, 0);
	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight[2].Get(), 0, NULL, &m_cbLight3, 0, 0);

	ID3D11Buffer*               pBuffers[3];
	pBuffers[0] = m_pConstantBufferLight[0].Get();
	pBuffers[1] = m_pConstantBufferLight[1].Get();
	pBuffers[2] = m_pConstantBufferLight[2].Get();

	m_pImmediateContext->PSSetConstantBuffers(1, 3, pBuffers);

	m_HeightMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_HeightMap.Render(m_pImmediateContext);

	//m_SphereObj.SetMatrix(&matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	//m_SphereObj.Render(m_pImmediateContext);	

	for (int iLight = 0; iLight < 3; iLight++)
	{
		m_SphereObj.m_cbData.Color = m_PointLight[iLight].m_DiffuseColor;
		m_SphereObj.SetMatrix(&m_PointLight[iLight].m_matWorld, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
		m_SphereObj.Render(m_pImmediateContext);
	}
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
	D3DXMatrixRotationY(&mRotation, t * 0);
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
	m_HeightMap.Frame();

	for (int iLight = 0; iLight < g_iMaxLight; iLight++)
	{
		m_PointLight[iLight].Frame(g_fDurationTime, g_fSecPerFrame);

		// 지형의 높이값을 얻는다.
		m_PointLight[iLight].m_matWorld._42 = m_HeightMap.GetHeight(m_PointLight[iLight].m_vPosition.x,
			m_PointLight[iLight].m_vPosition.z) + 3.0f;

		// 맵 오브젝트의 월드행렬의 변환을 적용한다.
		//m_PointLight[iLight].m_matWorld = m_PointLight[iLight].m_matWorld*(*m_pMainCamera->GetWorldMatrix());

		// 변환된 최종 라이트 위치값
		m_PointLight[iLight].m_vPosition.x = m_PointLight[iLight].m_matWorld._41;
		m_PointLight[iLight].m_vPosition.y = m_PointLight[iLight].m_matWorld._42;
		m_PointLight[iLight].m_vPosition.z = m_PointLight[iLight].m_matWorld._43;
	}
	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
			m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
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
GCORE_RUN(L"GBasisSample SpotLight");

