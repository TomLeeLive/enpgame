#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

//공통 사용 헤더
#include "GCamera.h"
#include "GTimer.h"

#include "GSeq.h"
#include "GAIIdle.h"
#include "GAIMove.h"
#include "GAIDie.h"
#include "GAIAttack.h"

#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"

#include "GModel.h"
#include "GZombie.h"
#include "GObjMgr.h"

//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"

