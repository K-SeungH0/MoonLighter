#include "FloatingFont.h"
#include "TimerManager.h"

HRESULT FloatingFont::Init()
{
	AddFontResource("./Font/DungGeunMo.ttf");

	return S_OK;
}

void FloatingFont::Release()
{
	RemoveFontResource("./Font/DungGeunMo.ttf");
}

void FloatingFont::Update()
{
	for (auto iter = vFonts.begin(); iter != vFonts.end(); iter++)
	{
		iter->duration -= TimerManager::GetInstance()->GetDeltaTime();
		iter->timer += 50 * TimerManager::GetInstance()->GetDeltaTime();

		if (iter->timer >= 1)
		{
			--iter->timer;
			--iter->pos.y;
		}
	}
}

void FloatingFont::Render(HDC hdc)
{
	for (auto iter = vFonts.begin(); iter != vFonts.end();)
	{
		if (iter->duration <= 0)
			iter = vFonts.erase(iter);
		else
		{
			Render(hdc, iter->pos, iter->size, iter->text.c_str(), RGB(255, 0, 0));
			iter++;
		}
	}
}

void FloatingFont::Render(HDC hdc, POINT pos, int size, const char* text, COLORREF textColor)
{
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("µÕ±Ù¸ð²Ã"));
	oldFont = (HFONT)SelectObject(hdc, hFont);
	SetTextColor(hdc, textColor);

	TextOut(hdc, pos.x, pos.y, text, strlen(text));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void FloatingFont::DamageRender(POINT pos, int damage, float duration)
{
	FontInfo fontInfo;

	fontInfo.text = to_string(damage);
	fontInfo.pos = pos;
	fontInfo.duration = duration;
	fontInfo.size = 18;

	vFonts.push_back(fontInfo);
}
