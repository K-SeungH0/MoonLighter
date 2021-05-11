#include "BattleScene.h"
#include "Image.h"

HRESULT BattleScene::Init()
{
    Load();
    tileImage = IMAGEMANAGER->FindImage("Tile Set");
    backGround = IMAGEMANAGER->FindImage("Dungeon Background");
	return S_OK;
}

void BattleScene::Release()
{

}

void BattleScene::Update()
{

}

void BattleScene::Render(HDC hdc)
{
    backGround->Render(hdc);
    for (int i = 0; i < TILE_X * TILE_Y; i++) 
    {
        tileImage->FrameRender(hdc,
            tileMap[i].rcTile.left,
            tileMap[i].rcTile.top,
            tileMap[i].frameX,
            tileMap[i].frameY,
            IMAGE_SIZE);
    }
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
