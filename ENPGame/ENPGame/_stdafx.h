#ifndef _STDAFX_H_ //인클루드 가드 #pragma once 와 동일한 것.
#define	 _STDAFX_H_


//각 기능별 코드 넣고/빼고 용도 for debugging
#define G_MACRO_MAP_ADD		1
#define G_MACRO_EFFECT_ADD   1
#define G_MACRO_CHAR_ADD     1


//공통 사용 헤더
#include "GCamera.h"
#include "GTimer.h"

//캐릭터
#ifdef G_MACRO_CHAR_ADD
#include "GTemplate.h"
#include "GParser.h"
#include "GObjMgr.h"
#include "GObject.h"
#include "GCharacter.h"
#include "GCharMgr.h"
#include "GHeroObj.h"
#endif

//맵
#ifdef G_MACRO_MAP_ADD
#include "GMiniMap.h"
#include "map/GNoiseMap.h"
#include "map/GQuadTreeIndex.h"
#include "map/GMapObject.h"
#endif

//이펙트
#ifdef G_MACRO_EFFECT_ADD
#include "GSprite.h"
#endif

//Main
#include "GBasisLib_0.h"
#include "GProjMain.h"

#endif
