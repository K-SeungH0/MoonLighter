#include "DungeonManager.h"

HRESULT DungeonManager::Init()
{
	return S_OK;
}

void DungeonManager::Release()
{
}

void DungeonManager::Update()
{
}

void DungeonManager::Render(HDC hdc)
{
}

void DungeonManager::RoomCreate()
{

}

void DungeonManager::DungeonLoad()
{
    string saveName = "Save/SaveDunGeonMapData";
    DWORD readBytes;
    HANDLE hFile;
    TILE_INFO tileMap[DUNGEON_TILE_X * DUNGEON_TILE_Y];
    Dungeon dungeon;

    for (int i = 1; i <= 10; i++)
    {
        saveName += to_string(i) + ".map";
        hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (ReadFile(hFile, tileMap, sizeof(TILE_INFO) * DUNGEON_TILE_X * DUNGEON_TILE_Y, &readBytes, NULL))
        {
            for (int j = 0; j < DUNGEON_TILE_X * DUNGEON_TILE_Y; j++)
            {
                dungeon.tileMap[j].collider = tileMap[j].collider;
                dungeon.tileMap[j].frameX = tileMap[j].frameX;
                dungeon.tileMap[j].frameY = tileMap[j].frameY;
                dungeon.tileMap[j].rcTile = tileMap[j].rcTile;
                dungeon.tileMap[j].type = tileMap[j].type;
            }
        }
        else
        {
            MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
        }
    }
    CloseHandle(hFile);
}
