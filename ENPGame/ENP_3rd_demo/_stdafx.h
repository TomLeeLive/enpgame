#ifndef _STDAFX_H_ //��Ŭ��� ���� #pragma once �� ������ ��.
#define	 _STDAFX_H_


#if defined(_G_RELEASE)
#pragma comment( lib, "msvcrtd.lib")
#endif

#define GMAIN			g_pMain
#define GHINST			g_pMain->m_hInstance
#define GHWND			g_pMain->m_hWnd
#define GDEVICE			g_pMain->m_pd3dDevice
#define GCONTEXT		g_pMain->m_pImmediateContext


//�� ��ɺ� �ڵ� �ְ�/���� �뵵 for debugging
#define G_MACRO_GAME_ADD		1	//���� ���� ����
#define G_MACRO_MAP_ADD		1	//��
#define G_MACRO_EFFECT_ADD   1	//����Ʈ
#define G_MACRO_CHAR_ADD     1	//ĳ����

//������ define
#include "_values.h"

//���ҽ� ��� define
#include "_resources.h"

//���� ��� ���
#include "GSound.h"
#include "GCamera.h"
#include "GFPSCamera.h"
#include "GTimer.h"
#include "GDirectWrite.h"



//ĳ����
#ifdef G_MACRO_CHAR_ADD

#if defined(_DEBUG) || defined(DEBUG)
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
//#include "GHeroObj.h"
#include "GZombie.h"
#include "GN2Zombie.h"
#include "GHero.h"

#endif

//��
#ifdef G_MACRO_MAP_ADD

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif

//#include "GMiniMap.h"
//#include "map/GNoiseMap.h"
//#include "map/GQuadTreeIndex.h"
#include "GN2Skybox.h"
#include "map/GMap.h"
#include "map/GHeightMap.h"
#include "map/GQuadTree.h"
#include "map/GMapObject.h"
#endif

//����Ʈ
#ifdef G_MACRO_EFFECT_ADD

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment( lib, "GEffectCore32d.lib" )
#else
#pragma comment( lib, "GEffectCore32.lib" )
#endif

#include "GSprite.h"
#endif

//UI
#include "GUIManager.h"

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
