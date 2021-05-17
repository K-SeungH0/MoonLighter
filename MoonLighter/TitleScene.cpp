#include "CommonFunction.h"
#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	ImageLoad();
	lpBackMenu = IMAGEMANAGER->FindImage("BackMenu");
	lpFrontMenu = IMAGEMANAGER->FindImage("FrontMenu");
	lpLogo = IMAGEMANAGER->FindImage("Logo");

	timer = 0;
	frame = 0;
	menu[0].name = "시작";
	menu[1].name = "맵툴";
	menu[2].name = "종료";

	return S_OK;
}

void TitleScene::Release()
{
	IMAGEMANAGER->DeleteAll();
}

void TitleScene::Update()
{
	timer += DELTATIME;
	if (timer >= 0.1f)
	{
		timer -= 0.1f;
		(++frame) %= 16;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->ChageScene("Battle");
	}
}

void TitleScene::Render(HDC hdc)
{
	lpBackMenu->FrameRender(hdc, 0, 0, frame, 0, IMAGE_SIZE);
	lpFrontMenu->FrameRender(hdc, 0, 0, frame, 0, IMAGE_SIZE);
	lpLogo->Render(hdc, WINSIZE_X / 2 - lpLogo->GetWidth(), WINSIZE_Y / 2 - lpLogo->GetHeight() - 100, IMAGE_SIZE);
	
}

void TitleScene::ImageLoad()
{
	COLORREF color = RGB(128, 128, 128);

	IMAGEMANAGER->AddImage("FrontMenu", L"Image/UI/Main_Menu_Front.png",
		10240, 360, 16, 1, true, color);
	IMAGEMANAGER->AddImage("BackMenu", L"Image/UI/Main_Menu_Back.png",
		10240, 360, 16, 1, true, color);
	IMAGEMANAGER->AddImage("Logo", L"Image/UI/Logo.png",
		282, 140, 1, 1, true, color);
}
