#include "_stdafx.h"

GProjMain* g_pMain;



bool GProjMain::Init()
{
	HRESULT hr;
	//카메라 생성
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);
	// 메인 카메라 뷰 행렬 세팅
	m_pMainCamera->SetViewMatrix(vCameraPosition, vTargetPosition, vUpVector);

	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		0.1f, 10000.0f);


	//CustomizeMap
	TMapDesc MapDesc = { 50, 50, 1.0f, 0.1f,L"data/baseColor.jpg", L"data/shader/CustomizeMap.hlsl" };
	m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	if (FAILED(m_CustomMap.Load(MapDesc)))
	{
		return false;
	}
	if (FAILED(CreateResource()))
	{
		return false;
	}

	//frustum
	m_pMainCamera->CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"data/shader/box.hlsl", "PS_COLOR"));
	//--------------------------------------------------------------------------------------
	// 박스 오브젝트 생성( 100개 박스가 공유해서 사용함)
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pBoxShape, GBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"data/shader/box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_LineShape 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	// 기저 박스(크기가 1이 기본 박스) 구성
	m_gBoxBase.vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_gBoxBase.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_gBoxBase.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);

	//100개의 박스 위치 세팅
	D3DXMATRIX matScale, matRotation, matWorld;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_vBoxPosition[iBox] = D3DXVECTOR3(25 - rand() % 50, 25 - rand() % 50, 25 - rand() % 50);
		m_vBoxColor[iBox] = D3DXVECTOR4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f);

		// S*R
		D3DXMatrixScaling(&matScale, (rand() % 256) / 255.0f*3.0f, (rand() % 256) / 255.0f*3.0f, (rand() % 256) / 255.0f*3.0f);
		D3DXMatrixRotationYawPitchRoll(&matRotation, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f);
		D3DXMatrixMultiply(&matWorld, &matScale, &matRotation);



		//obb 기저벡터의 축방향(axis) 구하기
		m_GBox[iBox].vCenter = m_vBoxPosition[iBox];
		D3DXVECTOR3 vMax, vMin, vHalf;
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[0], &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[1], &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[2], &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &matWorld);
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[0], &m_GBox[iBox].vAxis[0]); //박스의 x축의 길이를 1로 정규화
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[1], &m_GBox[iBox].vAxis[1]); //박스의 y축의 길이를 1로 정규화
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[2], &m_GBox[iBox].vAxis[2]); //박스의 z축의 길이를 1로 정규화

		//S*R*T
		matWorld._41 = m_vBoxPosition[iBox].x;
		matWorld._42 = m_vBoxPosition[iBox].y;
		matWorld._43 = m_vBoxPosition[iBox].z;

		// 박스의 각 축의 길이 구하기
		D3DXVec3TransformCoord(&vMax, &m_gBoxBase.vMax, &matWorld);
		D3DXVec3TransformCoord(&vMin, &m_gBoxBase.vMin, &matWorld);
		vHalf = vMax - m_GBox[iBox].vCenter;
		m_GBox[iBox].fExtent[0] = D3DXVec3Dot(&m_GBox[iBox].vAxis[0], &vHalf);//박스의 x축의 길이 구하기
		m_GBox[iBox].fExtent[1] = D3DXVec3Dot(&m_GBox[iBox].vAxis[1], &vHalf);//박스의 y축의 길이 구하기
		m_GBox[iBox].fExtent[2] = D3DXVec3Dot(&m_GBox[iBox].vAxis[2], &vHalf);//박스의 z축의 길이 구하기 

		m_matBoxWorld[iBox] = matWorld;
		
	}

	return true;
}


bool GProjMain::Frame()
{
	m_pMainCamera->Frame();

	m_CustomMap.Frame();
	g_pImmediateContext->UpdateSubresource(
		m_CustomMap.m_dxobj.g_pVertexBuffer.Get(), 0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);



	return true;
}
bool GProjMain::Render()
{
	m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(),
		m_pMainCamera->GetProjMatrix());
	m_CustomMap.Render(m_pImmediateContext);

	//박스 랜더링
	D3DXMATRIX matScale, matRotation;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		//m_pBoxShape->m_cbData.Color = m_vBoxColor[iBox];
		m_pBoxShape->SetMatrix(&m_matBoxWorld[iBox], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		//obb와 프로스텀 박스의 제외처리 *******
		if (m_pMainCamera->CheckOBBInPlane(&m_GBox[iBox]))
		{
			m_pBoxShape->Render(m_pImmediateContext);
		}

	}
	
	return true;
}
bool GProjMain::Release()
{
	m_CustomMap.Release();
	SAFE_DEL(m_pBoxShape);
	SAFE_DEL(m_pMainCamera);

	
	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	//{
	//	float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
	//		(float)m_SwapChainDesc.BufferDesc.Height;
	//	//m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	//}

	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{
	m_pMainCamera = NULL;
	SAFE_ZERO(m_pBoxShape);
	//SAFE_ZERO(m_pLine);
}
GProjMain::~GProjMain(void)
{

}



int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return -1;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GProjMain gProjMain; g_pMain = &gProjMain;
	if (!gProjMain.InitWindow(hInstance, nCmdShow, L"GRustum Test", 1024, 768)) { return 0; }
	ShowCursor(TRUE);
	gProjMain.Run();	return 1;
}


