#include "CommonFunction.h"
#include "TitleScene.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);
	ImageLoad();
	AddFontResource("./Font/MoonLighter_Font.ttf");
	SendMessage(g_hWnd, WM_FONTCHANGE, NULL, NULL);
	lpBackMenu = IMAGEMANAGER->FindImage("BackMenu");
	lpFrontMenu = IMAGEMANAGER->FindImage("FrontMenu");
	lpLogo = IMAGEMANAGER->FindImage("TitleLogo");
	lpSelect = IMAGEMANAGER->FindImage("Select");

	timer = 0;
	frame = 0;
	selectIndex = 0;

	for (int i = 0; i < (int)MENU::NONE; i++)
	{
		menu[i].type = (MENU)i;
		menu[i].pos = { WINSIZE_X / 2 - (float)lpSelect->GetWidth(), WINSIZE_Y / 2 + (float)(75 * (i + 1)) };
		
		switch (i)
		{
		case (int)MENU::START:
			menu[i].name = "����";
			break;
		case (int)MENU::MAPTOOL:
			menu[i].name = "����";
			break;
		case (int)MENU::EXIT:
			menu[i].name = "����";
			break;
		}
	}
	return S_OK;
}

void TitleScene::Release()
{
	IMAGEMANAGER->DeleteAll();
	RemoveFontResource("./Font/MoonLighter_Font.ttf");
}

void TitleScene::Update()
{
	timer += DELTATIME;
	if (timer >= 0.1f)
	{
		timer -= 0.1f;
		(++frame) %= 16;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		selectIndex--;

		if (selectIndex < (int)MENU::START)
			selectIndex = (int)MENU::EXIT;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		selectIndex++;

		if (selectIndex > (int)MENU::EXIT)
			selectIndex = (int)MENU::START;
	}


	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE) || KEYMANAGER->IsOnceKeyDown(VK_RETURN))
	{
		switch (menu[selectIndex].type)
		{
		case MENU::START:
			SCENEMANAGER->ChageScene("Battle");
			break;
		case MENU::MAPTOOL:
			SCENEMANAGER->ChageScene("TileMapTool");
			break;
		case MENU::EXIT:
			PostQuitMessage(0);
			break;
		}
	}
}

void TitleScene::Render(HDC hdc)
{
	lpBackMenu->FrameRender(hdc, 0, 0, frame, 0, IMAGE_SIZE);
	lpFrontMenu->FrameRender(hdc, 0, 0, frame, 0, IMAGE_SIZE);
	lpLogo->Render(hdc, WINSIZE_X / 2 - lpLogo->GetWidth(), WINSIZE_Y / 2 - lpLogo->GetHeight() - 100, IMAGE_SIZE);
	
	hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("������"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	for (int i = 0; i < (int)MENU::NONE; i++)
	{
		TextOut(hdc, menu[i].pos.x, menu[i].pos.y, menu[i].name, strlen(menu[i].name));
	}
	
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	lpSelect->Render(hdc, menu[selectIndex].pos.x - lpSelect->GetWidth(), menu[selectIndex].pos.y);
}

void TitleScene::ImageLoad()
{
	COLORREF color = RGB(128, 128, 128);

	IMAGEMANAGER->AddImage("FrontMenu", L"Image/UI/Main_Menu_Front.png",
		10240, 360, 16, 1, true, color);
	IMAGEMANAGER->AddImage("BackMenu", L"Image/UI/Main_Menu_Back.png",
		10240, 360, 16, 1, true, color);
	IMAGEMANAGER->AddImage("TitleLogo", L"Image/UI/TitleLogo.png",
		282, 140, 1, 1, true, color);
	IMAGEMANAGER->AddImage("Select", L"Image/UI/Select.png",
		32, 32, 1, 1, true, color);
}
