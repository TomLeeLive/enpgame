#pragma once

#define G_DEFINE_ANI_ZOMB_DIE L"ZOMBIE_DIE"
#define G_DEFINE_ANI_ZOMB_ATT L"ZOMBIE_ATTACK"
#define G_DEFINE_ANI_ZOMB_WLK L"ZOMBIE_WALK"
#define G_DEFINE_ANI_ZOMB_IDL L"ZOMBIE_IDLE"
#define G_DEFINE_ANI_ZOMB_FLW L"ZOMBIE_WALK"

#define G_DEFINE_MAX_AI_ZOMBIE  4
#define G_DEFINE_CHAR_Y_POS 40.0f;
#define G_DEFINE_AI_ALMOST_ZERO	0.2f
#define G_DEFINE_AI_MOVE_COOLTIME 3.0f
#define G_DEFINE_AI_FOLLOW_CHECK 100.0f
#define G_DEFINE_AI_ATTACK_CHECK 70.0f
#define G_DEFINE_AI_MOVE_SPEED 50.0f
#define G_DEFINE_AI_TEST_HERO_SPEED 100.0f

enum G_ZOMB_AI_ST {
	G_ZOMB_AI_ST_IDLE = 0,
	G_ZOMB_AI_ST_WALK,
	G_ZOMB_AI_ST_ATTACK,
	G_ZOMB_AI_ST_DEAD,
	G_ZOMB_AI_ST_FOLLOW,
	G_ZOMB_AI_ST_CNT
};

enum G_AI {
	G_AI_IDLE = 0,
	G_AI_MOVE,
	G_AI_ATTACK,
	G_AI_DIE,
	G_AI_FOLLOW,
	G_AI_CNT
};

#include "GCamera.h"
#include "GTimer.h"


#include "GCharacter.h"
#include "GModel.h"
#include "GZombie.h"
#include "GNewZombie.h"
#include "GObjMgr.h"
#include "GAIZombieMgr.h"

#include "GAISeq.h"
#include "GAIIdle.h"
#include "GAIMove.h"
#include "GAIFollow.h"
#include "GAIDie.h"
#include "GAIAttack.h"

#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"