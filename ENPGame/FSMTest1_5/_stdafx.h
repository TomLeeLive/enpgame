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

#define G_DEFINE_MAX_AI_ZOMBIE  1

enum G_ZOMB_ST {
	G_ZOMB_ST_IDLE =0,
	G_ZOMB_ST_WALK,
	G_ZOMB_ST_ATTACK,
	G_ZOMB_ST_DEAD,
	G_ZOMB_ST_FOLLOW,
	G_ZOMB_ST_CNT
};



//공통 사용 헤더
#include "GCamera.h"
#include "GTimer.h"

#include "GSeq.h"
#include "GAIIdle.h"
#include "GAIMove.h"
#include "GAIFollow.h"
#include "GAIDie.h"
#include "GAIAttack.h"

#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"

#include "GModel.h"
#include "GNewZombie.h"
#include "GObjMgr.h"

//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"
#include <time.h>

