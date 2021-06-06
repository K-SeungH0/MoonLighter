#include "EnemyManager.h"
#include "Enemy.h"
#include "ItemManager.h"
#include "Item.h"
#include <random>
#include <algorithm>

HRESULT EnemyManager::Init()
{
    ImageLoad();
    return S_OK;
}

HRESULT EnemyManager::Init(TILE_INFO* astarMap, POINTFLOAT* endPos, ItemManager* lpItemManager)
{
    Init();
    this->astarMap = astarMap;
    this->endPos = endPos;
    this->lpItemManager = lpItemManager;
    astar.Init(this->astarMap);

    test = true;
    return S_OK;
}

void EnemyManager::Release()
{

}

void EnemyManager::Update()
{
    int x = (endPos->x - 50) / ASTAR_TILESIZE;
    int y = (endPos->y - 50) / ASTAR_TILESIZE;

    if (x >= DUNGEON_TILE_X) x = DUNGEON_TILE_X - 1;
    if (y >= DUNGEON_TILE_Y) y = DUNGEON_TILE_Y - 1;
    astar.SetEndTile(x, y);

    for (auto iter = vEnemys.begin(); iter != vEnemys.end(); )
    {
        if ((*iter)->GetIsAilve())
        {
            x = ((*iter)->GetPos().x - 50) / ASTAR_TILESIZE;
            y = ((*iter)->GetPos().y - 50) / ASTAR_TILESIZE;
            astar.SetStartTile(x, y);
            astar.FindPath();

            if ((*iter)->CheckAstar())
            {
                if (astar.Result().size() > 1)
                {
                    (*iter)->SetAstarPos(astar.Result());
                }
            }
            astar.Init(this->astarMap);

            (*iter)->Update();
            iter++;
        }
        else
        {
            // TODO : 아이템 추가
            GameData::ItemData dropItem;
            dropItem = GetRandomItem();
            lpItemManager->AddItem(new Item(), dropItem, (*iter)->GetPos());
            COLLIDERMANAGER->RemoveCollider((*iter));
            (*iter)->Release();
            delete *iter;
            *iter = nullptr;

            iter = vEnemys.erase(iter);
        }
    }
}

void EnemyManager::Render(HDC hdc)
{
    for (auto iter = vEnemys.begin(); iter != vEnemys.end(); iter++)
    {
        (*iter)->Render(hdc);
    }
    
   // 랜덤 리스폰 pos 디버그용
   //if (isDebugMode)
   //{
   //    int i = 1;
   //    for (auto iter = vRespawnPos.begin(); iter != vRespawnPos.end(); iter++)
   //    {
   //        Rectangle(hdc, iter->x - 10, iter->y - 10, iter->x + 10, iter->y + 10);
   //        FLOATINGFONT->Render(hdc, { iter->x, iter->y }, 18, to_string(i++).c_str(), RGB(0, 0, 0));
   //    }
   //
   //    int x = (endPos->x - 50) / ASTAR_TILESIZE;
   //    int y = (endPos->y - 50) / ASTAR_TILESIZE;
   //    if (x >= DUNGEON_TILE_X) x = DUNGEON_TILE_X - 1;
   //    if (y >= DUNGEON_TILE_Y) y = DUNGEON_TILE_Y - 1;
   //
   //    FLOATINGFONT->Render(hdc, { 700,50 }, 24, to_string(x).c_str(), RGB(255, 0, 255));
   //    FLOATINGFONT->Render(hdc, { 800,50 }, 24, to_string(y).c_str(), RGB(255, 0, 255));
   //}
}

void EnemyManager::AddRespawn(POINT pos)
{
    vRespawnPos.push_back(pos);
}

void EnemyManager::RespawnShuffle()
{
    random_shuffle(vRespawnPos.begin(), vRespawnPos.end());
}

void EnemyManager::EnemySpawn()
{
    for (int i = 0; i < 1; i++)
    {
        POINT pos = vRespawnPos.back();
        vRespawnPos.pop_back();

        vEnemys.push_back(new Enemy());
        vEnemys.back()->Init(pos);
        vEnemys.back()->SetPos({ (float)pos.x, (float)pos.y });
        COLLIDERMANAGER->AddCollider(vEnemys.back());
    }
}

GameData::ItemData EnemyManager::GetRandomItem()
{
    GameData::ItemData result;
    vector<int> vRandom;
    int frist = 0;
    int second = 0;
    int third = 0;
    // 1. 무기 
    // 2. 잡템
    // 3. 물약
    // 4. 방어구

    vRandom.push_back(1);
    vRandom.push_back(2);
    vRandom.push_back(3);
    vRandom.push_back(4);

    random_shuffle(vRandom.begin(), vRandom.end());

    frist = 1000 * vRandom.back();
    vRandom.clear();

    if ((frist / 1000) == 1)
    {
        // 무기
        vRandom.push_back(0);
        vRandom.push_back(1);
        vRandom.push_back(2);
        vRandom.push_back(3);
        random_shuffle(vRandom.begin(), vRandom.end());
        second = 10 * vRandom.back();
        vRandom.clear();

        vRandom.push_back(0);
        vRandom.push_back(1);
        random_shuffle(vRandom.begin(), vRandom.end());
        third = vRandom.back();

        result.isEquipment = true;
    }
    else if ((frist / 1000) == 2)
    {
        // 잡템
        vRandom.push_back(0);
        vRandom.push_back(1);
        vRandom.push_back(2);
        vRandom.push_back(3);
        vRandom.push_back(4);
        vRandom.push_back(5);
        vRandom.push_back(6);
        vRandom.push_back(7);
        vRandom.push_back(8);
        vRandom.push_back(9);
        vRandom.push_back(10);
        vRandom.push_back(11);
        vRandom.push_back(12);
        random_shuffle(vRandom.begin(), vRandom.end());
        second = vRandom.back();
    }
    else if ((frist / 1000) == 3)
    {
        // 포션
        vRandom.push_back(0);
        vRandom.push_back(1);
        vRandom.push_back(2);
        vRandom.push_back(3);
        random_shuffle(vRandom.begin(), vRandom.end());
        second = vRandom.back();

        result.isEquipment = true;

    }
    else if ((frist / 1000) == 4)
    {
        // 방어구
        vRandom.push_back(0);
        vRandom.push_back(1);
        vRandom.push_back(2); 
        random_shuffle(vRandom.begin(), vRandom.end());
        second = 10 * vRandom.back();
        vRandom.clear();

        vRandom.push_back(0);
        vRandom.push_back(1);
        random_shuffle(vRandom.begin(), vRandom.end());
        third = vRandom.back();

        result.isEquipment = true;
    }

    result.itemCode = frist + second + third;

    GAMEDATA->SetGold(rand() % 100);
    return result;
}

void EnemyManager::ImageLoad()
{
    IMAGEMANAGER->AddImage("GolemMove", L"Image/Enemy/GolemMove.png", 8, 4);
    IMAGEMANAGER->AddImage("GolemAttack", L"Image/Enemy/GolemAttack.png", 13, 4);
}