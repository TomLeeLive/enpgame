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
#define G_DEFINE_ANI_ZOMB_FLW L"ZOMBIE_FOLLOW"

#define G_DEFINE_MAX_AI_ZOMBIE  1
#define SPEED 30.0f




//공통 사용 헤더
#include "GCamera.h"
#include "GTimer.h"

#include "GModel.h"
#include "GZombie.h"
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


#include "GNewZombie.h"
#include "GObjMgr.h"

//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"
#include <time.h>

