#include "BattleScene.h"
#include "Image.h"
#include "Player.h"
HRESULT BattleScene::Init()
{
    Load();
    tileImage = IMAGEMANAGER->FindImage("Tile Set");
    backGround = IMAGEMANAGER->FindImage("Dungeon Background");
    lpPlayer = new Player();
    lpPlayer->Init();
	return S_OK;
}

void BattleScene::Release()
{
    lpPlayer->Release();
}

void BattleScene::Update()
{
    lpPlayer->Update();
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
    lpPlayer->Render(hdc);

    wsprintf(text, "�÷��̾� �̵� : ����Ű");
    TextOut(hdc, 10, 10, text, strlen(text));

    wsprintf(text, "���� : A");
    TextOut(hdc, 10, 10 + 40, text, strlen(text));

    wsprintf(text, "ȸ�� : SpaceBar");
    TextOut(hdc, 10, 10 + 80, text, strlen(text));

    wsprintf(text, "���ⱳü : 1 ~ 5");
    TextOut(hdc, 10, 10 + 120, text, strlen(text));
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
        MessageBox(g_hWnd, "�ε� ����", "����", MB_OK);
    }

    CloseHandle(hFile);
}
