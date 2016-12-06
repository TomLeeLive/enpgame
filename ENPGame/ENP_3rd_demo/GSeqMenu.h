#pragma once
class GSeqMenu : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GSeqMenu;
		return pInstance_;
	}
	bool Init() { return true; };
	bool Frame();
	bool Render();
	bool Release() { return true; };

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource() { HRESULT hr; return S_OK; };
	HRESULT		DeleteResource() { HRESULT hr; return S_OK; };

	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };

public:
	virtual ~GSeqMenu() {};
protected:
	GSeqMenu() {};
private:
	static GSeqMenu *pInstance_;
};
