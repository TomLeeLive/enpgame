#pragma once

enum SNDRESOURCES {
	SND_BGM_1 = 0,
	SND_THEME = 1,
	SND_INTRO1 = 2,
	SND_BOOTS1 = 3,
	SND_BOOTS2 = 4,
	SND_BOOTS3 = 5,
	SND_BOOTS4 = 6,
	SND_SHOT1 = 7,
	SND_SHOT2 = 8,
	SND_RADIO = 9,
	SND_HIT_BY_ZOMBIE = 10,
	SND_DEAD_ZOMBIE = 11,
	SND_CLICK_BUTTON = 12,
	SND_RESOURCES_LAST
};
//오브젝트 위치
#define G_OBJ_LOC_LAB _T("data/object/lab/lab.GBS")
#define G_OBJ_LOC_DROPSHIP_LAND _T("data/object/dropship/dropship_land.GBS")
#define G_OBJ_LOC_CAR _T("data/object/car/car.GBS")
#define G_OBJ_LOC_FPS_SHOTGUN _T("data/object/fps_shotgun/shotgun3.GBS")

//오브젝트 매니저 등록 이름.
#define G_OBJ_NAME_LAB L"lab.GBS"
#define G_OBJ_NAME_DROPSHIP_LAND L"dropship_land.GBS"
#define G_OBJ_NAME_CAR L"car.GBS"

//셰이더 파일 위치
#define G_SHA_PLANE L"data/shader/plane.hlsl"
#define G_SHA_LINE L"data/shader/line.hlsl"
#define G_SHA_BOX L"data/shader/box.hlsl"
#define G_SHA_OBJ_DIFFUSE L"data/shader/Obj_Diffuse.hlsl"
#define G_SHA_OBJ_DIFFUSE_REVERSE L"data/shader/Obj_Diffuse_Rev.hlsl"
#define G_SHA_OBJ_SPECULAR L"data/shader/Obj_Specular.hlsl"
#define G_SHA_OBJ_SPECULAR_REVERSE L"data/shader/Obj_Specular_Rev.hlsl"
#define G_SHA_OBJ_SHADOW L"data/shader/Obj_DepthMapShadow.hlsl"

#define G_SHA_MAP_SHADOW L"data/shader/CustomizeMap_shadow.hlsl"