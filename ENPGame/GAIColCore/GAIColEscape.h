#pragma once

class GAIColEscape : public GAIColSeq
{
private:
	//static GAIColDie *pInstance_;
public:
	//static GAIColSeq* CreateInstance()
	//{
	//	if (pInstance_ == 0) pInstance_ = new GAIColDie;
	//	return pInstance_;
	//}
	//shared_ptr<GCamera > m_pMainCamera;
	//D3DXMATRIX  m_matWorld;

	bool Init(GAICol* iMyIndex);
	bool Frame(GAICol* iMyIndex, D3DXMATRIX matHeroWorld, D3DXMATRIX matHeroWorld2);
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
	virtual ~GAIColEscape();
	GAIColEscape();
protected:

};


