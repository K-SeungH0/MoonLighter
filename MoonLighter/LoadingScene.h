#pragma once
#include "GameObject.h"

class Image;
class LoadingScene : public GameObject
{
private:
	Image* lpBackGroundImage;
	Image* lpIcon;
	int frameX;
	float frameTimer;
	
	string text;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	~LoadingScene() override {};
};

