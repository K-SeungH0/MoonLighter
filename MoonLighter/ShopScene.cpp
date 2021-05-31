#include "ShopScene.h"
#include "Player.h"
#include "Image.h"
#include "Camera.h"

HRESULT ShopScene::Init()
{
	ImageLoad();
	GAMEDATA->RunTimeDataInit();

	lpBackGround = IMAGEMANAGER->FindImage("Shop_BackGround");
	lpBackGroundPixel = IMAGEMANAGER->FindImage("Shop_BackGround_Pixel");
	lpMidImage = IMAGEMANAGER->FindImage("Shop_Mid");
	lpDoor = IMAGEMANAGER->FindImage("Shop_Door");
	lpInteract = IMAGEMANAGER->FindImage("UI_Interact");
	pixelDC = lpBackGroundPixel->GetMemDC();

	lpPlayer = GAMEDATA->GetRunTimePlayer();
	lpPlayer->SetMoveArea({ lpBackGround->GetWidth(), lpBackGround->GetHeight() });
	lpPlayer->SetPos({ 875,500 });

	lpCamera = new Camera();    
	lpCamera->Init(lpBackGround, lpPlayer->GetpPos(), 350);
	lpPlayer->SetCamera(lpCamera);
	lpPlayer->SetPixelHDC(&pixelDC);

	//FLOATINGFONT->SetCameraPos(lpCamera->GetpCameraPos());
	doorFrameX = 0;
	doorFrameY = 0;
	exitAble = false;
	
	return S_OK;
}

void ShopScene::Release()
{
	if (lpCamera) 
	{
		lpCamera->Release();
		lpCamera = nullptr;
	}

	IMAGEMANAGER->DeleteAll();
}

void ShopScene::Update()
{
	lpPlayer->Update();
	lpCamera->Update();

	if (lpPlayer->PixelCollision(lpPlayer->GetCollider().left, lpPlayer->GetCollider().top, false, RGB(0, 255, 255))) exitAble = true;
	else if (lpPlayer->PixelCollision(lpPlayer->GetCollider().left, lpPlayer->GetCollider().top, true, RGB(0, 255, 255))) exitAble = true;
	else if (lpPlayer->PixelCollision(lpPlayer->GetCollider().right, lpPlayer->GetCollider().top, false, RGB(0, 255, 255))) exitAble = true;
	else if (lpPlayer->PixelCollision(lpPlayer->GetCollider().left, lpPlayer->GetCollider().bottom, true, RGB(0, 255, 255))) exitAble = true;
	else exitAble = false;

	if (exitAble)
	{
		if (KEYMANAGER->IsOnceKeyDown('J'))
			SCENEMANAGER->ChageScene("Town");
	}
}

void ShopScene::Render(HDC hdc)
{
	lpCamera->CameraRender(hdc, {0, 0}, lpBackGround);
	lpPlayer->Render(hdc);
	lpCamera->CameraRender(hdc, { 825, 607 }, lpMidImage);
	lpCamera->CameraFrameRender(hdc, lpDoor, {826,1040 }, doorFrameX, doorFrameY);

	if (exitAble)
	{
		lpCamera->CameraRender(hdc, { (LONG)lpPlayer->GetPos().x - lpInteract->GetWidth() / 2, (LONG)lpPlayer->GetPos().y - 100 }, lpInteract);
		FLOATINGFONT->Render(hdc, { (LONG)lpPlayer->GetPos().x - lpInteract->GetWidth() / 2 + 60, (LONG)lpPlayer->GetPos().y - 75 - 9}, 18, "키 눌러서 나가기", RGB(0, 0, 0));
	}

	if(isDebugMode)
		lpCamera->CameraRender(hdc, { 0, 0 } , lpBackGroundPixel);
}

void ShopScene::ImageLoad()
{
	IMAGEMANAGER->AddImage("Shop_BackGround", L"Image/Map/Shop_BackGround_.png");
	IMAGEMANAGER->AddImage("Shop_BackGround_Pixel", L"Image/Map/Shop_BackGround_Pixel.png");
	IMAGEMANAGER->AddImage("Shop_Mid", L"Image/Map/Shop_Mid.png");
	IMAGEMANAGER->AddImage("Shop_Door", L"Image/Map/shop_door.png",5,1);
	IMAGEMANAGER->AddImage("UI_Interact", L"Image/UI/UI_Interact.png");
}
