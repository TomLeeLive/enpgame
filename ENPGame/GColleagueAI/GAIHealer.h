#pragma once

class GAIHealer : public GAISeq
{
private:

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	int	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//----------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//----------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	virtual ~GAIHealer();
	GAIHealer();
protected:

};


