#pragma once
#include "GameObject.h"

class Image;
class LoadingScene : public GameObject
{
private:
	Image* lpBackGroundImage;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	~LoadingScene() override {};
};

