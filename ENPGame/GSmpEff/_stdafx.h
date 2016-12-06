#pragma once
#include "GCoreLibV2.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GEffectCore32d.lib" )
#else
#pragma comment( lib, "GEffectCore32.lib" )
#endif

//#include "KEffect.h"
#include "EffManager.h"
#include "GCamera.h"
#include "GProjMain.h"

