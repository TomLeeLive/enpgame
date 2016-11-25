#include "_stdafx.h"

GProjMain* g_pMain;

#define NUM_OBJECTS 100


bool GProjMain::Init()
{
	HRESULT hr;

	//--------------------------------------------------------------------------------------
	// 박스 오브젝트 생성( 100개 박스가 공유해서 사용함)
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pBoxShape, GBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"data/shader/box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 카메라 프로스텀 랜더링용 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_MainCamera.CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/box.hlsl", "PS_Color"));
	//--------------------------------------------------------------------------------------
	// 100개 박스의 위치를 세팅함
	//--------------------------------------------------------------------------------------
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_vBoxPosition[iBox] = D3DXVECTOR3(25 - rand() %50, 0.0f, 25 - rand() % 50);

		//m_vBoxColor[iBox] = D3DXVECTOR4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f,1.0f);
		D3DXVECTOR4 VColor = D3DXVECTOR4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f);
		m_vBoxColor[iBox] = VColor;	
	//	//// OBB 기저 벡터 변환(회전 변환 이후 정규화)
	//	//D3DXVECTOR3 vMax, vMin, vHalf;
	//	//// 지정된 행렬에 의해 3D 벡터를 변환해 , 그 결과를 w =1 에 투영한다. (pOut, pV, pM)
	//	//D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[0], &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &matWorld);
	//	////3D벡터를 정규화한 벡터를 돌려준다. (pOut, pV)
	//	//D3DXVec3Normalize(&m_GBox[iBox].vAxis[0], &m_GBox[iBox].vAxis[0]);
	}

	//--------------------------------------------------------------------------------------
	// 메인 카메라의 뷰 및 투영 행렬 세팅
	//--------------------------------------------------------------------------------------
	D3DXMatrixIdentity(&m_matBoxWorld);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	//메인 카메라 뷰 행렬 세팅
	//vPos, vTarget, vUp
	m_MainCamera.SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), vUpVector);
	m_fRadius = D3DXVec3Length(&(m_MainCamera.m_vCameraPos - m_MainCamera.m_vTargetPos));
	m_fCameraYaw = m_MainCamera.m_fCameraYawAngle;
	m_fCameraPitch = m_MainCamera.m_fCameraPitchAngle;
	// 투영행렬 세팅
	DXGI_SWAP_CHAIN_DESC Desc;
	if (FAILED(GetSwapChain()->GetDesc(&Desc)))
	{
		return false;
	}
	m_MainCamera.SetProjMatrix(D3DX_PI * 0.25f, Desc.BufferDesc.Width / (float)(Desc.BufferDesc.Height), 0.1f, 50.0f);

	return true;
}


bool GProjMain::Frame()
{
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	//float t = m_Timer.GetElapsedTime() * D3DX_PI;
	m_fRadius = 0;

	m_MainCamera.Update(D3DXVECTOR4(m_fCameraPitch, m_fCameraYaw, m_fCameraRoll, m_fRadius));
	return true;
}
bool GProjMain::Render()
{	
	HRESULT hr;
	G_SPHERE SphereObj;
	ApplyBS(m_pImmediateContext, GDxState::g_pAlphaBlend);
	ApplyDSS(m_pImmediateContext, GDxState::g_pDSSDepthEnable);
	ApplyRS(m_pImmediateContext, GDxState::g_pRSBackCullSolid);
	//--------------------------------------------------------------------------------------
	// 박스 랜더링
	//--------------------------------------------------------------------------------------
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_matBoxWorld._41 = m_vBoxPosition[iBox].x;
		m_matBoxWorld._42 = m_vBoxPosition[iBox].y;
		m_matBoxWorld._43 = m_vBoxPosition[iBox].z;

		float fDistance = D3DXVec3Length(&(*m_MainCamera.GetEyePt() - m_vBoxPosition[iBox])) / 100.0f;

		m_pBoxShape->m_cbData.Color = D3DXVECTOR4(fDistance, fDistance, fDistance, 1.0f);

		m_pBoxShape->SetMatrix(&m_matBoxWorld, m_MainCamera.GetViewMatrix(), m_MainCamera.GetProjMatrix());
		if (m_MainCamera.ClassifyPoint(&m_vBoxPosition[iBox]))
		{
			m_pBoxShape->Render(m_pImmediateContext);
		}
		else
		{
			SphereObj.vCenter = m_vBoxPosition[iBox];
			SphereObj.fRadius = sqrt(3.0f);
			if (m_MainCamera.ClassifySphere(&SphereObj))
			{
				m_pBoxShape->m_cbData.Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
				m_pBoxShape->Render(m_pImmediateContext);
			}
		}
	}

		//m_pBoxShape->m_cbData.Color = m_vBoxColor[iBox];
		//m_pBoxShape->SetMatrix(&m_matBoxWorld, m_MainCamera.GetViewMatrix(), m_MainCamera.GetProjMatrix());
		//if (m_MainCamera.CheckOBBInPlane(&m_GBox[iBox]))
		//{
		//	m_pBoxShape->Render(m_pImmediateContext);
		//}

	
	return true;
}
bool GProjMain::Release()
{
	SAFE_DEL(m_pBoxShape);
	//SAFE_DEL(m_pLine);

	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_MainCamera.SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}

	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

HRESULT GProjMain::ScreenViewPort(UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	//UINT iRectWidth  = iWidth/3;
	//UINT iRectHeight = iHeight/3;
	////--------------------------------------------------------------------------------------
	//// 미니맵 영역 설정
	////--------------------------------------------------------------------------------------
	//m_MiniMapVP.Set(	0, iHeight-iRectHeight,	iRectWidth, iRectHeight, 0.0f, 1.0f);		
	return hr;
}
GProjMain::GProjMain(void)
{
	m_fCameraYaw = 0.0f;
	m_fCameraPitch = 0.0f;
	m_fCameraRoll = 0.0f;
	m_fRadius = 0.0f;
	SAFE_ZERO(m_pBoxShape);
}
GProjMain::~GProjMain(void)
{

}



int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}
GCORE_RUN(ENP Test);



