#pragma once
class GSeqLoading : public GSeq
{
public:
	static GSeq* CreateInstance() { 
		if (pInstance_ == 0) pInstance_ = new GSeqLoading;
		return pInstance_;
	}
	bool Init();
	 bool Frame() ;
	 bool RenderManually(void* arg1 = NULL, void* arg2 = NULL);
	 bool Render();
	 bool Release() { return true; };

	//----------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//----------------------------------------------------
	HRESULT		CreateResource() { HRESULT hr; return S_OK; };
	HRESULT		DeleteResource() { HRESULT hr; return S_OK; };

	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return -1; };
public:
	virtual ~GSeqLoading() {};
protected:
	GSeqLoading() { pInstance_ = 0; };
private:
	static GSeqLoading *pInstance_;
};


