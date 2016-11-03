#pragma once
#include "GObjStd.h"
#include "GMesh.h"

class GAnimation
{
public:
	D3DXMATRIX	Interpolate(GMesh* pMesh, D3DXMATRIX* matParents, float fFrameTick, GScene tScene);
	D3DXMATRIX	Update(float fElapseTime, GMesh* pMesh, D3DXMATRIX &matWorld, GScene &tScene);
	bool		GetAnimationTrack(float fFrame, vector<shared_ptr<GAnimTrack>>& pTrackList, GAnimTrack** pStartTrack, GAnimTrack** pEndTrack);
public:
	GAnimation(void);
	virtual ~GAnimation(void);
};

