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
	//Start, End 위치
	(*pStage)->m_vPosStart = D3DXVECTOR3(3660,   40, -2633);
	(*pStage)->m_vPosEnd = D3DXVECTOR3(-3449, 40, -2698);

	//좀비생성
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(3246, 40, 3007));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(0, 40, 0));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(-2718, 40, -260));






	//Stage 1 [START]
	auto pEvent1 = make_shared<GEvent>(D3DXVECTOR3(3660.0f, 40.0f, -2633.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 행성에 도착하였는데. 아무도 없는 걸? 이상하지만 전진해 보자.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아무래도 느낌이 안좋아.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"별일 없을 수도 있어 너무 걱정 하지마.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEvent>(D3DXVECTOR3(2464.0f, 40.0f, 2099.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"저기 멀리 생존자인가?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아니야 뭔가 이상해.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"가까이 가보도록 하자.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEvent>(D3DXVECTOR3(-2306.0f, 40.0f, -477.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"여기 사람들이 이상하게 변했어...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"가까운 드롭십으로 빠르게 이동하자.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"빨리가자구!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent3);
	//Stage 1 [END]



	return true;
}
bool GEventMgr::initStage2(shared_ptr<GStage>* pStage) {
	//Start, End 위치
	(*pStage)->m_vPosStart = D3DXVECTOR3(-3131, 40, -3504);
	(*pStage)->m_vPosEnd = D3DXVECTOR3(3273, 40, 3534);

	//좀비생성
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(-3096, 232, -2583));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(-1476, 98, 352));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(538, 84, 74));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(3503, 115, 1170));


	//Stage 2 [START]
	auto pEvent1 = make_shared<GEvent>(D3DXVECTOR3(-3131.0f, 40.0f, -3504.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 행성에 도착하였는데. 아무도 없는 걸? 이상하지만 전진해 보자.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아무래도 느낌이 안좋아.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"별일 없을 수도 있어 너무 걱정 하지마.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEvent>(D3DXVECTOR3(-2523.0f, 40.0f, -735.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"저기 멀리 생존자인가?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아니야 뭔가 이상해.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"가까이 가보도록 하자.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEvent>(D3DXVECTOR3(2126.0f, 40.0f, 979.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"여기 사람들이 이상하게 변했어...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"가까운 드롭십으로 빠르게 이동하자.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"빨리가자구!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent3);




	auto pEvent4 = make_shared<GEvent>(D3DXVECTOR3(3273.0f, 40.0f, 3534.0f));

	auto pEvent4_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"다음 스테이지는 4차 발표에서 보여 드리겠습니다.");
	pEvent4->m_vecScript.push_back(pEvent4_Script1);
	auto pEvent4_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"다음에 다시 만나요~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script2);
	auto pEvent4_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"안녕~~");
	pEvent4->m_vecScript.push_back(pEvent4_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent4);
	//Stage 2 [END]
	return true;
}
bool GEventMgr::initStage3(shared_ptr<GStage>* pStage) {
	//Start, End 위치
	(*pStage)->m_vPosStart = D3DXVECTOR3(-3588, 40, 2500);
	(*pStage)->m_vPosEnd = D3DXVECTOR3(3245, 40, -2630);


	//좀비생성
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(-1421, 149, 2105));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(3138, 198, 996));
	(*pStage)->m_vecZombiePos.push_back(D3DXVECTOR3(4154, 204, -1254));


	//Stage 3 [START]
	auto pEvent1 = make_shared<GEvent>(D3DXVECTOR3(-3588.0f, 40.0f, 2500.0f));

	auto pEvent1_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"N2 행성에 도착하였는데. 아무도 없는 걸? 이상하지만 전진해 보자.");
	pEvent1->m_vecScript.push_back(pEvent1_Script1);
	auto pEvent1_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아무래도 느낌이 안좋아.");
	pEvent1->m_vecScript.push_back(pEvent1_Script2);
	auto pEvent1_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"별일 없을 수도 있어 너무 걱정 하지마.");
	pEvent1->m_vecScript.push_back(pEvent1_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent1);




	auto pEvent2 = make_shared<GEvent>(D3DXVECTOR3(199.0f, 40.0f, 1908.0f));

	auto pEvent2_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"저기 멀리 생존자인가?");
	pEvent2->m_vecScript.push_back(pEvent2_Script1);
	auto pEvent2_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"아니야 뭔가 이상해.");
	pEvent2->m_vecScript.push_back(pEvent2_Script2);
	auto pEvent2_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"가까이 가보도록 하자.");
	pEvent2->m_vecScript.push_back(pEvent2_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent2);




	auto pEvent3 = make_shared<GEvent>(D3DXVECTOR3(3245.0f, 40.0f, -2630.0f));

	auto pEvent3_Script1 = make_shared < GScriptData>(G_HERO_JAKE, L"여기 사람들이 이상하게 변했어...");
	pEvent3->m_vecScript.push_back(pEvent3_Script1);
	auto pEvent3_Script2 = make_shared < GScriptData>(G_HERO_TOM, L"가까운 드롭십으로 빠르게 이동하자.");
	pEvent3->m_vecScript.push_back(pEvent3_Script2);
	auto pEvent3_Script3 = make_shared < GScriptData>(G_HERO_JAKE, L"빨리가자구!!!");
	pEvent3->m_vecScript.push_back(pEvent3_Script3);

	(*pStage)->m_vecEvent.push_back(pEvent3);
	//Stage 3 [END]
	return true;
}
bool GEventMgr::init() {

	//지형 Loading [START]
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.Init(g_pMain);
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera = ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pFPSCamera[((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_CurrentHero].get();

	T_STR strFile;
	strFile = L"data/map/stage_1.map";
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.LoadMap(&strFile, ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera, g_pMain);

	strFile = L"data/map/stage_2.map";
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.LoadMap(&strFile, ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera, g_pMain);

	strFile = L"data/map/stage_3.map";
	((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_MapMgr.LoadMap(&strFile, ((GSeqSinglePlay*)g_pMain->m_pGameSeq[G_SEQ_SINGLE])->m_pCamera, g_pMain);
	//지형 Loading [END]



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

	//게임 이벤트 처리[Start]
	{
		if (pGame->m_bChatting != true)
		{
			D3DXVECTOR3 vDist = I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vPosEnd - vHeroPos;
			if (D3DXVec3Length(&vDist) < G_DEFINE_LENGTH_EVENT_RADIUS)
			{
				if (pGame->m_MapMgr.m_iMapSelected == 0) {
					g_pMain->ChangeSeq(G_SEQ_SINGLE_2S);
				}
				else if (pGame->m_MapMgr.m_iMapSelected == 1) {
					g_pMain->ChangeSeq(G_SEQ_SINGLE_3S);
				}
				else if (pGame->m_MapMgr.m_iMapSelected == 2) {
					g_pMain->ChangeSeq(G_SEQ_SINGLE_3E);
				}
			}
		}

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

			//채팅 창을 보여준다.
			if (I_GameEventMgr.m_vecStage[pGame->m_MapMgr.m_iMapSelected]->m_vecEvent[pGame->m_iEventNum]->m_vecScript[pGame->m_iScriptNum]->m_Hero == G_HERO_TOM) {
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = true;
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
			}
			else {
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
				pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = true;
			}




			//스페이스 키를 눌렀을때..
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

					//카메라를 바꾼다.
					pGame->m_pCamera = pGame->m_pFPSCamera[pGame->m_CurrentHero].get();

					//채팅 UI를 안보이게 한다.
					pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P1_IMG]->m_bRender = false;
					pGame->m_UIManager.m_pUIList[G_DEFINE_UI_CHATTING_P2_IMG]->m_bRender = false;
				}
				//클릭 사운드
				g_pMain->m_pSound.Play(SND_CLICK_BUTTON, true, false);
			}

			//경과시간.
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
	//게임 이벤트 처리[End]
	return true;
}
GEventMgr::GEventMgr() {

}




/*
===========================================================================
첫시작화면
이벤트 텍스처 출력 시간 지난후 시퀀스 변경

리셋:스테이지1 주인공 위치, 스테이지1 주인공2 위치 잡을것
주인공1,2 총알 HP 리셋
m_iSelected =0 으로 돌릴것
좀비매니저 좀비 초기화
1스테이지 좀비 push back 할것.
--------------------------------------------------------
다음스테이지 넘어가면

스테이지2 주인공1 위치, 스테이지2 주인공2 위치 잡을것
주인공1,2 총알 HP 리셋
m_iSelected =1
스테이지2 좀비 push back
이벤트 텍스처 출력 시간 지난후 시퀀스 변경
--------------------------------------------------------
스테이지3 주인공1 위치, 스테이지3 주인공2 위치 잡을것
주인공1,2 총알 HP 리셋
m_iSelected =2
스테이지3 좀비 push back
이벤트 텍스처 출력 시간 지난후 시퀀스 변경
--------------------------------------------------------

마지막 stage 끝나면
이벤트 텍스처 출력 시간 지난후 시퀀스 변경
--------------------------------------------------------


스테이지1 이벤트 3
스테이지2 이벤트 4
스테이지3 이벤트 3


스테이지1 이벤트 위치
3660   216,     -2633
2464, 185, 2099
-2306, 96, -477


스테이지2 이벤트 위치
-3131,  233,   -3504
-2523,  71,  -735
2126,  104,   979
3273, 106, 3534


스테이지3 이벤트 위치
-3588,    332,    2500
199,  283,   1908
3245, 277,   -2630


스테이지1 좀비 생성 위치(3)
3246,  122,   3007
0,0,0
-2718, 133,    -260

스테이지2 좀비 생성 위치(4)
-3096,  232,  -2583
-1476,   98,  352
538,     84,   74
3503,    115,  1170

스테이지3 좀비 생성 위치(3)
-1421,  149,  2105
3138,   198,  996
4154,	204,  -1254

스테이지1 start 위치
3660   216,     -2633

스테이지2 start 위치
-3131,  233,   -3504

스테이지3 start 위치
-3588,    332,    2500

스테이지1 End 위치
-3449     214,  -2698

스테이지2 End 위치
3273, 106, 3534

스테이지3 End 위치
3245, 277,   -2630
*/