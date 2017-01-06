#include "_stdafx.h"
//#include "GProjMain.h"
//#include "GFPSCamera.h"
//
//#include "GInput.h"
//#include "GTimer.h"
bool GFPSCamera::ChkOBBToRay(GBBox* pBox, G_RAY* pRay)
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

int GFPSCamera::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    if( ( (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
        ( (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
        ( (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK ) && m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_WorldArcBall.OnBegin( iMouseX, iMouseY );
    }

    if( ( (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
        ( (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
        ( (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK ) && m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_ViewArcBall.OnBegin( iMouseX, iMouseY );
    }

    if( uMsg == WM_MOUSEMOVE )
    {
        int iMouseX = (short)LOWORD(lParam);
        int iMouseY = (short)HIWORD(lParam);
        m_WorldArcBall.OnMove( iMouseX, iMouseY );
        m_ViewArcBall.OnMove( iMouseX, iMouseY );
    }

    if( (uMsg == WM_LBUTTONUP && m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
        (uMsg == WM_MBUTTONUP && m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
        (uMsg == WM_RBUTTONUP && m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        m_WorldArcBall.OnEnd();
    }

    if( (uMsg == WM_LBUTTONUP && m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
        (uMsg == WM_MBUTTONUP && m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
        (uMsg == WM_RBUTTONUP && m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
    {
        m_ViewArcBall.OnEnd();
    }

    if( uMsg == WM_CAPTURECHANGED )
    {
        if( (HWND)lParam != hWnd )
        {
            if( (m_nRotateModelButtonMask & MOUSE_LEFT_BUTTON) ||
                (m_nRotateModelButtonMask & MOUSE_MIDDLE_BUTTON) ||
                (m_nRotateModelButtonMask & MOUSE_RIGHT_BUTTON) )
            {
                m_WorldArcBall.OnEnd();
            }
        
            if( (m_nRotateCameraButtonMask & MOUSE_LEFT_BUTTON) ||
                (m_nRotateCameraButtonMask & MOUSE_MIDDLE_BUTTON) ||
                (m_nRotateCameraButtonMask & MOUSE_RIGHT_BUTTON) )
            {
                m_ViewArcBall.OnEnd();
            }
        }
    }

    
	if( uMsg == WM_MOUSEWHEEL )
	{
           // Update member var state
           m_nMouseWheelDelta += (short)HIWORD(wParam);
	}
    return -1;
}
void GFPSCamera::SetButtonMasks( int nRotateModelButtonMask, int nZoomButtonMask, int nRotateCameraButtonMask ) 
{ 
	m_nRotateModelButtonMask	= nRotateModelButtonMask, 
	m_nZoomButtonMask			= nZoomButtonMask; 
	m_nRotateCameraButtonMask	= nRotateCameraButtonMask; 
}

// 박스의 크기에 따라서 화면에 꽉차게 카메라가 조정된다.
D3DXMATRIX	GFPSCamera::SetObjectView( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin )
{
	D3DXMATRIX	matView;
	D3DXVECTOR3 vCenter = ( vMax + vMin ) * 0.5f;
	float fRadius = D3DXVec3Length( &(vMax-vMin) ) * 0.5f;	

	D3DXVECTOR3 vTarget = D3DXVECTOR3( vCenter.x, vCenter.y, vCenter.z );
	D3DXVECTOR3 vPos = (m_vLookVector *  (fRadius*2) ) * -1.0f;

	D3DXMatrixLookAtLH( &m_matView, &vPos, &vTarget , &D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	
	m_vCameraPos	= vPos;	
	m_vTargetPos	= vTarget;
	return m_matView;
}
D3DXMATRIX GFPSCamera::SetViewMatrix( D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp )
{
	m_vDefaultEye		= m_vCameraPos	= vPos;	
	m_vDefaultLookAt	= m_vTargetPos	= vTarget;
	D3DXMatrixLookAtLH( &m_matView, &m_vCameraPos, &m_vTargetPos , &vUp );
	
	D3DXQUATERNION qRotation;
	D3DXVECTOR3 vTrans, vScale, vAxis;
	D3DXMATRIX mInvView;
	D3DXQUATERNION q;
	float fAngle;

	if (SUCCEEDED(D3DXMatrixDecompose(&vScale, &qRotation, &vTrans, &m_matView)))
	{
		D3DXQuaternionNormalize(&qRotation, &qRotation);
		D3DXQuaternionToAxisAngle(&qRotation, &vAxis, &fAngle);
		// 반드시 정규화 해야 한다.
		D3DXVec3Normalize(&vAxis, &vAxis);

		q.x = sin(fAngle / 2) * vAxis.x;
		q.y = sin(fAngle / 2) * vAxis.y;
		q.z = sin(fAngle / 2) * vAxis.z;
		q.w = cos(fAngle / 2);
	}
	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	// The axis basis vectors and camera position are stored inside the 
	// position matrix in the 4 rows of the camera's world matrix.
	// To figure out the yaw/pitch of the camera, we just need the Z basis vector
	D3DXVECTOR3* pZBasis = (D3DXVECTOR3*)&mInvView._31;

	m_fCameraYawAngle = atan2f( pZBasis->x, pZBasis->z );
	float fLen = sqrtf( pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x );
	m_fCameraPitchAngle = -atan2f( pZBasis->y, fLen );

	return 	UpdateVector();	
}
D3DXMATRIX GFPSCamera::SetProjMatrix( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane )
{
    m_fFOV			= fFOV;
    m_fAspect		= fAspect;
    m_fNearPlane	= fNearPlane;
    m_fFarPlane		= fFarPlane;

    D3DXMatrixPerspectiveFovLH( &m_matProj, fFOV, fAspect, fNearPlane, fFarPlane );	
	return m_matProj;
}
D3DXMATRIX GFPSCamera::UpdateVector()
{
	m_vLookVector.x = m_matView._13;
	m_vLookVector.y = m_matView._23;
	m_vLookVector.z = m_matView._33;	
	m_vRightVector.x = m_matView._11;
	m_vRightVector.y = m_matView._21;
	m_vRightVector.z = m_matView._31;	
	m_vUpVector.x = m_matView._12;
	m_vUpVector.y = m_matView._22;
	m_vUpVector.z = m_matView._32;	
	
	D3DXVec3Normalize( &m_vLookVector, &m_vLookVector );
	
	GFrustum::SetMatrix( NULL, &m_matView, &m_matProj );
	GFrustum::CreateFrustum();	

	//g_pMain->UpdateGunPosition();
	return m_matView;
}
D3DXMATRIX GFPSCamera::Update( D3DXVECTOR4 vDirValue )
{
	D3DXMATRIX matRotation;
	D3DXQuaternionRotationYawPitchRoll(			&m_qRotation,	
												vDirValue.y,
												vDirValue.x,
												vDirValue.z );			

	m_vCameraPos += m_vLookVector * vDirValue.w;
	m_fRadius  += vDirValue.w;

	D3DXMatrixAffineTransformation( &matRotation, 1.0f, NULL, &m_qRotation, &m_vCameraPos );
	D3DXMatrixInverse( &m_matView, NULL, &matRotation );

	return UpdateVector();	
}
bool GFPSCamera::Frame(vector<shared_ptr<GObjData>>*	pVecObj)
{
	if (g_pMain->m_pGameSeq[G_SEQ_SINGLE]->m_bGameOver)
		return false;

	//if( g_InputData.bRightHold )
	//{
		m_fCameraYawAngle	+=	D3DXToRadian(g_InputData.iMouseValue[0] *0.1f);
		m_fCameraPitchAngle	+=  D3DXToRadian(g_InputData.iMouseValue[1] *0.1f);
	//}		
	// 카메라 이동 거리 = 속도 + ( 경과시간 * 마우스 휠 변위값 )
	float fValue = g_InputData.iMouseValue[2];
	float fDistance =  m_fSpeed * fValue * g_fSecPerFrame;
	
	if(g_InputData.bLeftShift)	m_fSpeed += g_fSecPerFrame * 40.0f;
	else						m_fSpeed -= g_fSecPerFrame * 40.0f;
	// 최소값으로 고정
	if( m_fSpeed < 100.0f ) m_fSpeed = 100.0f;

	/*
	if( g_InputData.bWKey ) 	MoveLook(g_fSecPerFrame * 5.0f * m_fSpeed);
	if( g_InputData.bSKey )		MoveLook(-g_fSecPerFrame * 5.0f* m_fSpeed);
	if( g_InputData.bDKey )		MoveSide(g_fSecPerFrame * 5.0f* m_fSpeed);
	if( g_InputData.bAKey )		MoveSide(-g_fSecPerFrame * 5.0f* m_fSpeed);
	*/






	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);

	UpdateCameraDir();
	m_vCameraDir;


	bool bContact = false;
	D3DXVECTOR3 slidingVector;
	//				0   1  2
	//				    |
	//				|   |  |
	//		6	----|------|----   9
	//		7 ------|      |------ 10
	//		8	----|------|----   11
	//				|   |  |
	//				    |
	//				3   4  5
	D3DXVECTOR3 vRayPos[12];

	vRayPos[0] = D3DXVECTOR3(-1.5f, 0.0f, 1.5f);
	vRayPos[1] = D3DXVECTOR3(0.0f, 0.0f, 1.5f);
	vRayPos[2] = D3DXVECTOR3(1.5f, 0.0f, 1.5f);
	vRayPos[3] = D3DXVECTOR3(-1.5f, 0.0f, -1.5f);
	vRayPos[4] = D3DXVECTOR3(0.0f, 0.0f, -1.5f);
	vRayPos[5] = D3DXVECTOR3(1.5f, 0.0f, -1.5f);

	vRayPos[6] = D3DXVECTOR3(-1.5f, 0.0f, 1.5f);
	vRayPos[7] = D3DXVECTOR3(-1.5f, 0.0f, 0.0f);
	vRayPos[8] = D3DXVECTOR3(-1.5f, 0.0f, -1.5f);
	vRayPos[9] = D3DXVECTOR3(1.5f, 0.0f, 1.5f);
	vRayPos[10] = D3DXVECTOR3(1.5f, 0.0f, 0.0f);
	vRayPos[11] = D3DXVECTOR3(1.5f, 0.0f, -1.5f);

	for (int i = 0; i<12; i++)
		D3DXVec3TransformCoord(&vRayPos[i], &vRayPos[i], &m_matWorld);



	for (int j = 0; j < 12; j++) {
		m_Ray.vOrigin = vRayPos[j];

		//if (j == 1 || j == 4)
		//	m_Ray.fExtent = 2.0f;
		//else
		m_Ray.fExtent = 1.5f;



		if (j >= 9) {
			D3DXMatrixRotationY(&matRot, D3DXToRadian(90.0f));
			D3DXVec3TransformCoord(&m_Ray.vDirection, &m_vCameraDir, &matRot);
		}
		else if (j >= 6) {
			D3DXMatrixRotationY(&matRot, D3DXToRadian(270.0f));
			D3DXVec3TransformCoord(&m_Ray.vDirection, &m_vCameraDir, &matRot);
		}
		else if (j >= 3) {
			m_Ray.vDirection = -m_vCameraDir;
		}
		else {
			m_Ray.vDirection = m_vCameraDir;
		}

		for (int iObbCnt = 0; iObbCnt < (*pVecObj).size(); iObbCnt++) {
			

			if (ChkOBBToRay(&(*pVecObj)[iObbCnt]->m_pObj->m_OBB, &m_Ray)) {
				//충돌이 되면. 해당 교점이 어느 평면인지 찾은후 해당 평면의 노말을 얻어온다.그후 슬라이딩 벡터 계산
				//슬라이딩 벡터를 DirectX로 표현하면 다음과 같다.
				//D3DXVECTOR3 slidingVector = moveVec - D3DXVec3Dot(&moveVec,&contactNormal)*contactNormal;

				D3DXVECTOR3 vPoint[8];
				for (int k = 0; k < 8; k++)
					D3DXVec3TransformCoord(&vPoint[k], &(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_vPoint[k], &(*pVecObj)[iObbCnt]->m_matObjWld);

				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_UP].CreatePlane(vPoint[2], vPoint[0], vPoint[3]);
				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_DOWN].CreatePlane(vPoint[4], vPoint[6], vPoint[5]);
				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_LEFT].CreatePlane(vPoint[4], vPoint[0], vPoint[6]);
				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_RIGHT].CreatePlane(vPoint[7], vPoint[3], vPoint[5]);
				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_FRONT].CreatePlane(vPoint[5], vPoint[1], vPoint[4]);
				(*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[G_OBB_BACK].CreatePlane(vPoint[6], vPoint[2], vPoint[7]);


				D3DXVECTOR3 vNormal;
				float fCalc = 0.0f;

				for (int i = 0; i < G_OBB_SIDE_CNT; i++) {
					vNormal = D3DXVECTOR3((*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[i].fA, (*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[i].fB, (*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[i].fC);
					float fCalc = vNormal.x* m_Select.m_vIntersection.x + vNormal.y* m_Select.m_vIntersection.y + vNormal.z* m_Select.m_vIntersection.z + (*pVecObj)[iObbCnt]->m_pObj->m_OBB.m_Plane[i].fD;
					if (fCalc < 0.001f && fCalc >= 0.0f)
					{
						slidingVector = m_Ray.vDirection - D3DXVec3Dot(&m_Ray.vDirection, &vNormal)*vNormal;
						bContact = true;
					}
				}
			}
		}

		
	}

	if (bContact == true) {
		if (g_InputData.bWKey) {

			m_vCameraPos = m_vCameraPos + g_fSecPerFrame * 5.0f * m_fSpeed * slidingVector;
		}
		if (g_InputData.bSKey) {

			m_vCameraPos = m_vCameraPos - g_fSecPerFrame * 5.0f * m_fSpeed * m_vCameraDir;
		}
		if (g_InputData.bAKey)
		{
			m_vCameraPos = m_vCameraPos + g_fSecPerFrame * 5.0f * m_fSpeed * slidingVector;
		}
		else if (g_InputData.bDKey)
		{
			m_vCameraPos = m_vCameraPos + g_fSecPerFrame * 5.0f * m_fSpeed * slidingVector;

		}
	}
	else {
		if (g_InputData.bWKey) 	MoveLook(g_fSecPerFrame * 5.0f * m_fSpeed);
		if (g_InputData.bSKey)		MoveLook(-g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bDKey)		MoveSide(g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bAKey)		MoveSide(-g_fSecPerFrame * 5.0f* m_fSpeed);
	}

























	//if( g_InputData.bQKey )		MoveUp(g_fSecPerFrame * 5.0f* m_fSpeed);
	//if( g_InputData.bEKey )		MoveUp(-g_fSecPerFrame * 5.0f* m_fSpeed);

	Update( D3DXVECTOR4( m_fCameraPitchAngle, m_fCameraYawAngle, m_fCameraRollAngle, fDistance) );
	UpdateVector();	
	UpdateCameraDir();
	return true;
}

D3DXMATRIX GFPSCamera::GetRotMatY()
{
	D3DXMATRIX matRotY, matRot180;

	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRot180);


	D3DXVECTOR3 vRight, vDir, vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixRotationY(&matRot180, D3DXToRadian(180.0f));
	D3DXVec3TransformCoord(&vDir, &m_vCameraDir, &matRot180);
	D3DXVec3Normalize(&vDir, &vDir);
	
	D3DXVec3Cross(&vRight, &vUp, &vDir);
	D3DXVec3Cross(&vUp, &vDir, &vRight);



	matRotY._11 = vRight.x;		    matRotY._12 = vRight.y;			matRotY._13 = vRight.z;
	matRotY._21 = vUp.x;			matRotY._22 = vUp.y;			matRotY._23 = vUp.z;
	matRotY._31 = vDir.x;			matRotY._32 = vDir.y;			matRotY._33 = vDir.z;

	return matRotY;
}

void GFPSCamera::UpdateCameraDir() {
	D3DXMATRIX matScl, matRot, matViewInv;

	D3DXVECTOR3 vScl, vTrans;
	D3DXQUATERNION qRot;

	D3DXMatrixIdentity(&matScl);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matViewInv);



	D3DXMatrixInverse(&matViewInv, NULL, &m_matView);
	D3DXMatrixDecompose(&vScl, &qRot, &vTrans, &matViewInv);

	D3DXMatrixScaling(&matScl, vScl.x, vScl.y, vScl.z);

	vTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &vTrans);

	//m_tbsobj.m_matWorld = matScl * matRot;// *matTrans;

	D3DXMatrixIdentity(&m_matRotY);

	m_matRotY._11 = matRot._11;
	m_matRotY._13 = matRot._13;
	m_matRotY._31 = matRot._31;
	m_matRotY._33 = matRot._33;

	m_vCameraDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformCoord(&m_vCameraDir, &m_vCameraDir, &m_matRotY);
	D3DXVec3Normalize(&m_vCameraDir, &m_vCameraDir);
}

void GFPSCamera::MoveLook( float fValue )
{
	//g_pMain->m_pSound.Play(SND_BOOTS1, true, true);

	//UpdateCameraDir();
	m_vCameraPos += m_vCameraDir * fValue;
}
void GFPSCamera::MoveSide( float fValue )
{
	m_vCameraPos += m_vRightVector * fValue;
}
void GFPSCamera::MoveUp( float fValue )
{
	m_vCameraPos += m_vUpVector * fValue;
}
void GFPSCamera::SetRadius( float fDefaultRadius, float fMinRadius, float fMaxRadius  ) 
{ 
  m_fDefaultRadius = m_fRadius = fDefaultRadius;
  m_fMinRadius = fMinRadius; 
  m_fMaxRadius = fMaxRadius; 
}
void GFPSCamera::SetWindow( int nWidth, int nHeight, float fArcballRadius )
{ 
	m_WorldArcBall.SetWindow( nWidth, nHeight, fArcballRadius ); 
	m_ViewArcBall.SetWindow( nWidth, nHeight, fArcballRadius ); 
}

void GFPSCamera::SetModelCenter( D3DXVECTOR3 vModelCenter ) 
{ 
	m_vModelCenter = vModelCenter;
}
GFPSCamera::GFPSCamera()
{		
	// 추가
	D3DXMatrixIdentity(&m_matRotY);
	m_vCameraDir			= D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_vPosDelta				= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	 
	m_fDefaultRadius		= 0.0f;
    m_fMinRadius			= 1.0f;
    m_fMaxRadius			= FLT_MAX;
	m_fRadius				= 0.0f;

	m_fCameraYawAngle		= 0.0f;
	m_fCameraPitchAngle		= 0.0f;
	m_fCameraRollAngle		= 0.0f;

	m_fSpeed				= 0.0f;

	// 추가
	m_nMouseWheelDelta		= 0;

	m_vModelCenter			= D3DXVECTOR3(0,0,0);

	D3DXMatrixIdentity( &m_matWorld );
    D3DXMatrixIdentity( &m_mModelRot );
    D3DXMatrixIdentity( &m_mModelLastRot );    
    D3DXMatrixIdentity( &m_mCameraRotLast );    

	m_nRotateModelButtonMask  = MOUSE_LEFT_BUTTON;
    m_nZoomButtonMask         = MOUSE_WHEEL;
    m_nRotateCameraButtonMask = MOUSE_RIGHT_BUTTON;


	D3DXMatrixIdentity( &m_matWorld );
	SetProjMatrix( D3DX_PI / 4.0f, 1.0f, 0.1f, 1000.0f );
	SetViewMatrix( D3DXVECTOR3( 0.0f, 0.0f, 10.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
}

GFPSCamera::~GFPSCamera()
{	
}
