#include "GProjMain.h"

GProjMain* g_pMain;

bool GProjMain::UpdateGunPosition() {

	D3DXMATRIX matWorld, matScl, matRot;

	D3DXVECTOR3 vScl, vTrans;
	D3DXQUATERNION qRot;

	D3DXQUATERNION  qRotation; //쿼터니온 생성
	D3DXQuaternionRotationYawPitchRoll(&qRotation,  // 이과정에서 X축과 Y축의 회전을 사용
		(float)D3DXToRadian(180.0f),    // 하여 사원수를 만듦
		0.0f,
		0.0f);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);

	if (!m_pMainCamera)
		return false;

	D3DXMatrixInverse(&matWorld, NULL, m_pMainCamera->GetViewMatrix());
	D3DXMatrixDecompose(&vScl, &qRot, &vTrans, &matWorld);

	D3DXMatrixScaling(&matScl, vScl.x, vScl.y, vScl.z);

	//vTrans.x += 10.0f;
	vTrans.y -= 5.0f;
	vTrans.z += 10.0f;
	qRot = qRot * qRotation;

	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &vTrans);

	m_tbsobj.m_matWorld = matScl * matRot;// *matTrans;

	return true;
}
bool GProjMain::Init()
{
	m_tbsobj.Init();	

	if (!m_tbsobj.Load(GetDevice(), _T("data/object/fps_shotgun/shotgun3.GBS"), L"data/shader/box.hlsl"))
	{
		return false;
	}

	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GFPSCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(10.0f, 10.0f, -10.0f), D3DXVECTOR3(-10.0f, 10.0f, 50.0f));

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);
	
	return true;
}
bool GProjMain::Render()
{	
	m_tbsobj.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	m_tbsobj.Render(m_pImmediateContext);

	return true;
}
bool GProjMain::Release()
{
	m_tbsobj.Release();
	return true;
}

bool GProjMain::Frame()
{	
	
	m_pMainCamera->Frame();

	UpdateGunPosition();
	m_tbsobj.Frame();	


	return true;
}

HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
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
}

GProjMain::~GProjMain(void)
{
}
int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}
GCORE_RUN(GBS Viewer);

