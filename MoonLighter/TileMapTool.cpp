#include "TileMapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TileMapTool::tileInfo[TILE_X * TILE_Y];
//int TileMapTool::selectStage = 1;

HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);
    ImageLoad();

    lpBackGroundTile = IMAGEMANAGER->FindImage("Dungeon_Background");
    currentScene = SELECTSCENE::DUNGEON;

    lpTileSetImage = IMAGEMANAGER->FindImage("Tile_Set");

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    int offset = 60;
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            // 메인 영역
            if (i == 0 && j == 0)
            {
                rcMain.left = TILESIZE * j + offset;
                rcMain.top = TILESIZE * i + offset + 10;
            }
            if (i == TILE_Y - 1 && j == TILE_X - 1)
            {
                rcMain.right = TILESIZE * (j + 1) + offset;
                rcMain.bottom = TILESIZE * (i + 1) + offset + 10;
            }

            tileInfo[i * TILE_X + j].frameX = TILE_X - 1;
            tileInfo[i * TILE_X + j].frameY = TILE_Y - 1;
            tileInfo[i * TILE_X + j].lpImage = nullptr;
            tileInfo[i * TILE_X + j].type = TILETYPE::NONE;

            tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j + offset;
            tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i + offset + 10;
            tileInfo[i * TILE_X + j].rcTile.right = TILESIZE * (j + 1) + offset;
            tileInfo[i * TILE_X + j].rcTile.bottom = TILESIZE * (i + 1) + offset + 10;
        }
    }
    
    for (int i = 0; i < TILE_SET_Y; i++)
    {
        for (int j = 0; j < TILE_SET_X; j++)
        {
            // 샘플 영역
            if (i == 0 && j == 0)
            {
                rcSample.left = TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j);
                rcSample.top = (TILESIZE * i);
            }
            if (i == TILE_SET_Y - 1 && j == TILE_SET_X - 1)
            {
                rcSample.right = TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j) + TILESIZE;
                rcSample.bottom = (TILESIZE * i) + TILESIZE;
            }
            tileSetInfo[i * TILE_SET_X + j].rcTile.left = TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j);
            tileSetInfo[i * TILE_SET_X + j].rcTile.top = (TILESIZE * i);
            tileSetInfo[i * TILE_SET_X + j].rcTile.right = TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2) + (TILESIZE * j) + TILESIZE;
            tileSetInfo[i * TILE_SET_X + j].rcTile.bottom = (TILESIZE * i) + TILESIZE;

            switch (i)
            {
                // 첫번째줄 BreakAble
                case 0:
                    tileSetInfo[i * TILE_SET_X + j].type = TILETYPE::BREAKABLE;
                    break;
                // 두번째줄 Wall
                case 1:
                    tileSetInfo[i * TILE_SET_X + j].type = TILETYPE::WALL;
                    break;
                // 세번째줄 Hole
                case 2:
                    tileSetInfo[i * TILE_SET_X + j].type = TILETYPE::HOLE;
                    break;
                default:
                    tileSetInfo[i * TILE_SET_X + j].type = TILETYPE::NONE;
                    break;

            }
        }
    }

    // UI Button
    saveButton = new Button();
    saveButton->Init("Save", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width - 120, TILEMAPTOOLSIZE_Y - 200 });
    saveButton->SetTileMap(this);
    saveButton->SetClick(&TileMapTool::Save, 1);

    loadButton = new Button();
    loadButton->Init("Load", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width + 20, TILEMAPTOOLSIZE_Y - 200 });
    loadButton->SetTileMap(this);
    loadButton->SetClick(&TileMapTool::Load, 1);
    
    leftButton = new Button();
    leftButton->Init("Left", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width - 120, TILEMAPTOOLSIZE_Y - 300 });
    leftButton->SetTileMap(this);
    leftButton->SetClick(&TileMapTool::StageSelect, -1);
    
    rightButton = new Button();
    rightButton->Init("Right", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width + 20, TILEMAPTOOLSIZE_Y - 300 });
    rightButton->SetTileMap(this);
    rightButton->SetClick(&TileMapTool::StageSelect, 1);
    
    townSelectButton = new Button();
    townSelectButton->Init("Town", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width -120, TILEMAPTOOLSIZE_Y - 400 });
    townSelectButton->SetTileMap(this);
    townSelectButton->SetClick(&TileMapTool::SceneSelect, 0);
    
    dungeonSelectButton = new Button();
    dungeonSelectButton->Init("Dungeon", { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width + 20, TILEMAPTOOLSIZE_Y - 400 });
    dungeonSelectButton->SetTileMap(this);
    dungeonSelectButton->SetClick(&TileMapTool::SceneSelect, 1);

    //selectStage = 1;

    cameraPos = { 0,0 };
    return S_OK;
}

