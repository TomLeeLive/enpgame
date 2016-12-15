#pragma 

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
class GEventData
{
public:
	D3DXVECTOR3 m_vEventPos;
	vector<shared_ptr<GScriptData>> m_vecScript;

	GEventData(D3DXVECTOR3 vecPos) {
		m_vEventPos = vecPos;
	};
	GEventData();
	virtual ~GEventData();
};

class GEvent : public GSingleton < GEvent >
{
private:
	friend class GSingleton<GEvent>;
public:
	vector<shared_ptr<GEventData>>  m_vecEvent;
	virtual bool init();

	GEvent();
	virtual ~GEvent() {};
};
#define I_GameEvent GEvent::GetInstance()

