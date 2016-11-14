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
Bounding Box size�� initBox min max�� �Ѱܼ� ���ǵ��� �Ѵ�.
���Ŀ� ������ ������ ������ ��ȯmatrix�� ���ڷ�moveBox�� ȣ����CBox ��ü�� ������ �ش�.
������ ������ ��CBox�� �ٸ� CBox���� �浹�� �Ͼ����BoxBoxIntersectionTest�� �˻��Ѵ�.
*/


/*
�浹�� �Ͼ�� ��� ��鳢�� �´�Ҵ��� ã�� �ʿ䰡 �ִ�.
*/

class GBBox
{
public:
	//D3DXPLANE			m_Plane[G_OBB_SIDE_CNT];			//���
	//D3DXVECTOR4			m_vPlaneNormal[G_OBB_SIDE_CNT];		//����� ���� ����

	//shared_ptr<GShape>	m_pPlane[G_OBB_SIDE_CNT];
	D3DXVECTOR3			m_vPoint[8];
	G_PLANE				m_Plane[G_OBB_SIDE_CNT];

	D3DXVECTOR4			m_vColor;		//����
	shared_ptr<GShape>	m_pLine;		//����׿� ��.
public:
	float				m_fRadius;		//������
	D3DXVECTOR3			m_vMin;
	D3DXVECTOR3			m_vMax;

