#pragma once
#include "GameObject.h"

class Image;

enum class STATE
{
	IDLE,
	MOVING,
	ATTACK,
	HIT,
	CHARGING,
	DEFENDING,
	AVOID,
	DIE,
	NONE
};

enum class DIR
{
	LEFT,
	UP,	
	RIGHT,
	DOWN,		
	NONE
};
class Unit : public GameObject
{
protected:
	POINTFLOAT pos;
	RECT hitBox;
	Image* lpImage;
	STATE state;
	DIR dir;

	int moveSpeed;
	int damage;
	int hp;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Hit();
	~Unit() override {};
};

