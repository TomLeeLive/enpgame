#ifndef __COLLISIONDETECTION_HPP
#define __COLLISIONDETECTION_HPP

#include "GCoreStd.h"
#include "GShape.h"
#include "GSelect.h"

#define fc_fabs fabsf

#define G_MACRO_INVALID_FLOAT 999999.0f

enum G_OBB_SIDE{
	G_OBB_UP = 0,
	G_OBB_DOWN,
	G_OBB_LEFT,
	G_OBB_RIGHT,
	G_OBB_FRONT,
	G_OBB_BACK,
	G_OBB_SIDE_CNT
};

typedef	float real;

/*
Bounding Box size를 initBox min max로 넘겨서 계산되도록 한다.
이후에 문제가 움직일 때마다 변환matrix를 인자로moveBox를 호출해CBox 객체를 갱신해 준다.
움직일 때마다 그CBox와 다른 CBox들이 충돌이 일어났는지BoxBoxIntersectionTest로 검사한다.
*/


/*
충돌이 일어나면 어느 평면끼리 맞닿았는지 찾을 필요가 있다.
*/

class GBBox
{
public:
	//D3DXPLANE			m_Plane[G_OBB_SIDE_CNT];			//평면
	//D3DXVECTOR4			m_vPlaneNormal[G_OBB_SIDE_CNT];		//평면의 법선 벡터

	//shared_ptr<GShape>	m_pPlane[G_OBB_SIDE_CNT];
	D3DXVECTOR3			m_vPoint[8];
	G_PLANE				m_Plane[G_OBB_SIDE_CNT];

	D3DXVECTOR4			m_vColor;		//선색
	shared_ptr<GShape>	m_pLine;		//디버그용 선.
public:
	float				m_fRadius;		//반지름
	D3DXVECTOR3			m_vMin;
	D3DXVECTOR3			m_vMax;

	D3DXVECTOR3			center; //Bounding box의 중심 좌표
	D3DXVECTOR3			axis[3];//transformation matrix. Bounding box의 3방향으로의 axis 벡터
	D3DXVECTOR3			extent;//half full size-eqivalent to radius not diameter. Bounding box의 각 axis 벡터 방향으로의 radius
	D3DXVECTOR3			translation;// translation vector
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
	bool IntersectTriangle(const D3DXVECTOR3& RayOrigin, const D3DXVECTOR3& RayDirection,
		D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, float& t, float& u, float& v);
	bool CheckValueValid(float fValue);
	D3DXVECTOR3 GetSlidingVector(GBBox* pBox, D3DXVECTOR3* vDir, D3DXVECTOR3* vIntersec); //슬라이딩벡터를 구하는 함수
	bool RaytoBox(D3DXVECTOR3* vIntersec,GBBox* box, G_RAY* pRay);
	float CalcDistance(const D3DXVECTOR3* v1, const D3DXVECTOR3* v2);
	int ColCheck(const GBBox* box0, const GBBox* box1);
	int BoxBoxColCheck(const GBBox* box0, const GBBox* box1);			//반지름을 이용한 거리 테스트후 OBB vs OBB
	int BoxBoxIntersectionTest(const GBBox& box0, const GBBox& box1);	//OBB vs OBB
	inline real DotProduct(const real v0[3], const real v1[3]);
	// bounding box 관련 함수들
	D3DXMATRIX* GetBoxTransform(D3DXMATRIX *pMat, GBBox* pBox);
	void SetBoxTransform(const D3DXMATRIX *pMat, GBBox* pBox);
	void initBox(GBBox *pBox, const D3DXVECTOR3& vecMin, const D3DXVECTOR3& vecMax);
	void moveBox(GBBox *pBox, const D3DXMATRIX& mat);
}



#endif//of #ifndef __COLLISIONDETECTION_HPP


/*
<이론 설명> http://thrillfighter.tistory.com/191
평면과 직선의 교차관계 계산.(3단계로 한다.)
1.교점이 있는지 체크. 직선의 방향벡터와 평면의 법선 벡터를 내적하여 0이 되는지 검사. 0이 되는 경우 교점은 없다.
2.교점의 계산. 교점을 계산하기 위해서 직선의 방정식을 평면의 방정식에 대입하여 매개변수 t를 구함.
3.직선과 평면의 교차 관계. 유한 직선과 유한 평면의 교차 여부 판단.

*/

