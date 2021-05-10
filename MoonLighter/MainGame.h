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
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

