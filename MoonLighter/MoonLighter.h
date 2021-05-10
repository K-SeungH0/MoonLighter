// MoonLighter.h
#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <vector>
using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

#define WINSIZE_X	1080
#define WINSIZE_Y	720

#define TILEMAPTOOLSIZE_X	1620
#define TILEMAPTOOLSIZE_Y	900

#define ASTARSIZE_X	1620
#define ASTARSIZE_Y	900

#define PI 3.1415926f
#define RADIAN 180/PI
#define DegToRad(x)	((x) * PI / 180.0f)
#define RadToDeg(x)	((x) * 180.0f / PI )

#define SAFE_DELETE(p) { if(p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if(p){p->Release(); delete p; p = nullptr;} }

#define KEYMANAGER KeyManager::GetInstance()
#define IMAGEMANAGER ImageManager::GetInstance()
#define TIMERMANAGER TimerManager::GetInstance()
#define DELTATIME TIMERMANAGER->GetDeltaTime()
#define SCENEMANAGER SceneManager::GetInstance()


enum class TILETYPE
{
	WALL,
	IRON,
	FOREST,
	RIVER,
	ICE,
	BOSS,
	NONE
};

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	TILETYPE type;
}TILE_INFO;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern TILE_INFO g_testTile[16];