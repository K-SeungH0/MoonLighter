#pragma once
#include "GameObject.h"
enum class BUTTONSTATE
{
	NONE,
	DOWN,
	UP
};

typedef void(*Click)(int);

class Image;
class Button : public GameObject
{
private:
	BUTTONSTATE state;
	Image* image;
	RECT rc;
	POINT pos;
	//void (*Click)(int);
	Click click;
	int index;
public:
	HRESULT Init(const char* fileName, POINT pos);
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void SetClick(Click click, int index) { this->click = click; this->index = index; }
	//void SetClick(void (*Click)(int)) { this->Click = Click; }
	virtual ~Button() {};
};

