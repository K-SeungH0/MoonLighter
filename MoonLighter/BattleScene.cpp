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

    lpUI = new BattleSceneUI();
    lpUI->Init();
    lpUI->SetCamera(lpCamera);
    lpUI->SetIsBattle(true);

    lpDungeonManager = new DungeonManager();
    lpDungeonManager->Init();

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

    for (int i = 0; i < DUNGEON_TILE_X * DUNGEON_TILE_Y; i++)
    {
        if (tileMap[i].type != TILETYPE::NONE) 
        {
            vObjects.push_back(new Block());
            ((Block*)vObjects.back())->Init(tileMap[i]);
        }
    }
    
    lpItemManager = new ItemManager();
    lpItemManager->Init(lpUI->GetInventory());

    GameData::ItemData testdata;
    testdata.isEquipment = true;
    testdata.itemCode = 1001;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 100, WINSIZE_Y - 100 });

    testdata.itemCode = 1010;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 200, WINSIZE_Y - 100 });
    testdata.itemCode = 1020;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 300, WINSIZE_Y - 100 });
    testdata.itemCode = 1030;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });

    testdata.itemCode = 4000;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 4001;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 4010;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 4011;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 4020;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 4021;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });

    testdata.itemCode = 3000;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    testdata.itemCode = 3003;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 100 });


    testdata.isEquipment = false;
    testdata.itemCode = 2001;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 200, WINSIZE_Y - 150 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 300, WINSIZE_Y - 150 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 - 400, WINSIZE_Y - 150 });

    testdata.itemCode = 2000;
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 + 100 , WINSIZE_Y - 150 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 + 200, WINSIZE_Y - 150 });
    lpItemManager->AddItem(new Item(), testdata, { WINSIZE_X / 2 + 300, WINSIZE_Y - 150 });

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

    if (!lpUI->GetInvenActive())
    {
        lpPlayer->Update();
        // TODO : Enemy Update추가
    }

    lpUI->Update();

    EFFECTMANAGER->Update();
}

void BattleScene::Render(HDC hdc)
{
    lpBackGround->Render(hdc);

    for (auto iter = vObjects.begin(); iter != vObjects.end(); iter++)
    {
        ((Block*)*iter)->Render(hdc);
    }

    lpPlayer->Render(hdc);
    lpItemManager->Render(hdc);
    EFFECTMANAGER->Render(hdc);
    lpUI->Render(hdc);
}

void BattleScene::Load()
{
    string saveName = "Save/SaveDunGeonMapData";
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