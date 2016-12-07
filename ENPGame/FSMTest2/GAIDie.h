#pragma once

class GAIDie : public GAISeq
{
private:
	//static GAIDie *pInstance_;
public:
	//static GAISeq* CreateInstance()
	//{
	//	if (pInstance_ == 0) pInstance_ = new GAIDie;
	//	return pInstance_;
	//}
	shared_ptr<GCamera > m_pMainCamera;
	//D3DXMATRIX  m_matWorld;

	bool Init(GNewZombie* iMyIndex);
	bool Frame(GNewZombie* iMyIndex);
	bool Render();
	bool Release();
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	D3DXVECTOR3 RandomPoint;

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIDie();
	GAIDie();
protected:

};


