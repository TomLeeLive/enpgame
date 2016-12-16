#include "_stdafx.h"



GEventData::GEventData()
{
	m_bDone = false;
	m_vEventPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


GEventData::~GEventData()
{
}

bool GEvent::init() {
	auto pEvent1 = make_shared<GEventData>(D3DXVECTOR3(-3052.0f, 40.0f, -3349.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 행성에 도착하였는데. 아무도 없는 걸? 이상하지만 전진해 보자.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아무래도 느낌이 안좋아.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"별일 없을 수도 있어 너무 걱정 하지마.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEventData>(D3DXVECTOR3(-2177.0f, 40.0f, -1092.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"저기 멀리 생존자인가?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아니야 뭔가 이상해.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"가까이 가보도록 하자.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEventData>(D3DXVECTOR3(2139.0f, 40.0f, 982.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"여기 사람들이 이상하게 변했어...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"가까운 드롭십으로 빠르게 이동하자.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"빨리가자구!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	m_vecEvent.push_back(pEvent3);




	auto pEvent4 = make_shared<GEventData>(D3DXVECTOR3(3944.0f, 40.0f, 3762.0f));

	auto pEvent4_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"다음 스테이지는 4차 발표에서 보여 드리겠습니다.");
	pEvent4->m_vecScript.push_back(pEvent4_Script1);
	auto pEvent4_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"다음에 다시 만나요~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script2);
	auto pEvent4_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"안녕~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script3);

	m_vecEvent.push_back(pEvent4);


	return true;
}
GEvent::GEvent() {

}