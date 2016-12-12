#include "TMatrixEx.h"

GMatrix TMatrixEx::CreateMatrixShadowD( Vector4* pPlane, 
										Vector4* pLight)
{
	pPlane->Normal();	
	Vector3 vPlane, vLight;
	vPlane = Vector3( pPlane->x, pPlane->y, pPlane->z );			
	vLight = Vector3( -pLight->x, -pLight->y, -pLight->z );	
	
	float b = *pPlane | *pLight;
	_11 = b-vPlane.x * pLight->x;	
	_12 = -vPlane.x * pLight->y;	
	_13 = -vPlane.x * pLight->z;	
	_14 = 0;
	_21 = -vPlane.y * pLight->x;	
	_22 = b-vPlane.y * pLight->y;	
	_23 = -vPlane.y * pLight->z;	
	_24 = 0;	
	_31 = -vPlane.z * pLight->x;	
	_32 = -vPlane.z * pLight->y;	
	_33 = b-vPlane.z * pLight->z;	
	_34 = 0;
	_41 = -pPlane->w * pLight->x;	
	_42 = -pPlane->w * pLight->y;	
	_43 = -pPlane->w * pLight->z;	
	_44 = b;
	return *this;
}
GMatrix TMatrixEx::CreateMatrixShadow( Vector4* pPlane, 
											 Vector4* pLight)
{
	//pPlane->Normal();	
	//Vector3 vPlane, vLight;
	//vPlane = Vector3( pPlane->x, pPlane->y, pPlane->z ) * -1.0f;
	//vLight = Vector3( pLight->x, pLight->y, pLight->z );// 라이트 디렉션이 바뀌지 않는다.
	//float b = (vPlane | Vector3(0.0f, -pPlane->w, 0.0f));
	//float a = vPlane | vLight;	
	//float D = b - a;
	//float c = *pPlane | *pLight;
	//_11 = vPlane.x * pLight->x+D;	_12 = vPlane.x * pLight->y;	
	//_13 = vPlane.x * pLight->z;	_14 = vPlane.x * pLight->w;
	//_21 = vPlane.y * pLight->x;	_22 = vPlane.y * pLight->y+D;	
	//_23 = vPlane.y * pLight->z;	_24 = vPlane.y * pLight->w;	
	//_31 = vPlane.z * pLight->x;	_32 = vPlane.z * pLight->y;	
	//_33 = vPlane.z * pLight->z+D;	_34 = vPlane.z * pLight->w;
	////_41 = -(a+D) * pLight->x;	_42 = -(a+D) * pLight->y;	
	////_43 = -(a+D) * pLight->z;	_44 = -a;
	//_41 = -pPlane->w * pLight->x;	_42 = -pPlane->w * pLight->y;	
	//_43 = -pPlane->w * pLight->z;	_44 = -a;
	//return *this;
		
	GMatrix mat;
	Vector4 plane,light;
	pPlane->Normal();	
	plane = (*pPlane) * -1.0f;
	light = (*pLight);// * -1.0f;
	float D = -(plane | light);	
	mat._11 = plane.x * light.x+D;	mat._12 = plane.x * light.y;	mat._13 = plane.x * light.z;	mat._14 = plane.x * light.w;
	mat._21 = plane.y * light.x;	mat._22 = plane.y * light.y+D;	mat._23 = plane.y * light.z;	mat._24 = plane.y * light.w;	
	mat._31 = plane.z * light.x;	mat._32 = plane.z * light.y;	mat._33 = plane.z * light.z+D;	mat._34 = plane.z * light.w;
	mat._41 = plane.w * light.x;	mat._42 = plane.w * light.y;	mat._43 = plane.w * light.z;	mat._44 = plane.w * light.w+D;
	return mat;
}
TMatrixEx::TMatrixEx(void)
{
}


TMatrixEx::~TMatrixEx(void)
{
}
