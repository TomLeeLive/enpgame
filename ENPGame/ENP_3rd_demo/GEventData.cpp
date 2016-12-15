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

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 �༺�� �����Ͽ��µ�. �ƹ��� ���� ��? �̻������� ������ ����.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"�ƹ����� ������ ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ���� ���� �־� �ʹ� ���� ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	m_vecEvent.push_back(pEvent1);

	return true;
}
GEvent::GEvent() {

}