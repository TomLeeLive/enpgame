#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif
#define G_DEFINE_ANI_ZOMB_DIE L"ZOMBIE_DIE"
#define G_DEFINE_ANI_ZOMB_ATT L"ZOMBIE_ATTACK"
#define G_DEFINE_ANI_ZOMB_WLK L"ZOMBIE_WALK"
#define G_DEFINE_ANI_ZOMB_IDL L"ZOMBIE_IDLE"
#define G_DEFINE_ANI_ZOMB_FLW L"ZOMBIE_WALK"

#define G_DEFINE_MAX_AI_ZOMBIE  4
#define G_DEFINE_AI_ALMOST_ZERO	0.2f
#define G_DEFINE_AI_MOVE_COOLTIME 3.0f
#define G_DEFINE_AI_FOLLOW_CHECK 70.0f
#define G_DEFINE_AI_ATTACK_CHECK 30.0f
#define G_DEFINE_AI_MOVE_SPEED 50.0f
#define G_DEFINE_AI_TEST_HERO_SPEED 100.0f



//공통 사용 헤더
#include "GCamera.h"
#include "GTimer.h"

#include "GCharacter.h"
#include "GAISeq.h"
#include "GAIIdle.h"
#include "GAIMove.h"
#include "GAIFollow.h"
#include "GAIDie.h"
#include "GAIAttack.h"

#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"

#include "GModel.h"
#include "GZombie.h"
#include "GNewZombie.h"
#include "GObjMgr.h"

#include <time.h>
//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"


