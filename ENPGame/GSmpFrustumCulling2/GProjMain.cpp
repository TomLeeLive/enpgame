#include "_stdafx.h"

GProjMain* g_pMain;



bool GProjMain::Init()
{
	HRESULT hr;
	//ī�޶� ����
	SAFE_NEW(m_pMainCamera, GCamera);

	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);
	// ���� ī�޶� �� ��� ����
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
	// �ڽ� ������Ʈ ����( 100�� �ڽ��� �����ؼ� �����)
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pBoxShape, GBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"data/shader/box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_LineShape ����"), _T("Fatal error"), MB_OK);
		return 0;
	}
	// ���� �ڽ�(ũ�Ⱑ 1�� �⺻ �ڽ�) ����
	m_gBoxBase.vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_gBoxBase.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_gBoxBase.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);

	//100���� �ڽ� ��ġ ����
	D3DXMATRIX matScale, matRotation, matWorld;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_vBoxPosition[iBox] = D3DXVECTOR3(25 - rand() % 50, 25 - rand() % 50, 25 - rand() % 50);
		m_vBoxColor[iBox] = D3DXVECTOR4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f);

		// S*R
		D3DXMatrixScaling(&matScale, (rand() % 256) / 255.0f*3.0f, (rand() % 256) / 255.0f*3.0f, (rand() % 256) / 255.0f*3.0f);
		D3DXMatrixRotationYawPitchRoll(&matRotation, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f);
		D3DXMatrixMultiply(&matWorld, &matScale, &matRotation);



		//obb ���������� �����(axis) ���ϱ�
		m_GBox[iBox].vCenter = m_vBoxPosition[iBox];
		D3DXVECTOR3 vMax, vMin, vHalf;
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[0], &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[1], &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_GBox[iBox].vAxis[2], &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &matWorld);
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[0], &m_GBox[iBox].vAxis[0]); //�ڽ��� x���� ���̸� 1�� ����ȭ
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[1], &m_GBox[iBox].vAxis[1]); //�ڽ��� y���� ���̸� 1�� ����ȭ
		D3DXVec3Normalize(&m_GBox[iBox].vAxis[2], &m_GBox[iBox].vAxis[2]); //�ڽ��� z���� ���̸� 1�� ����ȭ

		//S*R*T
		matWorld._41 = m_vBoxPosition[iBox].x;
		matWorld._42 = m_vBoxPosition[iBox].y;
		matWorld._43 = m_vBoxPosition[iBox].z;

		// �ڽ��� �� ���� ���� ���ϱ�
		D3DXVec3TransformCoord(&vMax, &m_gBoxBase.vMax, &matWorld);
		D3DXVec3TransformCoord(&vMin, &m_gBoxBase.vMin, &matWorld);
		vHalf = vMax - m_GBox[iBox].vCenter;
		m_GBox[iBox].fExtent[0] = D3DXVec3Dot(&m_GBox[iBox].vAxis[0], &vHalf);//�ڽ��� x���� ���� ���ϱ�
		m_GBox[iBox].fExtent[1] = D3DXVec3Dot(&m_GBox[iBox].vAxis[1], &vHalf);//�ڽ��� y���� ���� ���ϱ�
		m_GBox[iBox].fExtent[2] = D3DXVec3Dot(&m_GBox[iBox].vAxis[2], &vHalf);//�ڽ��� z���� ���� ���ϱ� 

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

	//�ڽ� ������
	D3DXMATRIX matScale, matRotation;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		//m_pBoxShape->m_cbData.Color = m_vBoxColor[iBox];
		m_pBoxShape->SetMatrix(&m_matBoxWorld[iBox], m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());

		//obb�� ���ν��� �ڽ��� ����ó�� *******
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