void TileMapTool::Release()
{
    SAFE_RELEASE(saveButton);
    SAFE_RELEASE(loadButton);
    SAFE_RELEASE(leftButton);
    SAFE_RELEASE(rightButton);
    DeleteObject(hSelectedBrush);
}

void TileMapTool::Update()
{
    if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
    {
        SCENEMANAGER->ChageScene("Title");
    }
    if (KEYMANAGER->IsStayKeyDown(VK_DOWN) || KEYMANAGER->IsStayKeyDown('S'))
    {
        cameraPos.y += 2;
        if (cameraPos.y > lpBackGroundTile->GetHeight() - WINSIZE_Y)
            cameraPos.y = lpBackGroundTile->GetHeight() - WINSIZE_Y;
    }
    if (KEYMANAGER->IsStayKeyDown(VK_UP) || KEYMANAGER->IsStayKeyDown('W'))
    {
        cameraPos.y -= 2;
        if (cameraPos.y < 0) cameraPos.y = 0;
    }
    if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) || KEYMANAGER->IsStayKeyDown('D'))
    {
        cameraPos.x += 2;
        if (cameraPos.x > lpBackGroundTile->GetWidth() - WINSIZE_X)
            cameraPos.x = lpBackGroundTile->GetWidth() - WINSIZE_X;
    }
    if (KEYMANAGER->IsStayKeyDown(VK_LEFT) || KEYMANAGER->IsStayKeyDown('A'))
    {
        cameraPos.x -= 2;
        if (cameraPos.x < 0) cameraPos.x = 0;
    }

    // 세이브, 로드
    saveButton->Update();
    loadButton->Update();
    leftButton->Update();
    rightButton->Update();
    townSelectButton->Update();
    dungeonSelectButton->Update();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_Y * TILE_X; i++)
            {
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    tileInfo[i].frameX = selectedFrame.x;
                    tileInfo[i].frameY = selectedFrame.y;
                    tileInfo[i].lpImage = lpTileSetImage;
                    tileInfo[i].type = tileSetInfo[(selectedFrame.y) * TILE_SET_X + (selectedFrame.x)].type;
                    break;
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
        {
            selectedFrame.x = g_ptMouse.x;
            selectedFrame.y = g_ptMouse.y;
            TileSelect();
        }
    }

    // Test
    if (KeyManager::GetInstance()->IsOnceKeyDown('Q'))
    {
        SceneManager::GetInstance()->ChageScene("Battle");
    }
}

void TileMapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // 타일 배경
    lpBackGroundTile->CameraRender(hdc, 0, 0, cameraPos.x, cameraPos.y);

    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);

    Rectangle(hdc, rcSample.left, rcSample.top, rcSample.right, rcSample.bottom);

    // 샘플타일 전체
    for (int i = 0; i < TILE_SET_Y * TILE_SET_X; i++)
    {
        Rectangle(hdc, tileSetInfo[i].rcTile.left, tileSetInfo[i].rcTile.top, tileSetInfo[i].rcTile.right, tileSetInfo[i].rcTile.bottom);
    }
    SelectObject(hdc, hOldSelectedBrush);

    lpTileSetImage->Render(hdc, TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2), 0, IMAGE_SIZE);

    // UI Button
    saveButton->Render(hdc);
    loadButton->Render(hdc);
    leftButton->Render(hdc);
    rightButton->Render(hdc);
    townSelectButton->Render(hdc);
    dungeonSelectButton->Render(hdc);

    wsprintf(szText, "DunGeon %d", this->selectStage);
    FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - lpTileSetImage->GetImageInfo()->width, TILEMAPTOOLSIZE_Y - 350 }, 18, szText, RGB(0, 0, 0));

    // 메인 영역 전체
    for (int i = 0; i < TILE_Y * TILE_X; i++)
    {
        if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
        {
            HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
            Rectangle(hdc, tileInfo[i].rcTile.left, tileInfo[i].rcTile.top, tileInfo[i].rcTile.right, tileInfo[i].rcTile.bottom);
            SelectObject(hdc, oldBrush);
            DeleteObject(myBrush);
        }
        else
        {
            SelectObject(hdc, hSelectedBrush);
            Rectangle(hdc, tileInfo[i].rcTile.left, tileInfo[i].rcTile.top, tileInfo[i].rcTile.right, tileInfo[i].rcTile.bottom);
        }
        SelectObject(hdc, hOldSelectedBrush);
        lpTileSetImage->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY, 
            IMAGE_SIZE);

    }

    // 선택된 타일
    lpTileSetImage->FrameRender(hdc,
        g_ptMouse.x,
        g_ptMouse.y,
        selectedFrame.x, 
        selectedFrame.y, 
        IMAGE_SIZE, 
        true);

    wsprintf(szText, "배틀 씬으로 넘어가기 : Q");
    FLOATINGFONT->Render(hdc, { TILEMAPTOOLSIZE_X - 300,  TILEMAPTOOLSIZE_Y - 100, }, 18, szText, RGB(0, 0, 0));
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

void TileMapTool::SceneSelect(int num)
{
    switch (num)
    {
    case (int)SELECTSCENE::TOWN:
        lpBackGroundTile = IMAGEMANAGER->FindImage("Town_BackGround");
        currentScene = SELECTSCENE::TOWN;
        break;
    case (int)SELECTSCENE::DUNGEON:
        lpBackGroundTile = IMAGEMANAGER->FindImage("Dungeon_Background");
        currentScene = SELECTSCENE::DUNGEON;
        break;
    }
    cameraPos = { 0,0 };
}

void TileMapTool::StageSelect(int num)
{
    selectStage += num;
    if (selectStage > 10) selectStage = 1;
    if (selectStage < 1) selectStage = 10;
}

void TileMapTool::TileSelect()
{
    selectedFrame.x -= TILEMAPTOOLSIZE_X - (lpTileSetImage->GetImageInfo()->width * 2);

    if (selectedFrame.x / TILESIZE >= 0 && selectedFrame.x / TILESIZE < TILE_SET_X &&
        selectedFrame.y / TILESIZE >= 0 && selectedFrame.y / TILESIZE < TILE_SET_Y)
    {
        selectedFrame.x = selectedFrame.x / TILESIZE;
        selectedFrame.y = selectedFrame.y / TILESIZE;
    }
}

void TileMapTool::ImageLoad()
{
    //IMAGEMANAGER->AddImage("SaveButton", "Image/Save.bmp", 144, 72, 2, 1);
    //IMAGEMANAGER->AddImage("LoadButton", "Image/Load.bmp", 144, 72, 2, 1);
    //IMAGEMANAGER->AddImage("LeftButton", "Image/Left.bmp", 120, 60, 2, 1);
    //IMAGEMANAGER->AddImage("RightButton", "Image/Right.bmp", 120, 60, 2, 1);

    // 이미지 추가
    IMAGEMANAGER->AddImage("Dungeon_Background", L"Image/Map/Dungeon_BackGround.png");
    IMAGEMANAGER->AddImage("Tile_Set", L"Image/Map/TileMap.png", TILE_SET_X, TILE_SET_Y);
    IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");
}
