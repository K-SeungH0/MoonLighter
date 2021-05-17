#pragma once
#include "GameObject.h"

struct Menu
{
	RECT rc;
	POINTFLOAT pos;
	string name;
};

class Image;
class TitleScene : public GameObject
{
private:
	Image* lpFrontMenu;
	Image* lpBackMenu;
	Image* lpLogo;

	Menu menu[3];

	float timer;
	int frame;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	
	void ImageLoad();
	~TitleScene() {};
};

