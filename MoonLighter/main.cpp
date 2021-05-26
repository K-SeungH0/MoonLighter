// main.cpp
#include "CommonFunction.h"
#include "MainGame.h"

// 전역변수
// 인스턴스 : 객체 메모리상에 존재하는 객체
HINSTANCE g_hInstance;		// 프로그램 인스턴스 핸들
HWND g_hWnd;				// 윈도우 핸들
POINT g_ptMouse;
LPSTR g_lpszClass = (LPSTR)TEXT("문라이터");
MainGame g_mainGame;
bool isDebugMode = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	// 윈도우를 생성하기 위한 기본셋팅
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 2068;
	wndClass.cbWndExtra = 2068;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		0, 0, 1080, 720,
		NULL, NULL, g_hInstance, NULL);


	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 윈도우 크기 조정
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	if (FAILED(g_mainGame.Init()))
	{
		MessageBox(g_hWnd, "메인 게임 초기화 실패!!", "경고", MB_OK);
		//return 0;
	}

	TimerManager::GetInstance()->Init();

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimerManager::GetInstance()->Update();
		
			g_mainGame.Update();
			g_mainGame.Render();
		}
	}
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	g_mainGame.Release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
