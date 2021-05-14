#pragma once
#include "GameObject.h"

class Image;
class MainGame : public GameObject
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	char szText[128] = "";

	Image* backBuffer;

public:
	HRESULT Init() override;		// 오버라이딩 : 다형성
	void Release() override;
	void Update() override;
	void Render();
	void Render(HDC hdc) override {};

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

