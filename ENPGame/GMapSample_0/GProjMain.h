#pragma once
//#define G_MACRO_MAP_ADD		1
#define G_MACRO_MAP_2_ADD		2

#ifdef G_MACRO_MAP_ADD
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d.lib" )
#else
#pragma comment( lib, "GMapCore32.lib" )
#endif
#endif

#ifdef G_MACRO_MAP_2_ADD
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "GMapCore32d_2.lib" )
#else
#pragma comment( lib, "GMapCore32_2.lib" )
#endif
#endif

#include "GCoreLibV2.h"

class GProjMain : public GCoreLibV2
{
public:
	GProjMain();
	virtual ~GProjMain();
};

