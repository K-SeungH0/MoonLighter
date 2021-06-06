#include "LoadingScene.h"
#include "Image.h"
HRESULT LoadingScene::Init()
{
    IMAGEMANAGER->AddImage("empty", L"Image/UI/empty.png");
    IMAGEMANAGER->AddImage("LoadingScene", L"Image/UI/Loading.png",68, 1);
    lpBackGroundImage = ImageManager::GetInstance()->FindImage("empty");
    lpIcon = ImageManager::GetInstance()->FindImage("LoadingScene");

    frameTimer = 0;
    return S_OK;
}

void LoadingScene::Release()
{

}

void LoadingScene::Update()
{
    frameTimer += DELTATIME;
    if (frameTimer > 0.1f)
    {
        frameTimer -= 0.1f;
        (++frameX) %= lpIcon->GetMaxFrameX();

        if (frameX % 3 == 0) text = "불러오는중.";
        if (frameX % 3 == 1) text = "불러오는중..";
        if (frameX % 3 == 2) text = "불러오는중...";
    }
}

void LoadingScene::Render(HDC hdc)
{
    lpBackGroundImage->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 10, true);
    lpIcon->FrameRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, frameX, 0, IMAGE_SIZE, true);
    FLOATINGFONT->Render(hdc, { (LONG)WINSIZE_X / 2 - 12*6, (LONG)WINSIZE_Y / 2 + 24*5},24, text.c_str(), RGB(255, 255, 255));
}
