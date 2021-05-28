#include "Button.h"
#include "Image.h"

HRESULT Button::Init(string name, POINT pos)
{
	state = BUTTONSTATE::NONE;
	this->pos = pos;
	
	rc =
	{
		pos.x - 60,
		pos.y - 20,
		pos.x + 60,
		pos.y + 20
	};
	this->name = name;
	this->isSelect = false;
	this->isClick = false;
	//this->name = new char;
	//wsprintf(this->name, name.c_str());
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
		isSelect = true;
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			isClick = true;
			state = BUTTONSTATE::DOWN;
		}
		
		else if (state == BUTTONSTATE::DOWN && KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
		{
			state = BUTTONSTATE::UP;
			isClick = false;
			// 버튼 기능 수행 : 세이브, 로드
			(tileMap->*Click)(index);
		}
	}
	else
	{
		state = BUTTONSTATE::NONE;
		isSelect = false;
		isClick = false;
	}
}

void Button::Render(HDC hdc)
{
	if (isClick)
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}

	else if (isSelect)
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 128, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}

	else
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	FLOATINGFONT->Render(hdc, { pos.x - (LONG)name.size() * 9 / 2, pos.y - 9}, 18, name.c_str(), RGB(0, 0, 0));
}
