#include "TownScene.h"
#include "Player.h"
#include "Image.h"
#include "Camera.h"

HRESULT TownScene::Init()
{
	ImageLoad();
	GAMEDATA->RunTimeDataInit();

	lpBackGround = IMAGEMANAGER->FindImage("Town_Test");
	lpInteract = IMAGEMANAGER->FindImage("UI_Interact");

	lpPlayer = GAMEDATA->GetRunTimePlayer();
	lpPlayer->SetWinSize({ lpBackGround->GetWidth(), lpBackGround->GetHeight()});
	//lpPlayer->SetPos({ 1945, 500 });
	lpPlayer->SetPos({ 1940, 650 });
	lpCamera = new Camera();
	lpCamera->Init(lpBackGround, lpPlayer->GetpPos(), 350);
	lpPlayer->SetCamera(lpCamera);

	//FLOATINGFONT->SetCameraPos(lpCamera->GetpCameraPos());
	isEnterDunGeon = false;
	return S_OK;
}

void TownScene::Release()
{

}

void TownScene::Update()
{
	lpPlayer->Update();
	lpCamera->Update();

	if (lpPlayer->GetPos().x > 2000 && lpPlayer->GetPos().x < 2100 && lpPlayer->GetPos().y >700 && lpPlayer->GetpPos()->y < 750)
		isEnterDunGeon = true;
	else 
		isEnterDunGeon = false;

	if (isEnterDunGeon)
	{
		if (KEYMANAGER->IsOnceKeyDown('J'))
			SCENEMANAGER->ChageScene("Battle");
	}
}

void TownScene::Render(HDC hdc)
{
	//lpBackGround->CameraRender(hdc, 0, 0, lpPlayer->GetPos().x, lpPlayer->GetPos().y);
	//lpCamera->CameraRender(hdc, { 0, 0}, lpBackGround);
	//lpPlayer->Render(hdc);

	lpCamera->CameraRender(hdc, { 0, 0 }, lpBackGround);
	lpPlayer->Render(hdc);

	if (isEnterDunGeon)
	{
		lpCamera->CameraRender(hdc, { (LONG)lpPlayer->GetPos().x - lpInteract->GetWidth() / 2, (LONG)lpPlayer->GetPos().y - 100 }, lpInteract);
		FLOATINGFONT->Render(hdc, { (LONG)lpPlayer->GetPos().x - (lpInteract->GetWidth() / 2) + 60, (LONG)lpPlayer->GetPos().y - 75 - 9}, 18, "키 눌러서 던전가기", RGB(0, 0, 0));
	}
}

void TownScene::ImageLoad()
{
	//IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");
	IMAGEMANAGER->AddImage("Town_Test", L"Image/Map/Town_Test.png");
	IMAGEMANAGER->AddImage("UI_Interact", L"Image/UI/UI_Interact.png");
}
