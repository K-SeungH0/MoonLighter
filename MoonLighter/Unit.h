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
	TELEPORT,
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

	int armor;
	int maxHp;
	int hp;
	
	float hitTime;
	float setHitTime;

	bool isAlive;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Hit(Unit* attacker, Image* hitEffect);
	
	inline DIR GetDir() { return this->dir; }
	inline int GetCurrentHp() { return this->hp; }
	inline int GetMaxHp() { return this->maxHp; }
	inline int GetArmor() { return this->armor; }
	inline int GetMoveSpeed() { return this->moveSpeed; }
	inline int GetDamage() { return this->damage; }
	inline bool GetIsAilve() { return this->isAlive; }
	~Unit() override {};
};

