#pragma 

class GSeqSinglePlay;

class GScriptData
{
public:
	//누가 말했나.
	G_HERO		m_Hero;
	//문자열
	T_STR		m_Str;
	GScriptData(G_HERO		Hero, T_STR str) {
		m_Hero = Hero;
		m_Str = str;
	};
	GScriptData() {};
	virtual ~GScriptData() {};
};
class GEvent
{
public:
	bool		m_bDone;
	D3DXVECTOR3 m_vEventPos;
	vector<shared_ptr<GScriptData>> m_vecScript;

	GEvent(D3DXVECTOR3 vecPos) {
		m_vEventPos = vecPos;
	};
	GEvent();
	virtual ~GEvent();
};

class GStage
{
public:
	D3DXVECTOR3			m_vPosStart;
	D3DXVECTOR3			m_vPosEnd;
	vector<shared_ptr<GEvent>>  m_vecEvent;
	virtual bool init();


	GStage();
	virtual ~GStage() {};
};


class GEventMgr : public GSingleton < GEventMgr >
{
private:
	friend class GSingleton<GStage>;
public:
	vector<shared_ptr<GStage>>  m_vecStage;
	virtual bool init();
	virtual bool initStage1(shared_ptr<GStage>* pStage);
	virtual bool initStage2(shared_ptr<GStage>* pStage);
	virtual bool initStage3(shared_ptr<GStage>* pStage);

	virtual bool frame(GSeqSinglePlay* pGame);

	GEventMgr();
	virtual ~GEventMgr() {};
};
#define I_GameEventMgr GEventMgr::GetInstance()
