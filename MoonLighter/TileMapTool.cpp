#include "TileMapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include "Camera.h"

TILE_INFO TileMapTool::dungeonTileInfo[DUNGEON_TILE_X * DUNGEON_TILE_Y];
TILE_INFO TileMapTool::townTileInfo[TOWN_TILE_X * TOWN_TILE_Y];
//int TileMapTool::selectStage = 1;

HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);
    ImageLoad();

    lpBackGroundTile = IMAGEMANAGER->FindImage("Town_BackGround");
    currentScene = TILESCENE::TOWN;

    lpTownTileSetImage = IMAGEMANAGER->FindImage("Town_TileSet");
    lpDunGeonTileSetImage = IMAGEMANAGER->FindImage("DunGeon_TileSet");
    selectTileInfo.lpImage = IMAGEMANAGER->FindImage("Town_BigTree");
    selectTileInfo.rcTile = { 80 * 2,112 * 2,127 * 2,159 * 2 };
    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    
    lpCamera = new Camera();
    lpCamera->Init(lpBackGroundTile, nullptr, 1000);

    int offset = 60;
    for (int i = 0; i < DUNGEON_TILE_Y; i++)
    {
        for (int j = 0; j < DUNGEON_TILE_X; j++)
        {
            // 메인 영역
            if (i == 0 && j == 0)
            {
                rcDungeonMain.left = TILESIZE * j + offset;
                rcDungeonMain.top = TILESIZE * i + offset + 10;
            }
            if (i == DUNGEON_TILE_Y - 1 && j == DUNGEON_TILE_X - 1)
            {
                rcDungeonMain.right = TILESIZE * (j + 1) + offset;
                rcDungeonMain.bottom = TILESIZE * (i + 1) + offset + 10;
            }

            dungeonTileInfo[i * DUNGEON_TILE_X + j].frameX = DUNGEON_TILE_X - 1;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].frameY = DUNGEON_TILE_Y - 1;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].lpImage = nullptr;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].type = TILETYPE::NONE;

            dungeonTileInfo[i * DUNGEON_TILE_X + j].rcTile.left = TILESIZE * j + offset;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].rcTile.top = TILESIZE * i + offset + 10;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].rcTile.right = TILESIZE * (j + 1) + offset;
            dungeonTileInfo[i * DUNGEON_TILE_X + j].rcTile.bottom = TILESIZE * (i + 1) + offset + 10;
        }
    }

    for (int i = 0; i < TOWN_TILE_Y; i++)
    {
        for (int j = 0; j < TOWN_TILE_X; j++)
        {
            // 메인 영역
            if (i == 0 && j == 0)
            {
                rcTownMain.left = TILESIZE * j;
                rcTownMain.top = TILESIZE * i;
            }
            if (i == TOWN_TILE_Y - 1 && j == TOWN_TILE_X - 1)
            {
                rcTownMain.right = TILESIZE * (j + 1);
                rcTownMain.bottom = TILESIZE * (i + 1);
            }

            townTileInfo[i * TOWN_TILE_X + j].frameX = TOWN_TILE_SET_X - 1;
            townTileInfo[i * TOWN_TILE_X + j].frameY = TOWN_TILE_SET_Y - 1;
            townTileInfo[i * TOWN_TILE_X + j].lpImage = nullptr;
            townTileInfo[i * TOWN_TILE_X + j].type = TILETYPE::NONE;

            townTileInfo[i * TOWN_TILE_X + j].rcTile.left = TILESIZE * j + ((TILESIZE) / 4);
            townTileInfo[i * TOWN_TILE_X + j].rcTile.top = TILESIZE * i + ((TILESIZE) / 4);
            townTileInfo[i * TOWN_TILE_X + j].rcTile.right = TILESIZE * (j + 1) +((TILESIZE) / 4);
            townTileInfo[i * TOWN_TILE_X + j].rcTile.bottom = TILESIZE * (i + 1) + ((TILESIZE) / 4);
        }
    }

    for (int i = 0; i < DUNGEON_TILE_SET_Y; i++)
    {
        for (int j = 0; j < DUNGEON_TILE_SET_X; j++)
        {
            // 샘플 영역
            if (i == 0 && j == 0)
            {
                rcDungeonTileSet.left = TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j);
                rcDungeonTileSet.top = (TILESIZE * i);
            }
            if (i == DUNGEON_TILE_SET_Y - 1 && j == DUNGEON_TILE_SET_X - 1)
            {
                rcDungeonTileSet.right = TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j) + TILESIZE;
                rcDungeonTileSet.bottom = (TILESIZE * i) + TILESIZE;
            }
            dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].rcTile.left = TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j);
            dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].rcTile.top = (TILESIZE * i);
            dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].rcTile.right = TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j) + TILESIZE;
            dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].rcTile.bottom = (TILESIZE * i) + TILESIZE;

            switch (i)
            {
                // 첫번째줄 BreakAble
                case 0:
                    dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::BREAKABLE;
                    break;
                // 두번째줄 Wall
                case 1:
                    if(j>=0 && j <5)
                        dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::WALL;
                    else
                        dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::NONE;

                    break;
                // 세번째줄 Hole
                case 2:
                case 3:
                case 4:
                    if (j >= 0 && j < 3)
                        dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::HOLE;
                    else
                        dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::NONE;
                    break;
                default:
                    dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::NONE;
                    break;

            }
            if (i == DUNGEON_TILE_SET_Y - 1 && j == DUNGEON_TILE_SET_X - 1)
            {
                dunGeonTileSetInfo[i * DUNGEON_TILE_SET_X + j].type = TILETYPE::SPAWN;
            }
        }
    }

    for (int y = 0; y < TOWN_TILE_SET_Y; y++)
    {
        for (int x = 0; x < TOWN_TILE_SET_X; x++)
        {
            if (x == 0 && y == 0)
            {
                rcTownTileSet.left = TILEMAPTOOLSIZE_X - (lpTownTileSetImage->GetImageInfo()->width * 2) + (TILESIZE*2 * x) - TILESIZE;
                rcTownTileSet.top = (TILESIZE * 2 * y);
            }
            if (y == TOWN_TILE_SET_Y - 1 && x == TOWN_TILE_SET_X - 1)
            {
                rcTownTileSet.right = TILEMAPTOOLSIZE_X - (lpTownTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * 2 * x ) + TILESIZE * 2 - TILESIZE;
                rcTownTileSet.bottom = (TILESIZE * 2 * y) + TILESIZE * 2;
            }
            townTileSetInfo[y * TOWN_TILE_SET_X + x].rcTile.left = TILEMAPTOOLSIZE_X - (lpTownTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * 2 * x) - TILESIZE;
            townTileSetInfo[y * TOWN_TILE_SET_X + x].rcTile.top = (TILESIZE * 2 * y);
            townTileSetInfo[y * TOWN_TILE_SET_X + x].rcTile.right = TILEMAPTOOLSIZE_X - (lpTownTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * 2 * x) + TILESIZE * 2 - TILESIZE;
            townTileSetInfo[y * TOWN_TILE_SET_X + x].rcTile.bottom = (TILESIZE * 2 * y) + TILESIZE * 2;
        }
    }

    // UI Button
    saveButton = new Button();
    saveButton->Init("Save", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width - 80, TILEMAPTOOLSIZE_Y - 150 });
    saveButton->SetTileMap(this);
    saveButton->SetClick(&TileMapTool::Save, 1);

    loadButton = new Button();
    loadButton->Init("Load", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width + 80, TILEMAPTOOLSIZE_Y - 150 });
    loadButton->SetTileMap(this);
    loadButton->SetClick(&TileMapTool::Load, 1);
    
    leftButton = new Button();
    leftButton->Init("Left", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width - 80, TILEMAPTOOLSIZE_Y - 200 });
    leftButton->SetTileMap(this);
    leftButton->SetClick(&TileMapTool::StageSelect, -1);
    
    rightButton = new Button();
    rightButton->Init("Right", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width + 80, TILEMAPTOOLSIZE_Y - 200 });
    rightButton->SetTileMap(this);
    rightButton->SetClick(&TileMapTool::StageSelect, 1);
    
    townSelectButton = new Button();
    townSelectButton->Init("Town", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width - 80, TILEMAPTOOLSIZE_Y - 250 });
    townSelectButton->SetTileMap(this);
    townSelectButton->SetClick(&TileMapTool::SceneSelect, 0);
    
    dungeonSelectButton = new Button();
    dungeonSelectButton->Init("Dungeon", { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width + 80, TILEMAPTOOLSIZE_Y - 250 });
    dungeonSelectButton->SetTileMap(this);
    dungeonSelectButton->SetClick(&TileMapTool::SceneSelect, 1);

    exitButton = new Button();
    exitButton->Init("Exit", { TILEMAPTOOLSIZE_X - 600,  TILEMAPTOOLSIZE_Y - 150 });
    exitButton->SetTileMap(this);
    exitButton->SetClick(&TileMapTool::SceneSelect, 2);

    selectStage = 1;
    selectPosX = 0;
    selectPosY = 0;
    timer = 0;
    overTile = true;
    overlapColliderTile = true;
    return S_OK;
}

