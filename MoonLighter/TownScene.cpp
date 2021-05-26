#include "TownScene.h"
#include "Player.h"
#include "Image.h"
#include "Camera.h"

HRESULT TownScene::Init()
{
	ImageLoad();
	GAMEDATA->RunTimeDataInit();

	lpBackGround = IMAGEMANAGER->FindImage("Town_BackGround");

	lpPlayer = GAMEDATA->GetRunTimePlayer();

	lpCamera = new Camera();
	lpCamera->Init(lpPlayer, lpBackGround);

	return S_OK;
}

void TownScene::Release()
{

}

void TownScene::Update()
{
	//lpPlayer->Update();

	lpCamera->Update();
}

void TownScene::Render(HDC hdc)
{
	//lpBackGround->CameraRender(hdc, 0, 0, lpPlayer->GetPos().x, lpPlayer->GetPos().y);
	lpCamera->CameraRender(hdc, { 0, 0}, lpBackGround);
	lpPlayer->Render(hdc);
	
	//lpPlayer->Render(hdc);
}

void TownScene::ImageLoad()
{
	IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");
}
