#include "BattleScene.h"
#include "Image.h"
#include "Player.h"
#include "CommonFunction.h"
#include "Block.h"
#include "Inventory.h"
#include "BattleSceneUI.h"
#include "Item.h"
#include "ItemManager.h"
#include "Weapon.h"
#include "Camera.h"
#include "DungeonManager.h"
#include "EnemyManager.h"

#include <random>
#include <algorithm>

HRESULT BattleScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
    GAMEDATA->RunTimeDataInit();
    ImageLoad();
    Load();
    lpBackGround = IMAGEMANAGER->FindImage("Dungeon_Background");

    lpPlayer = GAMEDATA->GetRunTimePlayer();

    lpCamera = new Camera();
    lpCamera->Init(lpBackGround, lpPlayer->GetpPos(), 350);

    lpPlayer->SetCamera(lpCamera);
    lpPlayer->SetProjectileCamera();
    lpPlayer->SetMoveArea({ 50, 50, WINSIZE_X - 50, WINSIZE_Y - 50 });

    lpUI = new BattleSceneUI();
    lpUI->Init();
    lpUI->SetCamera(lpCamera);
    lpUI->SetIsBattle(true);

    lpItemManager = new ItemManager();
    lpItemManager->Init(lpUI->GetInventory());

    lpDungeonManager = new DungeonManager();
    lpDungeonManager->Init();

    lpEnemyManager = new EnemyManager();
    lpEnemyManager->Init(tileMap, lpPlayer->GetpPos(), lpItemManager);

    for (int i = 0; i < DUNGEON_TILE_X * DUNGEON_TILE_Y; i++)
    {
        if (tileMap[i].type == TILETYPE::SPAWN)
        {
            lpEnemyManager->AddRespawn({ (tileMap[i].rcTile.right + tileMap[i].rcTile.left) / 2 ,(tileMap[i].rcTile.bottom + tileMap[i].rcTile.top) / 2 });
        }
        else if (tileMap[i].type != TILETYPE::NONE) 
        {
            vObjects.push_back(new Block());
            ((Block*)vObjects.back())->Init(tileMap[i], &tileMap[i].type);
        }
    }
    lpEnemyManager->RespawnShuffle();
    lpEnemyManager->EnemySpawn();

   
	return S_OK;
}

void BattleScene::Release()
{
    SAFE_RELEASE(lpCamera)      ;//lpCamera->Release();
    SAFE_RELEASE(lpUI)          ;//lpUI->Release();
    SAFE_RELEASE(lpItemManager) ;//lpItemManager->Release();

    for (auto iter = vObjects.begin(); iter != vObjects.end();)
    {
        (*iter)->Release();
        iter = vObjects.erase(iter);
    }
    COLLIDERMANAGER->RemoveAllCollider();
    IMAGEMANAGER->DeleteAll();
}

void BattleScene::Update()
{
    if (KEYMANAGER->IsOnceKeyDown('I'))
        lpUI->ToggleInven();

    if (KEYMANAGER->IsOnceKeyDown('0'))
        TestItem();

    if (!lpUI->GetInvenActive())
    {
        lpPlayer->Update();
        lpEnemyManager->Update();
    }

    lpUI->Update();
    EFFECTMANAGER->Update();
    if (!lpPlayer->GetIsAilve())
        SCENEMANAGER->ChageScene("Town", "LodingScene");
}

void BattleScene::Render(HDC hdc)
{
    lpBackGround->Render(hdc);

    for (auto iter = vObjects.begin(); iter != vObjects.end(); iter++)
    {
        ((Block*)*iter)->Render(hdc);
    }

    lpEnemyManager->Render(hdc);
    lpPlayer->Render(hdc);
    lpItemManager->Render(hdc);
    EFFECTMANAGER->Render(hdc);
    lpEnemyManager->Render(hdc);
    lpUI->Render(hdc);
}

void BattleScene::Load()
{
    string saveName = "Save/SaveDunGeonMapData";

    vector<int> randomDungeon;

    randomDungeon.push_back(1);
    randomDungeon.push_back(2);
    randomDungeon.push_back(3);
    randomDungeon.push_back(4);
    randomDungeon.push_back(5);
    randomDungeon.push_back(6);
    randomDungeon.push_back(7);
    randomDungeon.push_back(8);
    randomDungeon.push_back(9);
    randomDungeon.push_back(10);

    random_shuffle(randomDungeon.begin(), randomDungeon.end());
    saveName += to_string(1) + ".map";

    DWORD readBytes;

    HANDLE hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFile, tileMap, sizeof(TILE_INFO) * DUNGEON_TILE_X * DUNGEON_TILE_Y, &readBytes, NULL))
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

    IMAGEMANAGER->AddImage("Dungeon_Background", L"Image/Map/dungeon_background.png", BACKGROUND_TILE_X, BACKGROUND_TILE_Y);
    IMAGEMANAGER->AddImage("DunGeon_TileSet", L"Image/Map/DunGeon_TileSet.png",DUNGEON_TILE_SET_X, DUNGEON_TILE_SET_Y);
    
    IMAGEMANAGER->AddImage("UrnRest", L"Image/Object/BreakAble/UrnRest.png");
    IMAGEMANAGER->AddImage("SkullRest", L"Image/Object/BreakAble/SkullRest.png");
    IMAGEMANAGER->AddImage("ChairRest", L"Image/Object/BreakAble/ChairRest.png");
}

void BattleScene::TestItem()
{
    vector<POINT> pos;
    for (int i = 0; i < DUNGEON_TILE_X * DUNGEON_TILE_Y; i++)
    {
        if (tileMap[i].type == TILETYPE::SPAWN)
        {
            pos.push_back({ (tileMap[i].rcTile.right + tileMap[i].rcTile.left) / 2 ,(tileMap[i].rcTile.bottom + tileMap[i].rcTile.top) / 2 });
        }
    }
    
    GameData::ItemData testdata;
    testdata.isEquipment = true;
    testdata.itemCode = 1001;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y});
    pos.pop_back();

    testdata.itemCode = 1000;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 1011;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 1021;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 1031;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();


    testdata.itemCode = 4000;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 4001;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 4010;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 4011;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 4020;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 4021;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 3000;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    testdata.itemCode = 3003;
    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();


    testdata.isEquipment = false;
    testdata.itemCode = 2001;
    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, {(float)pos.back().x, (float)pos.back().y });
    pos.pop_back();


    testdata.itemCode = 2000;
    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y });
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y});
    pos.pop_back();

    lpItemManager->AddItem(new Item(), testdata, { (float)pos.back().x, (float)pos.back().y});
    pos.pop_back();
}
