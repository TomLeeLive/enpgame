#include "GProjMain.h"

GProjMain* g_pMain;

G_BoxObject::G_BoxObject()
{
	m_tBox.vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_tBox.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_tBox.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);

	m_vPosition = D3DXVECTOR3(25 - rand() % 50, 0, 25 - rand() % 50);
	m_vColor = D3DXVECTOR4(rand() % 256 / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f);

	D3DXMATRIX matScale, matRotation, matWorld;
	D3DXMatrixScaling(&matScale, (rand() % 256) / 255.0f*2.0f, (rand() % 256) / 255.0f*2.0f, (rand() % 256) / 255.0f *2.0f);
	D3DXMatrixMultiply(&matWorld, &matScale, &matRotation);

	m_tBox.vCenter = m_vPosition;
	D3DXVECTOR3 vMax, vMin, vHalf;
	D3DXVec3TransformCoord(&m_tBox.vAxis[0], &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &matWorld);
	D3DXVec3TransformCoord(&m_tBox.vAxis[1], &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &matWorld);
	D3DXVec3TransformCoord(&m_tBox.vAxis[2], &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &matWorld);
	D3DXVec3Normalize(&m_tBox.vAxis[0], &m_tBox.vAxis[0]);
	D3DXVec3Normalize(&m_tBox.vAxis[1], &m_tBox.vAxis[1]);
	D3DXVec3Normalize(&m_tBox.vAxis[2], &m_tBox.vAxis[2]);

	matWorld._41 = m_vPosition.x;
	matWorld._42 = m_vPosition.y;
	matWorld._42 = m_vPosition.z;

	D3DXVec3TransformCoord(&vMax, &m_tBox.vMax, &matWorld);
	D3DXVec3TransformCoord(&vMin, &m_tBox.vMin, &matWorld);
	vHalf = vMax - m_tBox.vCenter;
	m_tBox.fExtent[0] = D3DXVec3Dot(&m_tBox.vAxis[0], &vHalf);
	m_tBox.fExtent[1] = D3DXVec3Dot(&m_tBox.vAxis[1], &vHalf);
	m_tBox.fExtent[2] = D3DXVec3Dot(&m_tBox.vAxis[2], &vHalf);

	D3DXVECTOR3 vVertex[8];
	vVertex[0] = D3DXVECTOR3(m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMin.z);
	vVertex[1] = D3DXVECTOR3(m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMin.z);
	vVertex[2] = D3DXVECTOR3(m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMin.z);
	vVertex[3] = D3DXVECTOR3(m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMin.z);

	vVertex[4] = D3DXVECTOR3(m_tBox.vMin.x, m_tBox.vMax.y, m_tBox.vMax.z);
	vVertex[5] = D3DXVECTOR3(m_tBox.vMax.x, m_tBox.vMax.y, m_tBox.vMax.z);
	vVertex[6] = D3DXVECTOR3(m_tBox.vMax.x, m_tBox.vMin.y, m_tBox.vMax.z);
	vVertex[7] = D3DXVECTOR3(m_tBox.vMin.x, m_tBox.vMin.y, m_tBox.vMax.z);

	vMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
	vMax - D3DXVECTOR3(-100000.0f, -100000.0, -100000.0f);
	for (int iVer = 0; iVer < 8; iVer++)
	{
		D3DXVec3TransformCoord(&vVertex[iVer], &vVertex[iVer], &matWorld);
		if (vVertex[iVer].x > vMax.x) vMax.x = vVertex[iVer].x;
		if (vVertex[iVer].y > vMax.y) vMax.y = vVertex[iVer].y;
		if (vVertex[iVer].z > vMax.z) vMax.z = vVertex[iVer].z;

		if (vVertex[iVer].x < vMin.x) vMin.x = vVertex[iVer].x;
		if (vVertex[iVer].y < vMin.y) vMin.y = vVertex[iVer].y;
		if (vVertex[iVer].z < vMin.z) vMin.z = vVertex[iVer].z;
	}

	m_tBox.vMin = vMin;
	m_tBox.vMax = vMax;
	m_matWorld = matWorld;
}

void GProjMain::DrawObject()
{

}
void GProjMain::DrawSelectTreeLevel(D3DXMATRIX* pView, D3DXMATRIX* pProj)
{

}

bool GProjMain::Init()
{
	SAFE_NEW(m_pLine, GLineShape);
	if (FAILED(m_pLine->Create(GetDevice(), L"data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}	
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------
	//SAFE_NEW(m_pMainCamera, GCamera);
	m_pMainCamera = make_shared<GCamera>();

	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 300.0f, -300.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 3000.0f);



	SAFE_NEW(m_pBoxShape, GBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"data/shader/box.hlsl", L"data/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_pBoxShape 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	SAFE_NEW_ARRAY(m_pObject, G_BoxObject, NUM_OBJECTS);
	
	m_QuadTree.Build(50.0f, 50.0f);
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_QuadTree.AddObject(&m_pObject[iBox]);
	}
	m_QuadTree.Update(GetDevice(), m_pMainCamera.get());
	return true;
}
bool GProjMain::Frame()
{
	//2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = cosf(m_Timer.GetElapsedTime()) * D3DX_PI;
	m_pMainCamera->Frame();

	// 쿼드트리
	if (I_Input.KeyCheck(DIK_F4) == KEY_UP)
	{
		if (++m_iDrawDepth > 7)	m_iDrawDepth = -1;
		m_QuadTree.SetRenderDepth(m_iDrawDepth);
	}
	return m_QuadTree.Frame();

}
bool GProjMain::Render()
{
	//DrawQuadLine(m_QuadTree.m_pRootNode);
	return true;
}
bool GProjMain::Release()
{
	SAFE_DEL(m_pLine);
	return true;
}

bool GProjMain::DrawDebug()
{
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
	//QuadTree
	SAFE_ZERO(m_pLine);
	m_iDrawDepth = 0;

	// 기본 인터페이스
	m_pMainCamera = nullptr;
	GCoreLibV2::m_bDebugInfoPrint = false;
	//GCoreLibV2::m_bDebugFpsPrint = false;
}

GProjMain::~GProjMain(void)
{
	Release();
}
GCORE_RUN(L"TBasisSample CustomizeMap");

