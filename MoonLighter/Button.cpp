#include "Button.h"
#include "Image.h"
#include "TileMapTool.h"
HRESULT Button::Init(const char* fileName, POINT pos)
{
	state = BUTTONSTATE::NONE;
	image = ImageManager::GetInstance()->FindImage(fileName);

	if (image == nullptr)
	{
		string warrningText = string(fileName) + "가 없음.";
		MessageBox(g_hWnd, warrningText.c_str(), "실패", MB_OK);
		return E_FAIL;
	}

	this->pos = pos;

	rc =
	{
		pos.x - image->GetImageInfo()->frameWidth / 2,
		pos.y - image->GetImageInfo()->frameHeight / 2,
		pos.x + image->GetImageInfo()->frameWidth / 2,
		pos.y + image->GetImageInfo()->frameHeight / 2
	};

	this->click = click;

	return S_OK;
}

HRESULT Button::Init()
{
	return E_NOTIMPL;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTONSTATE::DOWN;
		}
		else if (state == BUTTONSTATE::DOWN &&
			KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
		{
			state = BUTTONSTATE::UP;

			// 버튼 기능 수행 : 세이브, 로드
			click(index);
		}
	}
	else
		state = BUTTONSTATE::NONE;

}

void Button::Render(HDC hdc)
{
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	switch (state)
	{
	case BUTTONSTATE::NONE:
	case BUTTONSTATE::UP:
		image->FrameRender(hdc, pos.x, pos.y, 0, 0, 1, true);
		break;
	case BUTTONSTATE::DOWN:
		image->FrameRender(hdc, pos.x, pos.y, 1, 0, 1, true);
		break;
	}

}
