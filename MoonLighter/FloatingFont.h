#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class FloatingFont : public Singleton<FloatingFont>
{
public:
	struct FontInfo
	{
		string text;
		POINT pos;
		float duration;
		float timer = 0;
		int size;
	};
private:
	HFONT hFont;
	HFONT oldFont;
	vector<FontInfo> vFonts;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, POINT pos, int size, const char* text, COLORREF textColor);
	void DamageRender(POINT pos, int damage, float duration);

};

