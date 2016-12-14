#pragma once
#include "GCoreStd.h"
//���� [Start]
struct LIGHT_CONSTANT_BUFFER
{
	D3DXMATRIX			g_matInvWorld;
	// Material
	D3DXVECTOR4			g_cAmbientMaterial;
	D3DXVECTOR4			g_cDiffuseMaterial;
	D3DXVECTOR4			g_cSpecularMaterial;
	D3DXVECTOR4			g_cEmissionMaterial;
	// Light
	D3DXVECTOR4			g_cAmbientLightColor;
	D3DXVECTOR4			g_cDiffuseLightColor;
	D3DXVECTOR4			g_cSpecularLightColor;
	D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : ����
	D3DXVECTOR4			g_vLightPos; // w = light radius
	D3DXVECTOR4			g_vEyeDir;// w = light intensity : ����
	D3DXVECTOR4			g_vEyePos;// w = light radius	
};
//���� [End]

enum G_LIGHT_TYPE {
	G_LIGHT_TYPE_DIFFUSE = 0,
	G_LIGHT_TYPE_SPECULAR = 1,
	G_LIGHT_TYPE_CNT
};