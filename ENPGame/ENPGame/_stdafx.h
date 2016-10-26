#ifndef _STDAFX_H_ //��Ŭ��� ���� #pragma once �� ������ ��.
#define	 _STDAFX_H_


//�� ��ɺ� �ڵ� �ְ�/���� �뵵 for debugging
#define G_MACRO_MAP_ADD		1
#define G_MACRO_EFFECT_ADD   1
#define G_MACRO_CHAR_ADD     1


//���� ��� ���
#include "GCamera.h"
#include "GTimer.h"

//ĳ����
#ifdef G_MACRO_CHAR_ADD
#include "GTemplate.h"
#include "GParser.h"
#include "GObjMgr.h"
#include "GObject.h"
#include "GCharacter.h"
#include "GCharMgr.h"
#include "GHeroObj.h"
#endif

//��
#ifdef G_MACRO_MAP_ADD
#include "GMiniMap.h"
#include "map/GNoiseMap.h"
#include "map/GQuadTreeIndex.h"
#include "map/GMapObject.h"
#endif

//����Ʈ
#ifdef G_MACRO_EFFECT_ADD
#include "GSprite.h"
#endif

//Main
#include "GBasisLib_0.h"
#include "GProjMain.h"

#endif
