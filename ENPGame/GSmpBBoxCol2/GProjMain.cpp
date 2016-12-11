#include "_stdafx.h"

GProjMain* g_pMain;

bool GProjMain::ChkOBBToRay(GBBox* pBox, G_RAY* pRay)
{
	if (pRay == NULL) pRay = &m_Ray;
	float t_min = -999999.0f;
	float t_max = 999999.0f;
	float  f[3], fa[3], s[3], sa[3];

	D3DXVECTOR3 vR = pRay->vOrigin - pBox->center;

	for (int v = 0; v < 3; v++)
	{
		f[v] = D3DXVec3Dot(&pBox->axis[v], &pRay->vDirection);
		s[v] = D3DXVec3Dot(&pBox->axis[v], &vR);
		fa[v] = fabs(f[v]);
		sa[v] = fabs(s[v]);

		if (sa[v] > pBox->extent[v] && s[v] * f[v] >= 0.0f)
			return false;

		float t1 = (-s[v] - pBox->extent[v]) / f[v];
		float t2 = (-s[v] + pBox->extent[v]) / f[v];
		if (t1 > t2)
		{
			swap(t1, t2);
		}
		t_min = max(t_min, t1);
		t_max = min(t_max, t2);
		if (t_min > t_max)
			return false;
	}

	float  fCross[3], fRhs;
	D3DXVECTOR3 vDxR;
	D3DXVec3Cross(&vDxR, &pRay->vDirection, &vR);
	// D X pBox->vAxis[0]  분리축
	fCross[0] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[0]));
	float fAxis2 = pBox->extent[1] * fa[2];
	float fAxis1 = pBox->extent[2] * fa[1];
	fRhs = fAxis2 + fAxis1;
	if (fCross[0] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}
	// D x pBox->vAxis[1]  분리축
	fCross[1] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[1]));
	fRhs = pBox->extent[0] * fa[2] + pBox->extent[2] * fa[0];
	if (fCross[1] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}
	// D x pBox->vAxis[2]  분리축
	fCross[2] = fabs(D3DXVec3Dot(&vDxR, &pBox->axis[2]));
	fRhs = pBox->extent[0] * fa[1] + pBox->extent[1] * fa[0];
	if (fCross[2] > fRhs)
	{
		m_Select.m_vDxR = vDxR;
		return false;
	}

	m_Select.m_vIntersection = pRay->vOrigin + pRay->vDirection* t_min;

	//코드 추가함. 거리를 구해서 광선의 길이 보다 짧았을때 true 리턴.
	D3DXVECTOR3 vLength = pRay->vOrigin - m_Select.m_vIntersection;
	float fLength = D3DXVec3Length(&vLength);
	if (fLength > pRay->fExtent)
		return false;

	return true;
}

