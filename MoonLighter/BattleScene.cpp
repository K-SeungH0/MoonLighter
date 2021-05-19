#include "BattleScene.h"
#include "Image.h"
#include "Player.h"
#include "CommonFunction.h"
#include "Block.h"
#include "Inventory.h"
#include "BattleSceneUI.h"
HRESULT BattleScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
    ImageLoad();
 
    Load();
    tileImage = IMAGEMANAGER->FindImage("Tile Set");
    backGround = IMAGEMANAGER->FindImage("Dungeon Background");

    lpPlayer = new Player();
    lpPlayer->Init();

    lpUI = new BattleSceneUI();
    lpUI->Init();
    
    int outsideSize = 50;
    RECTFLOAT outsideRc;
    outsideRc.left = 0;
    outsideRc.right = WINSIZE_X;
    outsideRc.top = 0;
    outsideRc.bottom = outsideSize;

    outsideColliderTop = new Block();
    ((Block*)outsideColliderTop)->Init(outsideRc);

    outsideRc.left = 0;
    outsideRc.right = outsideSize;
    outsideRc.top = 0;
    outsideRc.bottom = WINSIZE_Y;
    
    outsideColliderLeft = new Block();
    ((Block*)outsideColliderLeft)->Init(outsideRc);

    outsideRc.left = WINSIZE_X - outsideSize;
    outsideRc.right = WINSIZE_X;
    outsideRc.top = 0;
    outsideRc.bottom = WINSIZE_Y;

    outsideColliderRight = new Block();
    ((Block*)outsideColliderRight)->Init(outsideRc);

    outsideRc.left = 0;
    outsideRc.right = WINSIZE_X;
    outsideRc.top = WINSIZE_Y - outsideSize;
    outsideRc.bottom = WINSIZE_Y;

    outsideColliderBottom = new Block();
    ((Block*)outsideColliderBottom)->Init(outsideRc);

    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        if (tileMap[i].type != TILETYPE::NONE) 
        {
            vObjects.push_back(new Block());
            ((Block*)vObjects.back())->Init(tileMap[i]);
        }
    }

	return S_OK;
}

void BattleScene::Release()
{
    if(lpPlayer)
        lpPlayer->Release();
    if (lpUI)
        lpUI->Release();

    for (auto iter = vObjects.begin(); iter != vObjects.end();)
    {
        (*iter)->Release();
        //delete *iter;
        iter = vObjects.erase(iter);
    }

    IMAGEMANAGER->DeleteAll();
}

void BattleScene::Update()
{
    if (KEYMANAGER->IsOnceKeyDown('I'))
    {
        lpUI->ToggleInven();
    }
    if(lpUI->GetInvenActive())
        lpUI->Update();
    else
    {
        lpPlayer->Update();
        // TODO : Enemy Update추가
    }
}

void BattleScene::Render(HDC hdc)
{
    backGround->Render(hdc);

    for (auto iter = vObjects.begin(); iter != vObjects.end(); iter++)
    {
        ((Block*)*iter)->Render(hdc);
    }

    lpPlayer->Render(hdc);
    lpUI->Render(hdc);
}

void BattleScene::Load()
{
    string saveName = "Save/SaveMapData";
    saveName += to_string(1) + ".map";

    DWORD readBytes;

    HANDLE hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFile, tileMap, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}

void BattleScene::ImageLoad()
{
    COLORREF color = RGB(128, 128, 128);

    IMAGEMANAGER->AddImage("Dungeon Background", L"Image/Map/dungeon_background.png",
        1280, 720, BACKGROUND_TILE_X, BACKGROUND_TILE_Y, true, color);
    IMAGEMANAGER->AddImage("Tile Set", L"Image/Map/TileMap.png",
        320, 96, TILE_SET_X, TILE_SET_Y, true, color);
    
    IMAGEMANAGER->AddImage("UrnRest", L"Image/Object/BreakAble/UrnRest.png",
        32, 25, 1, 1, true, color);
    IMAGEMANAGER->AddImage("SkullRest", L"Image/Object/BreakAble/SkullRest.png",
        32, 32, 1, 1, true, color);
    IMAGEMANAGER->AddImage("ChairRest", L"Image/Object/BreakAble/ChairRest.png",
        23, 19, 1, 1, true, color);
}