void TileMapTool::Release()
{
    SAFE_RELEASE(saveButton);
    SAFE_RELEASE(loadButton);
    SAFE_RELEASE(leftButton);
    SAFE_RELEASE(rightButton);
    SAFE_RELEASE(townSelectButton);
    SAFE_RELEASE(dungeonSelectButton);
    SAFE_RELEASE(exitButton);

    for (int i = 0; i < TOWN_TILE_SET_Y * TOWN_TILE_SET_X; i++)
    {
        townTileSetInfo[i].lpImage = nullptr;
    }
    DeleteObject(hSelectedBrush);
    IMAGEMANAGER->DeleteAll();
}

void TileMapTool::Update()
{

    timer += DELTATIME;
    if (timer >= 0.1f)
    {
        timer -= 0.1f;
        IMAGEMANAGER->FindImage("Town_BigTree")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_BigTree")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_BigTree")->GetMaxFrameX());
        IMAGEMANAGER->FindImage("Town_Tree")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_Tree")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_Tree")->GetMaxFrameX());
        IMAGEMANAGER->FindImage("Town_Well")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_Well")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_Well")->GetMaxFrameX());
        IMAGEMANAGER->FindImage("Town_WillHome")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_WillHome")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_WillHome")->GetMaxFrameX());
        IMAGEMANAGER->FindImage("Town_House")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_House")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_House")->GetMaxFrameX());
    }

    if (currentScene == TILESCENE::TOWN)
    {
        if (KEYMANAGER->IsStayKeyDown(VK_DOWN) || KEYMANAGER->IsStayKeyDown('S'))
        {
            lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x, lpCamera->GetCameraPos().y + 5 });
            if (lpCamera->GetCameraPos().y > lpBackGroundTile->GetHeight() - WINSIZE_Y)
                lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x, (FLOAT)lpBackGroundTile->GetHeight() - WINSIZE_Y });
        }
        if (KEYMANAGER->IsStayKeyDown(VK_UP) || KEYMANAGER->IsStayKeyDown('W'))
        {
            lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x, lpCamera->GetCameraPos().y - 5 });
            if (lpCamera->GetCameraPos().y < 0)
                lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x, 0 });
        }
        if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) || KEYMANAGER->IsStayKeyDown('D'))
        {
            lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x + 5, lpCamera->GetCameraPos().y });
            if (lpCamera->GetCameraPos().x > lpBackGroundTile->GetWidth() - WINSIZE_X)
                lpCamera->SetCameraPos({ (FLOAT)lpBackGroundTile->GetWidth() - WINSIZE_X,lpCamera->GetCameraPos().y });
        }
        if (KEYMANAGER->IsStayKeyDown(VK_LEFT) || KEYMANAGER->IsStayKeyDown('A'))
        {
            lpCamera->SetCameraPos({ lpCamera->GetCameraPos().x - 5, lpCamera->GetCameraPos().y });
            if (lpCamera->GetCameraPos().x < 0)
                lpCamera->SetCameraPos({ 0 , lpCamera->GetCameraPos().y });
        }
    }

    POINT ptMouse = g_ptMouse;
    ptMouse.x += lpCamera->GetCameraPos().x;
    ptMouse.y += lpCamera->GetCameraPos().y;

    if (currentScene == TILESCENE::DUNGEON)
    {
        if (PtInRect(&rcDungeonTileSet, g_ptMouse))
        {
            if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
            {
                selectedFrame.x = g_ptMouse.x;
                selectedFrame.y = g_ptMouse.y;
                TileSelect();
            }
        }

        if (PtInRect(&rcDungeonMain, ptMouse))
        {
            if (g_ptMouse.x <= WINSIZE_X && g_ptMouse.y <= WINSIZE_Y)
            {
                if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
                {
                    for (int i = 0; i < DUNGEON_TILE_Y * DUNGEON_TILE_X; i++)
                    {
                        if (PtInRect(&(dungeonTileInfo[i].rcTile), ptMouse))
                        {
                            dungeonTileInfo[i].frameX = selectedFrame.x;
                            dungeonTileInfo[i].frameY = selectedFrame.y;
                            //dungeonTileInfo[i].lpImage = lpTownTileSetImage;
                            dungeonTileInfo[i].type = dunGeonTileSetInfo[(selectedFrame.y) * DUNGEON_TILE_SET_X + (selectedFrame.x)].type;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (PtInRect(&rcTownTileSet, g_ptMouse))
        {
            if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
            {
                overlapColliderTile = true;
                overTile = true;
                selectedFrame.x = g_ptMouse.x;
                selectedFrame.y = g_ptMouse.y;
                TileSelect();
            }
        }

        else if (PtInRect(&rcTownMain, ptMouse))
        {
            overlapColliderTile = true;
            for (int i = 0; i < TOWN_TILE_Y * TOWN_TILE_X; i++)
            {
                if (townTileInfo[i].lpImage)
                {
                    RECT temp;
                    RECT rcCompare;

                    rcCompare.left = selectTileInfo.rcTile.left + selectPosX + lpCamera->GetCameraPos().x;
                    rcCompare.right = selectTileInfo.rcTile.right + selectPosX + lpCamera->GetCameraPos().x;
                    rcCompare.top = selectTileInfo.rcTile.top + selectPosY + lpCamera->GetCameraPos().y;
                    rcCompare.bottom = selectTileInfo.rcTile.bottom + selectPosY + lpCamera->GetCameraPos().y;
                    if (IntersectRect(&temp, &townTileInfo[i].collider, &rcCompare))
                    {
                        overlapColliderTile = false;
                    }
                }
                POINT ptMouse = g_ptMouse;

                ptMouse.x += lpCamera->GetCameraPos().x;
                ptMouse.y += lpCamera->GetCameraPos().y;

                if (PtInRect(&(townTileInfo[i].rcTile), ptMouse) && selectTileInfo.lpImage)
                {
                    overTile = true;
                    if (selectTileInfo.lpImage)
                    {
                        int testX = selectTileInfo.lpImage->GetFrameWidth() * 2 / TILESIZE;
                        int testY = selectTileInfo.lpImage->GetFrameHeight() * 2 / TILESIZE;
                        for (int y = 0; y < testY; y++)
                        {
                            for (int x = 0; x < testX; x++)
                            {
                                if ((i % TOWN_TILE_X) + x >= TOWN_TILE_X)
                                    overTile = false;
                                if ((i / TOWN_TILE_X) + y >= TOWN_TILE_Y)
                                    overTile = false;
                            }
                        }
                    }
                }
            }

            if (g_ptMouse.x <= WINSIZE_X && g_ptMouse.y <= WINSIZE_Y * 1.5)
            {
                if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
                {
                    for (int i = 0; i < TOWN_TILE_Y * TOWN_TILE_X; i++)
                    {
                        if (PtInRect(&(townTileInfo[i].rcTile), ptMouse) && overTile && overlapColliderTile)
                        {
                            townTileInfo[i].frameX = selectedFrame.x;
                            townTileInfo[i].frameY = selectedFrame.y;

                            townTileInfo[i].lpImage = selectTileInfo.lpImage;
                            townTileInfo[i].collider.left = selectTileInfo.rcTile.left + selectPosX + lpCamera->GetCameraPos().x;
                            townTileInfo[i].collider.top = selectTileInfo.rcTile.top + selectPosY + lpCamera->GetCameraPos().y;
                            townTileInfo[i].collider.right = selectTileInfo.rcTile.right + selectPosX + lpCamera->GetCameraPos().x;
                            townTileInfo[i].collider.bottom = selectTileInfo.rcTile.bottom + selectPosY + lpCamera->GetCameraPos().y;
                            
                            townTileInfo[i].type = townTileSetInfo[(selectedFrame.y) * TOWN_TILE_SET_X + (selectedFrame.x)].type;
                            break;
                        }
                    }
                }
            }
        }
    }
    // 세이브, 로드
    saveButton->Update();
    loadButton->Update();
    leftButton->Update();
    rightButton->Update();
    townSelectButton->Update();
    dungeonSelectButton->Update();
    exitButton->Update();

    if (KeyManager::GetInstance()->IsOnceKeyDown('Q'))
    {
        SceneManager::GetInstance()->ChageScene("Battle");
    }
    if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
    {
        SCENEMANAGER->ChageScene("Title", "LodingScene");
    }
}

void TileMapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // 타일 배경
    lpCamera->CameraRender(hdc, { 0,0 }, lpBackGroundTile);

    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);

    if (currentScene == TILESCENE::TOWN)
    {
        // 메인 영역 전체
        for (int i = 0; i < TOWN_TILE_Y * TOWN_TILE_X; i++)
        {
            POINT ptMouse = g_ptMouse;

            ptMouse.x += lpCamera->GetCameraPos().x;
            ptMouse.y += lpCamera->GetCameraPos().y;

            if (PtInRect(&(townTileInfo[i].rcTile), ptMouse))
            {
                if (townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x >= 0 && townTileInfo[i].rcTile.right - lpCamera->GetCameraPos().x <= WINSIZE_X &&
                    townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y >= 0 && townTileInfo[i].rcTile.bottom - lpCamera->GetCameraPos().y < WINSIZE_Y * 1.5f)
                {
                    HBRUSH myBrush;
                    if(overTile && overlapColliderTile)
                        myBrush = (HBRUSH)CreateSolidBrush(RGB(100, 255, 175));
                    else
                        myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 100, 100));

                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                    if(selectTileInfo.lpImage)
                    for (int y = 0; y < selectTileInfo.lpImage->GetFrameHeight() * 2 / TILESIZE; y++)
                    {
                        for (int x = 0; x < selectTileInfo.lpImage->GetFrameWidth() * 2 / TILESIZE; x++)
                        {
                            Rectangle(hdc,
                                townTileInfo[i + TOWN_TILE_X * y + x].rcTile.left - lpCamera->GetCameraPos().x,
                                townTileInfo[i + TOWN_TILE_X * y + x].rcTile.top - lpCamera->GetCameraPos().y,
                                townTileInfo[i + TOWN_TILE_X * y + x].rcTile.right - lpCamera->GetCameraPos().x,
                                townTileInfo[i + TOWN_TILE_X * y + x].rcTile.bottom - lpCamera->GetCameraPos().y);
                        }
                    }
                    Rectangle(hdc, townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x, townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y, townTileInfo[i].rcTile.right - lpCamera->GetCameraPos().x, townTileInfo[i].rcTile.bottom - lpCamera->GetCameraPos().y);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(myBrush);
                    selectPosX = townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x;
                    selectPosY = townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y;
                }
            }
            else
            {
                SelectObject(hdc, hSelectedBrush);

                if (townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x >= 0 && townTileInfo[i].rcTile.right - lpCamera->GetCameraPos().x <= WINSIZE_X &&
                    townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y >= 0 && townTileInfo[i].rcTile.bottom - lpCamera->GetCameraPos().y < WINSIZE_Y * 1.5f)
                    Rectangle(hdc,
                        townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x,
                        townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y,
                        townTileInfo[i].rcTile.right - lpCamera->GetCameraPos().x,
                        townTileInfo[i].rcTile.bottom - lpCamera->GetCameraPos().y);
            }
            SelectObject(hdc, hOldSelectedBrush);

            if (townTileInfo[i].lpImage)
            {
                townTileInfo[i].lpImage->FrameRender(hdc,
                    townTileInfo[i].rcTile.left - lpCamera->GetCameraPos().x,
                    townTileInfo[i].rcTile.top - lpCamera->GetCameraPos().y,
                    townTileInfo[i].lpImage->GetCurrentFrameX(),
                    0, IMAGE_SIZE);

                if (isDebugMode)
                Rectangle(hdc,
                    townTileInfo[i].collider.left - lpCamera->GetCameraPos().x,
                    townTileInfo[i].collider.top - lpCamera->GetCameraPos().y,
                    townTileInfo[i].collider.right - lpCamera->GetCameraPos().x,
                    townTileInfo[i].collider.bottom - lpCamera->GetCameraPos().y);
            }
        }

        // selectTileInfo->Image 에서 Width 받아와서 TILESIZE로 나누고
        // PtInRect(&(townTileInfo[i].rcTile), 위 값)
        // 선택된 타일 + 위 값을 초록색으로 표시
        // 선택 타일
        if(selectTileInfo.lpImage)
        selectTileInfo.lpImage->FrameRender(hdc,
            selectPosX, selectPosY,
            selectTileInfo.lpImage->GetCurrentFrameX(),
            selectTileInfo.lpImage->GetCurrentFrameY(),
            IMAGE_SIZE);
        
        if(isDebugMode)
        Rectangle(hdc,
            selectTileInfo.rcTile.left + selectPosX,
            selectTileInfo.rcTile.top + selectPosY,
            selectTileInfo.rcTile.right + selectPosX,
            selectTileInfo.rcTile.bottom + selectPosY);

        // 샘플타일 전체
        Rectangle(hdc, rcTownTileSet.left, rcTownTileSet.top, rcTownTileSet.right, rcTownTileSet.bottom);

        for (int i = 0; i < TOWN_TILE_SET_Y * TOWN_TILE_SET_X; i++)
        {
            if (PtInRect(&townTileSetInfo[i].rcTile, g_ptMouse))
            {
                HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                Rectangle(hdc, townTileSetInfo[i].rcTile.left, townTileSetInfo[i].rcTile.top, townTileSetInfo[i].rcTile.right, townTileSetInfo[i].rcTile.bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);
            }
            else
                Rectangle(hdc, townTileSetInfo[i].rcTile.left, townTileSetInfo[i].rcTile.top, townTileSetInfo[i].rcTile.right, townTileSetInfo[i].rcTile.bottom);
        }
        SelectObject(hdc, hOldSelectedBrush);
        lpTownTileSetImage->Render(hdc, TILEMAPTOOLSIZE_X - (lpTownTileSetImage->GetImageInfo()->width * 2) - TILESIZE, 0, IMAGE_SIZE);
    }
    else // DunGeon
    {
        // 샘플타일 전체
        Rectangle(hdc, rcDungeonTileSet.left, rcDungeonTileSet.top, rcDungeonTileSet.right, rcDungeonTileSet.bottom);
        for (int i = 0; i < DUNGEON_TILE_SET_Y * DUNGEON_TILE_SET_X; i++)
        {
            if (PtInRect(&dunGeonTileSetInfo[i].rcTile, g_ptMouse))
            {
                HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                Rectangle(hdc, dunGeonTileSetInfo[i].rcTile.left, dunGeonTileSetInfo[i].rcTile.top, dunGeonTileSetInfo[i].rcTile.right, dunGeonTileSetInfo[i].rcTile.bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);
            }
            else
            {
                if (dunGeonTileSetInfo[i].type == TILETYPE::SPAWN)
                {
                    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 128));
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                    Rectangle(hdc, dunGeonTileSetInfo[i].rcTile.left, dunGeonTileSetInfo[i].rcTile.top, dunGeonTileSetInfo[i].rcTile.right, dunGeonTileSetInfo[i].rcTile.bottom);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(myBrush);
                }
                else
                    Rectangle(hdc, dunGeonTileSetInfo[i].rcTile.left, dunGeonTileSetInfo[i].rcTile.top, dunGeonTileSetInfo[i].rcTile.right, dunGeonTileSetInfo[i].rcTile.bottom);
            }
        }
        SelectObject(hdc, hOldSelectedBrush);
        lpDunGeonTileSetImage->Render(hdc, TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2),
            0, IMAGE_SIZE);

        // 메인 영역 전체
        for (int i = 0; i < DUNGEON_TILE_Y * DUNGEON_TILE_X; i++)
        {
            if (PtInRect(&(dungeonTileInfo[i].rcTile), g_ptMouse))
            {
                HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 0));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                Rectangle(hdc, dungeonTileInfo[i].rcTile.left, dungeonTileInfo[i].rcTile.top, dungeonTileInfo[i].rcTile.right, dungeonTileInfo[i].rcTile.bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);

                selectPosX = (dungeonTileInfo[i].rcTile.left + dungeonTileInfo[i].rcTile.right) / 2;
                selectPosY = (dungeonTileInfo[i].rcTile.top + dungeonTileInfo[i].rcTile.bottom) / 2;
            }
            else
            {
                SelectObject(hdc, hSelectedBrush);
                Rectangle(hdc, dungeonTileInfo[i].rcTile.left, dungeonTileInfo[i].rcTile.top, dungeonTileInfo[i].rcTile.right, dungeonTileInfo[i].rcTile.bottom);
            }
            SelectObject(hdc, hOldSelectedBrush);

            if (dungeonTileInfo[i].type == TILETYPE::SPAWN)
            {
                HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 128));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                Rectangle(hdc, dungeonTileInfo[i].rcTile.left, dungeonTileInfo[i].rcTile.top, dungeonTileInfo[i].rcTile.right, dungeonTileInfo[i].rcTile.bottom);
                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);
            }
            else
            lpDunGeonTileSetImage->FrameRender(hdc,
                dungeonTileInfo[i].rcTile.left,
                dungeonTileInfo[i].rcTile.top,
                dungeonTileInfo[i].frameX,
                dungeonTileInfo[i].frameY,
                IMAGE_SIZE);
        }

        // 선택된 타일

        if (dunGeonTileSetInfo[(selectedFrame.y) * DUNGEON_TILE_SET_X + (selectedFrame.x)].type == TILETYPE::SPAWN)
        {
            HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 128));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
            Rectangle(hdc, g_ptMouse.x - 32, g_ptMouse.y - 32, g_ptMouse.x + 32, g_ptMouse.y + 32);
            SelectObject(hdc, oldBrush);
            DeleteObject(myBrush);
        }
        else
        lpDunGeonTileSetImage->FrameRender(hdc,
            selectPosX,//g_ptMouse.x,
            selectPosY,//g_ptMouse.y,
            selectedFrame.x,
            selectedFrame.y,
            IMAGE_SIZE,
            true);
    }

    // UI Button
    saveButton->Render(hdc);
    loadButton->Render(hdc);
    townSelectButton->Render(hdc);
    dungeonSelectButton->Render(hdc);
    exitButton->Render(hdc);

    if (currentScene == TILESCENE::DUNGEON)
    {
        leftButton->Render(hdc);
        rightButton->Render(hdc);
        wsprintf(szText, "DunGeon %d", this->selectStage);
        FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - lpTownTileSetImage->GetImageInfo()->width - 11 * 9 / 2 + (LONG)lpCamera->GetCameraPos().x, TILEMAPTOOLSIZE_Y - 300 + (LONG)lpCamera->GetCameraPos().y }, 18, szText, RGB(0, 0, 0));
    }

    //POINT ptMouse = g_ptMouse;

    //ptMouse.x += lpCamera->GetCameraPos().x;
    //ptMouse.y += lpCamera->GetCameraPos().y;

    //wsprintf(szText, "+마우스 pos : %d %d", ptMouse.x, ptMouse.y);
    //FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - 300,  TILEMAPTOOLSIZE_Y - 200 }, 18, szText, RGB(0, 0, 0));

    //POINT _ptMouse = g_ptMouse;

    //_ptMouse.x -= lpCamera->GetCameraPos().x;
    //_ptMouse.y -= lpCamera->GetCameraPos().y;

    //wsprintf(szText, "-마우스 pos : %d %d", _ptMouse.x, _ptMouse.y);
    //FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - 300,  TILEMAPTOOLSIZE_Y - 250 }, 18, szText, RGB(0, 0, 0));

    //wsprintf(szText, "ㄹㅇ 마우스 pos : %d %d", g_ptMouse.x, g_ptMouse.y);
    //FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - 300,  TILEMAPTOOLSIZE_Y - 300 }, 18, szText, RGB(0, 0, 0));
}

