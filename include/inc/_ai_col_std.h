#pragma once

#define G_DEFINE_ANI_COL_DIE L"HERO2_DIE"
#define G_DEFINE_ANI_COL_ATT L"HERO2_ATTACK"
#define G_DEFINE_ANI_COL_WLK L"HERO2_WALK"
#define G_DEFINE_ANI_COL_IDL L"HERO2_IDLE"
#define G_DEFINE_ANI_COL_FLW L"HERO2_RUN"

#define G_DEFINE_MAX_AI_COL  4
#define G_DEFINE_CHAR_COL_Y_POS 36.2f;
#define G_DEFINE_AI_COL_ALMOST_ZERO	0.2f
#define G_DEFINE_AI_COL_MOVE_COOLTIME 3.0f
#define G_DEFINE_AI_COL_IDLE_CHECK 50.0f
#define G_DEFINE_AI_COL_FOLLOW_CHECK 100.0f
#define G_DEFINE_AI_COL_ATTACK_CHECK 40.0f
#define G_DEFINE_AI_COL_MOVE_SPEED 180.0f
#define G_DEFINE_AI_TEST_COL_HERO_SPEED 100.0f

enum G_COL_AI_ST {
	G_COL_AI_ST_IDLE = 0,
	G_COL_AI_ST_WALK,
	G_COL_AI_ST_ATTACK,
	G_COL_AI_ST_DEAD,
	G_COL_AI_ST_FOLLOW,
	G_COL_AI_ST_CNT
};

enum G_AI_COL {
	G_AI_COL_IDLE = 0,
	G_AI_COL_MOVE,
	G_AI_COL_ATTACK,
	G_AI_COL_ESCAPE,
	G_AI_COL_FOLLOW,
	G_AI_COL_CNT
};

#include "GCamera.h"
#include "GTimer.h"


#include "GCharacter.h"
#include "GModel.h"
//#include "GZombie.h"
#include "GHero.h"
#include "GAICol.h"
#include "GObjMgr.h"
#include "GAIColMgr.h"

#include "GAIColSeq.h"
#include "GAIColIdle.h"
#include "GAIColMove.h"
#include "GAIColFollow.h"
#include "GAIColEscape.h"
#include "GAIColAttack.h"

#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"