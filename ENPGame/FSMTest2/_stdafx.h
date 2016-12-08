#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GCharCore32d.lib" )	
#else
#pragma comment( lib, "GCharCore32.lib" )
#endif

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GAICore32d.lib" )	
#else
#pragma comment( lib, "GAICore32.lib" )
#endif


//���� ��� ���
#include "GCamera.h"
#include "GTimer.h"

#include "_ai_std.h"


#include <time.h>
//Main
#include "GCoreLibV2.h"
#include "GProjMain.h"


