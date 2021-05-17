#include "BattleScene.h"
#include "Image.h"
#include "Player.h"
#include "CommonFunction.h"
#include "Block.h"
#include "Inventory.h"

HRESULT BattleScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
    ImageLoad();
 
    Load();
    tileImage = IMAGEMANAGER->FindImage("Tile Set");
    backGround = IMAGEMANAGER->FindImage("Dungeon Background");

    lpPlayer = new Player();
    lpPlayer->Init();
    lpInventory = new Inventory();
    lpInventory->Init();

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
    if (lpInventory)
        lpInventory->Release();

    for (auto iter = vObjects.begin(); iter != vObjects.end();)
    {
        delete *iter;
        iter = vObjects.erase(iter);
    }

    IMAGEMANAGER->DeleteAll();
}

void BattleScene::Update()
{
    if (KEYMANAGER->IsOnceKeyDown('I'))
    {
        lpInventory->ToggleActive();
    }
    if(lpInventory->GetActive())
        lpInventory->Update();
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
    lpInventory->Render(hdc);
    //wsprintf(text, "플레이어 이동 : 방향키");
    //TextOut(hdc, 10, 10, text, strlen(text));
    //
    //wsprintf(text, "공격 : A");
    //TextOut(hdc, 10, 10 + 20, text, strlen(text));
    //
    //wsprintf(text, "회피 : SpaceBar");
    //TextOut(hdc, 10, 10 + 40, text, strlen(text));
    //
    //wsprintf(text, "무기교체 : 1 ~ 5");
    //TextOut(hdc, 10, 10 + 60, text, strlen(text));
    //
    //wsprintf(text, "RECT 보기 : P");
    //TextOut(hdc, 10, 10 + 80, text, strlen(text));
}

void BattleScene::CheckCollision()
{

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