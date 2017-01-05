#include "_stdafx.h"



GEvent::GEvent()
{
	m_bDone = false;
	m_vEventPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


GEvent::~GEvent()
{
}

bool GStage::init() {



	return true;
}
GStage::GStage() {

}
bool GEventMgr::initStage1(shared_ptr<GStage>* pStage) {

	//Stage 1 [START]
	auto pEvent1 = make_shared<GEvent>(D3DXVECTOR3(-3052.0f, 40.0f, -3349.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 �༺�� �����Ͽ��µ�. �ƹ��� ���� ��? �̻������� ������ ����.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"�ƹ����� ������ ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ���� ���� �־� �ʹ� ���� ������.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEvent>(D3DXVECTOR3(-2177.0f, 40.0f, -1092.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� �ָ� �������ΰ�?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"�ƴϾ� ���� �̻���.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"������ �������� ����.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEvent>(D3DXVECTOR3(2139.0f, 40.0f, 982.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ������� �̻��ϰ� ���߾�...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"����� ��ӽ����� ������ �̵�����.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"�������ڱ�!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent3);




	auto pEvent4 = make_shared<GEvent>(D3DXVECTOR3(3944.0f, 40.0f, 3762.0f));

	auto pEvent4_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"���� ���������� 4�� ��ǥ���� ���� �帮�ڽ��ϴ�.");
	pEvent4->m_vecScript.push_back(pEvent4_Script1);
	auto pEvent4_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"������ �ٽ� ������~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script2);
	auto pEvent4_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"�ȳ�~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent4);
	//Stage 1 [END]

	T_STR strFile;
	strFile = L"data/map/stage_1_2.map";
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.LoadMap(&strFile, ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera, g_pMain);

	return true;
}
bool GEventMgr::initStage2(shared_ptr<GStage>* pStage) {

	return true;
}
bool GEventMgr::initStage3(shared_ptr<GStage>* pStage) {

	return true;
}
bool GEventMgr::init() {


	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.Init(g_pMain);
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera = ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pFPSCamera[((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_CurrentHero].get();






	auto pStage1 = make_shared<GStage>();//shared_ptr<GEvent>* pStage1
	auto pStage2 = make_shared<GStage>();
	auto pStage3 = make_shared<GStage>();
	
	initStage1(&pStage1);

	initStage2(&pStage2);
	
	initStage3(&pStage3);

	m_vecStage.push_back(pStage1);
	m_vecStage.push_back(pStage2);
	m_vecStage.push_back(pStage3);




	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.m_iMapSelected = 0;


	return true;
}

bool GEventMgr::frame(GSeqSinglePlay* pGame) {

	D3DXVECTOR3 vHeroPos = D3DXVECTOR3(pGame->m_CharHero[pGame->m_CurrentHero]->m_matWorld._41, pGame->m_CharHero[pGame->m_CurrentHero]->m_matWorld._42, pGame->m_CharHero[pGame->m_CurrentHero]->m_matWorld._43);

	static float fSpaceKeyShadeTime = 0.0f;
	static bool	 fSpaceKeyShade = false;

	//���� �̺�Ʈ ó��[Start]
	{

		for (int iEvent = 0; iEvent < I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent.size(); iEvent++) {

			if (pGame->m_bChatting == true)
				break;

			if (I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[iEvent]->m_bDone == true)
				continue;

			if (D3DXVec3Length(&(I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[iEvent]->m_vEventPos - vHeroPos)) < G_DEFINE_LENGTH_EVENT_RADIUS) {
				pGame->m_bChatting = true;
				pGame->m_iEventNum = iEvent;
				pGame->m_iScriptNum = 0;

				fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
				pGame->m_pCamera = pGame->m_pEventCamera.get();

				break;
			}
		}

		if (pGame->m_bChatting) {

			pGame->SetEventCamera(I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[pGame->m_iEventNum]->m_vecScript[pGame->m_iScriptNum]->m_Hero);

			//ä�� â�� �����ش�.
			if (I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[pGame->m_iEventNum]->m_vecScript[pGame->m_iScriptNum]->m_Hero == G_HERO_TOM) {
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = true;
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
			}
			else {
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = true;
			}




			//�����̽� Ű�� ��������..
			if (I_Input.KeyCheck(DIK_SPACE) == KEY_PUSH) {

				if (pGame->m_iScriptNum < I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[pGame->m_iEventNum]->m_vecScript.size() - 1) {
					pGame->m_iScriptNum++;
				}
				else {
					I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[pGame->m_iEventNum]->m_bDone = true;
					pGame->m_iEventNum = -1;
					pGame->m_iScriptNum = -1;
					pGame->m_bChatting = false;

					fSpaceKeyShadeTime = 0.0f;
					fSpaceKeyShade = false;

					//ī�޶� �ٲ۴�.
					pGame->m_pCamera = pGame->m_pFPSCamera[pGame->m_CurrentHero].get();

					//ä�� UI�� �Ⱥ��̰� �Ѵ�.
					pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
					pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
				}
				//Ŭ�� ����
				g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
			}

			//����ð�.
			float fElapsedTime = g_pMain->m_Timer.GetElapsedTime() - fSpaceKeyShadeTime;

			if (fElapsedTime > G_DEFINE_TIME_SPACEKEY_SHADE) {
				fSpaceKeyShadeTime = g_pMain->m_Timer.GetElapsedTime();
				fSpaceKeyShade = !fSpaceKeyShade;
			}

			if (fSpaceKeyShade)
				((GButtonCtl*)pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_SPACE])->m_Box.SetColor(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
			else
				((GButtonCtl*)pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_SPACE])->m_Box.SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));





		}
	}
	//���� �̺�Ʈ ó��[End]
	return true;
}
GEventMgr::GEventMgr() {

}
