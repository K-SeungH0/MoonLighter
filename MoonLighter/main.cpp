// main.cpp
#include "CommonFunction.h"
#include "MainGame.h"

// ��������
// �ν��Ͻ� : ��ü �޸𸮻� �����ϴ� ��ü
HINSTANCE g_hInstance;		// ���α׷� �ν��Ͻ� �ڵ�
HWND g_hWnd;				// ������ �ڵ�
POINT g_ptMouse;
LPSTR g_lpszClass = (LPSTR)TEXT("��������");
MainGame g_mainGame;
bool isDebugMode = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;

	// �����츦 �����ϱ� ���� �⺻����
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

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		0, 0, 1080, 720,
		NULL, NULL, g_hInstance, NULL);


	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// ������ ũ�� ����
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

	if (FAILED(g_mainGame.Init()))
	{
		MessageBox(g_hWnd, "���� ���� �ʱ�ȭ ����!!", "���", MB_OK);
		//return 0;
	}

	TimerManager::GetInstance()->Init();

	// �޽��� ť�� �ִ� �޽��� ó��
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
