#pragma once
class GSeqSingle3S : public GSeq
{
public:
	static GSeq* CreateInstance() {
		if (pInstance_ == 0) pInstance_ = new GSeqSingle3S;
		return pInstance_;
	}
	bool Init() { return true; };
	bool Frame() { return true; };
	bool Render() { return true; };
	bool Release() { return true; };

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource() { HRESULT hr; return S_OK; };
	HRESULT		DeleteResource() { HRESULT hr; return S_OK; };

	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };

public:
	virtual ~GSeqSingle3S() {};
protected:
	GSeqSingle3S() { pInstance_ = 0; };
private:
	static GSeqSingle3S *pInstance_;
};
