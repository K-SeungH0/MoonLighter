#pragma once
#include "GameObject.h"

class Image;
enum class MENU
{
	START,
	MAPTOOL,
	EXIT,
	NONE
};

struct Menu
{
	MENU type;
	POINTFLOAT pos;
	const char* name;
};

class TitleScene : public GameObject
{
private:
	Image* lpFrontMenu;
	Image* lpBackMenu;
	Image* lpLogo;
	Image* lpSelect;

	Menu menu[(int)MENU::NONE];

	float timer;
	int frame;
	int selectIndex;
	HFONT hFont;
	HFONT oldFont;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	
	void ImageLoad();
	~TitleScene() {};
};

