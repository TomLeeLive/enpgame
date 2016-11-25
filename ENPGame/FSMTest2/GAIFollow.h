#pragma once
class GAIFollow : public GAISeq
{
private:
	static GAIFollow *pInstance_;
public:
	static GAISeq* CreateInstance()
	{
		if (pInstance_ == 0) pInstance_ = new GAIFollow;
		return pInstance_;
	}
	shared_ptr<GCamera > m_pMainCamera;
	//D3DXMATRIX  m_matWorld;

	bool Init(int iMyIndex);
	bool Frame(int iMyIndex);
	bool Render();
	bool Release();
	bool ZombieFollow(int i, D3DXVECTOR3 look, D3DXVECTOR3 Right, D3DXVECTOR3 Up);
	int hp;
	//GNewZombieMgr * ZombieMgr;

	D3DXVECTOR3 B_Look;
	D3DXMATRIX B_Trans;

	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	//D3DXMATRIX Trans;
	//D3DXMATRIX Rotation;
	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIFollow();
protected:
	GAIFollow();
};


