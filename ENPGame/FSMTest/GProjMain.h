#include "GCoreLibV2.h"
#include "GCamera.h"
//#include "GDxHelperEX.h"
#include "GMatrix.h"
#include "GShape.h"
struct SimpleVertex // 간단한 버텍스 구조, Position 과 Color 값만 갖자
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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	GProjMain(void);
	virtual ~GProjMain(void);
};