	D3DXVECTOR3			center; //Bounding box�� �߽� ��ǥ
	D3DXVECTOR3			axis[3];//transformation matrix. Bounding box�� 3���������� axis ����
	D3DXVECTOR3			extent;//half full size-eqivalent to radius not diameter. Bounding box�� �� axis ���� ���������� radius
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
 // �߰���.
 bool Init(D3DXVECTOR3 &min, D3DXVECTOR3 &max);
 bool Frame(D3DXMATRIX* mat);
 bool Render(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
 bool Release();
};

namespace GBBOXFUNC {
	bool IntersectTriangle(const D3DXVECTOR3& RayOrigin, const D3DXVECTOR3& RayDirection,
		D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, float& t, float& u, float& v);
	bool CheckValueValid(float fValue);
	D3DXVECTOR3 GetSlidingVector(GBBox* pBox, D3DXVECTOR3* vDir, D3DXVECTOR3* vIntersec); //�����̵����͸� ���ϴ� �Լ�
	bool RaytoBox(D3DXVECTOR3* vIntersec,GBBox* box, G_RAY* pRay);
	float CalcDistance(const D3DXVECTOR3* v1, const D3DXVECTOR3* v2);
	int ColCheck(const GBBox* box0, const GBBox* box1);
	int BoxBoxColCheck(const GBBox* box0, const GBBox* box1);			//�������� �̿��� �Ÿ� �׽�Ʈ�� OBB vs OBB
	int BoxBoxIntersectionTest(const GBBox& box0, const GBBox& box1);	//OBB vs OBB
	inline real DotProduct(const real v0[3], const real v1[3]);
	// bounding box ���� �Լ���
	D3DXMATRIX* GetBoxTransform(D3DXMATRIX *pMat, GBBox* pBox);
	void SetBoxTransform(const D3DXMATRIX *pMat, GBBox* pBox);
	void initBox(GBBox *pBox, const D3DXVECTOR3& vecMin, const D3DXVECTOR3& vecMax);
	void moveBox(GBBox *pBox, const D3DXMATRIX& mat);
}



#endif//of #ifndef __COLLISIONDETECTION_HPP


/*
<�̷� ����> http://thrillfighter.tistory.com/191
���� ������ �������� ���.(3�ܰ�� �Ѵ�.)
1.������ �ִ��� üũ. ������ ���⺤�Ϳ� ����� ���� ���͸� �����Ͽ� 0�� �Ǵ��� �˻�. 0�� �Ǵ� ��� ������ ����.
2.������ ���. ������ ����ϱ� ���ؼ� ������ �������� ����� �����Ŀ� �����Ͽ� �Ű����� t�� ����.
3.������ ����� ���� ����. ���� ������ ���� ����� ���� ���� �Ǵ�.

*/

/*
<�̷� ����>

Mesh�� ������ ��bounding box�� ���� �����Ͽ�, mesh��transform �� ��bounding box�� ����transform�� �� �ָ� �׻� ���mesh�� ����OBB�� ������ ���� �ִ�. �׷��ٸ� �츮�� ����mesh�� �����̸鼭 ���� ���ƴ��� ������OBB�� ���� �ִ�. �� ��, OBB�� ���� �浹�ߴ����� ��� ������ ���� ������? ���� ������ ����� �� ����OBB�� ��� ��� ���edge�� ���ؼ� ���� ����ϴ�edge�� �ִ��� �˻��ϴ� ����� ���̴�. �׷��� �� �����144���� �񱳰� �ʿ��ϰ�, ����� ��� �׽�Ʈ�̴�. ���⼭�� �ξ� �� ȿ������'axial projection'�� �̿��� �׽�Ʈ�� �Ұ��Ѵ�.

Axial projection �̶� �����ΰ�?

�� ����OBB�� ���� �и��Ǿ� �ִ����� �˱� ���� ���� ��� �� �ϳ���, ��OBB�� �������� � ��(�ݵ��x,y,z���� �ʿ�� ����)�� �����ϴ� ���̴�. �� ������'axial projection'�̶�� �ϸ�, �� ������ ���� ��OBB�� �� �� �interval�� �����Ѵ�. ���� �̷��� ������2����interval�� ���� ��ġ�� ������2����OBB�� ���� �и��Ǿ� �ִ� ���� Ȯ���ϸ�, �̶� �� ����'separating axis'��� �Ѵ�. ����2����interval�� ���� ��ģ�ٸ�2����OBB�� ���� �и��Ǿ� ���� ���� �ְ� �ƴ� ���� �ֱ� ������ �� ���� �˻簡 �ʿ��ϴ�.

2����OBB�� �浹�ߴ��� �˱� ���ؼ���axial projection�� �� �� �ؾ� �ϴ°�?

(����)
��������2���� �и���convex�� �ٰ���ü�� 1) �� ���� �ٰ���ü �� �ϳ��� ��� ��� ������ ��, �Ǵ�2) �� ���� �ٰ���ü �������� �ϳ���edge�� ������ �鿡 ���� �и��� �� �ִ�.

�� ������ ������ ���� �ֱ� ������, �װ��� �����ִ� ���� ã�� ���ð�. ��·�� �� ������ ����μ�, �츮�� ������ �� �� �ִ�:
��������2����convex�� �ٰ���ü�� �и��Ǳ� ���� �ʿ���� ������, 1) �� ���� �ٰ���ü �� �ϳ��� ��� ��� ������separating axis�� �����ϰų�, 2) �� ���� �ٰ���ü �������� �ϳ���edge�� ������separating axis�� �����ϴ� ���̴�.

��OBB��3����unique�� �� ������ �ְ�, 3����unique��edge ������ �ִ�. ���� ���� ������ �˻��ϱ� ���ؼ���15����separating axis�� �˻��ؾ� �Ѵ�.(�ϳ���OBB����3���� ��, �ٸ� OBB����3���� ��, 9����2����OBB����edge���� ����) ����2����OBB�� ���� �и��Ǿ� �ִٸ�(�浹���� �ʾҴٸ�) separating axis�� �ݵ�� �����ؾ� �ϰ� ������ �����15����axis �� �ϳ��� ��axis�� �Ǿ�� �Ѵ�. ����OBB���� �浹�ߴٸ�separating axis�� ���������� ���� ���̴�. ����, 2����OBB�� �浹 ���θ� �˻��ϱ� ���ؼ���15����seperating axis�� �˻�� ����ϴ�.

Separating axis �˻�� � ������� �� ���� �ִ°�?

�� �˻縦 �ϴ� �⺻���� ������ ������ ����:
1) ��OBB�� �߽��� �ش�axis�� �����Ѵ�.
2) ��OBB�� �ش�axis�� �����Ǿ���interval��radius(������ ��)�� ����Ѵ�.
3) ���� �ش�axis�� �������� ��OBB�� �߽� ������ �Ÿ��� ��OBB��interval radius�� �պ��� ũ��, �� ����OBB�� �и��� ������ �� �� �ִ�.

�ؿ� �ִ� �׸��� ���� ���ذ� �� ���� �� ���̴�. �׸�����A��B�� ����OBB�̰�B��A�κ���rotation R��translation T��ŭ �̵��� ��ġ�� �ִ�. A��B��half dimension(�Ǵ�radius) �� ����ai, bi�� ǥ���Ѵ�(i=1,2,3). A��B���� ��edge�� ������ �̷��axis�� ���� ���͸� ����Ai��Bi��� ǥ���Ѵ�(i=1,2,3). �̷��� �ؼ� ����6���� ���� ���͸�box axis��� ����. ���⼭ �ָ��� ����A��box axis��basis�� ����ϸ�, ȸ�� ��Ʈ����R��3����column��(��, x,y,z �������͸�transform ���� �� ������ ����)��3����Bi axis ���Ϳ� ���ٴ� ����̴�.
*/
