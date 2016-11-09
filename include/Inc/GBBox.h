#ifndef __COLLISIONDETECTION_HPP
#define __COLLISIONDETECTION_HPP

#include "GCoreStd.h"
#include "GShape.h"

#define fc_fabs fabsf

typedef	float real;

class GBBox
{
private:
	D3DXVECTOR4 m_vColor;
	shared_ptr<GShape>						m_pLine;
public:
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;

	real		center[3];
	real		axis[3][3];//transformation matrix
	real		extent[3];//half full size-eqivalent to radius not diameter
	real		translation[3];// translation vector
 void GetTransform(real t[16])
 {
  t[0]=axis[0][0];
  t[1]=axis[0][1];
  t[2]=axis[0][2];
  t[3]=((real)0.0);
  t[4]=axis[1][0];
  t[5]=axis[1][1];
  t[6]=axis[1][2];
  t[7]=((real)0.0);
  t[8]=axis[2][0];
  t[9]=axis[2][1];
  t[10]=axis[2][2];
  t[11]=((real)0.0);
  t[12]=translation[0];
  t[13]=translation[1];
  t[14]=translation[2];
  t[15]=((real)1.0);
 }
 // 추가함.
 bool Init(D3DXVECTOR3 &min, D3DXVECTOR3 &max);
 bool Frame(D3DXMATRIX* mat);
 bool Render(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
 bool Release();
};

namespace GBBOXFUNC {
	int BoxBoxIntersectionTest(const GBBox& box0, const GBBox& box1);
	inline real DotProduct(const real v0[3], const real v1[3]);
	// bounding box 관련 함수들
	D3DXMATRIX* GetBoxTransform(D3DXMATRIX *pMat, GBBox* pBox);
	void SetBoxTransform(const D3DXMATRIX *pMat, GBBox* pBox);
	void initBox(GBBox *pBox, const D3DXVECTOR3& vecMin, const D3DXVECTOR3& vecMax);
	void moveBox(GBBox *pBox, const D3DXMATRIX& mat);
}



#endif//of #ifndef __COLLISIONDETECTION_HPP
