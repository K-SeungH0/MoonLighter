#include "TileMapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TileMapTool::tileInfo[TILE_X * TILE_Y];
int TileMapTool::selectStage = 1;

HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    Sleep(20);

    ImageManager::GetInstance()->AddImage(
        "샘플타일", "Image/Tile.bmp", 48 * 3, 8 * 3,
        SAMPLE_TILE_X, SAMPLE_TILE_Y);
    sampleTile = ImageManager::GetInstance()->FindImage("샘플타일");

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i * TILE_X + j].frameX = 5;
            tileInfo[i * TILE_X + j].frameY = 0;
            tileInfo[i * TILE_X + j].type = TILETYPE::NONE;

            tileInfo[i * TILE_X + j].rcTile =
            {
                TILESIZE * j,
                TILESIZE * i,
                TILESIZE * (j + 1),
                TILESIZE * (i + 1)
            };
        }
    }

    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile =
            {
                TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width + (TILESIZE * j),
                (TILESIZE * j),
                TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width + (TILESIZE * j) + TILESIZE,
                (TILESIZE * j) + TILESIZE,
            };
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            switch (i)
            {
                // X = 0~1 WALL
            case 0:
            case 1:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::WALL;
                break;

                // X = 2~3 IRON
            case 2:
            case 3:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::IRON;
                break;

                // X = 4~9 RIVER
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::RIVER;
                break;

                // X = 10~11 FOREST
            case 10:
            case 11:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::FOREST;
                break;

                // X = 12~13 ICE
            case 12:
            case 13:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::ICE;
                break;
                // X = 14~15 BOSS
            case 14:
            case 15:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::BOSS;
                break;

                // X = 16~17 BOSSDIE
                // X = 18~19 NONE
            default:
                sampleTileInfo[i * SAMPLE_TILE_X + j].type = TILETYPE::NONE;
                break;
            }
        }
    }

    // UI Button
    saveButton = new Button();
    saveButton->Init("SaveButton", { TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width, TILEMAPTOOLSIZE_Y - 200 });
    saveButton->SetClick(Save, 1);

    loadButton = new Button();
    loadButton->Init("LoadButton", { TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width + 80, TILEMAPTOOLSIZE_Y - 200 });
    loadButton->SetClick(Load, 1);

    leftButton = new Button();
    leftButton->Init("LeftButton", { TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width, TILEMAPTOOLSIZE_Y - 300 });
    leftButton->SetClick(StageSelect, -1);

    rightButton = new Button();
    rightButton->Init("RightButton", { TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width + 80, TILEMAPTOOLSIZE_Y - 300 });
    rightButton->SetClick(StageSelect, 1);

    //selectStage = 1;
    return S_OK;
}

void TileMapTool::Release()
{
    SAFE_RELEASE(saveButton);
    SAFE_RELEASE(loadButton);
    SAFE_RELEASE(leftButton);
    SAFE_RELEASE(rightButton);
}

void TileMapTool::Update()
{
    // 세이브, 로드

    if (saveButton)
        saveButton->Update();
    if (loadButton)
        loadButton->Update();
    if (leftButton)
        leftButton->Update();
    if (rightButton)
        rightButton->Update();

    if (KeyManager::GetInstance()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
            Load(1);
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2))
            Load(2);
        else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3))
            Load(3);
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
        Save(1);
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2))
        Save(2);
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3))
        Save(3);


    // 마우스 왼쪽 버튼 클릭시 좌표 사용

    // 메인 영역
    rcMain =
    {
        0, 0,
        TILESIZE * TILE_X,
        TILESIZE * TILE_Y
    };

    // 샘플 영역
    rcSample =
    {
        TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width, 0,
        TILEMAPTOOLSIZE_X,
        sampleTile->GetImageInfo()->height
    };

    if (PtInRect(&rcMain, g_ptMouse))
    {
        if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_Y * TILE_X; i++)
            {
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        {
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
                            tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
                            tileInfo[i + j * TILE_X + k].type = sampleTileInfo[(ptStartSelectedFrame.y + j) * SAMPLE_TILE_X + (ptStartSelectedFrame.x + k)].type;
                        }
                    }
                    break;
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
        {
            ptStartSelectedFrame.x = g_ptMouse.x;
            ptStartSelectedFrame.y = g_ptMouse.y;
            ptSelected[0] = g_ptMouse;

        }
        else if (KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
        {
            ptEndSelectedFrame.x = g_ptMouse.x;
            ptEndSelectedFrame.y = g_ptMouse.y;
            TileSelect();
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }

    // Test
    if (KeyManager::GetInstance()->IsOnceKeyDown('Q'))
    {
        for (int i = 0; i < 16; i++)
        {
            g_testTile[i].frameX = tileInfo[i].frameX;
            g_testTile[i].frameY = tileInfo[i].frameY;
            g_testTile[i].rcTile = tileInfo[i].rcTile;
        }

        SceneManager::GetInstance()->ChageScene("Battle_1");
    }
}

void TileMapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // 샘플타일 전체
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - (sampleTile->GetImageInfo()->width), 0);

    // UI Button
    if (saveButton)
        saveButton->Render(hdc);
    if (loadButton)
        loadButton->Render(hdc);
    if (leftButton)
        leftButton->Render(hdc);
    if (rightButton)
        rightButton->Render(hdc);

    wsprintf(szText, "Stage : %d", this->selectStage);
    TextOut(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetImageInfo()->width + 20, TILEMAPTOOLSIZE_Y - 350, szText, strlen(szText));

    // 마우스 영역 표시
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // 메인 영역 전체

    for (int i = 0; i < TILE_Y * TILE_X; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY);
    }

    // 선택 영역 표시
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        //sampleTile->FrameRender(hdc,
        //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
        //    sampleTile->GetHeight() + 50,
        //    ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);

        sampleTile->FrameRender(hdc,
            g_ptMouse.x,
            g_ptMouse.y,
            ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                //sampleTile->FrameRender(hdc,
                //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                //    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                //    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

                sampleTile->FrameRender(hdc,
                    g_ptMouse.x + (j * TILESIZE),
                    g_ptMouse.y + (i * TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);
            }
        }
    }
}

void TileMapTool::Save(int stageNum)
{
    string saveName = "Save/SaveMapData";
    saveName += to_string(selectStage) + ".map";
    DWORD writtenBytes;

    HANDLE hFile = CreateFile(saveName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TileMapTool::Load(int stageNum)
{
    string saveName = "Save/SaveMapData";
    saveName += to_string(selectStage) + ".map";

    DWORD readBytes;

    HANDLE hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}

void TileMapTool::StageSelect(int num)
{
    selectStage += num;
    if (selectStage > 3) selectStage = 1;
    if (selectStage < 1) selectStage = 3;
}

void TileMapTool::TileSelect()
{
    ptStartSelectedFrame.x -= TILEMAPTOOLSIZE_X - (sampleTile->GetImageInfo()->width);
    ptEndSelectedFrame.x -= TILEMAPTOOLSIZE_X - (sampleTile->GetImageInfo()->width);

    if (ptStartSelectedFrame.x / TILESIZE >= 0 && ptStartSelectedFrame.x / TILESIZE < SAMPLE_TILE_X &&
        ptStartSelectedFrame.y / TILESIZE >= 0 && ptStartSelectedFrame.y / TILESIZE < SAMPLE_TILE_Y &&
        ptEndSelectedFrame.x / TILESIZE >= 0 && ptEndSelectedFrame.x / TILESIZE < SAMPLE_TILE_X &&
        ptEndSelectedFrame.y / TILESIZE >= 0 && ptEndSelectedFrame.y / TILESIZE < SAMPLE_TILE_Y)
    {
        ptStartSelectedFrame.x = ptStartSelectedFrame.x / TILESIZE;
        ptStartSelectedFrame.y = ptStartSelectedFrame.y / TILESIZE;
        ptEndSelectedFrame.x = ptEndSelectedFrame.x / TILESIZE;
        ptEndSelectedFrame.y = ptEndSelectedFrame.y / TILESIZE;
    }
}
