#ifndef _STDAFX_H_ //��Ŭ��� ���� #pragma once �� ������ ��.
#define	 _STDAFX_H_


#define GMAIN			g_pMain
#define GHINST			g_pMain->m_hInstance
#define GHWND			g_pMain->m_hWnd
#define GDEVICE			g_pMain->m_pd3dDevice
#define GCONTEXT		g_pMain->m_pImmediateContext


//�� ��ɺ� �ڵ� �ְ�/���� �뵵 for debugging
#define G_MACRO_MAP_ADD		1
#define G_MACRO_EFFECT_ADD   1
#define G_MACRO_CHAR_ADD     1



//���� ��� ���
#include "GCamera.h"
#include "GTimer.h"

//ĳ����
#ifdef G_MACRO_CHAR_ADD

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

#include "GTemplate.h"
#include "GParser.h"
#include "GObjMgr.h"
#include "GObject.h"
#include "GCharacter.h"
#include "GCharMgr.h"
#include "GHeroObj.h"
#endif

//��
#ifdef G_MACRO_MAP_ADD

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif

#include "map/GMap.h"
#endif

//����Ʈ
#ifdef G_MACRO_EFFECT_ADD

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GEffectCore32d.lib" )
#else
#pragma comment( lib, "GEffectCore32.lib" )
#endif

#include "GSprite.h"
#endif



//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"

#endif