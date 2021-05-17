#pragma once
#include "Object.h"

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

class Unit : public Object
{
protected:
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

	inline DIR GetDir() { return this->dir; }

	~Unit() override {};
};

