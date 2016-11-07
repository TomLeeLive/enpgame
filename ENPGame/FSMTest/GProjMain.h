#include "GCoreLibV2.h"
#include "GCamera.h"
//#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"
struct SimpleVertex // ������ ���ؽ� ����, Position �� Color ���� ����
{
	Vector3 p;
	Vector4 c;
};

class GProjMain : public GCoreLibV2
{
	shared_ptr<GCamera > m_pMainCamera;
	D3DXMATRIX  m_matWorld;
	GShape*		m_Box;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
