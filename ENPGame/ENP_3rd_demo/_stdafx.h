#ifndef _STDAFX_H_ //인클루드 가드 #pragma once 와 동일한 것.
#define	 _STDAFX_H_


#if defined(_G_RELEASE)
#pragma comment( lib, "msvcrtd.lib")
#endif

#define GMAIN			g_pMain
#define GHINST			g_pMain->m_hInstance
#define GHWND			g_pMain->m_hWnd
#define GDEVICE			g_pMain->m_pd3dDevice
#define GCONTEXT		g_pMain->m_pImmediateContext


//각 기능별 코드 넣고/빼고 용도 for debugging
#define G_MACRO_GAME_ADD		1	//게임 로직 관련
#define G_MACRO_MAP_ADD		1	//맵
#define G_MACRO_EFFECT_ADD   1	//이펙트
#define G_MACRO_CHAR_ADD     1	//캐릭터

//설정값 define
#include "_values.h"

//리소스 경로 define
#include "_resources.h"

//공통 사용 헤더
#include "GSound.h"
#include "GCamera.h"
#include "GFPSCamera.h"
#include "GTimer.h"
#include "GDirectWrite.h"



//캐릭터
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

//맵
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

//이펙트
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

//게임 플로우에 따른 각시퀀스를 GSeq 클래스를 상속하여 구현한다.(공통구조) FSM 쓰려고 함.
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
