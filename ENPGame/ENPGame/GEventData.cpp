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

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 �༺�� �����Ͽ��µ�. �ƹ��� ���� ��? �̻������� ������ ����.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"�ƹ����� ������ ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ���� ���� �־� �ʹ� ���� ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEventData>(D3DXVECTOR3(-2177.0f, 40.0f, -1092.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� �ָ� �������ΰ�?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"�ƴϾ� ���� �̻���.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"������ �������� ����.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEventData>(D3DXVECTOR3(2139.0f, 40.0f, 982.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ������� �̻��ϰ� ���߾�...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"����� ��ӽ����� ������ �̵�����.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"�������ڱ�!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	m_vecEvent.push_back(pEvent3);




	auto pEvent4 = make_shared<GEventData>(D3DXVECTOR3(3944.0f, 40.0f, 3762.0f));

	auto pEvent4_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ���������� 4�� ��ǥ���� ���� �帮�ڽ��ϴ�.");
	pEvent4->m_vecScript.push_back(pEvent4_Script1);
	auto pEvent4_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"������ �ٽ� ������~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script2);
	auto pEvent4_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"�ȳ�~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script3);

	m_vecEvent.push_back(pEvent4);


	return true;
}
GEvent::GEvent() {

}