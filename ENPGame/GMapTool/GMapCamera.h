#pragma once
#include "GCamera.h"

class GMapCamera : public GCamera
{
public:

	virtual bool				Frame() {
		if (g_InputData.bRightHold)
		{
			m_fCameraYawAngle += D3DXToRadian(g_InputData.iMouseValue[0] * 0.1f);
			m_fCameraPitchAngle += D3DXToRadian(g_InputData.iMouseValue[1] * 0.1f);
		}
		//// 카메라 이동 거리 = 속도 + ( 경과시간 * 마우스 휠 변위값 )
		//float fValue = g_InputData.iMouseValue[2];

		float fValue = 0.0f;
		float fDistance = m_fSpeed * fValue * g_fSecPerFrame;


		if (g_InputData.bLeftShift)	m_fSpeed += g_fSecPerFrame * 40.0f;
		else						m_fSpeed -= g_fSecPerFrame * 40.0f;		
		//if (g_InputData.bLeftBracket) 
		//	m_fSpeed += g_fSecPerFrame * 40.0f;		
		//if (g_InputData.bRightBracket) 
		//	m_fSpeed -= g_fSecPerFrame * 40.0f;
		// 최소값으로 고정
		if (m_fSpeed < 400.0f) m_fSpeed = 400.0f;

		if (g_InputData.bWKey) 	MoveLook(g_fSecPerFrame * 5.0f * m_fSpeed);
		if (g_InputData.bSKey)		MoveLook(-g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bDKey)		MoveSide(g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bAKey)		MoveSide(-g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bQKey)		MoveUp(g_fSecPerFrame * 5.0f* m_fSpeed);
		if (g_InputData.bEKey)		MoveUp(-g_fSecPerFrame * 5.0f* m_fSpeed);

		Update(D3DXVECTOR4(m_fCameraPitchAngle, m_fCameraYawAngle, m_fCameraRollAngle, fDistance));
		UpdateVector();
		return true;
	}
	GMapCamera();
	virtual ~GMapCamera();
};

