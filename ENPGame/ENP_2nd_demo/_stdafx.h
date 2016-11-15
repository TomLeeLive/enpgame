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

//#include "GMiniMap.h"
//#include "map/GNoiseMap.h"
//#include "map/GQuadTreeIndex.h"
#include "GN2Skybox.h"
#include "map/GMap.h"
#include "map/GQuadTree.h"
#include "map/GMapObject.h"
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

//���� �÷ο쿡 ���� ���������� GSeq Ŭ������ ����Ͽ� �����Ѵ�.(���뱸��) FSM ������ ��.
#include "GSeq.h"
#include "GSeqGameEnd.h"
#include "GSeqGameOver.h"
#include "GSeqHowTo.h"
#include "GSeqIntro.h"
#include "GSeqMenu.h"
#include "GSeqSinglePlay.h"
#include "GSeqSurvivalMode.h"

//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"

#endif
