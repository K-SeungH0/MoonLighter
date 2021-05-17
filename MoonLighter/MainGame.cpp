#include "MainGame.h"
#include "TileMapTool.h"
#include "Image.h"
#include "BattleScene.h"
#include "AstarScene.h"
#include "LoadingScene.h"
#include "TitleScene.h"
#include "CollisionManager.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	CollisionManager::GetInstance()->Init();

	// 백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(max(WINSIZE_X, TILEMAPTOOLSIZE_X), max(WINSIZE_Y, TILEMAPTOOLSIZE_Y));

	SceneManager::GetInstance()->AddScene("Battle", new BattleScene());
	SceneManager::GetInstance()->AddScene("TileMapTool", new TileMapTool());
	SceneManager::GetInstance()->AddScene("A*", new AstarScene());
	SceneManager::GetInstance()->AddScene("Title", new TitleScene());
	SceneManager::GetInstance()->AddLodingScene("LodingScene", new LoadingScene());

	SceneManager::GetInstance()->ChageScene("Title");
	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	ReleaseDC(g_hWnd, hdc);
	KEYMANAGER->Release();
	IMAGEMANAGER->Release();
	SCENEMANAGER->Release();
}

void MainGame::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('P'))
		isDebugMode = !isDebugMode;

	SceneManager::GetInstance()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	SCENEMANAGER->Render(hBackDC);
	TIMERMANAGER->Render(hBackDC);

	backBuffer->Render(hdc);

}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_LBUTTONUP:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
