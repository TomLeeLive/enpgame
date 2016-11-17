#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

enum G_ZOMBIE_AI_ST {
	G_ZOMBIE_AI_ST_WALK = 0,
	G_ZOMBIE_AI_ST_IDLE,
	G_ZOMBIE_AI_ST_ATTACK,
	G_ZOMBIE_AI_ST_DIE,
	G_ZOMBIE_AI_ST_CNT
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

