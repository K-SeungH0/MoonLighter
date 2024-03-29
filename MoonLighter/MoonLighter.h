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

struct RECTFLOAT
{
	float left;
	float top;
	float right;
	float bottom;
};

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "FloatingFont.h"
#include "GameData.h"

#define WINSIZE_X	1280
#define WINSIZE_Y	720

#define TILEMAPTOOLSIZE_X	1920
#define TILEMAPTOOLSIZE_Y	1080

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
#define SCENEMANAGER SceneManager::GetInstance()
#define COLLIDERMANAGER CollisionManager::GetInstance()
#define EFFECTMANAGER EffectManager::GetInstance()
#define FLOATINGFONT FloatingFont::GetInstance()
#define DELTATIME TIMERMANAGER->GetDeltaTime()

#define GAMEDATA GameData::GetInstance()

#define IMAGE_SIZE 2.0f

#define DUNGEON_TILE_SET_X	10
#define DUNGEON_TILE_SET_Y	5

#define TOWN_TILE_SET_X 4
#define TOWN_TILE_SET_Y 6

#define BACKGROUND_TILE_X 1
#define BACKGROUND_TILE_Y 1

#define TILESIZE		(32 * IMAGE_SIZE)

#define DUNGEON_TILE_X		18 
#define DUNGEON_TILE_Y		9

#define TOWN_TILE_X			46
#define TOWN_TILE_Y			38

enum class TILETYPE
{
	BREAKABLE,
	WALL,
	HOLE,
	SPAWN,
	NONE
};

typedef struct tagTile
{
	Image* lpImage;
	RECT rcTile;
	RECT collider;
	int frameX;
	int frameY;
	TILETYPE type;
}TILE_INFO;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern bool isDebugMode;