#include "LoadingScene.h"
#include "Image.h"
HRESULT LoadingScene::Init()
{
    lpBackGroundImage = ImageManager::GetInstance()->FindImage("LoadingScene");
    return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{

}

void LoadingScene::Render(HDC hdc)
{
    lpBackGroundImage->Render(hdc);
}