bool GProjMain::Init()
{

	if (FAILED(m_pDirectionLine.Create(GetDevice(), L"data_test/shader/Line.hlsl")))
	{
		MessageBox(0, _T("m_pDirectionLIne 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	if (FAILED(m_pPlane.Create(GetDevice(), L"data_test/shader/Plane.hlsl", L"data_test/Sand.jpg")))
	{
		MessageBox(0, _T("m_pPlane 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	if (FAILED(m_pBox.Create(GetDevice(), L"data_test/shader/Box.hlsl", L"data_test/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_pBox 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

#ifdef G_MACRO_ENEMYBOX
	if (FAILED(m_pBoxEnemy.Create(GetDevice(), L"data_test/shader/Box.hlsl", L"data_test/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_pBoxEnemy 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	D3DXMatrixIdentity(&m_matWorldEnemy);

	D3DXMatrixTranslation(&m_matWorldEnemy, 10.0f, 0.0f, 10.0f);
#endif
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotation);
	D3DXMatrixIdentity(&m_matTrans);

	D3DXMatrixIdentity(&m_World[0]);
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIX matRotX, matScale;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(90));
	D3DXMatrixScaling(&matScale, 100.0f, 100.0f, 100.0f);
	D3DXMatrixMultiply(&m_matWorldPlaneBase, &matScale, &matRotX);

	// 4 종류의 카메라 세팅
	D3DXVECTOR3 vTargetPosition = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 1.0f, -0.1f);


	// 메인 카메라 뷰 행렬 세팅
	SAFE_NEW(m_pMainCamera, GCamera);
	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 10000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);



	m_pBBox.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));


#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Init(D3DXVECTOR3(-1.5f, -1.5f, -1.5f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));

#endif


	return true;
}

bool GProjMain::Render()
{	
	HRESULT hr;
	//-----------------------------------------------------------------------
	// 메인 뷰포트
	//-----------------------------------------------------------------------	

	m_pBox.SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pBox.Render(m_pImmediateContext);
	m_pBBox.Render(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

#ifdef G_MACRO_ENEMYBOX
	m_pBoxEnemy.SetMatrix(&m_matWorldEnemy, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pBoxEnemy.Render(m_pImmediateContext);
	m_pBBoxEnemy.Render(&m_matWorldEnemy, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
#endif

	m_pPlane.SetMatrix(&m_matWorldPlaneBase, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pPlane.Render(m_pImmediateContext);



	return true;
}
bool GProjMain::Release()
{

	SAFE_DEL(m_pMainCamera);
	return true;
}

#define G_MACRO_CAR_SPEED 10.0f			//박스 Speed

bool GProjMain::Frame()
{	
	static float fSpeed = G_MACRO_CAR_SPEED;//박스 이동 스피드
	static float angle = 0.0f;//for 박스 회전 각도
	static D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f,0.0f,0.0f);// 박스 위치.

	//float 누적발생에 대한 오차를 줄이기 위해..
	if (angle > 360.0f || angle < -360.0f) {
		angle = 0.0f; D3DXMatrixIdentity(&m_matRotation);; m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//--------------------------------------------------------------------------------------
	// 엔진에 있는 뷰 및 투영 행렬 갱신
	//--------------------------------------------------------------------------------------
	m_pMainCamera->Frame();


#ifdef G_MACRO_ENEMYBOX
	m_pBBoxEnemy.Frame(&m_matWorldEnemy);


	/*
	int nRet = GBBOXFUNC::ColCheck(&m_pBBoxEnemy, &m_pBBox);

	if (nRet == 1) {
		// 충돌시 처리할 코드 add

		G_RAY  ray;
		D3DXVECTOR3 vSliding = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		ray.vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ray.vDirection = m_vLook;
		D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &m_matWorld);
		D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &m_matWorld);
		D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);

		if (GBBOXFUNC::RaytoBox(&vSliding, &m_pBBoxEnemy, &ray)) {


		}
		else {
			vSliding = m_vLook;
		}

		D3DXMATRIX matTran, matRot;
		D3DXMatrixIdentity(&matTran);
		D3DXMatrixIdentity(&matRot);

		D3DXVECTOR3 vRight, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vRight, &vUp, &vSliding);
		D3DXVec3Cross(&vUp, &vSliding, &vRight);

		matRot._11 = vRight.x;		    matRot._12 = vRight.y;			matRot._13 = vRight.z;
		matRot._21 = vUp.x;				matRot._22 = vUp.y;				matRot._23 = vUp.z;
		matRot._31 = vSliding.x;		matRot._32 = vSliding.y;		matRot._33 = vSliding.z;

		if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD) {

			vPos = vPos + m_Timer.GetSPF()*fSpeed* vSliding;
		}
		if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD) {

			vPos = vPos - m_Timer.GetSPF()*fSpeed* vSliding;
		}

		D3DXMatrixTranslation(&matTran, vPos.x, vPos.y, vPos.z);
		m_matWorld = m_matScale * matRot * matTran;
		m_matRotation = matRot;
		m_matTrans = matTran;
	}
	else {

	*/

		if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
		{
			D3DXMatrixRotationY(&m_matRotation, D3DXToRadian(angle -= 20.0f*m_Timer.GetSPF()*fSpeed));
		}
		else if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
		{
			D3DXMatrixRotationY(&m_matRotation, D3DXToRadian(angle += 20.0f*m_Timer.GetSPF()*fSpeed));

		}

		m_vLook.x = m_matRotation._31;
		m_vLook.y = m_matRotation._32;
		m_vLook.z = m_matRotation._33;


		/*
		if (I_Input.KeyCheck(DIK_UP)) {

			vPos = vPos + m_Timer.GetSPF()*fSpeed * m_vLook;
		}
		if (I_Input.KeyCheck(DIK_DOWN)) {

			vPos = vPos - m_Timer.GetSPF()*fSpeed * m_vLook;
		}
		D3DXMatrixTranslation(&m_matTrans, vPos.x, vPos.y, vPos.z);



		m_matWorld = m_matScale * m_matRotation * m_matTrans;
		*/
	//}

#endif

	//m_pBBox.Frame(&m_matWorld);

		bool bContact = false;
		D3DXVECTOR3 slidingVector;
	// 0   1  2
	//     |
	// |   |  |
	// |------|
	// |      |
	// |------|
	// |   |  |
	//     |
	// 3   4  5
	D3DXVECTOR3 vRayPos[6];

	vRayPos[0] = D3DXVECTOR3(-1.5f, 0.0f, 1.5f -0.5f);
	vRayPos[1]= D3DXVECTOR3(0.0f, 0.0f, 1.5f - 0.5f);
	vRayPos[2] = D3DXVECTOR3(1.5f, 0.0f, 1.5f - 0.5f);
	vRayPos[3] = D3DXVECTOR3(-1.5f, 0.0f, -1.5f + 0.5f);
	vRayPos[4] = D3DXVECTOR3(0.0f, 0.0f, -1.5f + 0.5f);
	vRayPos[5] = D3DXVECTOR3(1.5f, 0.0f, -1.5f + 0.5f);

	for(int i=0;i<6;i++)
		D3DXVec3TransformCoord(&vRayPos[i], &vRayPos[i], &m_matWorld);



	for (int j = 0; j < 6; j++) {
		m_Ray.vOrigin = vRayPos[j]; 

		if (j == 1 || j == 4)
			m_Ray.fExtent = 2.0f;
		else
			m_Ray.fExtent = 1.0f;

		if (j >= 3)
			m_Ray.vDirection = -m_vLook;
		else
			m_Ray.vDirection = m_vLook;

		if (ChkOBBToRay(&m_pBBoxEnemy, &m_Ray)) {
			//충돌이 되면. 해당 교점이 어느 평면인지 찾은후 해당 평면의 노말을 얻어온다.그후 슬라이딩 벡터 계산
			//슬라이딩 벡터를 DirectX로 표현하면 다음과 같다.
			//D3DXVECTOR3 slidingVector = moveVec - D3DXVec3Dot(&moveVec,&contactNormal)*contactNormal;

			D3DXVECTOR3 vPoint[8];
			for (int k = 0; k < 8; k++)
				D3DXVec3TransformCoord(&vPoint[k], &m_pBBoxEnemy.m_vPoint[k], &m_matWorldEnemy);

			m_pBBoxEnemy.m_Plane[G_OBB_UP].CreatePlane(vPoint[2], vPoint[0], vPoint[3]);
			m_pBBoxEnemy.m_Plane[G_OBB_DOWN].CreatePlane(vPoint[4], vPoint[6], vPoint[5]);
			m_pBBoxEnemy.m_Plane[G_OBB_LEFT].CreatePlane(vPoint[4], vPoint[0], vPoint[6]);
			m_pBBoxEnemy.m_Plane[G_OBB_RIGHT].CreatePlane(vPoint[7], vPoint[3], vPoint[5]);
			m_pBBoxEnemy.m_Plane[G_OBB_FRONT].CreatePlane(vPoint[5], vPoint[1], vPoint[4]);
			m_pBBoxEnemy.m_Plane[G_OBB_BACK].CreatePlane(vPoint[6], vPoint[2], vPoint[7]);


			D3DXVECTOR3 vNormal;
			float fCalc = 0.0f;

			for (int i = 0; i < G_OBB_SIDE_CNT; i++) {
				vNormal = D3DXVECTOR3(m_pBBoxEnemy.m_Plane[i].fA, m_pBBoxEnemy.m_Plane[i].fB, m_pBBoxEnemy.m_Plane[i].fC);
				float fCalc = vNormal.x* m_Select.m_vIntersection.x + vNormal.y* m_Select.m_vIntersection.y + vNormal.z* m_Select.m_vIntersection.z + m_pBBoxEnemy.m_Plane[i].fD;
				if (fCalc < 0.001f && fCalc >= 0.0f)
				{
					slidingVector = m_Ray.vDirection - D3DXVec3Dot(&m_Ray.vDirection, &vNormal)*vNormal;
					bContact = true;
				}
			}
		}
	}

	if (bContact == true) {
		if (I_Input.KeyCheck(DIK_UP)) {

			vPos = vPos + m_Timer.GetSPF()*fSpeed * slidingVector;
		}
		if (I_Input.KeyCheck(DIK_DOWN)) {

			vPos = vPos - m_Timer.GetSPF()*fSpeed * -slidingVector;
		}

	}
	else {
		if (I_Input.KeyCheck(DIK_UP)) {

			vPos = vPos + m_Timer.GetSPF()*fSpeed * m_vLook;
		}
		if (I_Input.KeyCheck(DIK_DOWN)) {

			vPos = vPos - m_Timer.GetSPF()*fSpeed * m_vLook;
		}


	}



	D3DXMatrixTranslation(&m_matTrans, vPos.x, vPos.y, vPos.z);

	m_matWorld = m_matScale * m_matRotation * m_matTrans;
	m_pBBox.Frame(&m_matWorld);

	return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;

	if (m_pMainCamera)
	{
		// Setup the camera's projection parameters
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetWindow(m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr = S_OK;

	// 아래의 경고는 GetDevice()->ClearState();를 호출하지 않을 때 발생한다.
	//D3D10: INFO: ID3D11Device::RSSetState: The currently bound RasterizerState is being deleted; 
	//so naturally, will no longer be bound. [ STATE_SETTING INFO #46: RSSETSTATE_UNBINDDELETINGOBJECT ]
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
GProjMain::GProjMain(void)
{
	// 추가
	m_iCameraType = 3; // User Camera	
	m_fCameraYaw = 0.0f;
	m_fCameraPitch = 0.0f;
	m_fCameraRoll = 0.0f;
	m_fRadius = 0.0f;

	SAFE_ZERO(m_pMainCamera);
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



bool GProjMain::DrawDebug()
{


	m_pDirectionLine.SetMatrix(&m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);

	m_pDirectionLine.SetMatrix(&m_World[0], &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_pDirectionLine.Render(m_pImmediateContext);
	return GCoreLibV2::DrawDebug();
}


GCORE_RUN(ENP Test);



