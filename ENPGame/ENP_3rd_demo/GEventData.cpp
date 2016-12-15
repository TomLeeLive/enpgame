#include "_stdafx.h"



GEventData::GEventData()
{
	m_vEventPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


GEventData::~GEventData()
{
}

bool GEvent::init() {
	auto pEvent1 = make_shared<GEventData>(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 행성에 도착하였는데. 아무도 없는 걸? 이상하지만 전진해 보자.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아무래도 느낌이 안좋아.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"별일 없을 수도 있어 너무 걱정 하지마.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	m_vecEvent.push_back(pEvent1);

	return true;
}
GEvent::GEvent() {

}