/*
<이론 설명>

Mesh를 생성할 때bounding box도 같이 생성하여, mesh를transform 할 때bounding box도 같이transform을 해 주면 항상 모든mesh에 대해OBB를 유지할 수가 있다. 그렇다면 우리는 이제mesh가 움직이면서 같이 돌아댕기는 여럿의OBB를 갖고 있다. 이 때, OBB가 서로 충돌했는지는 어떻게 감지할 수가 있을까? 가장 무식한 방법은 두 개의OBB의 모든 면과 모든edge에 대해서 면을 통과하는edge가 있는지 검사하는 방식일 것이다. 그런데 이 방식은144번의 비교가 필요하고, 상당히 비싼 테스트이다. 여기서는 훨씬 더 효율적인'axial projection'을 이용한 테스트를 소개한다.

Axial projection 이란 무엇인가?

두 개의OBB가 서로 분리되어 있는지를 알기 위한 쉬운 방법 중 하나는, 각OBB를 공간상의 어떤 축(반드시x,y,z축일 필요는 없다)에 투영하는 것이다. 이 투영을'axial projection'이라고 하며, 이 투영을 통해 각OBB는 축 상에 어떤interval을 형성한다. 만일 이렇게 형성된2개의interval이 서로 겹치지 않으면2개의OBB는 서로 분리되어 있는 것이 확실하며, 이때 이 축을'separating axis'라고 한다. 만일2개의interval이 서로 겹친다면2개의OBB는 서로 분리되어 있을 수도 있고 아닐 수도 있기 때문에 더 많은 검사가 필요하다.

2개의OBB가 충돌했는지 알기 위해서는axial projection을 몇 번 해야 하는가?

(공리)
공간상의2개의 분리된convex한 다각면체는 1) 두 개의 다각면체 중 하나의 어느 면과 평행인 면, 또는2) 두 개의 다각면체 각각에서 하나의edge와 평행한 면에 의해 분리될 수 있다.

이 공리를 증명한 논문도 있긴 하지만, 그것은 관심있는 분은 찾아 보시고. 어쨌든 이 공리의 결과로서, 우리는 다음을 알 수 있다:
공간상의2개의convex한 다각면체가 분리되기 위한 필요충분 조건은, 1) 두 개의 다각면체 중 하나의 어느 면과 수직인separating axis가 존재하거나, 2) 두 개의 다각면체 각각에서 하나의edge와 수직인separating axis가 존재하는 것이다.

각OBB는3개의unique한 면 방향이 있고, 3개의unique한edge 방향이 있다. 따라서 위의 조건을 검사하기 위해서는15개의separating axis를 검사해야 한다.(하나의OBB에서3개의 면, 다른 OBB에서3개의 면, 9개의2개의OBB에서edge들의 조합) 만일2개의OBB가 서로 분리되어 있다면(충돌하지 않았다면) separating axis가 반드시 존재해야 하고 위에서 언급한15개의axis 중 하나가 그axis가 되어야 한다. 만일OBB들이 충돌했다면separating axis가 존재하지를 않을 것이다. 따라서, 2개의OBB의 충돌 여부를 검사하기 위해서는15개의seperating axis의 검사로 충분하다.

Separating axis 검사는 어떤 방식으로 할 수가 있는가?

이 검사를 하는 기본적인 전략은 다음과 같다:
1) 각OBB의 중심을 해당axis에 투영한다.
2) 각OBB가 해당axis에 투영되었을interval의radius(길이의 반)을 계산한다.
3) 만일 해당axis에 투영했을 때OBB의 중심 사이의 거리가 각OBB의interval radius의 합보다 크면, 두 개의OBB는 분리된 것으로 볼 수 있다.

밑에 있는 그림을 보면 이해가 더 쉽게 갈 것이다. 그림에서A와B는 각각OBB이고B는A로부터rotation R과translation T만큼 이동한 위치에 있다. A와B의half dimension(또는radius) 는 각각ai, bi로 표기한다(i=1,2,3). A와B에서 각edge와 평행을 이루는axis의 단위 벡터를 각각Ai와Bi라고 표기한다(i=1,2,3). 이렇게 해서 생긴6개의 단위 벡터를box axis라고 하자. 여기서 주목할 것은A의box axis를basis로 사용하면, 회전 매트릭스R의3개의column들(즉, x,y,z 단위벡터를transform 했을 때 나오는 벡터)이3개의Bi axis 벡터와 같다는 사실이다.
*/