void TileMapTool::Save(int stageNum)
{
    string saveName;
    DWORD writtenBytes;
    HANDLE hFile;
    switch (currentScene)
    {
    case TILESCENE::TOWN:
        saveName = "Save/SaveTownMapData.map";

        for (int i = 0; i < TOWN_TILE_X * TOWN_TILE_Y; i++)
        {
            if (townTileInfo[i].lpImage)
            {
                townTileInfo[i].lpImage = nullptr;
            }
        }

        hFile = CreateFile(saveName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (WriteFile(hFile, townTileInfo, sizeof(TILE_INFO) * TOWN_TILE_X * TOWN_TILE_Y, &writtenBytes, NULL))
        {

        }
        else
        {
            MessageBox(g_hWnd, "세이브 실패", "실패", MB_OK);
        }

        CloseHandle(hFile);
        break;
    case TILESCENE::DUNGEON:
        saveName = "Save/SaveDunGeonMapData";
        saveName += to_string(selectStage) + ".map";

        hFile = CreateFile(saveName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (WriteFile(hFile, dungeonTileInfo, sizeof(TILE_INFO) * DUNGEON_TILE_X * DUNGEON_TILE_Y, &writtenBytes, NULL))
        {
        }
        else
        {
            MessageBox(g_hWnd, "세이브 실패", "실패", MB_OK);
        }

        CloseHandle(hFile);
        break;
    }

    Load(1);
}

void TileMapTool::Load(int stageNum)
{
    string saveName;
    DWORD readBytes;
    HANDLE hFile;

    switch (currentScene)
    {
    case TILESCENE::TOWN:
        saveName = "Save/SaveTownMapData.map";
        
        hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (ReadFile(hFile, townTileInfo, sizeof(TILE_INFO) * TOWN_TILE_X * TOWN_TILE_Y, &readBytes, NULL))
        {
            for (int i = 0; i < TOWN_TILE_Y * TOWN_TILE_X; i++)
            {
                townTileInfo[i].lpImage = GetObjectInfo(townTileInfo[i].frameX, townTileInfo[i].frameY).lpSelectTile;
            }
        }
        else
        {
            MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
        }
        CloseHandle(hFile);
        break;
    case TILESCENE::DUNGEON:
        saveName = "Save/SaveDunGeonMapData";
        saveName += to_string(selectStage) + ".map";
        
        hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (ReadFile(hFile, dungeonTileInfo, sizeof(TILE_INFO) * DUNGEON_TILE_X * DUNGEON_TILE_Y, &readBytes, NULL))
        {

        }
        else
        {
            MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
        }
        CloseHandle(hFile);
        break;
    }
}

void TileMapTool::SceneSelect(int num)
{
    switch (num)
    {
    case (int)TILESCENE::TOWN:
        lpBackGroundTile = IMAGEMANAGER->FindImage("Town_BackGround");
        currentScene = TILESCENE::TOWN;
        break;
    case (int)TILESCENE::DUNGEON:
        lpBackGroundTile = IMAGEMANAGER->FindImage("Dungeon_Background");
        currentScene = TILESCENE::DUNGEON;
        break;
    case (int)TILESCENE::EXIT:
        SCENEMANAGER->ChageScene("Title", "LodingScene");
        return;
    }
    lpCamera->Init(lpBackGroundTile, nullptr, 1000);
    lpCamera->SetCameraPos({ 0,0 });
}

void TileMapTool::StageSelect(int num)
{
    selectStage += num;
    if (selectStage > 10) selectStage = 1;
    if (selectStage < 1) selectStage = 10;

    for (int i = 0; i < DUNGEON_TILE_X * DUNGEON_TILE_Y; i++)
    {
        dungeonTileInfo[i].frameX = DUNGEON_TILE_X - 1;
        dungeonTileInfo[i].frameY = DUNGEON_TILE_Y - 1;
        dungeonTileInfo[i].lpImage = nullptr;
        dungeonTileInfo[i].type = TILETYPE::NONE;

    }
}

void TileMapTool::TileSelect()
{
    switch (currentScene)
    {
    case TILESCENE::TOWN:
        selectedFrame.x -= rcTownTileSet.left;

        if (selectedFrame.x / ((TILESIZE) * 2) >= 0 &&
            selectedFrame.x / ((TILESIZE) * 2) < TOWN_TILE_SET_X &&
            selectedFrame.y / ((TILESIZE) * 2) >= 0 &&
            selectedFrame.y / ((TILESIZE) * 2) < TOWN_TILE_SET_Y)
            {
                selectedFrame.x = selectedFrame.x / ((TILESIZE) * 2);
                selectedFrame.y = selectedFrame.y / ((TILESIZE) * 2);

                selectTileInfo.lpImage = GetObjectInfo(selectedFrame.x, selectedFrame.y).lpSelectTile;
                selectTileInfo.rcTile = GetObjectInfo(selectedFrame.x, selectedFrame.y).rcTile;
            }
        break;
    case TILESCENE::DUNGEON:
        selectedFrame.x -= TILEMAPTOOLSIZE_X - (lpDunGeonTileSetImage->GetImageInfo()->width * 2);

        if (selectedFrame.x / TILESIZE >= 0 && selectedFrame.x / TILESIZE < DUNGEON_TILE_SET_X &&
            selectedFrame.y / TILESIZE >= 0 && selectedFrame.y / TILESIZE < DUNGEON_TILE_SET_Y)
        {
            selectedFrame.x = selectedFrame.x / TILESIZE;
            selectedFrame.y = selectedFrame.y / TILESIZE;
        }
        break;
    }
}

ObjectTileInfo TileMapTool::GetObjectInfo(int x, int y)
{
    if (x == 0 && y == 0)
        return { IMAGEMANAGER->FindImage("Town_BigTree"), {80 * 2,112 * 2,127 * 2,159 * 2}};
    if (x == 1 && y == 0)
        return { IMAGEMANAGER->FindImage("Town_Tree"), {32 * 2,48 * 2,63 * 2,79 * 2} };
    if (x == 2 && y == 0)
        return { IMAGEMANAGER->FindImage("Town_Well"), {25 * 2,32 * 2,75 * 2,78 * 2} };
    if (x == 3 && y == 0)
        return { IMAGEMANAGER->FindImage("Town_WillHome"), {20 * 2,64 * 2,245 * 2,203 * 2} };

    if (x == 0 && y == 1)
        return { IMAGEMANAGER->FindImage("Town_House_1"), {11 * 2,42 *2,150* 2,176 * 2}  };
    if (x == 1 && y == 1)
        return { IMAGEMANAGER->FindImage("Town_House_2"), {9*2,26 *2,190 * 2,241 * 2} };
    if (x == 2 && y == 1)
        return { IMAGEMANAGER->FindImage("Town_House"), {9 * 2,5 * 2,214*2,149*2} };
    if (x == 3 && y == 1)
        return { IMAGEMANAGER->FindImage("Town_BigStone"), {15*2,3*2,53*2,55*2} };

    if (x == 0 && y == 2)
        return { IMAGEMANAGER->FindImage("Town_Sign_1"), {0 , 0, 32 * 2, 32 * 2} };
    if (x == 1 && y == 2)
        return { IMAGEMANAGER->FindImage("Town_Sign_2"),  {0 , 0, 32 * 2, 32 * 2} };
    if (x == 2 && y == 2)                                
        return { IMAGEMANAGER->FindImage("Town_Sign_3"),  {0 , 0, 32 * 2, 32 * 2} };
    if (x == 3 && y == 2)                                 
        return { IMAGEMANAGER->FindImage("Town_Sign_4"),  {0 , 0, 32 * 2, 32 * 2} };
    if (x == 0 && y == 3)                                
        return { IMAGEMANAGER->FindImage("Town_Sign_5"),  {0 , 0, 32 * 2, 32 * 2} };
    if (x == 1 && y == 3)                                 
        return { IMAGEMANAGER->FindImage("Town_Sign_6"),  {0 , 0, 32 * 2, 32 * 2} };
    if (x == 2 && y == 3)
        return { IMAGEMANAGER->FindImage("Town_Post"),  {21*2 , 24*2, 43 * 2, 47 * 2} };
    if (x == 3 && y == 3)
        return { IMAGEMANAGER->FindImage("Town_Board"),  {21* 2 , 13 * 2, 75 * 2, 61 * 2} };

    if (x == 0 && y == 4)
        return { IMAGEMANAGER->FindImage("Town_Barrel"), {0 , 0, 32 * 2, 32 * 2} };
    if (x == 1 && y == 4)
        return {IMAGEMANAGER->FindImage("Town_Bench_01"), {0,0,64*2,32*2} };
    if (x == 2 && y == 4)
        return { IMAGEMANAGER->FindImage("Town_Bench_02"), {0,0,64 * 2,64 * 2} }; 
    if (x == 3 && y == 4)
        return { IMAGEMANAGER->FindImage("Town_Bench_03"), {0,0,64 * 2,64 * 2} }; 

    if (x == 0 && y == 5)
        return { IMAGEMANAGER->FindImage("Town_BlackSmithHouse"), {0,48 * 2,287 * 2,223 * 2} };
    if (x == 1 && y == 5)
        return { IMAGEMANAGER->FindImage("Town_WitchHouse"), {16,176 * 2,271 * 2,335 * 2} };

    return { nullptr, {0,0,0,0}};
}

void TileMapTool::ImageLoad()
{
    // 이미지 추가
    IMAGEMANAGER->AddImage("Dungeon_Background", L"Image/Map/Dungeon_BackGround.png");
    IMAGEMANAGER->AddImage("DunGeon_TileSet", L"Image/Map/DunGeon_TileSet.png", DUNGEON_TILE_SET_X, DUNGEON_TILE_SET_Y);

    IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");
    IMAGEMANAGER->AddImage("Town_TileSet", L"Image/Map/Town_TileSet_.png", TOWN_TILE_SET_X, TOWN_TILE_SET_Y);

    IMAGEMANAGER->AddImage("Town_BigTree", L"Image/Object/Town/Town_BigTree.png", 11, 1);
    IMAGEMANAGER->AddImage("Town_Tree", L"Image/Object/Town/Town_Tree.png", 10, 1);
    IMAGEMANAGER->AddImage("Town_Well", L"Image/Object/Town/Town_Well.png", 8, 1);

    IMAGEMANAGER->AddImage("Town_WillHome", L"Image/Object/Town/Town_WillHome.png", 13, 1);
    IMAGEMANAGER->AddImage("Town_House", L"Image/Object/Town/Town_House.png", 12, 1);
    IMAGEMANAGER->AddImage("Town_House_1", L"Image/Object/Town/Town_House_1.png");
    IMAGEMANAGER->AddImage("Town_House_2", L"Image/Object/Town/Town_House_2.png");

    IMAGEMANAGER->AddImage("Town_Barrel", L"Image/Object/Town/Town_Barrel.png");
    IMAGEMANAGER->AddImage("Town_Bench_01", L"Image/Object/Town/Town_Bench_01.png");
    IMAGEMANAGER->AddImage("Town_Bench_02", L"Image/Object/Town/Town_Bench_02.png");
    IMAGEMANAGER->AddImage("Town_Bench_03", L"Image/Object/Town/Town_Bench_03.png");
    IMAGEMANAGER->AddImage("Town_BigStone", L"Image/Object/Town/Town_BigStone.png");

    IMAGEMANAGER->AddImage("Town_Sign_1", L"Image/Object/Town/Town_Sign_1.png");
    IMAGEMANAGER->AddImage("Town_Sign_2", L"Image/Object/Town/Town_Sign_2.png");
    IMAGEMANAGER->AddImage("Town_Sign_3", L"Image/Object/Town/Town_Sign_3.png");
    IMAGEMANAGER->AddImage("Town_Sign_4", L"Image/Object/Town/Town_Sign_4.png");
    IMAGEMANAGER->AddImage("Town_Sign_5", L"Image/Object/Town/Town_Sign_5.png");
    IMAGEMANAGER->AddImage("Town_Sign_6", L"Image/Object/Town/Town_Sign_6.png");
    IMAGEMANAGER->AddImage("Town_Post", L"Image/Object/Town/Town_Post.png");
    IMAGEMANAGER->AddImage("Town_Board", L"Image/Object/Town/Town_Board.png");

    IMAGEMANAGER->AddImage("Town_Erase", L"Image/Object/Town/Town_Erase.png");

    IMAGEMANAGER->AddImage("Town_BlackSmithHouse", L"Image/Object/Town/Town_BlackSmithHouse.png");
    IMAGEMANAGER->AddImage("Town_WitchHouse", L"Image/Object/Town/Town_WitchHouse.png");
}
